#ifndef Camera_H
#define Camera_H

#include <QObject>

#include <OgreCamera.h>
#include <OIS.h>
#include <SdkCameraMan.h>

class Camera : public QObject
{

    Q_OBJECT

public:

    Camera(Ogre::Camera * ogreCam,QObject *parent = 0);
    Camera(Ogre::Camera * ogreCam,OgreBites::SdkCameraMan * cameraMan,QObject *parent = 0);
    ~Camera();

    Ogre::Camera * get();
    OgreBites::SdkCameraMan * getCameraController();

public slots:
    void onKeyPressed(Qt::Key key);
    void onKeyReleased(Qt::Key key);
    void onMouseMove(qreal mouseX, qreal mouseY);
private:

    Ogre::Camera * m_camera;
    OgreBites::SdkCameraMan * m_camera_controller;
};

#endif // Camera_H
