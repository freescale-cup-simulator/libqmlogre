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

Ogre::Camera *Camera::get()
{
    return m_camera;
}

OgreBites::SdkCameraMan *Camera::getCameraController()
{
    return m_camera_controller;
}
