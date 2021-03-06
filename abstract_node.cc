
#include <RenderSystems/GL/OgreGLTexture.h>
#include <RenderSystems/GL/OgreGLFrameBufferObject.h>
#include <RenderSystems/GL/OgreGLFBORenderTexture.h>

#include <abstract_node.h>


AbstractNode::AbstractNode()
    : QSGGeometryNode()
    , m_geometry(QSGGeometry::defaultAttributes_TexturedPoint2D(), 4)
    , m_texture(0)
    , m_ogreEngineItem(0)
    , m_camera(0)
    , m_renderTarget(0)
    , m_viewport(0)
    , m_ogreFboId(0)
    , m_dirtyFBO(false)
{
    setMaterial(&m_material);
    setOpaqueMaterial(&m_materialO);
    setGeometry(&m_geometry);
    setFlag(UsePreprocess);
}

AbstractNode::~AbstractNode()
{
    if (m_renderTarget) {
        m_renderTarget->removeAllViewports();
    }

    if (Ogre::Root::getSingletonPtr()) {
        Ogre::Root::getSingletonPtr()->detachRenderTarget(m_renderTarget);
    }
}

void AbstractNode::setSize(const QSize &size)
{
    if (size == m_size)
        return;

    m_size = size;
    m_dirtyFBO = true;
    markDirty(DirtyGeometry);
}

void AbstractNode::update()
{
    if (m_dirtyFBO)
    {
        activateOgreContext();
        updateFBO();
        m_ogreFboId = getOgreFboId();
        m_dirtyFBO = false;
        doneOgreContext();
    }
}

/*
 *Called only if node size was changed (setSize method)
*/

void AbstractNode::updateFBO()
{
    if (m_renderTarget)
        Ogre::TextureManager::getSingleton().remove(m_camera->getName());
    //qDebug()<<"UpdateFBO "<<m_camera->getName().c_str();
    int samples = m_ogreEngineItem->ogreContext()->format().samples();
    //qDebug()<<"FBO samples:"<<samples;
    m_rttTexture = Ogre::TextureManager::getSingleton().createManual(m_camera->getName(),
                                                                     Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
                                                                     Ogre::TEX_TYPE_2D,
                                                                     m_size.width(),
                                                                     m_size.height(),
                                                                     0,
                                                                     Ogre::PF_R8G8B8A8,
                                                                     Ogre::TU_RENDERTARGET, 0, false,
                                                                     samples);

    m_renderTarget = m_rttTexture->getBuffer()->getRenderTarget();
    m_renderTarget->addViewport(m_camera);
    m_renderTarget->getViewport(0)->setClearEveryFrame(true);
    m_renderTarget->getViewport(0)->setBackgroundColour(Ogre::ColourValue::Black);
    m_renderTarget->getViewport(0)->setOverlaysEnabled(false);


    Ogre::Real aspectRatio = Ogre::Real(m_size.width()) / Ogre::Real(m_size.height());
    m_camera->setAspectRatio(aspectRatio);

    QSGGeometry::updateTexturedRectGeometry(&m_geometry,
                                            QRectF(0, 0, m_size.width(), m_size.height()),
                                            QRectF(0, 0, 1, 1));

    Ogre::GLTexture *nativeTexture = static_cast<Ogre::GLTexture *>(m_rttTexture.get());

    delete m_texture;
    m_texture = m_ogreEngineItem->createTextureFromId(nativeTexture->getGLID(), m_size);

    m_material.setTexture(m_texture);
    m_materialO.setTexture(m_texture);
}

GLuint AbstractNode::getOgreFboId()
{
    if (!m_renderTarget)
        return 0;

    Ogre::GLFrameBufferObject *ogreFbo = 0;
    m_renderTarget->getCustomAttribute("FBO", &ogreFbo);
    Ogre::GLFBOManager *manager = ogreFbo->getManager();
    manager->bind(m_renderTarget);

    GLint id;
    glGetIntegerv(GL_FRAMEBUFFER_BINDING, &id);

    return id;
}

void AbstractNode::doneOgreContext()
{
    if (m_ogreFboId != 0)
    {
        Ogre::GLFrameBufferObject *ogreFbo = NULL;
        m_renderTarget->getCustomAttribute("FBO", &ogreFbo);
        Ogre::GLFBOManager *manager = ogreFbo->getManager();
        manager->unbind(m_renderTarget);
    }
    m_ogreEngineItem->doneOgreContext();
}

void AbstractNode::activateOgreContext()
{
    m_ogreEngineItem->activateOgreContext();
    m_ogreEngineItem->ogreContext()->functions()->glBindFramebuffer(GL_FRAMEBUFFER_EXT, m_ogreFboId);
}
