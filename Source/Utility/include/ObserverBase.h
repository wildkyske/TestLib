#ifndef ObserverBase_h__
#define ObserverBase_h__

#include <list>

/*
	ClassName:	ObserverBase
	Brief:		被观察者基类，类似于Subject
	Author:		kyske
	Date:		2013/05/05
*/
template <typename T>
class ObserverBase
{
public:
    ObserverBase()
    {

    }

    virtual ~ObserverBase()
    {

    }

    bool registerObserver(T* ob)
    {
        if (NULL == ob)
        {
            return false;
        }

        typename std::list<T*>::iterator it = std::find(mObserverLst.begin(), mObserverLst.end(), ob);
        if (it != mObserverLst.end())
        {
            return true;
        }

        mObserverLst.push_back(ob);

        return true;
    }

    bool unregisterObserver(T* ob)
    {
        if (NULL == ob)
        {
            return false;
        }

        typename std::list<T*>::iterator it = std::find(mObserverLst.begin(), mObserverLst.end(), ob);
        if (it == mObserverLst.end())
        {
            return true;
        }

        mObserverLst.erase(it);

        return true;
    }

protected:
    std::list<T*> mObserverLst;
};
#endif // ObserverBase_h__
