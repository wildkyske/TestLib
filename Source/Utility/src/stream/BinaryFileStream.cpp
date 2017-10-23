#include "../../include/stream/BinaryFileStream.h"
#include <fstream>

namespace XStream
{
    BinaryFileStream::BinaryFileStream( BinaryStream& refSteam,
        const std::string& filePath ) 
        : mStreamRef(refSteam)
        , mFilePath(filePath)
    {

    }

    BinaryFileStream::~BinaryFileStream()
    {

    }

    void BinaryFileStream::setFilePath(const std::string& filePath)
    {
        mFilePath = filePath;
    }

    std::string BinaryFileStream::filePath() const
    {
        return mFilePath;
    }

    void BinaryFileStream::saveToFile()
    {
        std::ofstream os;
        os.open(mFilePath.c_str(), std::ios::out | std::ios::binary);
        if (os.fail())
        {
            return;
        }
        __writeHeader(os);
        //TODO:
        os.write((char*)mStreamRef.ptr(), mStreamRef.filledDataSize());

        os.close();
    }

    void BinaryFileStream::readFromFile()
    {
        std::ifstream is;
        is.open(mFilePath.c_str(), std::ios::in | std::ios::binary);
        if (is.fail())
        {
            return;
        }
        __readHeader(is);
        //TODO:
        char* szBuf = new char[mFileHeader.nDataLen];
        is.read(szBuf, mFileHeader.nDataLen);
        mStreamRef.writeToStream((unsigned char*)szBuf, mFileHeader.nDataLen);
        delete[] szBuf;
        
        is.close();
    }

    bool BinaryFileStream::__readHeader(std::istream& is)
    {
        if (is.fail())
        {
            return false;
        }
        is.read((char*)&mFileHeader, sizeof(mFileHeader));
        return true;
    }

    bool BinaryFileStream::__writeHeader(std::ostream& os)
    {
        mFileHeader.nDataLen = mStreamRef.filledDataSize();
        os.write((const char*)&mFileHeader, sizeof(mFileHeader));
        return true;
    }

}
