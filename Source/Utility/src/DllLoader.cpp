#include "../include/DllLoader.h"
#include "../include/CodeConvert.h"

#if __linux__
#include <dlfcn.h>
#endif

DllLoader::DllLoader( const std::string& strName ) 
    : mHandler(NULL)
    , mLoadStatus(DLL_LOAD_STATUS_UNLOAD)
    , mName(strName)
{

}

DllLoader::~DllLoader( void )
{
	release();
}

bool DllLoader::load( const std::string& dllpath )
{
#ifdef WIN32
    tstring strDllPath = CodeConvert::str2x(dllpath);
    mHandler = ::LoadLibrary(strDllPath.c_str());
    if (NULL == mHandler)
    {
        mLoadStatus = DLL_LOAD_STATUS_UNLOAD;
        return false;
    }

    //保存加载路径
    mDllPath = dllpath;
    
    //获取dll路径
    xchar szFileName[255 + 1] = {0};
    ::GetModuleFileName(mHandler, szFileName, 255);
    mModelPath = CodeConvert::x2str(tstring(szFileName));

    mLoadStatus = DLL_LOAD_STATUS_LOADED;
#else
    
    mHandler = dlopen(dllpath.c_str(), RTLD_LAZY|RTLD_GLOBAL);
	if (NULL == mHandler)
	{
		mLoadStatus = DLL_LOAD_STATUS_UNLOAD;
        std::cout << "dlopen failed.["  << dlerror() << "]" << std::endl;
		return false;
	}
    mLoadStatus = DLL_LOAD_STATUS_LOADED;
#endif
    return true;
}

bool DllLoader::reload()
{
    release();

    return load(mDllPath);
}

void DllLoader::release()
{
    if (NULL != mHandler)
    {
#ifdef WIN32
        ::FreeLibrary(mHandler);
#elif defined(__linux__)
		int nRet = dlclose(mHandler);
		if (nRet != 0)
		{
			//卸载失败.
            std::cout << "dlclose failed.["  << dlerror() << "]" << std::endl;
		}
#endif
        mHandler = NULL;
    }

    mLoadStatus = DLL_LOAD_STATUS_UNLOAD;
}

int DllLoader::loadStatus() const
{
    return mLoadStatus;
}

std::string& DllLoader::loadPath()
{
    return mDllPath;
}

const std::string& DllLoader::loadPath() const
{
    return mDllPath;
}

std::string& DllLoader::loadModelPath()
{
    return mModelPath;
}

const std::string& DllLoader::loadModelPath() const
{
    return mModelPath;
}

void DllLoader::setName( const std::string& strName )
{
    mName = strName;
}

std::string& DllLoader::name()
{
    return mName;
}

const std::string& DllLoader::name() const
{
    return mName;
}

void DllLoader::setUserData( const std::string& strData )
{
    mUserData = strData;
}

std::string& DllLoader::userData()
{
    return mUserData;
}

const std::string& DllLoader::userData() const
{
    return mUserData;
}

bool DllLoader::invoke(const std::string& strFuncName)
{
	if (NULL == mHandler)
	{
		return false;
	}
#ifdef WIN32

	::GetProcAddress(mHandler, strFuncName.c_str());
#elif defined(__linux__)
	
#else

#endif

	return true;
}

void* DllLoader::resolve(const std::string& strFuncName)
{
	if(mLoadStatus == DLL_LOAD_STATUS_UNLOAD || NULL == mHandler)
	{
		return NULL;
	}

	void* pAddress = NULL;
#ifdef WIN32
	pAddress = (void*)GetProcAddress(mHandler, strFuncName.c_str());
#elif defined(__linux__)
	pAddress = dlsym(mHandler, strFuncName.c_str());
    if(NULL == pAddress)
    {
        std::cout << "dlsym failed.["  << dlerror() << "]" << std::endl;
    }
#endif

	return pAddress;
}
