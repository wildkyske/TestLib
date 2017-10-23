#include "../include/variant.h"
#include "../include/StlUtil.h"
#include <string.h>

Variant::Variant() 
    : mFixedSize(sizeof(long long))
    , mSize(mFixedSize)
    , mSharedMemory(false)
{

}

Variant::~Variant()
{

}

void Variant::destroy()
{
    if (mSharedMemory)
    {
        free(ptr);
        mSharedMemory = false;
        memset(&ptr, 0, mFixedSize);
    }

    mType = "";
    mSize = 0;
}

void Variant::zero()
{
    if (mSharedMemory)
    {
        memset(ptr, 0, mSize);
    }
    else
    {
        memset(&ptr, 0, mFixedSize);
    }
}

bool Variant::isValid() const
{
    return mSize == 0 || mType == "";
}

int Variant::size() const
{
    return mSize;
}

bool Variant::isShared() const
{
    return mSharedMemory;
}

std::string Variant::typeString() const
{
    return mType;
}

void Variant::construct( char c )
{
    mSize = sizeof(c);
    mType = std::string(typeid(c).name());
    mSharedMemory = false;
    this->c = c;
}

void Variant::construct( unsigned char uc )
{
    mSize = sizeof(uc);
    mType = std::string(typeid(uc).name());
    mSharedMemory = false;
    this->uc = uc;
}

void Variant::construct( short s )
{
    mSize = sizeof(s);
    mType = std::string(typeid(s).name());
    mSharedMemory = false;
    this->s = s;
}

void Variant::construct( unsigned short us )
{
    mSize = sizeof(us);
    mType = std::string(typeid(us).name());
    mSharedMemory = false;
    this->us = us;
}

void Variant::construct( int i )
{
    mSize = sizeof(i);
    mType = std::string(typeid(i).name());
    mSharedMemory = false;
    this->i = i;
}

void Variant::construct( unsigned int ui )
{
    mSize = sizeof(ui);
    mType = std::string(typeid(ui).name());
    mSharedMemory = false;
    this->ui = ui;
}

void Variant::construct( long long ll )
{
    mSize = sizeof(ll);
    mType = std::string(typeid(ll).name());
    mSharedMemory = false;
    this->ll = ll;
}

void Variant::construct( unsigned long long ull )
{
    mSize = sizeof(ull);
    mType = std::string(typeid(ull).name());
    mSharedMemory = false;
    this->ull = ull;
}

void Variant::construct( float f )
{
    mSize = sizeof(f);
    mType = std::string(typeid(f).name());
    mSharedMemory = false;
    this->f = f;
}

void Variant::construct( double d )
{
    mSize = sizeof(d);
    mType = std::string(typeid(d).name());
    mSharedMemory = false;
    this->d = d;
}

void Variant::construct( void* ptr )
{
    mSize = sizeof(ptr);
    mType = std::string(typeid(ptr).name());
    mSharedMemory = false;
    this->ptr = ptr;
}

//--

char Variant::toChar() const
{
    return c;
}

unsigned char Variant::toUChar() const
{
    return uc;
}

short Variant::toShort() const
{
    return s;
}

unsigned short Variant::toUShort() const
{
    return us;
}

int Variant::toInt() const
{
    return i;
}

unsigned int Variant::toUInt() const
{
    return ui;
}

long long Variant::toLongLong() const
{
    return ll;
}

unsigned long long Variant::toULongLong() const
{
    return ull;
}

float Variant::toFloat() const
{
    return f;
}

double Variant::toDouble() const
{
    return d;
}

void* Variant::toVoidPtr() const
{
    return ptr;
}

tstring Variant::toString() const
{
    return stlu::toString<int>(i);
}
