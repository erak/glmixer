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

#ifndef GLSLCODEEDITOR_H
#define GLSLCODEEDITOR_H

#include <QTextEdit>
#include <QScrollBar>


class CodeEditor : public QTextEdit
{
    Q_OBJECT

public:
    CodeEditor(QWidget *parent, QTextEdit *lineNumberArea);
    virtual ~CodeEditor();

    // shift in line number display, 0 for none
    void setShiftLineNumber(int i) { _shiftLineNumber = i; }

    // past code as plain text
    void insertFromMimeData ( const QMimeData * source ) {
        insertPlainText ( source->text() );
    }

    // allow wheel scrolling only for main code editor
    void wheelEvent ( QWheelEvent * e ) {
        if (_lineNumberArea)
            QTextEdit::wheelEvent(e);
    }

    // update line numbers when resized (in case block height changed)
    void resizeEvent ( QResizeEvent * e ) {
        if (_lineNumberArea)
            updateLineNumbers();
        QTextEdit::resizeEvent(e);
    }

public slots:
    // update the line numbers area
    void updateLineNumbers();
    void gotoline(unsigned int lineNumber);

private slots:
    void highlightCurrentLine();

private:
    // associated line Number area, if any
    QTextEdit *_lineNumberArea;
    // shift in line numbers (to start from a non-zero line number)
    int _shiftLineNumber;
    // the syntax highlighter
    class GLSLSyntaxHighlighter *highlighter;
};


class GLSLCodeEditor : public QWidget
{
    Q_OBJECT

public:
    GLSLCodeEditor(QWidget *parent = 0);
    ~GLSLCodeEditor();

    // 'ala' QTextEdit API
    void setCode(QString text);
    QString code();
    void clear();
    void setReadOnly(bool);

    // line count management
    int lineCount();
    void setShiftLineNumber(int i) { codeArea->setShiftLineNumber(i); }
    // go to a line
    void gotoline(unsigned int lineNumber);

private:
    CodeEditor *codeArea;
    QTextEdit *lineNumberArea;
};


#endif // GLSLCODEEDITOR_H
