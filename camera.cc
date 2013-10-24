#include <camera.h>



Camera::Camera(Ogre::Camera *ogreCam, QObject *parent)
    : QObject(parent),
    m_camera(ogreCam),
    m_camera_controller(0)
{

}

Camera::Camera(Ogre::Camera *ogreCam, OgreBites::SdkCameraMan *cameraMan, QObject *parent):
    QObject(parent),
    m_camera(ogreCam),
    m_camera_controller(cameraMan)
{

}

Camera::~Camera()
{
    if(m_camera_controller)
        delete m_camera_controller;
}

Ogre::Camera *Camera::get()
{
    return m_camera;
}

OgreBites::SdkCameraMan *Camera::getCameraController()
{
    return m_camera_controller;
}

void Camera::onKeyPressed(Qt::Key key)
{
    if(!m_camera_controller)
        return;
    OIS::KeyCode code=OIS::KC_0;
    switch(key)
    {
    case Qt::Key_W:
        code=OIS::KC_W;
        break;
    case Qt::Key_S:
        code=OIS::KC_S;
        break;
    case Qt::Key_A:
        code=OIS::KC_A;
        break;
    case Qt::Key_D:
        code=OIS::KC_D;
        break;
    default:
        break;
    }
    OIS::KeyEvent evt(0,code,code);
    m_camera_controller->injectKeyDown(evt);
}

void Camera::onKeyReleased(Qt::Key key)
{
    if(!m_camera_controller)
        return;
    OIS::KeyCode code=OIS::KC_0;
    switch(key)
    {
    case Qt::Key_W:
        code=OIS::KC_W;
        break;
    case Qt::Key_S:
        code=OIS::KC_S;
        break;
    case Qt::Key_A:
        code=OIS::KC_A;
        break;
    case Qt::Key_D:
        code=OIS::KC_D;
        break;
    default:
        break;
    }
    OIS::KeyEvent evt(0,code,code);
    m_camera_controller->injectKeyUp(evt);
}
