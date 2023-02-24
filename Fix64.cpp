//
//  Fix64.cpp
//  MathLib
//
//  Created by christ on 2020/7/8.
//  Copyright © 2020 christ. All rights reserved.
//

#include "Fix64.h"
#include <climits>
using namespace FMath;

const Fix64 Fix64::Zero = Fix64::FromInt(0);
const Fix64 Fix64::One = Fix64::FromInt(1);
const Fix64 Fix64::Half = Fix64::One / 2;
const Fix64 Fix64::MaxValue = Fix64::FromRawValue(0x00007fffffffffff);
const Fix64 Fix64::MinValue = Fix64::FromRawValue(-Fix64::MaxValue.rawValue);
const Fix64 Fix64::E = Fix64::FromRawValue(0x000000000002b7e1);;
const Fix64 Fix64::PI = Fix64::FromRawValue(0x000000000003243f);
const Fix64 Fix64::Epsilon = Fix64::FromRawValue(1);
const Fix64 Fix64::PositiveInfinity = Fix64::FromRawValue(LLONG_MAX);
const Fix64 Fix64::NegativeInfinity = Fix64::FromRawValue(LLONG_MIN);

const Fix64 Fix64::_degToRad = Fix64::FromRawValue(0x0000000000000477);
const Fix64 Fix64::_radToDeg = Fix64::FromRawValue(0x0000000000394bbf);

const Fix64 Fix64::EN1 = Fix64::One / 10;
const Fix64 Fix64::EN2 = Fix64::One / 100;
const Fix64 Fix64::EN3 = Fix64::One / 1000;
const Fix64 Fix64::EN4 = Fix64::One / 10000;
const Fix64 Fix64::EN5 = Fix64::One / 100000;

Fix64::Fix64(int value)
{
    rawValue = value * fractionFactor;
}

Fix64::Fix64(double value)
{
    rawValue = (int64_t)(value * fractionFactor);
}

Fix64::Fix64(float value)
{
    rawValue = (int64_t)(value * fractionFactor);
}

Fix64::Fix64(const Fix64& other)
{
    rawValue = other.rawValue;
}
Fix64::Fix64()
{
    rawValue = 0;
}
    
Fix64 Fix64::FromInt(int val)
{
    return Fix64(val);
}

Fix64 Fix64::FromSingle(float val)
{
    return Fix64(val);
}

Fix64 Fix64::FromDouble(double val)
{
    return Fix64(val);
}

Fix64 Fix64::DegToRad(const Fix64& angle)
{
    return angle / _radToDeg;
}

Fix64 Fix64::RadToDeg(const Fix64& rad)
{
    return rad / _degToRad;
}

int64_t Fix64::integer() const
{
    return rawValue / fractionFactor;
}

int64_t Fix64::fraction() const
{
    return rawValue % fractionFactor;
}

double Fix64::ToDouble() const
{
    return (integer() + fraction() / (double)(fractionFactor));
}

float Fix64::ToSingle() const
{
    return (integer() + fraction() / (float)(fractionFactor));
}

bool Fix64::IsInfinity() const
{
    return rawValue == PositiveInfinity.rawValue || rawValue == NegativeInfinity.rawValue;
}

bool Fix64::IsPositiveInfinity() const
{
    return rawValue == PositiveInfinity.rawValue;
}

bool Fix64::IsNegativeInfinity() const
{
    return rawValue == NegativeInfinity.rawValue;
}

Fix64 Fix64::FromRawValue(int64_t rawValue)
{
    struct Fix64 ret(0);
    ret.rawValue = rawValue;
    return ret;
}

Fix64 Fix64::FromComponents(int64_t i, int64_t f)
{
    return FromRawValue(i * fractionFactor + f);
}

void Fix64::GetIntegerAndFraction(int64_t& integer, int64_t& fraction) const
{
    fraction = rawValue % fractionFactor;
    integer = (rawValue - fraction) >> fractionBits;
}

//Fix64::operator char()
//{
//    return integer();
//}

Fix64 Fix64::operator -() const
{
    return Fix64::FromRawValue(-rawValue);
}

Fix64 FMath::operator +(const Fix64& a, const Fix64& b)
{
    return Fix64::FromRawValue(a.rawValue + b.rawValue);
}

const Fix64& FMath::operator+=(Fix64& a, const Fix64& b)
{
    a = a + b;
    return a;
}

Fix64 FMath::operator -(const Fix64& a, const Fix64& b)
{
    return Fix64::FromRawValue(a.rawValue - b.rawValue);
}

bool FMath::operator ==(const Fix64& a, const Fix64& b)
{
    return a.rawValue == b.rawValue;
}

bool FMath::operator !=(const Fix64& a, const Fix64& b)
{
    return a.rawValue != b.rawValue;
}

bool FMath::operator >(const Fix64& a, const Fix64& b)
{
    return a.rawValue > b.rawValue;
}

bool FMath::operator >=(const Fix64& a, const Fix64& b)
{
    return a.rawValue >= b.rawValue;
}

bool FMath::operator <(const Fix64& a, const Fix64& b)
{
    return a.rawValue < b.rawValue;
}

bool FMath::operator <=(const Fix64& a, const Fix64& b)
{
    return a.rawValue <= b.rawValue;
}

Fix64 FMath::operator *(const Fix64& a, const Fix64& b)
{
    int64_t f1 = a.rawValue % Fix64::fractionFactor;
    int64_t f2 = b.rawValue % Fix64::fractionFactor;

    int64_t i1 = (a.rawValue - f1) >> Fix64::fractionBits;
    int64_t i2 = (b.rawValue - f2) >> Fix64::fractionBits;

    // 推导过程
    // i1*i2*fractionFactor + i1*f2 + i2*f1 + (f1*f2)/fractionFactor
    // (i1*fractionFactor + f1)*i2 + i1*f2 + (f1*f2)/fractionFactor
    // a.rawValue*i2 + i1*f2 + (f1*f2)/fractionFactor
    int64_t r1 = ((a.rawValue * i2)) + i1 * f2 + ((f1 * f2) / Fix64::fractionFactor);

    return Fix64::FromRawValue(r1);
}

Fix64 FMath::operator*(const float a, const Fix64& b)
{
    return Fix64(a) * b;
}

Fix64 FMath::operator*(const Fix64& a, const float b)
{
    return a * Fix64(b);
}

Fix64 FMath::operator *(const Fix64& a, int b)
{
    return Fix64::FromRawValue(a.rawValue * b);
}

Fix64 FMath::operator *(int a, const Fix64& b)
{
    return Fix64::FromRawValue(a * b.rawValue);
}

const Fix64& FMath::operator*=(Fix64& a, const Fix64& b)
{
    a = a * b;
    return a;
}

Fix64 FMath::operator /(Fix64 a, Fix64 b)
{
    if (b.rawValue == 0)
    {
        b.rawValue = 1;
    }

    return Fix64::FromRawValue((a.rawValue << Fix64::fractionBits) / b.rawValue);
}

Fix64 FMath::operator /(const Fix64& a, int b)
{
    return Fix64::FromRawValue(a.rawValue / b);
}

Fix64 FMath::operator/(const Fix64& a, float b)
{
    return a / Fix64(b);
}

const Fix64& FMath::operator /=(Fix64& a, const Fix64 b)
{
    a = a / b;
    return a;
}

std::string Fix64::ToString() const
{
    return to_string(integer() + fraction() / (double)(fractionFactor));
}

int32_t Fix64::Sign()
{
    return Sign(rawValue);
}

typedef uint32_t u_int32_t;
typedef uint64_t u_int64_t;

int32_t Fix64::Sign(int64_t rawValue)
{
    if (rawValue == 0) return 0;
    else if (rawValue < 0) return -1;
    else return 1;
    
//    u_int32_t k = (u_int32_t)(((u_int64_t)(rawValue)) >> 63);
//    k ^= 1;
//
//    return (int)(k << 1) - 1;
}

Fix64 Fix64::Abs()
{
    return FromRawValue(Abs(rawValue));
}

inline int64_t Fix64::Abs(int64_t rawValue)
{
    return rawValue >= 0 ? rawValue : -rawValue;
}

Fix64 Fix64::Sqrt()
{
    return FromRawValue(Sqrt(rawValue));
}

/// <summary>
/// 1/sqrt(x)
/// </summary>
/// <returns></returns>
Fix64 Fix64::InvSqrt()
{
    return One / Sqrt();
}


int64_t Fix64::Sqrt(int64_t rawValue)
{
    if (rawValue > 0)
    {
        int64_t last_res = 0;
        int64_t y = rawValue << FMath::Fix64::fractionBits;
        int64_t res = rawValue >> 1;      // 初始值取x/2,可以提升20-25%左右的性能（rawValue为正数）
        int64_t diff = 0;

        if (res != 0)
        {
            do
            {
                last_res = res;
                res = (res + y / res) >> 1;
                diff = last_res - res;
            }
            while (diff > 1 || diff < -1);
        }

        return res;
    }
    else
    {
        return 0;
    }
}


int64_t Fix64::Sqrt(int64_t rawValue, int64_t x0)
{
    if (rawValue > 0)
    {
        int64_t last_res = 0;
        int64_t y = rawValue << fractionBits;
        int64_t res = x0;      // 初始值为外部指定的数值
        int64_t diff = 0;

        do
        {
            last_res = res;
            res = (res + y / res) >> 1;
            diff = last_res - res;
        }
        while (diff > 1 || diff < -1);

        return res;
    }
    else
    {
        return 0;
    }
}



int64_t Fix64::Sqrt(int64_t rawValue, int64_t x0, int& counter)
{
    counter = 0;

    if (rawValue > 0)
    {
        int64_t last_res = 0;
        int64_t y = rawValue << fractionBits;
        int64_t res = x0;      // 初始值为外部指定的数值
        int64_t diff = 0;

        do
        {
            ++counter;
            last_res = res;
            res = (res + y / res) >> 1;
            diff = last_res - res;
        }
        while (diff > 1 || diff < -1);

        return res;
    }
    else
    {
        return 0;
    }
}

Fix64 Fix64::Repeat(const Fix64& t, const Fix64& length)
{
    return t - length * (t / length).Floor();
}

int Fix64::Floor()
{
    // positive
    if (rawValue >= 0)
    {
        return (int)integer();
    }
    else // negative
    {
        int64_t i, f;
        GetIntegerAndFraction(i, f);

        if (f != 0) // f < 0
        {
            return (int)(i - 1);
        }
        else
        {
            return (int)i;
        }
    }
    return 0;
}







