#ifndef IxComponent_h__
#define IxComponent_h__

#include "IxObject.h"
#include <string>

// x系列组件 [3/6/2016 Administrator]
class UTILITY_EXPORT IxComponent : public IxObject
{
public:
	virtual ~IxComponent(){}

	virtual std::string name() = 0;
};

// 组件查询接口,如果组件不存在,返回NULL [3/6/2016 Administrator]
UTILITY_EXPORT IxComponent* searchComponent(const std::string& strComponentName);

// 组件查询接口,使用组件ID作为key,失败,返回NULL [3/6/2016 Administrator]
UTILITY_EXPORT IxComponent* searchComponent(int nID);

#endif // IxComponent_h__
