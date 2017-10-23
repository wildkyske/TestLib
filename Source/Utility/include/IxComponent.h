#ifndef IxComponent_h__
#define IxComponent_h__

#include "IxObject.h"
#include <string>

// xϵ����� [3/6/2016 Administrator]
class UTILITY_EXPORT IxComponent : public IxObject
{
public:
	virtual ~IxComponent(){}

	virtual std::string name() = 0;
};

// �����ѯ�ӿ�,������������,����NULL [3/6/2016 Administrator]
UTILITY_EXPORT IxComponent* searchComponent(const std::string& strComponentName);

// �����ѯ�ӿ�,ʹ�����ID��Ϊkey,ʧ��,����NULL [3/6/2016 Administrator]
UTILITY_EXPORT IxComponent* searchComponent(int nID);

#endif // IxComponent_h__
