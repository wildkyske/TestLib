#pragma once
#ifndef MessageIDGenerator_h__
#define MessageIDGenerator_h__

#include "UniqueIDGenerator.h"

class MessageIDGenerator
{
public:
    MessageIDGenerator();
    ~MessageIDGenerator();

    static int makeID();

protected:
    static UniqueIDGenerator _staticIdGen;
};
#endif // MessageIDGenerator_h__