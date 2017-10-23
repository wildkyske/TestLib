#pragma once
#ifndef XFile_h__
#define XFile_h__

#include "UtilityExport.h"
#include <string>
#include <fstream>

namespace IOx
{
    class XDir;
    //目录类
    class UTILITY_EXPORT XFile
    {
    public:
        XFile(const std::string& strFilePath = "");

		//通过目录和文件来构造文件对象
		XFile(const XDir& rDir, const std::string& strFileName);

        XFile(const XFile& rhs);

        ~XFile();

        bool operator==(const XFile& rhs);

        XFile& operator=(const XFile& rhs);

        bool exist() const;

        //绝对路径 [10/30/2015 Administrator]
        std::string absolutePath() const;

        //相对路径
        std::string relativePath() const;

		// 绝对路径目录 [2/22/2016 Administrator]
		std::string absoluteDir() const;

        int size() const;

        void dir(XDir& rDir);

        bool valid() const;

        std::string suffix() const;

        std::string baseName() const;

        std::string fileName() const;

        void setFilePath(const std::string& strFilePath);

        static bool isAbsolutePath(const std::string& strFilePath);

		static XFile getApplicationPath();

    public:

        //打开文件
        bool open(bool bReadOnly = true);

        //读文件
        bool read(unsigned char* pBuffer, int nSize = -1);

        //写文件
        bool write(unsigned char* pBuffer, int nSize);

        //关闭文件
        void close();

        //是否打开
        bool isOpen() const;

        bool create();

        bool remove();

        void clear();

    protected:
        std::string mAbsolutePath;
        std::string mRelativePath;
        std::ofstream mWriteStream; //写文件流
        std::ifstream mReadStream;  //读文件流
        int mFileSize;
    };
}

using namespace IOx;

#endif // XFile_h__

