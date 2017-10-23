#pragma once
#ifndef EXIO_H
#define EXIO_H

#include "base_constant.h"
//-------------------------------------------
//
//-------------------------------------------

#include "StlUtil.h"
#include "MemoryManager.h"
#if defined(WIN32)
#include <Windows.h>
#include <ShellAPI.h>
#include <Winbase.h>
#include <tchar.h>
#include <io.h>
#else
#include <linux/types.h>
#include <dirent.h>
#include <unistd.h>
#include <memory.h>
#endif
namespace ExIO
{
#if defined(WIN32)
inline void getFilesOnPath(const tstring& path,
    STRING_LIST& filenames,
    const tstring& filter = _TX("*.*"),
    unsigned int fileType = _A_ARCH)
{
    long flag;
    _tfinddata_t fd;
    tstring temp(path);
    tstring::size_type index = path.find_last_of(_TX("/"));
    if (path.length()-1 != index && -1 != index)
    {
        temp += _T("/");
    }
    temp += filter;
    if (-1 == (flag = _tfindfirst(temp.c_str(), &fd)))
    {
        return ;
    }
    do
    {
        if (-1 == fileType || fd.attrib == fileType)
        {
            filenames.push_back(fd.name);
        }
    } while (0 == _tfindnext(flag, &fd));

    _findclose(flag);
}

inline void getFilesOnPathIterator(STRING_LIST& target,
    const tstring& path,
    const tstring& filter = _TX("*.*"))
{
    long flag;
    _tfinddata_t fd;
    tstring temp(path);
    tstring::size_type index = path.find_last_of(_TX("/"));
    if (path.length()-1 != index && -1 != index)
    {
        temp += _TX("/");
    }
    tstring temp2(temp);
    temp += filter;
    if (-1 == (flag = _tfindfirst(temp.c_str(), &fd)))
    {
        return ;
    }
    do
    {
        target.push_back(temp2 + fd.name);
        if (_A_SUBDIR == fd.attrib
            && 0 != _tcscmp(_TX("."), fd.name)
            && 0 != _tcscmp(_TX(".."), fd.name)
            && 0 != _tcscmp(_TX("..."), fd.name))
        {
            getFilesOnPathIterator(target, temp2 + fd.name, filter);
        }
    } while (0 == _tfindnext(flag, &fd));

    _findclose(flag);
    //subdir
    //fd.attrib == _A_SUBDIR;_A_RDONLY;_A_SYSTEM;_A_NORMAL;_A_ARCH;
}

inline tstring getCurrentModulePath()
{
    /* param 1 means a exe-file. */
    TCHAR szPath[255 + 1] = {0};
    if (GetModuleFileName(NULL, szPath, 255)<=0)
    {
        return tstring();
    }
    return tstring(szPath);
}
inline tstring getCurrentPath()
{
    TCHAR szPath[255 + 1] = {0};
    if (GetCurrentDirectory(255, szPath) <= 0)
    {
        return tstring();
    }

    return tstring(szPath);
}
inline bool removeFile(const tstring& path)
{
    //1.deal with the LPCSTR
    int MAX_SIZE = path.length() + 2;
    TCHAR* szPath = new TCHAR[MAX_SIZE + 1];
    memset(szPath, 0, MAX_SIZE + 1);
    memcpy(szPath, path.c_str(), path.length());

    //tip
    tcout<<_T("deleting file ")<<path.c_str()<<_T("  ...")<<std::endl;
    //2.do good thing
    SHFILEOPSTRUCT shop={0};
    shop.hwnd = HWND_DESKTOP;
    shop.fFlags = FOF_ALLOWUNDO | FOF_NOCONFIRMATION;
    shop.pFrom = szPath;
    shop.pTo = NULL;
    shop.wFunc = FO_DELETE;
    int result = SHFileOperation(&shop);
    delete[] szPath;
    return 0 == result;
}

inline bool existFile(LPCXSTR strPath)
{
    return -1 != _taccess(strPath, 0);
}

inline bool existFile(const tstring& strPath)
{
    return -1 != _taccess(strPath.c_str(), 0);
}

inline void pause()
{
    system("pause");
}
#else
inline void getFilesOnPath(const std::string& path,
    std::list<std::string>& lstFileName, const std::string& filter = "*.*")
{
    DIR* fd = opendir(path.c_str());
    if(NULL == fd) return;
    struct dirent*  dirptr = NULL;
    while(NULL != (dirptr = readdir(fd)))
    {
        lstFileName.push_back(std::string(dirptr->d_name));
    }
    closedir(fd);
}

inline void pause(){}

inline bool existFile(const char* strPath)
{
    return -1 != access(strPath, 0);
}

#endif
}
namespace ExIO{
    /* eraser. */
    inline void eraserStringBySuffix(STRING_LIST& target,
        const tstring& suffix)
    {
        for (STRING_LIST_ITER it = target.begin(); 
            it != target.end(); )
        {
            if (stlu::isEndWith(*it, suffix))
            {
                it = target.erase(it);
            }else
            {
                ++it;
            }
        }
        
    }
    /* eraser not. */
    inline void eraserStringNotSuffix(STRING_LIST& target, 
        const tstring& suffix)
    {
        for (STRING_LIST_ITER it = target.begin(); 
            it != target.end(); )
        {
            if (!stlu::isEndWith(*it, suffix))
            {
                it = target.erase(it);
            }else
            {
                ++it;
            }
        }
    }
    /* eraser not && iterator. */
    inline void eraserStringNotSuffix(STRING_LIST& target, 
        const STRING_LIST& suffix)
    {
        for (STRING_LIST_ITER it = target.begin(); 
            it != target.end(); )
        {
            bool needEraser = true;
            for (STRING_LIST_CONST_ITER itor = suffix.begin(); 
                itor != suffix.end(); ++itor)
            {
                if (stlu::isEndWith(*it, *itor))
                {
                    needEraser = false;
                    break;
                }
            }

            if (needEraser)
            {
                it = target.erase(it);
            }else
            {
                ++it;
            }
        }
    }
    //remove files linux && window
    inline int removeFileEx(const tstring& path)
    {
        return remove((char*)path.c_str());
    }
    //load a struct from a file
    template<class T>
    long readFile(T& stData, const char* path)
    {
        FILE* fp = NULL;
        if (NULL == (fp = fopen(path, "r")))
        {
            return -1;
        }
        fread(&stData, sizeof(T), 1, fp);
        fclose(fp);
        return 0;
    }
    //write a struct to a file
    template<class T>
    long writeFile(const T& stData, const char* path)
    {
        FILE* fp = NULL;
        if (NULL == (fp = fopen(path, "w")))
        {
            return -1;
        }
        fwrite(&stData, sizeof(T), 1, fp);
        fclose(fp);
        return 0;
    }
    //
    typedef struct stDynamicData
    {
        unsigned char* buf;
        int len;

        unsigned char* alloc(int l)
        {
            len = l;
            buf = new unsigned char[l + 1];
            memset(buf, 0x00, (l+1) * sizeof(unsigned char));
            return buf;
        }

        void copy(unsigned char* src, int len)
        {
            if (!isDestroyed())
            {
                destroy();
            }

            alloc(len);

            memcpy(buf, src, len);            
        }

        void copyTo(unsigned char* dest, int enoughBuffer = 0)
        {
            if (enoughBuffer != 0 && enoughBuffer < len)
            {
                return;
            }
            memcpy(dest, buf, len);            
        }

        void set(unsigned char value)
        {
            memset(buf, value, len + 1);
        }

        void zero()
        {
            set(0);
        }

        stDynamicData() : buf(NULL), len(0) {}
        ~stDynamicData()
        {
            destroy();
        }
        void destroy()
        {
            if (NULL != buf)
            {
                delete[] buf;
                buf = NULL;
            }

            len = 0;
        }
        bool isDestroyed() const
        {
            return NULL == buf && 0 == len;
        }
    }DYN_DATA, *LP_DYN_DATA;

    inline int fileReader(const char* path, DYN_DATA& data)
    {
        FILE* fp = NULL;
        if(NULL == (fp = fopen(path, "rb")))
        {
            return -1;
        }
        fseek(fp, 0, SEEK_END);
        int len = ftell(fp);
        fseek(fp, 0, SEEK_SET);
        unsigned char* pBuf = data.alloc(len);
        while(!feof(fp))
        {
            fread(pBuf, 1, 1, fp);
            pBuf += 1;
        }
        fclose(fp);
        return len;
    }

    inline int fileSize(const char* path)
    {
        FILE* fp = NULL;
        if(NULL == (fp = fopen(path, "rb")))
        {
            return -1;
        }
        fseek(fp, 0, SEEK_END);
        int len = ftell(fp);
        fclose(fp);
        return len;
    }

    inline int fileReaderEx(const char* path, DYN_DATA& data)
    {
        FILE* fp = NULL;
        if (NULL == (fp = fopen(path, "rb")))
        {
            return -1;
        }
        fseek(fp, 0, SEEK_END);
        int len = ftell(fp);
        fseek(fp, 0, SEEK_SET);
        unsigned char* pBuf = data.alloc(len);
        fread(pBuf, len, 1, fp);
        fclose(fp);
        return len;        
    }

    inline void fileWrite(const char* path, const DYN_DATA& data)
    {
        FILE* fp = NULL;
        if (NULL == (fp = fopen(path, "wb")))
        {
            return ;
        }
        fwrite(data.buf, data.len, 1, fp);
        fclose(fp);
    }
}


namespace Lazy
{
    inline void TARCE(const std::string& msg, std::ostream& os = std::cout)
    {
        os<<msg<<std::endl;
    }

    inline void _sleep(int ms)
    {
#if defined(WIN32)
        Sleep(ms);
#else
        sleep(ms);
#endif
    }
}


#endif

