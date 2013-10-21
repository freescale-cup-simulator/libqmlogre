#ifndef IMAGE_NODE_H
#define IMAGE_NODE_H

#include <abstract_node.h>

class ImageNode : public AbstractNode
{
public:
    ImageNode(OgreEngine * engine,Camera * cameraObj);
    virtual void preprocess();
};

#endif
