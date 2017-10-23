#include "../include/MathUtilBase.h"

namespace MathUtil
{
    void clamp(double& a)
    {
        clamp<double>(a, 0.0, 1.0);
    }

    UTILITY_EXPORT void clamp( float& a )
    {
        clamp<float>(a, 0.0f, 1.0f);
    }

    void byteswap( unsigned char& lhs, unsigned char& rhs )
    {
        XSWAP(lhs, rhs);
    }

    void byteswap( char& lhs, char& rhs )
    {
        XSWAP(lhs, rhs);
    }

    void lerp( double& rRlt, double a, double b, double t )
    {
        rRlt = a * (1 - t) + t * b;
    }

    void lerp( float& rRlt, float a, float b, double t )
    {
        rRlt = a * (1 - t) + t * b;
    }

}
