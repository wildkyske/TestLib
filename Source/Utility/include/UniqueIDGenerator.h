#pragma once
#ifndef UniqueIDGenerator_h__
#define UniqueIDGenerator_h__

#include "UtilityExport.h"

class UTILITY_EXPORT UniqueIDGenerator
{
public:
    UniqueIDGenerator();
    virtual ~UniqueIDGenerator();

    int makeid();
protected:
    int mCurKey;
};

#endif // UniqueIDGenerator_h__
