//
//  FVector4.cpp
//  MathLib
//
//  Created by christ on 2020/7/17.
//  Copyright © 2020 christ. All rights reserved.
//

#include "FVector4.h"
using namespace FMath;

const FVector4 Zero = FVector4(Fix64::Zero, Fix64::Zero, Fix64::Zero, Fix64::Zero);

const FVector4 One = FVector4(Fix64::One, Fix64::One, Fix64::One, Fix64::One);

Fix64 FVector4::Magnitude() const
{
    return (x * x + y * y + z * z + w * w).Sqrt();
}

Fix64 FVector4::SqrMagnitude() const
{
    return x * x + y * y + z * z + w * w;
}

FVector4 FVector4::Normalized() const
{
    Fix64 len = Magnitude();
    return FVector4(x / len, y / len, z / len, w / len);
}

string FVector4::ToString()
{
    return x.ToString() + "," + y.ToString() + "," + z.ToString() + "," + w.ToString();
}

bool FVector4::Equals(const FVector4& obj)
{
    return obj.x == x &&
           obj.y == y &&
           obj.z == z &&
           obj.w == w;
}

int FVector4::GetHashCode()
{
    return Magnitude().GetHashCode();
}

void FVector4::Normalize()
{
    Fix64 len = Magnitude();
    x = x / len;
    y = y / len;
    z = z / len;
    w = w / len;
}

void FVector4::Scale(const FVector4& scale)
{
    x = x * scale.x;
    y = y * scale.y;
    z = z * scale.z;
    w = w * scale.w;
}

void FVector4::Set(const Fix64& x, const Fix64& y, const Fix64& z, const Fix64& w)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

FVector4 FMath::operator +(const FVector4& a, const FVector4& b)
{
    return FVector4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
}

FVector4 FMath::operator -(const FVector4& a)
{
    return FVector4(-a.x, -a.y, -a.z, -a.w);
}

FVector4 FMath::operator -(const FVector4& a, const FVector4& b)
{
    return FVector4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
}

FVector4 FMath::operator *(const Fix64& d, const FVector4& a)
{
    return FVector4(a.x * d, a.y * d, a.z * d, a.w * d);
}

FVector4 FMath::operator *(const FVector4& a, const Fix64& d)
{
    return FVector4(a.x * d, a.y * d, a.z * d, a.w * d);
}

FVector4 FMath::operator /(const FVector4& a, const Fix64& d)
{
    return FVector4(a.x / d, a.y / d, a.z / d, a.w / d);
}

bool FMath::operator ==(const FVector4& lhs, const FVector4& rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z && lhs.w == rhs.w;
}

bool FMath::operator !=(const FVector4& lhs, const FVector4& rhs)
{
    return lhs.x != rhs.x || lhs.y != rhs.y || lhs.z != rhs.z || lhs.w != rhs.w;
}

void FVector4::ClampMagnitude(const Fix64& maxLength)
{
    Fix64 len = Magnitude();

    if (len > maxLength)
    {
        // x / magnitude * maxLength, y / magnitude * maxLength
        // x * (maxLength / magnitude), y * (maxLength / magnitude)
        Fix64 scaleFactor = maxLength / len;

        x = x * scaleFactor;
        y = y * scaleFactor;
        z = z * scaleFactor;
        w = w * scaleFactor;
    }
}

Fix64 FVector4::Distance(FVector4 a, FVector4 b)
{
    Fix64 dx = a.x - b.x;
    Fix64 dy = a.y - b.y;
    Fix64 dz = a.z - b.z;
    Fix64 dw = a.w - b.w;

    return (dx * dx + dy * dy + dz * dz + dw * dw).Sqrt();
}

Fix64 FVector4::SqrDistance(FVector4 a, FVector4 b)
{
    Fix64 dx = a.x - b.x;
    Fix64 dy = a.y - b.y;
    Fix64 dz = a.z - b.z;
    Fix64 dw = a.w - b.w;

    return dx * dx + dy * dy + dz * dz + dw * dw;
}

Fix64 FVector4::Dot(FVector4 a, FVector4 b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

FVector4 FVector4::Scale(FVector4 a, FVector4 b)
{
    return FVector4(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
}

FVector4 FVector4::Lerp(FVector4 a, FVector4 b, Fix64 t)
{
    return FVector4(
        Fix64::Lerp(a.x, b.x, t),
        Fix64::Lerp(a.y, b.y, t),
        Fix64::Lerp(a.z, b.z, t),
        Fix64::Lerp(a.w, b.w, t));
}

FVector4 FVector4::LerpClamped(FVector4 a, FVector4 b, Fix64 t)
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

FVector4 FVector4::Max(FVector4 a, FVector4 b)
{
    return FVector4(Fix64::Max(a.x, b.x), Fix64::Max(a.y, b.y), Fix64::Max(a.z, b.z), Fix64::Max(a.w, b.w));
}

FVector4 FVector4::Min(FVector4 a, FVector4 b)
{
    return FVector4(Fix64::Min(a.x, b.x), Fix64::Min(a.y, b.y), Fix64::Min(a.z, b.z), Fix64::Min(a.w, b.w));
}
