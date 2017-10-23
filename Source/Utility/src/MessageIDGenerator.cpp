#include "../include/MessageIDGenerator.h"

UniqueIDGenerator MessageIDGenerator::_staticIdGen;

MessageIDGenerator::MessageIDGenerator()
{

}

MessageIDGenerator::~MessageIDGenerator()
{

}

int MessageIDGenerator::makeID()
{
    return _staticIdGen.makeid();
}
