#include "../include/IxObject.h"

int NUM_INVALID_ID = -1;
int NUM_START_ID = 0x1000;
int NUM_ID_COUNTER = NUM_START_ID;


int generateUniqueID()
{
	NUM_ID_COUNTER++;
	return NUM_ID_COUNTER;
}

void setStartUniqueID(int nID)
{
	NUM_ID_COUNTER = nID;
}

void setStartID(int nStartID)
{
	NUM_START_ID = nStartID;
}

IxObject::IxObject()
	: mID(NUM_INVALID_ID)
{

}

IxObject::~IxObject()
{

}

void IxObject::setID(int nID)
{
	mID  = nID;
}

int IxObject::id()
{
	return mID;
}


