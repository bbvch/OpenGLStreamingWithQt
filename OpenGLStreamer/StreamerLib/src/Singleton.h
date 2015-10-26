/**************************************************************************
**   Author: Oleksiy Kasilov, bbv Software Services AG
**   Date:   10/23/2015
**   Year:   2015
**************************************************************************/

#ifndef SINGLETON
#define SINGLETON

#include <QtGlobal>
#include <QScopedPointer>

template <typename T>
class Singleton
{
public:
    static T& instance()
    {
        return *mObject;
    }

    template <typename ...Args>
    static void createInstance(Args &&...args)
    {
        mObject.reset(new T(std::forward<Args>(args)...));
    }

private:
    Singleton() {}
    ~Singleton() {}
    Q_DISABLE_COPY(Singleton)

    static QScopedPointer<T> mObject;
};

template<class T> QScopedPointer<T> Singleton<T>::mObject(0);

#endif // SINGLETON

