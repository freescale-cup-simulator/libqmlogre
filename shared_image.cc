#include <shared_image.h>


SharedImage::SharedImage(QObject *parent)
    : QObject(parent)
    , m_data(0)
{

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
        m_data = new quint8[m_size.width()*m_size.height()*4];
    }
    m_mutex.unlock();
}

quint8 *SharedImage::lock()
{
    m_mutex.lock();
    return m_data;
}

void SharedImage::unlock()
{
    m_mutex.unlock();
}
