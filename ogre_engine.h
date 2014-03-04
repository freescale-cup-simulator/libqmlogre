#ifndef OGREENGINEITEM_H
#define OGREENGINEITEM_H

#include <QObject>
#include <QQuickWindow>
#include <QtQml>
#include <QOpenGLContext>
#include <QOpenGLFunctions>

#include <OgreRoot.h>
#include <OgreRenderTexture.h>
#include <OgreViewport.h>
#include <OgreRenderTarget.h>
#include <OgreRenderWindow.h>

#define LOG_FILE_NAME "mylog.txt"
#define RENDER_SYSTEM_NAME "OpenGL Rendering Subsystem"
#define WINDOW_NAME "OgreWindow"

/**
 * @brief The OgreEngineItem class
 * Must only be constructed from within Qt QML rendering thread.
 */

class OgreEngine : public QObject
{
    Q_OBJECT

public:

    OgreEngine(QQuickWindow *window = 0);
    ~OgreEngine();

    Ogre::Root * startEngine(Ogre::String plugins_config_directory);
    void stopEngine();
    inline Ogre::Root * ogreRoot(){return m_root;}

    void activateOgreContext();
    void doneOgreContext();

    QOpenGLContext * ogreContext() const;

    QSGTexture * createTextureFromId(uint id, const QSize &size, QQuickWindow::CreateTextureOptions options = QQuickWindow::CreateTextureOption(0)) const;

private:
    Ogre::RenderWindow * m_ogreWindow;

    QQuickWindow * m_quickWindow;

    /** Pointer to QOpenGLContext to be used by Ogre. */
    QOpenGLContext * m_ogreContext;

    /** Pointer to QOpenGLContext to be restored after Ogre context. */
    QOpenGLContext * m_qtContext;

    Ogre::LogManager * m_log_manager;

    void loadOgrePlugin(Ogre::Root *ogreRoot, const QString &name);

    Ogre::Root * m_root;
protected:
    void setQuickWindow(QQuickWindow *window);
};

#endif // OGREENGINEITEM_H
