#include <RenderSystems/GL/OgreGLTexture.h>
#include <RenderSystems/GL/OgreGLFrameBufferObject.h>
#include <RenderSystems/GL/OgreGLFBORenderTexture.h>

#include <image_node.h>

ImageNode::ImageNode(OgreEngine *engine, Camera *cameraObj, SharedImage *sharedImage)
    : m_shared_image(sharedImage)
{
    this->m_camera=cameraObj->get();
    this->m_ogreEngineItem=engine;
}

ImageNode::~ImageNode()
{

}

void ImageNode::preprocess()
{
    activateOgreContext();
    m_renderTarget->update(true);

    // Hardware Buffer for the texture
    Ogre::HardwarePixelBufferSharedPtr pixelBuffer = m_rttTexture->getBuffer();

    Ogre::Image::Box lockBox(0,0,m_rttTexture->getWidth(),m_rttTexture->getHeight());
    pixelBuffer->lock(lockBox,Ogre::HardwareBuffer::HBL_NORMAL);

    const Ogre::PixelBox &pixBox  = pixelBuffer->getCurrentLock();
    Ogre::uint8* pDest = static_cast<Ogre::uint8*>(pixBox.data);
    if(m_shared_image->size()!=m_size)
        m_shared_image->realloc(m_size);
    quint8 * im_data=m_shared_image->tryLock();
    if(im_data)
    {
        memcpy(im_data,pDest,m_size.width()*m_size.height()*4);
        m_shared_image->unlock();
    }
    pixelBuffer->unlock();
    doneOgreContext();
}

