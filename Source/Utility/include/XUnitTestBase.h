#pragma once
#ifndef XUnitTestBase_h__
#define XUnitTestBase_h__

#include <set>
#include <vector>
#include <sstream>
#include "Singleton.h"
#include "UtilityExport.h"

class UTILITY_EXPORT XTestObject
{
public:
    XTestObject();

    virtual ~XTestObject();

    virtual void initTestFunction() = 0;
};

class UTILITY_EXPORT XUnitTestFrameBase
{
public:
    XUnitTestFrameBase();
    virtual ~XUnitTestFrameBase();

    void registerTestClass(XTestObject* pObject);

    void unregisterTestClass(XTestObject* pObject);

    void exec();

    void addError(const std::string& strError = "");

    void addTestCount();

    void clear();

    std::string toString() const;

    bool save(const std::string& strPath = "../log/test.txt");

protected:
    int mErrorCount;
    int mTestCount;
    std::vector<std::string> mErrorInfo;
    std::set<XTestObject*> mTestObjects;
};

DECLARE_SINGLETON_CLASS(XUnitTestFrame, XUnitTestFrameBase, UTILITY_EXPORT)

template <typename T>
class XUnitTestRegisterAgent
{
public:
    XUnitTestRegisterAgent()
        : mObj(NULL)
    {
        mObj = new T();

        XUnitTestFrame::getInstancePtr()->registerTestClass(mObj);
    }

    ~XUnitTestRegisterAgent()
    {
        XUnitTestFrame::getInstancePtr()->unregisterTestClass(mObj);

        if (NULL != mObj)
        {
            delete mObj;
            mObj = NULL;
        }
    }

protected:
    T* mObj;
};

#define  DECLARE_UNIT_TEST() \
    public:\
    virtual void initTestFunction();

#define BEGIN_IMPLEMENT_TEST(className) \
    static XUnitTestRegisterAgent<className> g_Test##className; \
    void className::initTestFunction(){

#define END_IMPLEMENT_TEST() \
    } 

#define ADD_TEST_FUNCTION(funcName) funcName();

#define UNIT_TEST_ASSERT(bValue) XUnitTestFrame::getInstancePtr()->addTestCount(); \
        if(!(bValue))\
        {\
        std::stringstream ss; \
        ss << std::string(__FILE__) << " " << std::string(__FUNCTION__) << " (LINE:" <<  __LINE__ << ")"; \
        XUnitTestFrame::getInstancePtr()->addError(ss.str());} 

#endif // XUnitTestBase_h__
