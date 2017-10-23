#pragma once
#ifndef SMART_PTR_H
#define SMART_PTR_H

template <class T> class SmartPtr;

template <class T> class IRefCount
{
    friend class SmartPtr<T>;
protected:
    virtual void AddRef() = 0;
    virtual void Release() = 0;
    virtual T* GetPtr() const = 0;
};

template <class T> class IRefCountImpl : public IRefCount<T>
{
protected:
    virtual void AddRef()
    {
        ++m_iCount;
    }
    virtual void Release()
    {
        m_iCount--;
        if (m_iCount <= 0)
        {
            Destroy();
        }
    }
    virtual T* GetPtr() const 
    {
        return ((T*)this);
    }
    virtual void Destroy()
    {
        if (NULL != GetPtr())
        {
            delete GetPtr();
        }
    }
    IRefCountImpl() : m_iCount(0)
    {

    }
private:
    int m_iCount;
};

template < class T>
class SmartPtr
{
    class RefCounter : public IRefCountImpl<T>
    {
    public:
        RefCounter(T* ptr) : m_lpPtr(ptr)
        {

        }
        virtual ~RefCounter()
        {
            IRefCountImpl<T>::Destroy();
        }

    protected:
        virtual T* GetPtr() const 
        {
            return m_lpPtr;
        }
    private:
        T* m_lpPtr;
    };
public:
    void Assign(void* ptr)
    {
        if (NULL == ptr)
        {
            Assign((IRefCount<T> *)NULL);
        }
        else
        {
            Assign(new RefCounter(static_cast<T*>(ptr)));
        }
    }

    void Assign(IRefCount<T>* refcount)
    {
        if (NULL != refcount)
        {
            refcount->AddRef();
        }
        IRefCount<T>* oldref = m_iRefCount;
        m_iRefCount = refcount;
        if (NULL != oldref)
        {
            oldref->Release();
        }
    }
public:
    SmartPtr(void) : m_iRefCount(NULL)
    {

    }
    SmartPtr(T* ptr) : m_iRefCount(NULL)
    {
        Assign(ptr);
    }
    SmartPtr(const SmartPtr& sp)
    {
        m_iRefCount = NULL;
        Assign(sp.m_iRefCount);
    }
    virtual ~SmartPtr(void)
    {
        Assign((IRefCount<T>*)NULL);
    }

    T* GetPtr() const 
    {
        return NULL == m_iRefCount ? NULL : m_iRefCount->GetPtr();
    }

    // ÊÇ·ñÓÐÐ§ [3/23/2014 Administrator]
    bool IsValid() const
    {
        return NULL != GetPtr();
    }

    SmartPtr& operator= (const SmartPtr& sp)
    {
        Assign(sp.m_iRefCount);
        return *this;
    }
    SmartPtr& operator= (T* ptr)
    {
        Assign(ptr);
        return *this;
    }

    T* operator->()
    {
        return GetPtr();
    }
    operator T* () const 
    {
        return GetPtr();
    }

    bool operator!() 
    {
        return GetPtr()==NULL;
    }
    bool operator==(const SmartPtr& sp)
    {
        return sp.GetPtr()==GetPtr();
    }
    bool operator!=(const SmartPtr& sp)
    {
        return sp.GetPtr()!=GetPtr();
    }
private:
    IRefCount<T> *m_iRefCount;
};

#endif







