#pragma once
#ifndef KEY_POINTER_MANAGER_H
#define KEY_POINTER_MANAGER_H

#include <map>
#include "typedefs.h"

/*
    @. 该类用来存new的对象
*/
template <typename KeyType, typename ObjectType>
class KeyPointerManager
{
public:
    typedef std::map<KeyType, ObjectType*> ObjectMap;
public:
    KeyPointerManager(void);
    virtual ~KeyPointerManager(void);

    bool insertObject(const KeyType& key, ObjectType* obj);

    bool getObject(const KeyType& key, ObjectType*& obj ) const;

    ObjectType* getObject(const KeyType& key) const;

    bool removeObject(const KeyType& key);

    void setObjectValue(const KeyType& key, ObjectType* obj);

    virtual void cleanup();

    std::map<KeyType, ObjectType*>& objectMap();

    const std::map<KeyType, ObjectType*>& objectMap() const;

protected:
    ObjectMap mObjects;
};

template <typename KeyType, typename ObjectType>
const std::map<KeyType, ObjectType*>& KeyPointerManager<KeyType, ObjectType>::objectMap() const
{
    return mObjects;
}

template <typename KeyType, typename ObjectType>
std::map<KeyType, ObjectType*>& KeyPointerManager<KeyType, ObjectType>::objectMap()
{
    return mObjects;
}

template <typename KeyType, typename ObjectType>
void KeyPointerManager<KeyType, ObjectType>::setObjectValue( const KeyType& key, ObjectType* obj )
{
    typename ObjectMap::iterator it = mObjects.find(key);
    if (it == mObjects.end())
    {
        mObjects.insert(std::make_pair(key, obj));
    }else
    {
        it->second = obj;
    }
}

template <typename KeyType, typename ObjectType>
ObjectType* KeyPointerManager<KeyType, ObjectType>::getObject( const KeyType& key ) const
{
     typename ObjectMap::const_iterator it = mObjects.find(key);
    if (it == mObjects.end())
    {
        return NULL;
    }
    return it->second;
}

template <typename KeyType, typename ObjectType>
bool KeyPointerManager<KeyType, ObjectType>::getObject( const KeyType& key, ObjectType*& obj ) const
{
     typename  ObjectMap::const_iterator it = mObjects.find(key);
    if (it == mObjects.end())
    {
        return false;
    }
    obj = it->second;
    return true;
}

template <typename KeyType, typename ObjectType>
void KeyPointerManager<KeyType, ObjectType>::cleanup()
{
    for ( typename ObjectMap::iterator it = mObjects.begin();
        it != mObjects.end(); ++it)
    {
        ObjectType* ptr = it->second;
        if (NULL != ptr)
        {
            delete ptr;
        }
    }

    mObjects.clear();
}

template <typename KeyType, typename ObjectType>
bool KeyPointerManager<KeyType, ObjectType>::removeObject( const KeyType& key )
{
     typename ObjectMap::iterator it = mObjects.find(key);
    if (it == mObjects.end())
    {
        return false;
    }

    if (NULL != it->second)
    {
        delete it->second;
    }

    mObjects.erase(it);
    return true;
}

template <typename KeyType, typename ObjectType>
bool KeyPointerManager<KeyType, ObjectType>::insertObject( const KeyType& key, ObjectType* obj )
{
     typename ObjectMap::iterator it = mObjects.find(key);
    if (it != mObjects.end())
    {
        return false;
    }
    mObjects.insert(std::make_pair(key, obj));
    return true;
}

template <typename KeyType, typename ObjectType>
KeyPointerManager<KeyType, ObjectType>::~KeyPointerManager( void )
{
    cleanup();
}

template <typename KeyType, typename ObjectType>
KeyPointerManager<KeyType, ObjectType>::KeyPointerManager( void ) 
{

}

#endif
