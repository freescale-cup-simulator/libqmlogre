#ifndef CONTROLLED_NODE_H
#define CONTROLLED_NODE_H

#include <QElapsedTimer>
#include <abstract_node.h>

class ControlledNode : public AbstractNode
{
public:
    ControlledNode(OgreEngine * engine,Camera * cameraObj);
    virtual void update();
    virtual void preprocess();

protected:

    OgreBites::SdkCameraMan * m_camera_man;
    Ogre::FrameEvent m_evt;

    QElapsedTimer m_timer;
};

#endif
