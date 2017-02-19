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

#include "GLSLSyntaxHighlighter.moc"

GLSLSyntaxHighlighter::GLSLSyntaxHighlighter(QTextEdit *parent) :
        QSyntaxHighlighter(parent)
{
    HighlightingRule rule;

    /*******************************************
     * FORMATS
     *******************************************/

    statementFormat.setForeground(QColor(51, 0, 170));
    statementFormat.setFontWeight(QFont::Bold);

    numberFormat.setForeground(QColor(17, 102, 68));
    numberFormat.setFontWeight(QFont::Bold);

    typesFormat.setForeground(QColor(119, 0, 136));
    typesFormat.setFontWeight(QFont::Bold);

//    keywordFormat.setFontWeight(QFont::Bold);
    keywordFormat.setFontItalic(true);

    commentFormat.setForeground(QColor(0, 136, 0));
    swizzleFormat.setFontWeight(QFont::Bold);
    preprocessorFormat.setForeground(QColor(100, 100, 100));

    /*******************************************
     * RULES
     *******************************************/

    QStringList glslkeywords;
    glslkeywords.append("iResolution");
    glslkeywords.append("iChannelResolution");
    glslkeywords.append("iChannel0");
    glslkeywords.append("iGlobalTime");
    glslkeywords.append("iChannelTime");
    glslkeywords.append("iDate");
    glslkeywords.append("key");
    addPatternFromList(glslkeywords, keywordFormat);

    QStringList glslConditional;
    glslConditional.append("if");
    glslConditional.append("else");
    addPatternFromList(glslConditional, statementFormat);

    QStringList glslStatement;
    glslStatement.append("break");
    glslStatement.append("return");
    glslStatement.append("continue");
    glslStatement.append("discard");
    glslStatement.append("true");
    glslStatement.append("false");
    addPatternFromList(glslStatement, statementFormat);

    QStringList glslRepeat;
    glslRepeat.append("while");
    glslRepeat.append("for");
    glslRepeat.append("do");
    addPatternFromList(glslRepeat, statementFormat);

    /* Numbers */
    rule.pattern = QRegExp("\\b\\d+(u{,1}l{0,2}|ll{,1}u)\\b");
    rule.format = numberFormat;
    highlightingRules.append(rule);
    rule.pattern = QRegExp("\\b0x\\x+(u{,1}l{0,2}|ll{,1}u)\\b");
    rule.format = numberFormat;
    highlightingRules.append(rule);
    rule.pattern = QRegExp("\\b\\d+f\\b");
    rule.format = numberFormat;
    highlightingRules.append(rule);
    rule.pattern = QRegExp("\\b\\d+\\.\\d*(e[-+]{,1}\\d+){,1}[fl]{,1}\\b");
    rule.format = numberFormat;
    highlightingRules.append(rule);
    rule.pattern = QRegExp("\\b\\.\\d+(e[-+]{,1}\\d+){,1}[fl]{,1}\\b");
    rule.format = numberFormat;
    highlightingRules.append(rule);
    rule.pattern = QRegExp("\\b\\d+e[-+]{,1}\\d+[fl]{,1}\\b");
    rule.format = numberFormat;
    highlightingRules.append(rule);
    rule.pattern = QRegExp("\\b0\\o*[89]\\d*\\b");
    rule.format = numberFormat;
    highlightingRules.append(rule);

    /* Swizzles */
    rule.pattern = QRegExp("\\.[xyzw]{1,4}\\b");
    rule.format = swizzleFormat;
    highlightingRules.append(rule);
    rule.pattern = QRegExp("\\.[rgba]{1,4}\\b");
    rule.format = swizzleFormat;
    highlightingRules.append(rule);
    rule.pattern = QRegExp("\\.[stpq]{1,4}\\b");
    rule.format = swizzleFormat;
    highlightingRules.append(rule);

    /* Types */
    QStringList glslTypes;
    glslTypes.append("void");
    glslTypes.append("bool");
    glslTypes.append("bvec2");
    glslTypes.append("bvec3");
    glslTypes.append("bvec4");
    glslTypes.append("int");
    glslTypes.append("ivec2");
    glslTypes.append("ivec3");
    glslTypes.append("ivec4");
    glslTypes.append("float");
    glslTypes.append("vec2");
    glslTypes.append("vec3");
    glslTypes.append("vec4");
    glslTypes.append("sampler1D");
    glslTypes.append("sampler2D");
    glslTypes.append("sampler3D");
    glslTypes.append("samplerCUBE");
    glslTypes.append("sampler1DShadow");
    glslTypes.append("sampler2DShadow");
    glslTypes.append("vec4");
    glslTypes.append("vec4");
    glslTypes.append("struct");
    addPatternFromList(glslTypes, typesFormat);

    /* Storage class */
    QStringList glslStorageClass;
    glslStorageClass.append("const");
    glslStorageClass.append("attribute");
    glslStorageClass.append("varying");
    glslStorageClass.append("uniform");
    glslStorageClass.append("in");
    glslStorageClass.append("out");
    glslStorageClass.append("inout");
    addPatternFromList(glslStorageClass, typesFormat);

    /* Functions */
    QStringList glslFunc;
    glslFunc.append("radians");
    glslFunc.append("degrees");
    glslFunc.append("sin");
    glslFunc.append("cos");
    glslFunc.append("tan");
    glslFunc.append("asin");
    glslFunc.append("acos");
    glslFunc.append("atan");
    glslFunc.append("pow");
    glslFunc.append("exp2");
    glslFunc.append("log2");
    glslFunc.append("sqrt");
    glslFunc.append("inversesqrt");
    glslFunc.append("abs");
    glslFunc.append("sign");
    glslFunc.append("floor");
    glslFunc.append("ceil");
    glslFunc.append("fract");
    glslFunc.append("mod");
    glslFunc.append("min");
    glslFunc.append("max");
    glslFunc.append("clamp");
    glslFunc.append("mix");
    glslFunc.append("step");
    glslFunc.append("smoothstep");
    glslFunc.append("length");
    glslFunc.append("distance");
    glslFunc.append("dot");
    glslFunc.append("cross");
    glslFunc.append("normalize");
    glslFunc.append("ftransform");
    glslFunc.append("faceforward");
    glslFunc.append("reflect");
    glslFunc.append("matrixcompmult");
    glslFunc.append("lessThan");
    glslFunc.append("lessThanEqual");
    glslFunc.append("greaterThan");
    glslFunc.append("greaterThanEqual");
    glslFunc.append("equal");
    glslFunc.append("notEqual");
    glslFunc.append("any");
    glslFunc.append("all");
    glslFunc.append("not");
    glslFunc.append("texture1D");
    glslFunc.append("texture1DProj");
    glslFunc.append("texture1DLod");
    glslFunc.append("texture1DProjLod");
    glslFunc.append("texture2D");
    glslFunc.append("texture2DProj");
    glslFunc.append("texture2DLod");
    glslFunc.append("texture2DProjLod");
    glslFunc.append("texture3D");
    glslFunc.append("texture3DProj");
    glslFunc.append("texture3DLod");
    glslFunc.append("texture3DProjLod");
    glslFunc.append("textureCube");
    glslFunc.append("textureCubeLod");
    glslFunc.append("shadow1D");
    glslFunc.append("shadow1DProj");
    glslFunc.append("shadow1DLod");
    glslFunc.append("shadow1DProjLod");
    glslFunc.append("shadow2D");
    glslFunc.append("shadow2DProj");
    glslFunc.append("shadow2DLod");
    glslFunc.append("shadow2DProjLod");
    glslFunc.append("dFdx");
    glslFunc.append("dFdy");
    glslFunc.append("fwidth");
    glslFunc.append("noise1");
    glslFunc.append("noise2");
    glslFunc.append("noise3");
    glslFunc.append("noise4");
    glslFunc.append("refract");
    glslFunc.append("exp");
    glslFunc.append("log");
    glslFunc.append("mainImage");
    addPatternFromList(glslFunc, statementFormat);

    /* States */
    QStringList glslState;
    glslState.append("gl_Position");
    glslState.append("gl_PointSize");
    glslState.append("gl_ClipVertex");
    glslState.append("gl_FragCoord");
    glslState.append("gl_FrontFacing");
    glslState.append("gl_FragColor");
    glslState.append("gl_FragData");
    glslState.append("gl_FragDepth");
    glslState.append("gl_Color");
    glslState.append("gl_SecondaryColor");
    glslState.append("gl_Normal");
    glslState.append("gl_Vertex");
    glslState.append("gl_FogCoord");
    glslState.append("gl_FrontColor");
    glslState.append("gl_BackColor");
    glslState.append("gl_FrontSecondaryColor");
    glslState.append("gl_BackSecondaryColor");
    glslState.append("gl_TexCoord");
    glslState.append("gl_FogFragCoord");
    glslState.append("gl_MultiTexCoord\\d+");
    addPatternFromList(glslState, typesFormat);

    /* Uniforms */
    QStringList glslUniform;
    glslUniform.append("gl_ModelViewMatrix");
    glslUniform.append("gl_ProjectionMatrix");
    glslUniform.append("gl_ModelViewProjectionMatrix");
    glslUniform.append("gl_NormalMatrix");
    glslUniform.append("gl_TextureMatrix");
    glslUniform.append("gl_NormalScale");
    glslUniform.append("gl_DepthRange");
    glslUniform.append("gl_ClipPlane");
    glslUniform.append("gl_Point");
    glslUniform.append("gl_FrontMaterial");
    glslUniform.append("gl_BackMaterial");
    glslUniform.append("gl_LightSource");
    glslUniform.append("gl_LightModel");
    glslUniform.append("gl_FrontLightModelProduct");
    glslUniform.append("gl_BackLightModelProduct");
    glslUniform.append("gl_FrontLightProduct");
    glslUniform.append("gl_BackLightProduct");
    glslUniform.append("glTextureEnvColor");
    glslUniform.append("gl_TextureEnvColor");
    glslUniform.append("gl_Fog");
    glslUniform.append("gl_ModelViewMatrixInverse");
    glslUniform.append("gl_ProjectionMatrixInverse");
    glslUniform.append("gl_ModelViewProjectionMatrixInverse");
    glslUniform.append("gl_TextureMatrixInverse");
    glslUniform.append("gl_ModelViewMatrixTranspose");
    glslUniform.append("gl_ProjectionMatrixTranspose");
    glslUniform.append("gl_ModelViewProjectionMatrixTranspose");
    glslUniform.append("gl_TextureMatrixTranspose");
    glslUniform.append("gl_ModelViewMatrixInverseTranspose");
    glslUniform.append("gl_ProjectionMatrixInverseTranspose");
    glslUniform.append("gl_ModelViewProjectionMatrixInverseTranspose");
    glslUniform.append("gl_TextureMatrixInverseTranspose");
    glslUniform.append("gl_EyePlane");
    glslUniform.append("gl_ObjectPlane");
    addPatternFromList(glslUniform, typesFormat);

    /* preprocessor */
    //rule.pattern = QRegExp("\\s*#\\.*\\n");
    rule.pattern = QRegExp("#.*");
    rule.format = preprocessorFormat;
    highlightingRules.append(rule);

    /* single line comments */
    rule.pattern = QRegExp("//.*");
    rule.format = commentFormat;
    highlightingRules.append(rule);

    /* multi line comments */
    commentStartExpression = QRegExp("/\\*");
    commentEndExpression = QRegExp("\\*/");
}

void GLSLSyntaxHighlighter::addPatternFromList(QStringList &list,
        QTextCharFormat &format)
{
    HighlightingRule rule;

    foreach (QString pattern, list) {
        rule.pattern = QRegExp(QString("\\b") + pattern + QString("\\b"));
        rule.format = format;
        highlightingRules.append(rule);
    }
}

void GLSLSyntaxHighlighter::highlightBlock(const QString &text)
{
    foreach (HighlightingRule rule, highlightingRules) {
        QRegExp &expression = rule.pattern;
        int index = rule.pattern.indexIn(text);
        while (index >= 0) {
            int length = expression.matchedLength();
//			if (length <= 0) {
//				fprintf(stderr,
//						"length==0 for " "%s" " mathcing in " "%s" " at %d\n",
//						expression.pattern().toAscii().data(),
//						text.toAscii().data(), index);
//			}
            setFormat(index, length, rule.format);
            index = expression.indexIn(text, index + length);
        }
    }
    setCurrentBlockState(0);

    int startIndex = 0;
    if (previousBlockState() != 1) {
        startIndex = commentStartExpression.indexIn(text);
    }

    while (startIndex >= 0) {
        int endIndex = commentEndExpression.indexIn(text, startIndex);
        int commentLength;
        if (endIndex == -1) {
            setCurrentBlockState(1);
            commentLength = text.length() - startIndex;
        } else {
            commentLength = endIndex - startIndex
                    + commentEndExpression.matchedLength();
        }
        setFormat(startIndex, commentLength, commentFormat);
        startIndex = commentStartExpression.indexIn(text,
                startIndex + commentLength);
    }
}

