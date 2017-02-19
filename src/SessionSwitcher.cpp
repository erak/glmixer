/*
 * SessionSwitcher.cpp
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

#include "SessionSwitcher.moc"

#include "ViewRenderWidget.h"
#include "OutputRenderWindow.h"
#include "RenderingManager.h"
#include "VideoSource.h"
#include "VideoFile.h"
#include "AlgorithmSource.h"
#include "CaptureSource.h"

#include <QGLWidget>

SessionSwitcher::SessionSwitcher(QObject *parent)  : QObject(parent), manual_mode(false), duration(1000), currentAlpha(0.0), overlayAlpha(0.0),
transition_type(TRANSITION_NONE), customTransitionColor(Qt::black), overlayColor(Qt::black)
{

    // alpha opacity mask
    alphaAnimation = new QPropertyAnimation(this, "alpha");
    alphaAnimation->setDuration(500);
    alphaAnimation->setEasingCurve(QEasingCurve::InOutQuad);

    // transition overlay
    overlayAnimation = new QPropertyAnimation(this, "overlay");
    overlayAnimation->setDuration(0);
    overlayAnimation->setEasingCurve(QEasingCurve::InOutQuad);

    QObject::connect(overlayAnimation, SIGNAL(finished()), this, SIGNAL(animationFinished() ) );
    QObject::connect(overlayAnimation, SIGNAL(finished()), this, SLOT(endTransition() ) );

    // default transition of 1 second
    setTransitionDuration(1000);

}

SessionSwitcher::~SessionSwitcher() {

    if (alphaAnimation)
        delete alphaAnimation;
    if (overlayAnimation)
        delete overlayAnimation;
}

void SessionSwitcher::render() {

    if (currentAlpha > 0.0) {

        glColor4f(0.0, 0.0, 0.0, currentAlpha);
        glCallList(ViewRenderWidget::quad_texured);
    }

    // if we shall render the overlay, do it !
    if ( overlayAlpha > 0.0 ) {

        glColor4f(overlayColor.redF(), overlayColor.greenF(), overlayColor.blueF(), overlayAlpha);

        if (transition_type > TRANSITION_CUSTOM_COLOR) {
//            if (overlayMedia.isNull())
//                overlayMedia = RenderingManager::getInstance()->captureFrameBuffer().mirrored();
            RenderingManager::getRenderingWidget()->bindTexture(overlayMedia);
        }
        else {
            glBindTexture(GL_TEXTURE_2D, ViewRenderWidget::white_texture);
        }

        glCallList(ViewRenderWidget::quad_texured);
    }

}


bool SessionSwitcher::transitionActive() const
{
    return (overlayAnimation->state() == QAbstractAnimation::Running );
}

void SessionSwitcher::setTransitionCurve(int curveType)
{
    overlayAnimation->setEasingCurve( (QEasingCurve::Type) qBound( (int) QEasingCurve::Linear, curveType, (int) QEasingCurve::OutInBounce));
}

int SessionSwitcher::transitionCurve() const
{
    return (int) overlayAnimation->easingCurve().type();
}

void SessionSwitcher::setTransitionDuration(int ms)
{
    duration = ms;
}

int SessionSwitcher::transitionDuration() const
{
    return duration;
}

void SessionSwitcher::setTransparency(int alpha)
{
    overlayAlpha = 1.f - ((float) alpha / 100.f);
}

void SessionSwitcher::setTransitionMedia(QString filename)
{
    customTransitionMedia = filename;
    setTransitionType(TRANSITION_CUSTOM_MEDIA);
}

QString SessionSwitcher::transitionMedia() const
{
    return customTransitionMedia;
}

void SessionSwitcher::setTransitionType(transitionType t)
{
    transition_type = t;

    switch (transition_type) {
    case TRANSITION_CUSTOM_COLOR:
        overlayColor = customTransitionColor;
        break;
    case TRANSITION_BACKGROUND:
        overlayColor = QColor(Qt::black);
        break;
    case TRANSITION_CUSTOM_MEDIA:
        overlayColor = QColor(Qt::white);
        overlayMedia = QImage(customTransitionMedia).mirrored();
        break;
    case TRANSITION_LAST_FRAME:
        overlayColor = QColor(Qt::white);
        overlayMedia = QImage();
        break;
    default:
        overlayColor = QColor(Qt::black);
        break;
    }

}

void SessionSwitcher::endTransition()
{
    RenderingManager::getRenderingWidget()->setFaded(false);
}


void SessionSwitcher::startTransition(bool sceneVisible, bool instanteneous){

    if (overlayAnimation->state() == QAbstractAnimation::Running )
        overlayAnimation->stop();

    switch (transition_type) {
    case TRANSITION_LAST_FRAME:
        // special case ; don't behave identically for fade in than fade out
        if (!sceneVisible) {
            // capture screen and use it immediately as transition image
            overlayMedia = RenderingManager::getInstance()->captureFrameBuffer().mirrored();
            instanteneous = true;
        }
        break;
    case TRANSITION_NONE:
        instanteneous = true;
        break;
    default:
        break;
    }

    if (manual_mode) {
        instanteneous = true;
        sceneVisible = false;
    }
    overlayAnimation->setCurrentTime(0);
    overlayAnimation->setDuration( instanteneous ? 0 : duration );
    overlayAnimation->setStartValue( overlayAlpha );
    overlayAnimation->setEndValue( sceneVisible ? 0.0 : 1.0 );
    // do not do "animationAlpha->start();" immediately ; there is a delay in rendering
    // so, we also delay a little the start of the transition to make sure it is fully applied
    QTimer::singleShot(60, overlayAnimation, SLOT(start()));

    RenderingManager::getRenderingWidget()->setFaded(!instanteneous);
}


void SessionSwitcher::setAlpha(float a)
{
    currentAlpha = a;
    emit alphaChanged( int( a * 100.0) );
}

void SessionSwitcher::setAlpha(int a)
{
    currentAlpha = float(a) / 100.0;
}

void SessionSwitcher::smoothAlphaTransition(bool visible){

    if (alphaAnimation->state() == QAbstractAnimation::Running )
        alphaAnimation->stop();

    alphaAnimation->setStartValue( currentAlpha );
    alphaAnimation->setEndValue( visible ? 0.0 : 1.1 );
    alphaAnimation->start();

}
