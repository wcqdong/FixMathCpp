//
//  FVector3.cpp
//  MathLib
//
//  Created by christ on 2020/7/17.
//  Copyright © 2020 christ. All rights reserved.
//

#include "FVector3.h"
using namespace FMath;

const FVector3 FVector3::Back = FVector3(Fix64::Zero, Fix64::Zero, -Fix64::One);

const FVector3 FVector3::Forward = FVector3(Fix64::Zero, Fix64::Zero, Fix64::One);

const FVector3 FVector3::Down = FVector3(Fix64::Zero, -Fix64::One, Fix64::Zero);

const FVector3 FVector3::Up = FVector3(Fix64::Zero, Fix64::One, Fix64::Zero);

const FVector3 FVector3::Left = FVector3(-Fix64::One, Fix64::Zero, Fix64::Zero);

const FVector3 FVector3::Right = FVector3(Fix64::One, Fix64::Zero, Fix64::Zero);

const FVector3 FVector3::Zero = FVector3(Fix64::Zero, Fix64::Zero, Fix64::Zero);

const FVector3 FVector3::One = FVector3(Fix64::One, Fix64::One, Fix64::One);

Fix64 FVector3::Magnitude() const
{
    return (x * x + y * y + z * z).Sqrt();
}

/// <summary>
/// squared of length.
/// </summary>
Fix64 FVector3::SqrMagnitude() const
{
    return x * x + y * y + z * z;
}

FVector3 FVector3::Normalized() const
{
    Fix64 len = Magnitude();

    if (len == Fix64::Zero)
    {
        return FVector3::Zero;
    }

    return FVector3(x / len, y / len, z / len);
}

string FVector3::ToString()
{
    return x.ToString() + "," + y.ToString() + "," + z.ToString();
}

bool FVector3::Equals(const FVector3& obj)
{
    return obj.x == x &&
           obj.y == y &&
           obj.z == z;
}

int FVector3::GetHashCode()
{
    return Magnitude().GetHashCode();
}

void FVector3::Normalize()
{
    Fix64 len = Magnitude();

    x = x / len;
    y = y / len;
    z = z / len;
}

void FVector3::Scale(const FVector3& scale)
{
    x = x * scale.x;
    y = y * scale.y;
    z = z * scale.z;
}

void FVector3::Set(const Fix64& x, const Fix64& y, const Fix64& z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

FVector3 FMath::operator +(const FVector3& a, const FVector3& b)
{
    return FVector3(a.x + b.x, a.y + b.y, a.z + b.z);
}

FVector3 FMath::operator -(const FVector3& a)
{
    return FVector3(-a.x, -a.y, -a.z);
}

FVector3 FMath::operator -(const FVector3& a, const FVector3& b)
{
    return FVector3(a.x - b.x, a.y - b.y, a.z - b.z);
}

FVector3 FMath::operator *(const Fix64& d, const FVector3& a)
{
    //return new FVector3(Fix64.Mul(a.x, d), Fix64.Mul(a.y, d), Fix64.Mul(a.z, d));
    return FVector3(a.x * d, a.y * d, a.z * d);
}

FVector3 FMath::operator *(const FVector3& a, const Fix64& d)
{
    //return new FVector3(Fix64.Mul(a.x, d), Fix64.Mul(a.y, d), Fix64.Mul(a.z, d));
    return FVector3(a.x * d, a.y * d, a.z * d);
}

FVector3 FMath::operator /(const FVector3& a, const Fix64& d)
{
    //return new FVector3(Fix64.Div(a.x, d), Fix64.Div(a.y, d), Fix64.Div(a.z, d));
    return FVector3(a.x / d, a.y / d, a.z / d);
}

bool FMath::operator ==(const FVector3& lhs, const FVector3& rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
}

bool FMath::operator !=(const FVector3& lhs, const FVector3& rhs)
{
    return lhs.x != rhs.x || lhs.y != rhs.y || lhs.z != rhs.z;
}

void FVector3::ClampMagnitude(const Fix64& maxLength)
{
    Fix64 len = Magnitude();

    if (len > maxLength)
    {
        // x / magnitude * maxLength, y / magnitude * maxLength
        // x * (maxLength / magnitude), y * (maxLength / magnitude)
        //Fix64 scaleFactor = Fix64.Div(maxLength, len);
        Fix64 invScaleFactor = len / maxLength;

        //x = Fix64.Mul(x, scaleFactor);
        //y = Fix64.Mul(y, scaleFactor);
        //z = Fix64.Mul(z, scaleFactor);

        x = x / invScaleFactor;
        y = y / invScaleFactor;
        z = z / invScaleFactor;
    }
}

Fix64 FVector3::Distance(const FVector3& a, const FVector3& b)
{
    Fix64 dx = a.x - b.x;
    Fix64 dy = a.y - b.y;
    Fix64 dz = a.z - b.z;

    //return Fix64.Sqrt(Fix64.Square(dx) + Fix64.Square(dy) + Fix64.Square(dz));
    return (dx * dx + dy * dy + dz * dz).Sqrt();
}

Fix64 FVector3::SqrDistance(const FVector3& a, const FVector3& b)
{
    Fix64 dx = a.x - b.x;
    Fix64 dy = a.y - b.y;
    Fix64 dz = a.z - b.z;

    //return Fix64.Square(dx) + Fix64.Square(dy) + Fix64.Square(dz);
    return dx * dx + dy * dy + dz * dz;
}

Fix64 FVector3::Dot(const FVector3& a, const FVector3& b)
{
    //return Fix64.Mul(a.x, b.x) + Fix64.Mul(a.y, b.y) + Fix64.Mul(a.z, b.z);
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

FVector3 FVector3::Cross(const FVector3& a, const FVector3& b)
{
    //Fix64 cx = Fix64.Mul(a.y, b.z) - Fix64.Mul(a.z, b.y);
    //Fix64 cy = Fix64.Mul(a.z, b.x) - Fix64.Mul(a.x, b.z);
    //Fix64 cz = Fix64.Mul(a.x, b.y) - Fix64.Mul(a.y, b.x);

    Fix64 cx = a.y * b.z - a.z * b.y;
    Fix64 cy = a.z * b.x - a.x * b.z;
    Fix64 cz = a.x * b.y - a.y * b.x;

    return FVector3(cx, cy, cz);
}

FVector3 FVector3::Scale(const FVector3& a, const FVector3& b)
{
    //return new FVector3(Fix64.Mul(a.x, b.x), Fix64.Mul(a.y, b.y), Fix64.Mul(a.z, b.z));
    return FVector3(a.x * b.x, a.y * b.y, a.z * b.z);
}

FVector3 FVector3::Lerp(const FVector3& a, const FVector3& b, const Fix64& t)
{
    return FVector3(
        Fix64::Lerp(a.x, b.x, t),
        Fix64::Lerp(a.y, b.y, t),
        Fix64::Lerp(a.z, b.z, t));
}

FVector3 FVector3::LerpClamped(const FVector3& a, const FVector3& b, Fix64 t)
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

FVector3 FVector3::Max(const FVector3& a, const FVector3& b)
{
    return FVector3(Fix64::Max(a.x, b.x), Fix64::Max(a.y, b.y), Fix64::Max(a.z, b.z));
}

FVector3 FVector3::Min(const FVector3& a, const FVector3& b)
{
    return FVector3(Fix64::Min(a.x, b.x), Fix64::Min(a.y, b.y), Fix64::Min(a.z, b.z));
}

Fix64 FVector3::Angle(const FVector3& from, const FVector3& to)
{
    Fix64 dot = Dot(from, to);
    Fix64 len2 = from.Magnitude() * to.Magnitude();

    return Fix64::Acos(dot / len2);
}

FVector3 FVector3::Reflect(const FVector3& inDirection, const FVector3& inNormal)
{
    Fix64 projectionLen2 = Dot(inDirection, inNormal) * 2;
    FVector3 v = inNormal * -projectionLen2;

    return inDirection + v;
}

FVector3 FVector3::Project(const FVector3& v, const FVector3& n)
{
    return n * Dot(v, n);
}

FVector3 FVector3::ProjectOnPlane(const FVector3& v, const FVector3& n)
{
    return n * Dot(v, n) + v;
}

FVector3 FVector3::Slerp(const FVector3& a, const FVector3& b, const Fix64& t)
{
    Fix64 lenA = a.Magnitude();
    Fix64 lenB = b.Magnitude();

    FVector3 v1 = a.Normalized();
    FVector3 v2 = b.Normalized();

    Fix64 cos_theta = Dot(v1, v2);

    if ((Fix64::One - cos_theta) < Fix64::Epsilon && (Fix64::One - cos_theta) > -Fix64::Epsilon)
    {
        return a + (b - a) * t;
    }

    Fix64 angle = Fix64::Acos(cos_theta);
    FVector3 axis = Cross(a, b);
    
    return FVector3((Fix64)0, (Fix64)0, (Fix64)0);

//            FQuaternion q = FQuaternion.AngleAxis(angle * t, axis);
//            FVector3 vt = q * v1;
//
//            return (lenA + (lenB - lenA) * t) * vt;
}
  

