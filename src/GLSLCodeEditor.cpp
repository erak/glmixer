/*
 *   GLSLCodeEditor
 *
 *   This file is part of GLMixer.
 *
 *   GLMixer is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   GLMixer is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with GLMixer.  If not, see <http://www.gnu.org/licenses/>.
 *
 *   Copyright 2009, 2012 Bruno Herbelin
 *
 */

#include <QtGui>

#include "common.h"
#include "GLSLSyntaxHighlighter.h"
#include "GLSLCodeEditor.moc"



CodeEditor::CodeEditor(QWidget *parent, QTextEdit *lineNumberArea) : QTextEdit(parent), _lineNumberArea(lineNumberArea), _shiftLineNumber(0)
{
    // highlight syntaxt of code area
    highlighter = new GLSLSyntaxHighlighter((QTextEdit *)this);
    highlighter->rehighlight();

    setTabStopWidth(30);

    // synchronize scrolling with line numbers area
    connect(verticalScrollBar(), SIGNAL(valueChanged(int)), _lineNumberArea->verticalScrollBar(), SLOT(setValue(int)));

    // update line numbers when text is changed
    connect(this, SIGNAL(textChanged()), this, SLOT(updateLineNumbers()));

    // highlight line if editable
    if (!isReadOnly())
        connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));

    // show current line
    highlightCurrentLine();
}

CodeEditor::~CodeEditor(){
    delete highlighter;
}

void CodeEditor::highlightCurrentLine()
{
    // use extra selection mechanism for highligt line
    QList<QTextEdit::ExtraSelection> extraSelections;
    // only editable text edit higlight line for edit
    if (!isReadOnly()) {
        QTextEdit::ExtraSelection selection;

        selection.format.setBackground(palette().color(QPalette::Midlight));
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }
    // apply highlight line (empty if not set)
    setExtraSelections(extraSelections);

    // Ensure non-proportionnal font, large enough
    QFont f = font();
    f.setFamily( getMonospaceFont() );
#ifdef Q_OS_WIN32
    f.setPointSize(QApplication::font().pointSize() + 1);
#else
    f.setPointSize(QApplication::font().pointSize() - 1);
#endif
    setFont( f );

    // make sure line number area is of same font
    _lineNumberArea->setFont( f );

//    // rescroll line area in case the change of line caused a scroll in code area
//    _lineNumberArea->verticalScrollBar()->setValue(verticalScrollBar()->value());
}

void CodeEditor::updateLineNumbers ()
{
    QString linenumbers;
    QTextBlock block = document()->firstBlock();
    while (block.isValid()) {
        // compute number of lines taken by the block
        QRectF r = document()->documentLayout()->blockBoundingRect(block) ;
        int n = (int) ( r.height() / (float) fontMetrics().height() );

        // insert line number
        linenumbers.append( QString::number(block.blockNumber() + _shiftLineNumber + 1) );
        // append lines where block is more than 1 line
        linenumbers.append( QString().fill('\n', n));
        // loop next block of text
        block = block.next();
    }
    // display this text as line numbers
    _lineNumberArea->setPlainText(linenumbers);

    // rescroll line area in case the change of line caused a scroll in code area
    _lineNumberArea->verticalScrollBar()->setValue(verticalScrollBar()->value());
}

void CodeEditor::gotoline(unsigned int lineNumber)
{
    int blocnumber = lineNumber - _shiftLineNumber;
    if (blocnumber > document()->blockCount())
        return;

    const QTextBlock &block = document()->findBlockByNumber(blocnumber);
    QTextCursor cursor(block);
    cursor.movePosition(QTextCursor::Right, QTextCursor::MoveAnchor, 0);
    setTextCursor(cursor);
    highlightCurrentLine();
}

GLSLCodeEditor::GLSLCodeEditor(QWidget *parent) : QWidget(parent)
{
    // layout to place two Code editors
    QHBoxLayout *horizontalLayout = new QHBoxLayout(this);
    horizontalLayout->setSpacing(0);
    horizontalLayout->setContentsMargins(0, 0, 0, 0);

    // Code editor special for line numbers
    lineNumberArea = new QTextEdit(this);
    lineNumberArea->setObjectName(QString::fromUtf8("lineNumberArea"));
    lineNumberArea->setMaximumWidth(40);
    lineNumberArea->setStyleSheet(QString::fromUtf8("background-color: rgb(88, 88, 88);\n"
    "color: white;"));
    lineNumberArea->setFrameShape(QFrame::NoFrame);
    lineNumberArea->setReadOnly(true);
    lineNumberArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    lineNumberArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    horizontalLayout->addWidget(lineNumberArea);

    codeArea = new CodeEditor( this, lineNumberArea);
    codeArea->setObjectName(QString::fromUtf8("codeArea"));
    codeArea->setFrameShape(QFrame::NoFrame);

    horizontalLayout->addWidget(codeArea);

}

GLSLCodeEditor::~GLSLCodeEditor(){
    delete codeArea;
    delete lineNumberArea;
}

void GLSLCodeEditor::gotoline(unsigned int lineNumber)
{
    codeArea->gotoline(lineNumber);
}

void GLSLCodeEditor::setCode(QString code)
{
    codeArea->setText(code);
}

QString GLSLCodeEditor::code()
{
    return codeArea->toPlainText();
}

void GLSLCodeEditor::clear()
{
    codeArea->clear();
    lineNumberArea->clear();
}

int GLSLCodeEditor::lineCount()
{
    return codeArea->document()->blockCount();
}


void GLSLCodeEditor::setReadOnly(bool on)
{
    codeArea->setReadOnly(on);
    codeArea->setLineWrapMode(QTextEdit::NoWrap);
}
