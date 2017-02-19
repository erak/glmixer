/*
 *   GLSLCodeEditorWidget
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
#ifndef GLSLCodeEditorWidget_H
#define GLSLCodeEditorWidget_H

#include <QtGui>

namespace Ui {
class GLSLCodeEditorWidget;
}

class FFGLPluginSource;
class FFGLPluginSourceShadertoy;

class GLSLCodeEditorWidget : public QWidget
{
    Q_OBJECT

public:
    GLSLCodeEditorWidget(QWidget *parent = 0);
    ~GLSLCodeEditorWidget();

public slots:

    // associate / dissociate plugin to the GUI
    void linkPlugin(FFGLPluginSourceShadertoy *plugin);
    void unlinkPlugin();

    // management of code
    void apply();
    void showLogs();
    void updateFields();

    // actions from buttons
    void showHelp();
    void pasteCode();
    void loadCode();
    void saveCode();
    void restoreCode();
    void openExample(int index);

    // reset signaling of errors
    void restoreStyle();

private:

    void fillExamplesList(bool effect = true);

    Ui::GLSLCodeEditorWidget *ui;
    QDir _currentDirectory;
    FFGLPluginSourceShadertoy *_currentplugin;
};



#endif // GLSLCodeEditorWidget_H
