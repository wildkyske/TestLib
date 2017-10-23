#pragma once
#ifndef MathUtil_h__
#define MathUtil_h__

#include "UtilityExport.h"

// @Brief ��ѧ�������� [12/8/2013 kyske]
//.��epsilon�Ƶ������������ֱ��ʹ��
namespace MathUtil
{
    // @Brief ��������ֵ֮�� [12/8/2013 kyske]
    template <typename T>
    void clamp(T& a, T min, T max)
    {
        if (a < min)
        {
            a = min;
        }
        else if(a > max)
        {
            a = max;
        }
    }

    // @Brief clamp to [0.0, 1.0] [12/8/2013 kyske]
    UTILITY_EXPORT void clamp(double& a);

    // @Brief clamp to [0.0f,1.0f] [12/8/2013 kyske]
    UTILITY_EXPORT void clamp(float& a);

    // @Brief �ֽڽ��� [12/8/2013 kyske]
    UTILITY_EXPORT void byteswap(unsigned char& lhs, unsigned char& rhs);

    // @Brief �ֽڽ��� [12/8/2013 kyske]
    UTILITY_EXPORT void byteswap(char& lhs, char& rhs);

    UTILITY_EXPORT void lerp(double& rRlt, double a, double b, double t);

    UTILITY_EXPORT void lerp(float& rRlt, float a, float b, double t);
}

#define XSWAP(a, b) a^=b^=a^=b

#endif // MathUtil_h__
