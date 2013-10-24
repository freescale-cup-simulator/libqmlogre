#include <shared_image.h>


SharedImage::SharedImage(QObject *parent)
    : QObject(parent)
    , m_data(0)
{
    m_empty_mutex.lock();
}

SharedImage::~SharedImage()
{
    if(m_data)
        delete[] m_data;
}

QSize SharedImage::size()
{
    return m_size;
}

void SharedImage::realloc(QSize size)
{
    m_mutex.lock();
    if(size!=m_size)
    {
        if(m_data)
            delete[] m_data;
        m_size=size;
        //qDebug()<<"Shared image size: "<<m_size;
        m_data = new quint8[m_size.width()*m_size.height()*4];
    }
    m_mutex.unlock();
}

quint8 *SharedImage::lock()
{
    m_mutex.lock();
    return m_data;
}

quint8 *SharedImage::tryLock()
{
    if(!m_mutex.tryLock())
        return 0;
    return m_data;
}

void SharedImage::unlock()
{
    m_mutex.unlock();
    m_empty_mutex.unlock();
}
