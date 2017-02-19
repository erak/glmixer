/*
 * selectionView.h
 *
 *  Created on: May 12, 2010
 *      Author: bh
 *
 *  This file is part of GLMixer.
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

#ifndef CATALOGVIEW_H_
#define CATALOGVIEW_H_

#include "View.h"
#include <QStack>



class CatalogView: public View {

public:

    class Icon {
    public:
        Source *source;
        QRectF texturecoordinates;
        QRect fbocoordinates;
        QRect coordinates;
    };

    CatalogView();
	virtual ~CatalogView();

	// View implementation
	void setModelview();
	void clear();
	void paint();
    void resize(int w, int h);
    bool mousePressEvent(QMouseEvent *event);
    bool mouseDoubleClickEvent(QMouseEvent * event);
    bool mouseMoveEvent(QMouseEvent *event);
    bool mouseReleaseEvent ( QMouseEvent * event );
    bool wheelEvent ( QWheelEvent * event );

    bool getSourcesAtCoordinates(int mouseX, int mouseY, bool clic = false);

	// Specific implementation
    bool isInside(const QPoint &pos);
	void setVisible(bool on);
    bool visible() { return _visible;}
	void setTransparent(bool on);
	inline bool isTransparent() const { return _alpha < 0.9; }
	typedef enum { SMALL = 0, MEDIUM = 1, LARGE = 2 } catalogSize;
	void setSize(catalogSize s);
	inline catalogSize getSize() const { return _currentSize; }

	// drawing
    void drawSource(Source *s);
    void reorganize();

private:
    bool _visible;
    double _size[3], _iconSize[3], _spacing[3];
    catalogSize _currentSize;
    float _alpha;
    QGLFramebufferObject *_catalogfbo;
    QRect _allSourcesArea, _widgetArea;
    QStack <Icon *> _icons;
};

#endif /* SELECTIONVIEW_H_ */
