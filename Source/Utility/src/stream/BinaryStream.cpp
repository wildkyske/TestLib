#include "../../include/stream/BinaryStream.h"
#include <string.h>
#include <memory>

namespace XStream
{
    BinaryStream::BinaryStream(int nDefAllocSize) 
        : mBufferData(NULL)
        , mBufferSize(0)
        , mDataOffset(0)
        , mFilledDataSize(0)
    {
        alloc(nDefAllocSize);
    }

    BinaryStream::~BinaryStream()
    {
        destroy();
    }

    void BinaryStream::alloc(int nBufferSize)
    {
        destroy();

        mBufferSize = nBufferSize;
        mBufferData = new unsigned char[mBufferSize];
    }

    unsigned char* BinaryStream::ptr()
    {
        return mBufferData;
    }

    void BinaryStream::resetOffset(int nPos)
    {
        mDataOffset = nPos;
    }

    int BinaryStream::bufferSize() const
    {
        return mBufferSize;
    }

    int BinaryStream::offset() const
    {
        return mDataOffset;
    }

    int BinaryStream::filledDataSize() const
    {
        return mFilledDataSize;
    }

    void BinaryStream::setFilledDataSize(int nSize)
    {
        mFilledDataSize = nSize;
    }

    bool BinaryStream::writeToStream(unsigned char* pData, int nLen)
    {
        if (mFilledDataSize + nLen > mBufferSize)
        {
            return false;
        }

        memcpy(offsetPtr(), pData, nLen);
        mDataOffset += nLen;
        //写入后，有效数据长度变为和Offset一致
        mFilledDataSize = mDataOffset;
        return true;
    }

    bool BinaryStream::modifyStream(unsigned char* pData, int nLen)
    {
        if (mFilledDataSize + nLen > mBufferSize)
        {
            return false;
        }

        memcpy(offsetPtr(), pData, nLen);
        mDataOffset += nLen;
        if (mDataOffset > mFilledDataSize)
        {
            mFilledDataSize = mDataOffset;
        }
        return true;
    }

    bool BinaryStream::readFromStream(unsigned char* pData, int nLen)
    {
        memcpy(pData, offsetPtr(), nLen);
        mDataOffset += nLen;
        return true;
    }

    void BinaryStream::destroy()
    {
        if (NULL != mBufferData)
        {
            delete[] mBufferData;
            mBufferData = NULL;
        }
        mBufferSize = 0;
        mDataOffset = 0;
        mFilledDataSize = 0;
    }

    unsigned char* BinaryStream::offsetPtr()
    {
        unsigned char* ptrOffsetData = mBufferData;
        ptrOffsetData += mDataOffset;
        return ptrOffsetData;
    }
}
