#include "../include/UniqueIDGenerator.h"

UniqueIDGenerator::UniqueIDGenerator()
    : mCurKey(0)
{

}

UniqueIDGenerator::~UniqueIDGenerator()
{

}

int UniqueIDGenerator::makeid()
{
    return ++mCurKey;
}


