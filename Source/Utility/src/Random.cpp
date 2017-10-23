#include "../include/Random.h"
#include <time.h>

XRandom::XRandom(void)
    : m_iMti(KMATH_N+1)
{
    
}

XRandom::~XRandom(void)
{
}

unsigned int XRandom::Random(unsigned int nSeed)
{
    unsigned long y;
    static unsigned long mag01[2] = {0x0,KMATH_MATRIX_A};

    if (0 == nSeed)
    {
        return 0;
    }

    if (m_iMti >= KMATH_N)
    {
        int kk;
        if (KMATH_N+1 == m_iMti)
        {
            SetRandomSeed(4357);
        }

        for (kk=0;kk<KMATH_N-KMATH_M;++kk)
        {
            y = (m_nMt[kk] & KMATH_UPPER_MASK)|(m_nMt[kk+1]&KMATH_LOWER_MASK);
            m_nMt[kk] = m_nMt[kk+KMATH_M] ^ (y>>1) ^ mag01[y & 0x1];
        }

        for (;kk<KMATH_N-1;++kk)
        {
            y = (m_nMt[kk]&KMATH_UPPER_MASK)|(m_nMt[kk+1]&KMATH_LOWER_MASK);
            m_nMt[kk] = m_nMt[kk+(KMATH_M-KMATH_N)]^(y>>1)^mag01[y&0x1];
        }

        y = (m_nMt[KMATH_N - 1]&KMATH_UPPER_MASK)|(m_nMt[0] & KMATH_LOWER_MASK);
        m_nMt[KMATH_N - 1] = m_nMt[KMATH_M - 1]^(y>>1)^mag01[y & 0x1];

        m_iMti = 0;
    }

    y = m_nMt[++m_iMti];
    y ^= KMATH_TEMPERING_SHIFT_U(y);
    y ^= KMATH_TEMPERING_SHIFT_S(y) & KMATH_TEMPERING_MASK_B;
    y ^= KMATH_TEMPERING_SHIFT_T(y) & KMATH_TEMPERING_MASK_C;
    y ^= KMATH_TEMPERING_SHIFT_L(y);

    return (y % nSeed);
}

unsigned long XRandom::KMATH_TEMPERING_SHIFT_U( unsigned long& y )
{
    return y >> 11;
}

unsigned long XRandom::KMATH_TEMPERING_SHIFT_S( unsigned long& y )
{
    return y << 7;
}

unsigned long XRandom::KMATH_TEMPERING_SHIFT_T( unsigned long& y )
{
    return y << 15;
}

unsigned long XRandom::KMATH_TEMPERING_SHIFT_L( unsigned long& y )
{
    return y >> 18;
}

unsigned int XRandom::RandomNuber( unsigned int nMaxValue )
{
    static XRandom _instance;
    return _instance.Random(nMaxValue);
}

void XRandom::SetRandomSeed( unsigned int nSeed )
{
    m_nMt[0] = nSeed & 0xffffffff;
    for (m_iMti = 1; m_iMti < KMATH_N; ++m_iMti)
    {
        m_nMt[m_iMti] = (69069 * m_nMt[m_iMti - 1]) & 0xffffffff;
    }
}

