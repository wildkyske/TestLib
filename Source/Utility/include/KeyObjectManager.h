#pragma once
#ifndef KEY_OBJECT_MANAGER_H
#define KEY_OBJECT_MANAGER_H

#include <map>
#include <vector>

/*该类不负责释放:通常用来存指针和结构*/
template <typename KeyType, typename ObjectType>
class KeyObjectManager
{
public:
    typedef std::map<KeyType, ObjectType> ObjectMap;
public:
    KeyObjectManager(void);
    virtual ~KeyObjectManager(void);

    bool insertObject(const KeyType& key, ObjectType obj);

    bool getObject(const KeyType& key, ObjectType& obj);

    bool removeObject(const KeyType& key);

    void setObjectValue(const KeyType& key, const ObjectType& obj);

    ObjectMap& objectMap()
    {
        return mObjects;
    }

    const ObjectMap& objectMap() const
    {
        return mObjects;
    }

    void cleanup();

    bool isEmpty() const;

protected:
    
    ObjectMap mObjects;
};

template <typename KeyType, typename ObjectType>
bool KeyObjectManager<KeyType, ObjectType>::isEmpty() const
{
    return mObjects.empty();
}

template <typename KeyType, typename ObjectType>
void KeyObjectManager<KeyType, ObjectType>::setObjectValue( const KeyType& key, const ObjectType& obj )
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
void KeyObjectManager<KeyType, ObjectType>::cleanup()
{
    mObjects.clear();
}

template <typename KeyType, typename ObjectType>
bool KeyObjectManager<KeyType, ObjectType>::removeObject( const KeyType& key )
{
    typename ObjectMap::iterator it = mObjects.find(key);
    if (it == mObjects.end())
    {
        return false;
    }
    mObjects.erase(it);
    return true;
}

template <typename KeyType, typename ObjectType>
bool KeyObjectManager<KeyType, ObjectType>::getObject( const KeyType& key, ObjectType& obj )
{
    typename ObjectMap::iterator it = mObjects.find(key);
    if (it == mObjects.end())
    {
        return false;
    }
    obj = it->second;
    return true;
}

template <typename KeyType, typename ObjectType>
bool KeyObjectManager<KeyType, ObjectType>::insertObject( const KeyType& key, ObjectType obj )
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
KeyObjectManager<KeyType, ObjectType>::~KeyObjectManager( void )
{
    cleanup();
}

template <typename KeyType, typename ObjectType>
KeyObjectManager<KeyType, ObjectType>::KeyObjectManager( void )
{

}

#endif
