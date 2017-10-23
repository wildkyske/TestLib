#pragma once
#ifndef	MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include <string.h>
#include <stdlib.h>
#include <memory>

#define SAFE_DELETE(s) if(NULL != s){delete s;s=NULL;}
#define SAFE_RELEASE(s) if(NULL != s){s->Release();s=NULL;}
#define SAFE_DELETE_ARRAY(s) if(NULL != s){delete[] s; s = NULL;}

namespace XCahrBase{
    namespace MemoryManager
    {
        template <class T>
        void allocateA(T*& src, int num)
        {
            src = new T[num];
        }
        template <class T>
        void allocateA(T**& src, int row, int col)
        {
            src = new T*[row];
            for (int i = 0; i < row	; i++)
            {
                src[i] = new T[col];
            }
        }
        template <class T>
        void releaseA(T*& src)
        {
            if (NULL != src)
            {
                delete[] src;
            }
        }
        template <class T>
        void releaseA(T**& src, int row)
        {
            for (int i=0; i < row; ++i)
            {
                delete[] src[i];
            }
            delete[] src;
        }
        template <class T>
        void memsetA(T**& src, int m, int n)
        {
            for (int i = 0; i < m; ++i)
            {
                for (int j = 0; j < n; ++j)
                {
                    src[i][j] = 0;
                }
            }
        }
        template <class T, class K>
        void memcpyA(T**& src, K**& des, int m, int n)
        {
            for (int i = 0; i < m; ++i)
            {
                for (int j = 0; j < n; ++j)
                {
                    des[i][j] = K(src[i][j]);
                }
            }
        }
    }
}
#endif
