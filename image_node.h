#ifndef IMAGE_NODE_H
#define IMAGE_NODE_H

#include <abstract_node.h>
#include <shared_image.h>

class ImageNode : public AbstractNode
{
public:
    ImageNode(OgreEngine * engine,Camera * cameraObj,SharedImage * sharedImage);
    virtual ~ImageNode();
    virtual void preprocess();

private:
    SharedImage * m_shared_image;
};

#endif
