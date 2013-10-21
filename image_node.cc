#include <image_node.h>

ImageNode::ImageNode(OgreEngine *engine, Camera *cameraObj)
{
    this->m_camera=cameraObj->get();
    this->m_ogreEngineItem=engine;
}

void ImageNode::preprocess()
{
    activateOgreContext();
    m_renderTarget->update(true);
    doneOgreContext();
}
