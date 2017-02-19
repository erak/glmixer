/*
 *   FFGLPluginBrowser
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

#ifndef FFGLPLUGINBROWSER_H
#define FFGLPLUGINBROWSER_H


#include "PropertyBrowser.h"
#include "FFGLPluginSourceStack.h"

class FFGLPluginBrowser : public PropertyBrowser
{
    Q_OBJECT

public:
    FFGLPluginBrowser(QWidget *parent = 0, bool allowRemove = true);

public slots:

    void clear();
    void showProperties(FFGLPluginSourceStack *plugins);

    // Update the plugin when an action is performed on a property in the browser
    // This concerns every properties editable in the browser
    void valueChanged(QtProperty *property, bool value);
    void valueChanged(QtProperty *property, int value);
    void valueChanged(QtProperty *property, double value);
    void valueChanged(QtProperty *property, const QString &value);

    void resetAll();
    void defaultValue();

    void ctxMenuTree(const QPoint &);

    // Context menu actions
    void moveUpPlugin();
    void moveDownPlugin();
    void removePlugin();
    void editPlugin();
    void enablePlugin(bool);

signals:
    // inform to refresh the GUI
    void pluginChanged();
    void edit(FFGLPluginSource *);

private:

    // implementation methods
    bool canChange();

    // the link with plugin
    FFGLPluginSourceStack *currentStack;
    QMap<QtProperty *, QPair<FFGLPluginSource *, QString> > propertyToPluginParameter;

    QtProperty *createPluginPropertyTree(FFGLPluginSource *plugin);
    QAction *removeAction;
    QAction *moveUpAction, *moveDownAction;
    QAction *editAction, *enableAction;
};

#endif // FFGLPLUGINBROWSER_H
