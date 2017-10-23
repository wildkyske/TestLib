#pragma once

/*
	@. brief 多变类型

	@. author Administrator . 2/22/2013 .
*/
#include <string>
#include <memory>
#include "typedefs.h"
#include <typeinfo>

class Variant
{
public:
    Variant();
    ~Variant();

    template <typename T>
    void setValue(const T& val);

    template <typename T>
    bool getValue(T& val) const;

    void destroy();

    void zero();

    bool isValid() const;

    int size() const;

    bool isShared() const;

    std::string typeString() const;

public:
    //类型构造 
    void construct(char c);
    void construct(unsigned char uc);
    void construct(short s);
    void construct(unsigned short us);
    void construct(int i);
    void construct(unsigned int i);
    void construct(long long ll);
    void construct(unsigned long long ull);
    void construct(float f);
    void construct(double d);
    void construct(void* ptr);

    //类型转换
    char toChar() const;
    unsigned char toUChar() const;
    short toShort() const;
    unsigned short toUShort() const;
    int toInt() const;
    unsigned int toUInt() const;
    long long toLongLong() const;
    unsigned long long toULongLong() const;
    float toFloat() const;
    double toDouble() const;
    void* toVoidPtr() const;
    tstring toString() const;

protected:
    union
    {
        char c;
        unsigned char uc;
        short s;
        unsigned short us;
        int i;
        unsigned int ui;
        long long ll;
        unsigned long long ull;
        float f;
        double d;
        void* ptr;
    };

    bool mSharedMemory;
    int mFixedSize;
    int mSize;
    std::string mType;
};

template <typename T>
bool Variant::getValue( T& val ) const
{
    //检查类型和大小
    if (std::string(typeid(val).name()) != mType)
    {
        return false;
    }
    int nTSize = sizeof(T);
    if (nTSize != mSize)
    {
        return false;
    }

    //TODO:
    if (mSharedMemory)
    {
        memcpy(&val, ptr, nTSize);
    }
    else
    {
        memcpy(&val, &ptr, nTSize);
    }

    return true;
}

template <typename T>
void Variant::setValue( const T& val )
{
    destroy();

    mType = std::string(typeid(T).name());
    int nTSize = sizeof(T);
    mSize = nTSize;
    mSharedMemory = nTSize > mFixedSize;

    if (mSharedMemory)
    {
        ptr = (void*)new unsigned char[mSize];
        memcpy(ptr, &val, mSize);
    }
    else
    {
        memcpy(&ptr, &val, mSize);
    }
}
