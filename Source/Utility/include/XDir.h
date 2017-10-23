#pragma once
#ifndef XDir_h__
#define XDir_h__

#include "UtilityExport.h"
#include <string>
#include <list>

namespace IOx
{
    class XFile;
    //Ŀ¼��
    class UTILITY_EXPORT XDir
    {
    public:
        class DirVisitor
        {
        public:
            DirVisitor();
            virtual ~DirVisitor();

            //�ļ�����
            virtual bool apply(XFile& rFile);

            //Ŀ¼����
            virtual bool apply(XDir& rDir);

            void setFilter(const std::string& rToken);

            std::string& filter();

            const std::string& filter() const;
        protected:
            std::string mFilterToken;
        };

    public:
        XDir(const std::string& = "./");
        ~XDir();

        bool exist() const;

        std::string absolutePath() const;

        std::string relativePath() const;

        void setDirPath(const std::string& strDirPath);

        static bool isAbsolutePath(const std::string& strPath);

        //��ȡĿ¼�������ļ�
        bool getAllFiles(std::list<XFile>& rLstFile, const std::string& strFilter = "*.*") ;

        //��ȡĿ¼������Ŀ¼
        bool getAllDir(std::list<XDir>& rLstDir);

        //�����ļ�Ŀ¼,(Ĭ�ϵݹ�)
        void travel(DirVisitor& rVisitor);

        //�����ļ�
        bool createFile(const std::string& strFileName);

        //����Ŀ¼
        bool createDir(const std::string& strDirName);

        //�Ƴ��ļ�
        bool removeFile(const std::string& strFileName);

        //�Ƴ�Ŀ¼
        bool removeDir(const std::string& strDirName);

        bool valid() const;

        bool create();

        bool remove();

		// ������һ��Ŀ¼ [3/19/2016 Administrator]
		XDir prevDir();

		// +Ŀ¼ [3/19/2016 Administrator]
		XDir append(const std::string& strAppendPath);

    protected:
        std::string mAbsolutePath;
        std::string mRelativePath;
    };
}

using namespace IOx;

#endif // XDir_h__

