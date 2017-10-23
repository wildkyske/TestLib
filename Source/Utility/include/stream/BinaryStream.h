#pragma once
#ifndef BINARY_STREAM_H
#define BINARY_STREAM_H

#include "../UtilityExport.h"
#include <memory>

namespace XStream
{
    /*
        @. ������������
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
            @. �����ڴ档
        */
        void alloc(int nBufferSize);

        /*
            @. ����������ָ�롣
        */
        unsigned char* ptr();

        /*
            @. ���õ�ǰ��ȡ����ƫ��.
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
            @. ������ƫ�ƴ���ʼд,д�����Ч���ݳ��Ⱥ�ƫ��һ��
        */
        bool writeToStream(unsigned char* pData, int nLen);

        /*
            @. ��offset�����޸����ݣ���������Ч���ݳ��Ȳ��� 
        */
        bool modifyStream(unsigned char* pData, int nLen);

        /**/
        bool readFromStream(unsigned char* pData, int nLen);

        /*
            @. �������ݡ�
        */
        void destroy();

        /*
            @. ��ȡ��ǰƫ��λ�õ�����ָ��
        */
        unsigned char* offsetPtr();

    protected:
        //�����С
        int mBufferSize;
        //����������
        unsigned char* mBufferData;
        //��ǰ���������ݳ���
        int mFilledDataSize;
        //��ǰ���ݶ�ȡƫ��
        int mDataOffset;
    };
}
#endif
