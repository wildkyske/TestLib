#pragma once
#ifndef RAND_GEN_H
#define RAND_GEN_H

#include "UtilityExport.h"

class UTILITY_EXPORT XRandom
{
public:
    XRandom();
    ~XRandom();

    unsigned int Random(unsigned int nMaxValue);

    void SetRandomSeed(unsigned int nSeed);
public:
    static unsigned int RandomNuber(unsigned int nMaxValue = 100);

public:
    static const int KMATH_N = 624;
    static const int KMATH_M = 397;
    static const int KMATH_MATRIX_A   = 0x9908b0df;
    static const int KMATH_UPPER_MASK = 0x80000000;
    static const int KMATH_LOWER_MASK = 0x7fffffff;

    static const int KMATH_TEMPERING_MASK_B = 0x9d2c5680;
    static const int KMATH_TEMPERING_MASK_C = 0xefc60000;

    unsigned long KMATH_TEMPERING_SHIFT_U(unsigned long& y);

    unsigned long KMATH_TEMPERING_SHIFT_S(unsigned long& y);

    unsigned long KMATH_TEMPERING_SHIFT_T(unsigned long& y);

    unsigned long KMATH_TEMPERING_SHIFT_L(unsigned long& y);

private:
    unsigned long m_nMt[KMATH_N];
    int m_iMti;
};

#endif
