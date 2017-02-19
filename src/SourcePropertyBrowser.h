/*
 * SourcePropertyBrowser.h
 *
 *  Created on: Mar 14, 2010
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

#ifndef SOURCEPROPERTYBROWSER_H_
#define SOURCEPROPERTYBROWSER_H_

#include "PropertyBrowser.h"
#include "SourceSet.h"


class SourcePropertyBrowser  : public PropertyBrowser {

    Q_OBJECT

    friend class SourcePropertyTreeFiller;

public:
    SourcePropertyBrowser(QWidget *parent = 0);

    static PropertyBrowser *createSpecificPropertyBrowser(Source *s, QWidget *parent);


public slots:
    // Shows the properties in the browser for the given source (iterator in the Manager list)
    // This is called every time we want to get information on a source
    void showProperties(Source *source);
    void showProperties(SourceSet::iterator sourceIt);

    // Update the values of the property browser for the current source
    void updateMixingProperties();
    void updateGeometryProperties();
    void updateLayerProperties();

    void valueChanged(QtProperty *property, const QColor &value);
    void valueChanged(QtProperty *property, const QPointF &value);
    void valueChanged(QtProperty *property, bool value);
    void valueChanged(QtProperty *property, int value);
    void enumChanged(QtProperty *property, int value);
    void valueChanged(QtProperty *property, double value);
    void valueChanged(QtProperty *property, const QString &value);
    void valueChanged(QtProperty *property, const QRectF &value);
    void resetAll();

    // restore default values to current item
    void defaultValue();

signals:
    void changed(Source *s);

private:

    // property tree
    QtProperty *root;

    // the link with source
    Source *currentItem;
    QMutex propertyTreeAccesslock;

    // implementation methods
    bool canChange();
    void createSourcePropertyTree();
    void updateProperty(QString name, Source *s);
    void updatePropertyTree();

};


class SourcePropertyTreeFiller : public QThread
 {
     Q_OBJECT

     void run();

     SourcePropertyBrowser *_spb;

public:
     SourcePropertyTreeFiller(SourcePropertyBrowser *spb);

};

#endif /* SOURCEPROPERTYBROWSER_H_ */
