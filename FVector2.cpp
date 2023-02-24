//
//  FVector2.cpp
//  MathLib
//
//  Created by christ on 2020/7/17.
//  Copyright © 2020 christ. All rights reserved.
//

#include "FVector2.h"
using namespace FMath;

const FVector2 FVector2::Down = FVector2(Fix64::Zero, -Fix64::One);

const FVector2 FVector2::Left = FVector2(-Fix64::One, Fix64::Zero);;

const FVector2 FVector2::Right = FVector2(Fix64::One, Fix64::Zero);

const FVector2 FVector2::Up = FVector2(Fix64::Zero, Fix64::One);

const FVector2 FVector2::Zero = FVector2(Fix64::Zero, Fix64::Zero);

const FVector2 FVector2::One = FVector2(Fix64::One, Fix64::One);

Fix64 FVector2::Magnitude()
{
    return (x * x + y * y).Sqrt();
}

Fix64 FVector2::SqrMagnitude()
{
   return x * x + y * y;
}

FVector2 FVector2::Normalized()
{
   Fix64 len = Magnitude();
   return FVector2(x / len, y / len);
}

void FVector2::Normalize()
{
   Fix64 len = Magnitude();
   x = x / len;
   y = y / len;
}

void FVector2::Scale(const FVector2& scale)
{
    x = x * scale.x;
    y = y * scale.y;
}

void FVector2::ClampMagnitude(const Fix64& maxLength)
{
    Fix64 len = Magnitude();

    if (len > maxLength)
    {
        // x / magnitude * maxLength, y / magnitude * maxLength
        // x * (maxLength / magnitude), y * (maxLength / magnitude)
        Fix64 scaleFactor = maxLength / len;

        x = x * scaleFactor;
        y = y * scaleFactor;
    }
}

bool FVector2::Equals(const FVector2& obj)
{
    return obj.x == x && obj.y == y;
}

int FVector2::GetHashCode()
{
    return Magnitude().GetHashCode();
}

void FVector2::Set(const Fix64& x, const Fix64& y)
{
    this->x = x;
    this->y = y;
}

FVector2 FMath::operator +(const FVector2& a, const FVector2& b)
{
    return FVector2(a.x + b.x, a.y + b.y);
}

FVector2 FMath::operator -(const FVector2& a)
{
    return FVector2(-a.x, -a.y);
}

FVector2 FMath::operator -(const FVector2& a, const FVector2& b)
{
    return FVector2(a.x - b.x, a.y - b.y);
}

FVector2 FMath::operator *(const Fix64& d, const FVector2& a)
{
    //return new FVector2(Fix64.Mul(a.x, d), Fix64.Mul(a.y, d));
    return FVector2(a.x * d, a.y * d);
}

FVector2 FMath::operator *(const FVector2& a, const Fix64& d)
{
    //return new FVector2(Fix64.Mul(a.x, d), Fix64.Mul(a.y, d));
    return FVector2(a.x * d, a.y * d);
}

FVector2 FMath::operator /(const FVector2& a, const Fix64& d)
{
    //return new FVector2(Fix64.Div(a.x, d), Fix64.Div(a.y, d));
    return FVector2(a.x / d, a.y / d);
}

bool FMath::operator ==(const FVector2& lhs, const FVector2& rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

bool FMath::operator !=(const FVector2& lhs, const FVector2& rhs)
{
    return lhs.x != rhs.x || lhs.y != rhs.y;
}

string FVector2::ToString()
{
    return x.ToString() + "," + y.ToString();
}

Fix64 FVector2::Distance(const FVector2& a, const FVector2& b)
{
    Fix64 dx = a.x - b.x;
    Fix64 dy = a.y - b.y;

    return (dx * dx + dy * dy).Sqrt();
}

Fix64 FVector2::SqrDistance(const FVector2& a, const FVector2& b)
{
    Fix64 dx = a.x - b.x;
    Fix64 dy = a.y - b.y;

    return dx * dx + dy * dy;
}

Fix64 FVector2::Dot(const FVector2& a, const FVector2& b)
{
    return a.x * b.x + a.y * b.y;
}

FVector2 FVector2::Scale(const FVector2& a, const FVector2& b)
{
    return FVector2(a.x * b.x, a.y * b.y);
}

FVector2 FVector2::Lerp(const FVector2& a, const FVector2& b, Fix64 t)
{
    return FVector2(
        Fix64::Lerp(a.x, b.x, t),
        Fix64::Lerp(a.y, b.y, t));
}

FVector2 FVector2::LerpClamped(const FVector2& a, const FVector2& b, Fix64 t)
{
    if (t > Fix64::One)
    {
        t = Fix64::One;
    }
    else if (t < Fix64::Zero)
    {
        t = Fix64::Zero;
    }

    return Lerp(a, b, t);
}

FVector2 FVector2::Max(const FVector2& a, const FVector2& b)
{
    return FVector2(Fix64::Max(a.x, b.x), Fix64::Max(a.y, b.y));
}

FVector2 FVector2::Min(const FVector2& a, const FVector2& b)
{
    return FVector2(Fix64::Min(a.x, b.x), Fix64::Min(a.y, b.y));
}

FVector2 FVector2::Reflect(const FVector2& inDirection, const FVector2& inNormal)
{
    Fix64 projectionLen2 = Dot(inDirection, inNormal) * 2;
    FVector2 v = inNormal * projectionLen2;

    return inDirection +  v;
}

FVector2 FVector2::Project(const FVector2& v, const FVector2& n)
{
    return n * Dot(v, n);
}
