/*
 * RenderingManager
 *
 *  Created on: 3 nov. 2009
 *      Author: herbelin
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

#ifndef RENDERINGMANAGER_H_
#define RENDERINGMANAGER_H_

#include "SourceSet.h"

#include <output_stream.h>

typedef enum {
    QUALITY_VGA = 0,
    QUALITY_PAL,
    QUALITY_SVGA,
    QUALITY_XGA,
    QUALITY_UXGA,
    QUALITY_QXGA,
    QUALITY_UNSUPPORTED
} frameBufferQuality;

typedef enum {
    ASPECT_RATIO_4_3 = 0,
    ASPECT_RATIO_3_2,
    ASPECT_RATIO_16_10,
    ASPECT_RATIO_16_9,
    ASPECT_RATIO_FREE
} standardAspectRatio;

standardAspectRatio doubleToAspectRatio(double ar);

#include <QObject>
#include <QDomElement>
#include <QtSvg>
#include <QUrl>

class QGLFramebufferObject;
class VideoFile;
class VideoStream;
class ViewRenderWidget;
class SourcePropertyBrowser;
class HistoryManager;
class RenderingEncoder;
class SessionSwitcher;

class RenderingManager: public QObject {

    Q_OBJECT

    friend class RenderingSource;
    friend class OutputRenderWidget;
    friend class UndoManager;

    RenderingManager();
    virtual ~RenderingManager();
    static RenderingManager *_instance;


public:
    /**
     * singleton mechanism
     */
    static ViewRenderWidget *getRenderingWidget();
    static SourcePropertyBrowser *getPropertyBrowserWidget();
    static RenderingEncoder *getRecorder();
    static SessionSwitcher *getSessionSwitcher();
    static RenderingManager *getInstance();
    static void deleteInstance();

    /**
    * Management of the sources
    **/
//    QString renameSource(Source *s, const QString name);

    // create source per type :
    Source *newRenderingSource(bool recursive, double depth = -1.0);
    Source *newCaptureSource(QImage img, double depth = -1.0);
    Source *newMediaSource(VideoFile *vf, double depth = -1.0);
    Source *newSvgSource(QSvgRenderer *svg, double depth = -1.0);
    Source *newWebSource(QUrl web, int w, int h, int height, int scroll, int update, double depth = -1.0);
    Source *newAlgorithmSource(int type, int w, int h, double v, int p, bool ia, double depth = -1.0);
    Source *newCloneSource(SourceSet::iterator sit, double depth = -1.0);

#ifdef GLM_OPENCV
    Source *newOpencvSource(int opencvIndex, int mode, double depth = -1.0);
#endif
#ifdef GLM_SHM
    Source *newSharedMemorySource(qint64 shmid, double depth = -1.0);
#endif
#ifdef GLM_SPOUT
    Source *newSpoutSource(QString senderName, double depth = -1.0);
#endif
#ifdef GLM_FFGL
    Source *newFreeframeGLSource(QDomElement configuration, int w, int h, double depth = -1.0);
#endif
    Source *newStreamSource(VideoStream *vs, double depth = -1.0);

    // insert & remove sources into the scene
    bool insertSource(Source *s);
    int removeSource(SourceSet::iterator itsource);
    void replaceSource(GLuint oldsource, GLuint newsource);
    void addSourceToBasket(Source *s);
    int getSourceBasketSize() const;
    Source *getSourceBasketTop() const;

    SourceSet::iterator getBegin();
    SourceSet::iterator getEnd();
    SourceSet::const_iterator getBegin() const;
    SourceSet::const_iterator getEnd() const;
    SourceSet::iterator getById(const GLuint id);
    SourceSet::iterator getByName(const QString name);
    SourceSet::const_iterator getByName(const QString name) const;
    bool notAtEnd(SourceSet::const_iterator itsource) const;
    bool isValid(SourceSet::const_iterator itsource) const;
    QString getAvailableNameFrom(QString name) const;
    double getAvailableDepthFrom(double depth = -1) const;
    SourceSet::iterator changeDepth(SourceSet::iterator itsource,double newdepth);

    inline bool empty() const { return _front_sources.empty(); }
    inline SourceSet getCopy() { return SourceSet (_front_sources); }

    // current source
    bool isCurrentSource(const Source *s);
    bool isCurrentSource(SourceSet::iterator si);
    void setCurrentSource(SourceSet::iterator si);
    void setCurrentSource(GLuint id);
    inline SourceSet::iterator getCurrentSource()  const{
        return _currentSource;
    }
    bool setCurrentNext();
    bool setCurrentPrevious();
    void unsetCurrentSource() { setCurrentSource( getEnd() ); }


    /**
     * management of the rendering
     */
    void resetFrameBuffer();
    void preRenderToFrameBuffer();
    void sourceRenderToFrameBuffer(Source *source);
    void postRenderToFrameBuffer();

    void setRenderingQuality(frameBufferQuality q);
    inline frameBufferQuality getRenderingQuality() const {
        return renderingQuality;
    }

    void setRenderingAspectRatio(standardAspectRatio ar);
    standardAspectRatio getRenderingAspectRatio() const {
        return renderingAspectRatio;
    }

    double getFrameBufferAspectRatio() const;
    inline QSize getFrameBufferResolution() const {
            return renderingSize;
    }

    inline int getFrameBufferWidth() const{
        return renderingSize.width();
    }

    inline int getFrameBufferHeight() const{
        return renderingSize.height();
    }

    inline GLuint getFrameBufferTexture() const{
        return _fbo ? _fbo->texture() : 0;
    }

    inline GLuint getFrameBufferHandle() const{
        return _fbo ? _fbo->handle() : 0;
    }

    inline unsigned int getPreviousFrameDelay() const {
        return previousframe_delay;
    }

    QImage captureFrameBuffer(QImage::Format format = QImage::Format_RGB888);
    inline bool clearToWhite() const {
        return clearWhite;
    }

#ifdef GLM_SHM
    uint getSharedMemoryColorDepth();
    void setSharedMemoryColorDepth(uint mode);
#endif

    /**
     * save and load configuration
     */
    QDomElement getConfiguration(QDomDocument &doc, QDir current = QDir());
    int addConfiguration(QDomElement xmlconfig, QDir current, QString version = XML_GLM_VERSION);

    inline Source *defaultSource() { return _defaultSource; }
    inline Source::scalingMode getDefaultScalingMode() const { return _scalingMode; }
    inline void setDefaultScalingMode(Source::scalingMode sm) { _scalingMode = sm; }
    inline bool getDefaultPlayOnDrop() const { return _playOnDrop; }
    inline void setDefaultPlayOnDrop(bool on){ _playOnDrop = on; }
    inline bool isPaused () { return paused; }

    static inline bool useFboBlitExtension() { return blit_fbo_extension; }
    static void setUseFboBlitExtension(bool on);

    static inline bool usePboExtension() { return pbo_extension; }
    static void setUsePboExtension(bool on);


public slots:

    inline void setClearToWhite(bool on) { clearWhite = on; }
    inline void setPreviousFrameDelay(unsigned int delay) { previousframe_delay = CLAMP(delay,1,1000);}

    void pause(bool on);
    void clearBasket();
    void clearSourceSet();
    void resetSource(SourceSet::iterator sit);
    void resetCurrentSource();
    void refreshCurrentSource();
    void toggleUnchangeableCurrentSource(bool);
    void toggleFixAspectRatioCurrentSource(bool);
    void setOriginalAspectRatioCurrentSource();
    void setRenderingAspectRatioCurrentSource();

    void dropSource();
    void dropSourceWithAlpha(double alphax, double alphay);
    void dropSourceWithCoordinates(double x, double y);
    void dropSourceWithDepth(double depth);

    void onSourceFailure();

#ifdef GLM_SHM
    void setFrameSharingEnabled(bool on);
#endif
#ifdef GLM_SPOUT
    void setSpoutSharingEnabled(bool on);
#endif

signals:
    void frameBufferChanged();
    void currentSourceChanged(SourceSet::iterator csi);
    void methodCalled(QString);
    void editCurrentSource();
#ifdef GLM_SPOUT
    void spoutSharingEnabled(bool on);
#endif

protected:
    // insert & remove sources into the scene
    bool _insertSource(Source *s);
    int _removeSource(SourceSet::iterator itsource);
    int _removeSource(const GLuint idsource);
    int _addSourceConfiguration(QDomElement child, QDir current = QDir(), QString version = XML_GLM_VERSION);

    // frame buffer
    void setFrameBufferResolution(QSize size);

    // the rendering area
    ViewRenderWidget *_renderwidget;
    // properties of the sources
    SourcePropertyBrowser *_propertyBrowser;

    // the frame buffers
    QSize renderingSize;
    QGLFramebufferObject *_fbo;
    QGLFramebufferObject *previousframe_fbo;
    GLuint pboIds[2];
    int pbo_index, pbo_nextIndex;
    unsigned int previousframe_index, previousframe_delay;
    bool clearWhite;
    GLint maxtexturewidth, maxtextureheight;
    frameBufferQuality renderingQuality;
    standardAspectRatio renderingAspectRatio;

    // the set of sources for display (front)
    SourceSet _front_sources;
    // the recorder
    RenderingEncoder *_recorder;
    // the session switcher
    SessionSwitcher *_switcher;

    // manipulation of sources
    SourceSet::iterator _currentSource;
    SourceList dropBasket;
    Source *_defaultSource;
    Source::scalingMode _scalingMode;
    bool _playOnDrop;
    bool paused;
    unsigned int maxSourceCount;
    // set of sources using previousframe_fbo
    SourceSet _rendering_sources;


#ifdef GLM_SHM
    // The shared memory buffer
    class QSharedMemory *_sharedMemory;
    GLenum _sharedMemoryGLFormat, _sharedMemoryGLType;
#endif
#ifdef GLM_SPOUT
    bool _spoutEnabled, _spoutInitialized;
#endif

    output_stream stream_;

    static bool blit_fbo_extension, pbo_extension;
    static QSize sizeOfFrameBuffer[ASPECT_RATIO_FREE][QUALITY_UNSUPPORTED];
};

#endif /* RENDERINGMANAGER_H_ */
