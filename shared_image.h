#ifndef SHARED_IMAGE_H
#define SHARED_IMAGE_H

#include <QObject>
#include <QMutex>
#include <QSize>
#include <QDebug>

class SharedImage : public QObject
{
    Q_OBJECT
public:

    SharedImage(QObject * parent=0);
    ~SharedImage();

    QSize size();
    void realloc(QSize size);
    quint8 * lock();
    quint8 * tryLock();
    void unlock();

private:
    QSize m_size;
    quint8 * m_data;
    QMutex m_mutex;
    QMutex m_empty_mutex;
};

#endif
