/*!
 * \copyright (c) Nokia Corporation and/or its subsidiary(-ies) (qt-info@nokia.com) and/or contributors
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 *
 * \license{This source file is part of QmlOgre abd subject to the BSD license that is bundled
 * with this source code in the file LICENSE.}
 */

#include "camera_grabber.h"

CameraGrabber::CameraGrabber(QQuickItem *parent)
    : QQuickItem(parent)
    , m_timerID(0)
    , m_camera(0)
    , m_ogreEngineItem(0)
{
    setFlag(ItemHasContents);
    setSmooth(false);
    startTimer(16);
}

CameraGrabber::CameraGrabber(OgreEngine *engine, Camera *camera, SharedImage *shared_image_buffer, QQuickItem *parent)
    : QQuickItem(parent)
    , m_timerID(0)
    , m_camera(camera)
    , m_ogreEngineItem(engine)
    , m_shared_image(shared_image_buffer)
{

}

CameraGrabber::~CameraGrabber()
{

}

QObject * CameraGrabber::camera() const
{
    return qobject_cast<QObject *>(m_camera);
}

QSGNode *CameraGrabber::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *)
{
    if (width() <= 0 || height() <= 0 || !m_camera || !m_ogreEngineItem) {
        delete oldNode;
        return 0;
    }

    AbstractNode *node = static_cast<AbstractNode *>(oldNode);
    //
    if (!node)
    {
        if(m_camera->getCameraController())
            node=new ControlledNode(m_ogreEngineItem,m_camera);
        else
        {
            Q_ASSERT(m_shared_image);
            node=new ImageNode(m_ogreEngineItem,m_camera,m_shared_image);
        }
    }
    node->setSize(QSize(width(), height()));
    node->update();
    // mark texture dirty, otherwise Qt will not trigger a redraw (preprocess())
    node->markDirty(QSGNode::DirtyMaterial);
    return node;
}

void CameraGrabber::timerEvent(QTimerEvent *)
{
    update();
}


void CameraGrabber::log(QString text)
{
    qDebug()<<"["<<this->objectName()<<"] "<<text;
}

void CameraGrabber::setCamera(QObject *camera)
{
    m_camera = qobject_cast<Camera*>(camera);
    this->setObjectName("CameraGrabber::"+m_camera->objectName());
}

void CameraGrabber::setOgreEngine(OgreEngine *ogreEngine)
{
    m_ogreEngineItem = ogreEngine;
}

SharedImage *CameraGrabber::sharedImage() const
{
    return m_shared_image;
}

void CameraGrabber::setSharedImage(SharedImage *img)
{
    m_shared_image=img;
}
