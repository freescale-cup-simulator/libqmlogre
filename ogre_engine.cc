/*!
 * \copyright (c) Nokia Corporation and/or its subsidiary(-ies) (qt-info@nokia.com) and/or contributors
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 *
 * \license{This source file is part of QmlOgre abd subject to the BSD license that is bundled
 * with this source code in the file LICENSE.}
 */

#include <ogre_engine.h>

OgreEngine::OgreEngine(QQuickWindow *window)
    : QObject()
    , m_log_manager(0)
    , m_root(0)
{
    qmlRegisterType<OgreEngine>("OgreEngine", 1, 0, "OgreEngine");
    setQuickWindow(window);
}

OgreEngine::~OgreEngine()
{
    delete m_ogreContext;
    if(m_log_manager)
        delete m_log_manager;
}

Ogre::Root* OgreEngine::startEngine(Ogre::String resources_directory,Ogre::String plugins_config_directory)
{
    activateOgreContext();
    //m_log_manager=new Ogre::LogManager();
    //m_log_manager->createLog(LOG_FILE_NAME,true,false,false);

    Ogre::Root *ogreRoot = new Ogre::Root(plugins_config_directory);

    Ogre::RenderSystem *renderSystem = ogreRoot->getRenderSystemByName(RENDER_SYSTEM_NAME);
    Ogre::ConfigOptionMap config=renderSystem->getConfigOptions();
    Ogre::StringVector::const_iterator it=config.at("FSAA").possibleValues.cbegin();
    qDebug()<<"Available anti-aliasing options:";
    while(it!=config.at("FSAA").possibleValues.cend())
    {
        qDebug()<<"FSAA:"<<it->c_str();
        it++;
    }

    ogreRoot->setRenderSystem(renderSystem);
    ogreRoot->initialise(false);

    Ogre::NameValuePairList params;

    params["externalGLControl"] = "true";
    params["currentGLContext"] = "true";
    //params["FSAA"]="8";

    //Finally create our window.
    m_ogreWindow = ogreRoot->createRenderWindow(WINDOW_NAME, 1, 1, false, &params);
    m_ogreWindow->setVisible(false);
    m_ogreWindow->update(false);

    Ogre::ResourceGroupManager & rm = Ogre::ResourceGroupManager::getSingleton();
    rm.addResourceLocation(resources_directory+"materials", "FileSystem");
    rm.addResourceLocation(resources_directory+"meshes", "FileSystem");
    rm.initialiseAllResourceGroups();
    Ogre::MaterialManager::getSingleton().setDefaultTextureFiltering(Ogre::TFO_ANISOTROPIC);
    Ogre::MaterialManager::getSingleton().setDefaultAnisotropy(4);


    m_scene_manager = ogreRoot->createSceneManager(Ogre::ST_GENERIC, "SceneManager");
    m_scene_manager->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
    m_scene_manager->setAmbientLight(Ogre::ColourValue(255, 255, 255));

    doneOgreContext();
    m_root=ogreRoot;
    return ogreRoot;
}

void OgreEngine::stopEngine()
{
    if (m_root) {

        //m_root->detachRenderTarget(m_renderTexture);
        // TODO tell node(s) to detach

    }

    delete m_root;
}

void OgreEngine::setQuickWindow(QQuickWindow *window)
{
    Q_ASSERT(window);

    m_quickWindow = window;
    m_qtContext = QOpenGLContext::currentContext();

    // create a new shared OpenGL context to be used exclusively by Ogre
    m_ogreContext = new QOpenGLContext();

    // anti-aliasing
    QSurfaceFormat format=m_quickWindow->requestedFormat();
    format.setSamples(8);
    m_quickWindow->setFormat(format);
    m_ogreContext->setFormat(format);

    m_ogreContext->setShareContext(m_qtContext);
    m_ogreContext->create();
}

void OgreEngine::activateOgreContext()
{
    glPopAttrib();
    glPopClientAttrib();

    m_qtContext->functions()->glUseProgram(0);
    m_qtContext->doneCurrent();

    m_ogreContext->makeCurrent(m_quickWindow);
}

void OgreEngine::doneOgreContext()
{
    m_ogreContext->functions()->glBindBuffer(GL_ARRAY_BUFFER, 0);
    m_ogreContext->functions()->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    m_ogreContext->functions()->glBindRenderbuffer(GL_RENDERBUFFER, 0);
    m_ogreContext->functions()->glBindFramebuffer(GL_FRAMEBUFFER_EXT, 0);

    // unbind all possible remaining buffers; just to be on safe side
    m_ogreContext->functions()->glBindBuffer(GL_ARRAY_BUFFER, 0);
    m_ogreContext->functions()->glBindBuffer(GL_ATOMIC_COUNTER_BUFFER, 0);
    m_ogreContext->functions()->glBindBuffer(GL_COPY_READ_BUFFER, 0);
    m_ogreContext->functions()->glBindBuffer(GL_COPY_WRITE_BUFFER, 0);
    m_ogreContext->functions()->glBindBuffer(GL_DRAW_INDIRECT_BUFFER, 0);
//    m_ogreContext->functions()->glBindBuffer(GL_DISPATCH_INDIRECT_BUFFER, 0);
    m_ogreContext->functions()->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    m_ogreContext->functions()->glBindBuffer(GL_PIXEL_PACK_BUFFER, 0);
    m_ogreContext->functions()->glBindBuffer(GL_PIXEL_UNPACK_BUFFER, 0);
//    m_ogreContext->functions()->glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
    m_ogreContext->functions()->glBindBuffer(GL_TEXTURE_BUFFER, 0);
    m_ogreContext->functions()->glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, 0);
    m_ogreContext->functions()->glBindBuffer(GL_UNIFORM_BUFFER, 0);

    m_ogreContext->doneCurrent();

    m_qtContext->makeCurrent(m_quickWindow);
    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glPushClientAttrib(GL_CLIENT_ALL_ATTRIB_BITS);
}

QOpenGLContext* OgreEngine::ogreContext() const
{
    return m_ogreContext;
}

QSGTexture* OgreEngine::createTextureFromId(uint id, const QSize &size, QQuickWindow::CreateTextureOptions options) const
{
    return m_quickWindow->createTextureFromId(id, size, options);
}
