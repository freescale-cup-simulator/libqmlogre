#ifndef ABSTRACTNODE_H
#define ABSTRACTNODE_H

#include <QtQuick/QSGGeometryNode>
#include <QtQuick/QSGTextureMaterial>
#include <QtQuick/QSGOpaqueTextureMaterial>
#include <QtQuick/QQuickWindow>

#include <QSurfaceFormat>
#include <QOpenGLContext>
#include <QOpenGLFunctions>

#include <QDebug>

#include <OgreRoot.h>
#include <OgreCamera.h>
#include <OgreSceneManager.h>
#include <OgreRenderTexture.h>
#include <OgreViewport.h>
#include <OgreRenderTarget.h>

#include <ogre_engine.h>
#include <camera.h>


class AbstractNode : public QSGGeometryNode
{

public:

    AbstractNode();
    virtual ~AbstractNode();

    virtual void setSize(const QSize &size);
    virtual QSize size() const { return m_size; }

    virtual void update();
    virtual void updateFBO();

    virtual GLuint getOgreFboId();

    virtual void doneOgreContext();
    virtual void activateOgreContext();

    virtual void preprocess()=0;

protected:

    QSGTextureMaterial m_material;
    QSGOpaqueTextureMaterial m_materialO;
    QSGGeometry m_geometry;
    QSGTexture * m_texture;
    QSize m_size;

    OgreEngine * m_ogreEngineItem;

    Ogre::Camera * m_camera;
    Ogre::RenderTexture * m_renderTarget;
    Ogre::Viewport * m_viewport;
    Ogre::TexturePtr m_rttTexture;

    //OgreBites::SdkCameraMan * m_camera_man;
    //Ogre::FrameEvent m_evt;

    GLuint m_ogreFboId;
    bool m_dirtyFBO;

    //QElapsedTimer m_timer;
};

#endif // ABSTRACTNODE_H
