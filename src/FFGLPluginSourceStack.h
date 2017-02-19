/*
 *   FFGLPluginSourceStack
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

#ifndef FFGLPLUGINSOURCESTACK_H
#define FFGLPLUGINSOURCESTACK_H

#include <QStack>

class FFGLPluginSource;

class FFGLPluginSourceStack: public QStack<FFGLPluginSource *>
{

public:
    FFGLPluginSourceStack() {}
    FFGLPluginSourceStack(FFGLPluginSource *);

    QStringList namesList();

    FFGLPluginSource *pushNewPlugin(QString filename, int widht, int height, unsigned int inputTexture);
    FFGLPluginSource *pushNewPlugin(int widht, int height, unsigned int inputTexture);

    void removePlugin(FFGLPluginSource *p);
    void moveUp(FFGLPluginSource *p);
    void moveDown(FFGLPluginSource *p);

    void update();
    void bind() const;
    void clear();
    void play(bool on);

private:

};

#endif // FFGLPLUGINSOURCESTACK_H
