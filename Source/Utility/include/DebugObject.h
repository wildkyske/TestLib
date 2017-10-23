#ifndef DebugObject_h__
#define DebugObject_h__

#include "UtilityExport.h"
#include "typedefs.h"
/*
	ClassName:	DebugObject
	Brief:		带有调试信息的对象
	Author:		kyske
	Date:		2013/12/09
*/
class UTILITY_EXPORT DebugObject
{
public:
    DebugObject();
    virtual ~DebugObject();

    // @Brief 设置错误字串 [12/9/2013 kyske]
    void setErrorString(const tstring& strErrorInfo);

    // @Brief 返回字串 [12/9/2013 kyske]
    const tstring& errorString() const;

    // @Brief 错误代码 [12/9/2013 kyske]
    void setErrorCode(int nCode);

    // @Brief 返回错误代码 [12/9/2013 kyske]
    int errorCode() const;
protected:
    tstring mStrErrInfo;    //错误信息

    int mErrorCode; //错误代码
};
#endif // DebugObject_h__