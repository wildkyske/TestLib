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
	Brief:		�������ע��������(ʵ��)
	Author:		kyske
	Date:		2014/01/14
*/
class RepInstance_Implement : public Singleton<RepInstance_Implement>
{
public:
    // @Brief ����һ���������ע���� [1/14/2014 kyske]
    bool insert(const std::string& className, RepInstance* repInstace);

    // @Brief ͨ�����ֲ��ҷ������ע���� [1/14/2014 kyske]
    RepInstance* find(const std::string& className);

    // @Brief ͨ������ɾ���������ע����,�����ͷſռ䣬���ض����ָ�� [1/14/2014 kyske]
    RepInstance* remove(const std::string& className);

    // @Brief ͨ��ָ��ɾ���������ע���� [1/14/2014 kyske]
    bool remove(RepInstance* repInstance);

public: //֪ͨ�۲���

    bool registeObserver(ReflectTypeRegisterObserver* ob);

    bool unregisteObserver(ReflectTypeRegisterObserver* ob);

    bool notifyTypeRegiste(const std::string& className);

    bool notifyTypeUnregiste(const std::string& className);
protected:
    ClassMap mClassMap;

    std::set<ReflectTypeRegisterObserver*> mTypeObs;
};
#endif
