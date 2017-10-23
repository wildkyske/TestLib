#ifndef IxObject_h__
#define IxObject_h__

#include "UtilityExport.h"

// x系列对象 [3/6/2016 Administrator]
class UTILITY_EXPORT IxObject
{
public:
	IxObject();
    virtual ~IxObject();

    virtual int id();

	virtual void setID(int nID);
protected:
	int mID;
};

extern "C" UTILITY_EXPORT int generateUniqueID();

extern "C" UTILITY_EXPORT void setStartUniqueID(int nID);

extern "C" UTILITY_EXPORT void setStartID(int nStartID);

UTILITY_EXPORT extern int NUM_INVALID_ID;

UTILITY_EXPORT extern int NUM_START_ID;

#endif // IObject_h__
