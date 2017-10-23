#pragma once
#ifndef REFLECT_OBJECT_IMPLEMENT_H
#define REFLECT_OBJECT_IMPLEMENT_H

#include <map>
#include <set>
#include "typedefs.h"
#include "Singleton.h"

class RepInstance;
class ReflectTypeRegisterObserver;

typedef std::map<const std::string, RepInstance*> ClassMap;
typedef ClassMap::iterator ClassMapIter;

/*
	ClassName:	RepInstance_Implement
	Brief:		反射对象注册器管理(实现)
	Author:		kyske
	Date:		2014/01/14
*/
class RepInstance_Implement : public Singleton<RepInstance_Implement>
{
public:
    // @Brief 插入一个反射对象注册器 [1/14/2014 kyske]
    bool insert(const std::string& className, RepInstance* repInstace);

    // @Brief 通过名字查找发射对象注册器 [1/14/2014 kyske]
    RepInstance* find(const std::string& className);

    // @Brief 通过名称删除反射对象注册器,不会释放空间，返回对象的指针 [1/14/2014 kyske]
    RepInstance* remove(const std::string& className);

    // @Brief 通过指针删除反射对象注册器 [1/14/2014 kyske]
    bool remove(RepInstance* repInstance);

public: //通知观察者

    bool registeObserver(ReflectTypeRegisterObserver* ob);

    bool unregisteObserver(ReflectTypeRegisterObserver* ob);

    bool notifyTypeRegiste(const std::string& className);

    bool notifyTypeUnregiste(const std::string& className);
protected:
    ClassMap mClassMap;

    std::set<ReflectTypeRegisterObserver*> mTypeObs;
};
#endif
