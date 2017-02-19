/*
 *   GLSLSyntaxHighlighter
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

#ifndef _GLSL_SYNTAX_HIGHLIGHTER_QT_H_
#define _GLSL_SYNTAX_HIGHLIGHTER_QT_H_

#include <QSyntaxHighlighter>
#include <QTextCharFormat>

class GLSLSyntaxHighlighter: public QSyntaxHighlighter {
Q_OBJECT
public:
    GLSLSyntaxHighlighter(QTextEdit *parent = 0);

protected:
    void highlightBlock(const QString &text);

private:
    void addPatternFromList(QStringList &list, QTextCharFormat &format);

    struct HighlightingRule {
        QRegExp pattern;
        QTextCharFormat format;
    };
    QVector<HighlightingRule> highlightingRules;

    QRegExp commentStartExpression;
    QRegExp commentEndExpression;

    QTextCharFormat keywordFormat;
    QTextCharFormat statementFormat;
    QTextCharFormat commentFormat;
    QTextCharFormat preprocessorFormat;
    QTextCharFormat numberFormat;
    QTextCharFormat typesFormat;
    QTextCharFormat swizzleFormat;
};

#endif

