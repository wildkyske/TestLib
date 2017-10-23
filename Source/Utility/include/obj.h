#pragma once
#ifndef OBJ_H
#define OBJ_H

#include <stdlib.h>
#include <memory.h>
#include <string>
/*
	@. 该函数可作为中间变量.匹配任意类型.
*/
class obj
{
public:
	enum
	{
		MAX_BUFFER_LEN = 255,
	};
public:
    const char* ToString();
	double ToDouble();
	long ToLong();
	int ToInt();
	float ToFloat();
    bool isNull() const;
    void SetValue(const char* lpByteBuffer, int len);
public:
    obj(void);
	obj(int rhs);
	obj(const char* rhs);
    ~obj(void);
	obj& operator= (const char* rhs);
	obj& operator= (int rhs);
private:
    //Byte-Stream
    char buffer[MAX_BUFFER_LEN + 1];
};

inline obj::obj(void)
{
	memset(buffer, 0, (MAX_BUFFER_LEN + 1)*sizeof(char));
}

inline obj::obj(int rhs)
{
	memset(buffer, 0, (MAX_BUFFER_LEN + 1)*sizeof(char));
    //_itoa(rhs, buffer, MAX_BUFFER_LEN, 10);
}

inline obj::obj(const char* rhs)
{
	memset(buffer, 0, (MAX_BUFFER_LEN + 1)*sizeof(char));
	if (NULL != rhs)
	{
		memcpy(buffer, rhs, 
			strlen(rhs) > MAX_BUFFER_LEN ? MAX_BUFFER_LEN : strlen(rhs));
	}
}

inline obj::~obj(void)
{
	memset(buffer, 0, (MAX_BUFFER_LEN + 1)*sizeof(char));
}


inline obj& obj::operator =(const char* rhs)
{
	memset(buffer, 0, (MAX_BUFFER_LEN + 1)*sizeof(char));
	memcpy(buffer, rhs, 
		strlen(rhs) > MAX_BUFFER_LEN ? MAX_BUFFER_LEN : strlen(rhs));
	return *this;
}

inline obj& obj::operator =(int rhs)
{
	memset(buffer, 0, (MAX_BUFFER_LEN + 1)*sizeof(char));
    //_itoa_s(rhs, buffer, MAX_BUFFER_LEN, 10);
	return *this;
}

inline bool obj::isNull() const
{
    return NULL == buffer || buffer[0] == 0;
}

inline void obj::SetValue(const char* lpByteBuffer, int len)
{
    memset(buffer, 0, (MAX_BUFFER_LEN + 1)*sizeof(char));
    memcpy(buffer, lpByteBuffer, 
        len > MAX_BUFFER_LEN ? MAX_BUFFER_LEN : len);
    buffer[MAX_BUFFER_LEN] = 0;
}

inline int obj::ToInt()
{
    return atoi((const char*)buffer);
}

inline const char* obj::ToString()
{
    return (const char*)buffer;
}

inline double obj::ToDouble()
{
    return atof((const char*)buffer);
}

inline float obj::ToFloat()
{
	return float(ToDouble());
}
inline long obj::ToLong()
{
    return atol((const char*)buffer);
}

#endif

