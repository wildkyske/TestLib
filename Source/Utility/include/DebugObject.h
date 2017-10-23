#ifndef DebugObject_h__
#define DebugObject_h__

#include "UtilityExport.h"
#include "typedefs.h"
/*
	ClassName:	DebugObject
	Brief:		���е�����Ϣ�Ķ���
	Author:		kyske
	Date:		2013/12/09
*/
class UTILITY_EXPORT DebugObject
{
public:
    DebugObject();
    virtual ~DebugObject();

    // @Brief ���ô����ִ� [12/9/2013 kyske]
    void setErrorString(const tstring& strErrorInfo);

    // @Brief �����ִ� [12/9/2013 kyske]
    const tstring& errorString() const;

    // @Brief ������� [12/9/2013 kyske]
    void setErrorCode(int nCode);

    // @Brief ���ش������ [12/9/2013 kyske]
    int errorCode() const;
protected:
    tstring mStrErrInfo;    //������Ϣ

    int mErrorCode; //�������
};
#endif // DebugObject_h__