#include <controlled_node.h>

ControlledNode::ControlledNode(OgreEngine *engine, Camera *cameraObj)
{
    this->m_camera=cameraObj->get();
    this->m_camera_man=cameraObj->getCameraController();
    this->m_ogreEngineItem=engine;

    m_timer.start();
}

/*
 *Called by CameraGrabber timer or by QQuickWindow
*/

void ControlledNode::update()
{
    qint64 time=m_timer.restart();
    m_evt.timeSinceLastFrame=(double) time/2200;

    if(m_camera_man)
        m_camera_man->frameRenderingQueued(m_evt);
    AbstractNode::update();
}

void ControlledNode::preprocess()
{
    activateOgreContext();
    m_renderTarget->update(true);
    doneOgreContext();
}
