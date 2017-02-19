/*
 * VideoFileDisplayWidget.cpp
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

#include "VideoFileDisplayWidget.moc"

#include <QtGui/QImage>



VideoFileDisplayWidget::VideoFileDisplayWidget(QWidget *parent)
  : glRenderWidget(parent), is(NULL), squareDisplayList(-1), textureIndex(-1), useVideoAspectRatio(true)

{

}

VideoFileDisplayWidget::~VideoFileDisplayWidget()
{
    if (squareDisplayList){
        makeCurrent();
        if (squareDisplayList>0)
            glDeleteLists(squareDisplayList, 1);
        if (textureIndex>0)
            glDeleteTextures(1, &textureIndex);
    }
}


void VideoFileDisplayWidget::setVideo(VideoFile *f){

    is = f;
    makeCurrent();

    if (is) {
        glEnable(GL_TEXTURE_2D);
        QObject::connect(is, SIGNAL(frameReady(VideoPicture*)), this, SLOT(updateFrame(VideoPicture*)));
    } else {
        glDisable(GL_TEXTURE_2D);
        update();
    }
}



void VideoFileDisplayWidget::initializeGL()
{
	glRenderWidget::initializeGL();

//    cubeTexture = bindTexture(QImage("./cubelogo.png"));
    glGenTextures(1, &textureIndex);
	GLclampf lowpriority = 0.1;
	glPrioritizeTextures(1, &textureIndex, &lowpriority);

    glBindTexture(GL_TEXTURE_2D, textureIndex);
    // ugly but fast for preview
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    squareDisplayList = glGenLists(1);
    glNewList(squareDisplayList, GL_COMPILE);
    {
        glBegin(GL_QUADS); // begin drawing a square

        // Front Face (note that the texture's corners have to match the quad's corners)
        glNormal3f(0.0f, 0.0f, 1.0f); // front face points out of the screen on z.
        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-1.0f, -1.0f, 0.0f); // Bottom Left
        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(1.0f, -1.0f, 0.0f); // Bottom Right
        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(1.0f, 1.0f, 0.0f); // Top Right
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-1.0f, 1.0f, 0.0f); // Top Left

        glEnd();
    }
    glEndList();

}



void VideoFileDisplayWidget::updateFrame (VideoPicture *vp)
{

    makeCurrent();

    // start update texture
    if ( vp && vp->getBuffer() != NULL ) {

        glBindTexture(GL_TEXTURE_2D, textureIndex);

        if ( vp->getFormat() == AV_PIX_FMT_RGBA)
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8,  vp->getWidth(),
                     vp->getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE,
                     vp->getBuffer() );
        else
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,  vp->getWidth(),
                     vp->getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                     vp->getBuffer() );

        if (vp->hasAction(VideoPicture::ACTION_DELETE))
            delete vp;

        vp = NULL;
    }
    // end

    update();
}


void VideoFileDisplayWidget::paintGL()
{
	glRenderWidget::paintGL();

	if (is) {
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		if (useVideoAspectRatio) {
			float windowaspectratio = (float) width() / (float) height();
			if ( windowaspectratio < is->getStreamAspectRatio())
				glScalef(   1.f, windowaspectratio / is->getStreamAspectRatio(), 1.f);
			else
				glScalef(   is->getStreamAspectRatio() / windowaspectratio,  1.f, 1.f);
		}

		glCallList(squareDisplayList);
	}
}


void VideoFileDisplayWidget::setVideoAspectRatio(bool usevideoratio){

	useVideoAspectRatio = usevideoratio;

}

