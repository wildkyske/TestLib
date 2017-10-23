#pragma once
#ifndef XDir_h__
#define XDir_h__

#include "UtilityExport.h"
#include <string>
#include <list>

namespace IOx
{
    class XFile;
    //目录类
    class UTILITY_EXPORT XDir
    {
    public:
        class DirVisitor
        {
        public:
            DirVisitor();
            virtual ~DirVisitor();

            //文件访问
            virtual bool apply(XFile& rFile);

            //目录访问
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

        //获取目录下所有文件
        bool getAllFiles(std::list<XFile>& rLstFile, const std::string& strFilter = "*.*") ;

        //获取目录下所有目录
        bool getAllDir(std::list<XDir>& rLstDir);

        //遍历文件目录,(默认递归)
        void travel(DirVisitor& rVisitor);

        //创建文件
        bool createFile(const std::string& strFileName);

        //创建目录
        bool createDir(const std::string& strDirName);

        //移除文件
        bool removeFile(const std::string& strFileName);

        //移除目录
        bool removeDir(const std::string& strDirName);

        bool valid() const;

        bool create();

        bool remove();

		// 返回上一级目录 [3/19/2016 Administrator]
		XDir prevDir();

		// +目录 [3/19/2016 Administrator]
		XDir append(const std::string& strAppendPath);

    protected:
        std::string mAbsolutePath;
        std::string mRelativePath;
    };
}

using namespace IOx;

#endif // XDir_h__

