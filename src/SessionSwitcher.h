/*
 * SessionSwitcher.h
 *
 *  Created on: Mar 27, 2011
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

#ifndef SESSIONSWITCHER_H_
#define SESSIONSWITCHER_H_

#include <QColor>
#include <QPropertyAnimation>
#include <QImage>

class Source;

class SessionSwitcher: public QObject {

    Q_OBJECT
    Q_PROPERTY(float overlay READ overlay WRITE setOverlay)
    Q_PROPERTY(float alpha READ alpha WRITE setAlpha)

    friend class SessionSwitcherWidget;

public:
    SessionSwitcher(QObject *parent = 0);
    virtual ~SessionSwitcher();

    void render();

    void setAlpha(float a);
    float alpha() const { return currentAlpha; }
    void setOverlay(float a) { overlayAlpha = a; }
    float overlay() const { return overlayAlpha; }

    int transitionDuration() const;
    int transitionCurve() const ;
    bool transitionActive() const;

    void setTransitionColor(QColor c) { customTransitionColor = c; }
    QColor transitionColor() const { return customTransitionColor; }

    void setTransitionMedia(QString filename);
    QString transitionMedia() const ;

    typedef enum {
        TRANSITION_NONE = 0,
        TRANSITION_BACKGROUND = 1,
        TRANSITION_CUSTOM_COLOR = 2,
        TRANSITION_LAST_FRAME = 3,
        TRANSITION_CUSTOM_MEDIA = 4
    } transitionType;
    void setTransitionType(transitionType t);
    transitionType getTransitionType() const {return transition_type;}

public slots:
    // initiate the transition animation
    void startTransition(bool sceneVisible, bool instanteneous = false);
    // end the transition
    void endTransition();
    // set the duration of fading
    void setTransitionDuration(int ms);
    // set the profile of fading
    void setTransitionCurve(int curveType);
    // instantaneous set transparency of overlay
    void setTransparency(int alpha);
    // alpha mask
    void setAlpha(int a);
    void smoothAlphaTransition(bool visible);

signals:
    void animationFinished();
    void alphaChanged(int);

private:
    bool manual_mode;
    int duration;
    float currentAlpha, overlayAlpha;
    QPropertyAnimation *alphaAnimation, *overlayAnimation;
    transitionType transition_type;
    QColor customTransitionColor, overlayColor;
    QString customTransitionMedia;
    QImage overlayMedia;
};

#endif /* SESSIONSWITCHER_H_ */
