/*!
 * \copyright (c) Nokia Corporation and/or its subsidiary(-ies) (qt-info@nokia.com) and/or contributors
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 *
 * \license{This source file is part of QmlOgre abd subject to the BSD license that is bundled
 * with this source code in the file LICENSE.}
 */

#ifndef CameraGrabber_H
#define CameraGrabber_H

#include <QQuickWindow>
#include <QtQml>
#include <QtQuick/QQuickItem>
#include <QtCore/QPropertyAnimation>
#include <QEventLoop>


#include <controlled_node.h>
#include <image_node.h>
#include <ogre_engine.h>
#include <camera.h>
#include <shared_image.h>

class CameraGrabber : public QQuickItem
{
    Q_OBJECT

    Q_PROPERTY(QObject * camera READ camera WRITE setCamera)
    Q_PROPERTY(OgreEngine * ogreEngine READ ogreEngine WRITE setOgreEngine)
    Q_PROPERTY(QObject * sharedImage READ sharedImage WRITE setSharedImage)

public:
    CameraGrabber(QQuickItem *parent = 0);
    CameraGrabber(OgreEngine * engine, Camera * camera, SharedImage * shared_image_buffer, QQuickItem *parent = 0);

    ~CameraGrabber();

    QObject * camera() const;
    void setCamera(QObject *camera);

    OgreEngine * ogreEngine() const { return m_ogreEngineItem; }
    void setOgreEngine(OgreEngine * ogreEngine);

    QObject * sharedImage() const;
    void setSharedImage(QObject * img);

protected:

    virtual QSGNode *updatePaintNode(QSGNode *, UpdatePaintNodeData *);
    void timerEvent(QTimerEvent *);

private:

    void log(QString text);

    int m_timerID;
    Camera *m_camera;
    OgreEngine *m_ogreEngineItem;
    SharedImage * m_shared_image;

};

#endif // CameraGrabber_H
