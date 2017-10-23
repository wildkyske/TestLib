#pragma once
#ifndef XFile_h__
#define XFile_h__

#include "UtilityExport.h"
#include <string>
#include <fstream>

namespace IOx
{
    class XDir;
    //Ŀ¼��
    class UTILITY_EXPORT XFile
    {
    public:
        XFile(const std::string& strFilePath = "");

		//ͨ��Ŀ¼���ļ��������ļ�����
		XFile(const XDir& rDir, const std::string& strFileName);

        XFile(const XFile& rhs);

        ~XFile();

        bool operator==(const XFile& rhs);

        XFile& operator=(const XFile& rhs);

        bool exist() const;

        //����·�� [10/30/2015 Administrator]
        std::string absolutePath() const;

        //���·��
        std::string relativePath() const;

		// ����·��Ŀ¼ [2/22/2016 Administrator]
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

        //���ļ�
        bool open(bool bReadOnly = true);

        //���ļ�
        bool read(unsigned char* pBuffer, int nSize = -1);

        //д�ļ�
        bool write(unsigned char* pBuffer, int nSize);

        //�ر��ļ�
        void close();

        //�Ƿ��
        bool isOpen() const;

        bool create();

        bool remove();

        void clear();

    protected:
        std::string mAbsolutePath;
        std::string mRelativePath;
        std::ofstream mWriteStream; //д�ļ���
        std::ifstream mReadStream;  //���ļ���
        int mFileSize;
    };
}

using namespace IOx;

#endif // XFile_h__

