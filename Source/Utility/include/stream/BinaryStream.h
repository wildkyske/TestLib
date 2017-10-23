#pragma once
#ifndef BINARY_STREAM_H
#define BINARY_STREAM_H

#include "../UtilityExport.h"
#include <memory>

namespace XStream
{
    /*
        @. 二进制数据流
    */
    class UTILITY_EXPORT BinaryStream
    {
        enum
        {
            BS_DEFAULT_BUFFER_SIZE = 2048,
        };
    public:
        BinaryStream(int nDefAllocSize = BS_DEFAULT_BUFFER_SIZE);
        ~BinaryStream();

        /*
            @. 分配内存。
        */
        void alloc(int nBufferSize);

        /*
            @. 返回数据区指针。
        */
        unsigned char* ptr();

        /*
            @. 设置当前读取数据偏移.
        */
        void resetOffset(int nPos = 0);

        /**/
        int bufferSize() const;

        /**/
        int offset() const;

        /**/
        int filledDataSize() const;

        /**/
        void setFilledDataSize(int nSize);

        /*
            @. 从数据偏移处开始写,写入后有效数据长度和偏移一致
        */
        bool writeToStream(unsigned char* pData, int nLen);

        /*
            @. 从offset处，修改数据，但保持有效数据长度不变 
        */
        bool modifyStream(unsigned char* pData, int nLen);

        /**/
        bool readFromStream(unsigned char* pData, int nLen);

        /*
            @. 销毁数据。
        */
        void destroy();

        /*
            @. 获取当前偏移位置的数据指针
        */
        unsigned char* offsetPtr();

    protected:
        //缓存大小
        int mBufferSize;
        //缓存数据区
        unsigned char* mBufferData;
        //当前已填充的数据长度
        int mFilledDataSize;
        //当前数据读取偏移
        int mDataOffset;
    };
}
#endif
