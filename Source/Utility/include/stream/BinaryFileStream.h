#pragma once
#ifndef BINARY_FILE_STREAM_H
#define BINARY_FILE_STREAM_H

#include "BinaryStream.h"
#include <iostream>
#include <memory.h>

namespace XStream
{
    /*
        @. �������ļ�ͷ
    */
    typedef struct tagBinaryFileHeader
    {
        char szTag[2];
        //���ݳ���
        int nDataLen;
        //����
        char szReserve[58];

        tagBinaryFileHeader()
        {
            szTag[0] = 'B';
            szTag[1] = 'S';
            memset(&nDataLen, 0, sizeof(nDataLen));
            memset(szReserve, 0, sizeof(szReserve));
        }
    }BinaryFileHeader;

    /*
        @. �ļ���
    */
    class UTILITY_EXPORT BinaryFileStream
    {
    public:
        BinaryFileStream(BinaryStream& refSteam, const std::string& filePath);
        ~BinaryFileStream();

        void setFilePath(const std::string& filePath);
        std::string filePath() const;

        void saveToFile();

        void readFromFile();
    protected:

        /*
            @. ��istream�ж�ȡ�ļ�ͷ
        */
        bool __readHeader(std::istream& is);

        /*
            @. ͨ��mStreamRef��д���ļ�ͷ�ṹ
        */
        bool __writeHeader(std::ostream& os);
    protected:
        BinaryStream& mStreamRef;
        std::string mFilePath;
        BinaryFileHeader mFileHeader;
    };
}
#endif
