/*
 *   FFGLSourceCreationDialog
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

#ifndef FFGLSOURCECREATIONDIALOG_H
#define FFGLSOURCECREATIONDIALOG_H

#include <QDialog>
#include <QDomElement>
#include <QSettings>

namespace Ui {
class FFGLSourceCreationDialog;
}

class FFGLSourceCreationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FFGLSourceCreationDialog(QWidget *parent = 0, QSettings *settings = 0);
    ~FFGLSourceCreationDialog();

    QDomElement getFreeframePluginConfiguration();
    int getSelectedWidth();
    int getSelectedHeight();

public slots:

    void done(int r);

    void updateSourcePreview();

    void browseFreeframePlugin();
    void deleteFreeframePlugin();
    void browseShadertoyPlugin();
    void deleteShadertoyPlugin();

    void showErrorMessage();
    void showFreeframeHelp();
    void showShadertoyHelp();

protected:
    void showEvent(QShowEvent *);

private:

    Ui::FFGLSourceCreationDialog *ui;

    class FFGLSource *s;

    QDomElement pluginConfiguration;
    QSettings *appSettings;
};

#endif // FFGLSOURCECREATIONDIALOG_H
