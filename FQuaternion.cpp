//
//  FQuaternion.cpp
//  MathLib
//
//  Created by christ on 2020/7/17.
//  Copyright © 2020 christ. All rights reserved.
//

#include "FQuaternion.h"

using namespace FMath;

const FQuaternion FQuaternion::Identity = FQuaternion(Fix64::One, Fix64::Zero, Fix64::Zero, Fix64::Zero);

Fix64 FQuaternion::Magnitude() const
{
    return (w * w + x * x + y * y + z * z).Sqrt();
}

Fix64 FQuaternion::SqrMagnitude() const
{
    return w * w + x * x + y * y + z * z;
}

FQuaternion FQuaternion::Conjugate() const
{
    return FQuaternion(-x, -y, -z, w);
}

FQuaternion FQuaternion::Normalized() const
{
    Fix64 len = Magnitude();
    //return new FQuaternion(Fix64.Div(x, len), Fix64.Div(y, len), Fix64.Div(z, len), Fix64.Div(w, len));
    return FQuaternion(x / len, y / len, z / len, w / len);
}

FQuaternion FQuaternion::Inverse(FQuaternion q)
{
    Fix64 sqrLen = q.SqrMagnitude();

    if (sqrLen == Fix64::One)
    {
        return q.Conjugate();
    }
    else
    {
        //return new FQuaternion(Fix64.Div(-q.x, sqrLen), Fix64.Div(-q.y, sqrLen),
        //Fix64.Div(-q.z, sqrLen), Fix64.Div(q.w, sqrLen));

        return FQuaternion(-q.x / sqrLen, -q.y / sqrLen,
           -q.z / sqrLen, q.w /sqrLen);
    }
}

FQuaternion FQuaternion::AngleAxis(Fix64 angle, FVector3 axis)
{
    Fix64 angle_over_2 = angle / 2;

    Fix64 sin_theta = Fix64::Sin(angle_over_2);
    Fix64 cos_theta = Fix64::Sin(angle_over_2);

    FVector3 v = axis.Normalized() * sin_theta;

    return FQuaternion(v.x, v.y, v.z, cos_theta);
}

FQuaternion FQuaternion::Conjugate(FQuaternion q)
{
    return FQuaternion(-q.x, -q.y, -q.z, q.w);
}

FQuaternion FMath::operator +(FQuaternion a, FQuaternion b)
{
    return FQuaternion(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
}

FQuaternion FMath::operator -(FQuaternion a, FQuaternion b)
{
    return FQuaternion(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
}

Fix64 FQuaternion::Dot(FQuaternion a, FQuaternion b)
{
    return a.w * b.w - (a.x * b.x + a.y * b.y + a.z * b.z);
    //return Fix64.Mul(a.w, b.w) - (Fix64.Mul(a.x, b.x) + Fix64.Mul(a.y, b.y) + Fix64.Mul(a.z, b.z));
}

FQuaternion FMath::operator *(FQuaternion a, FQuaternion b)
{
    FQuaternion q = FQuaternion();

    q.w = a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z;
    q.x = a.w * b.x + b.w * a.x + a.y * b.z - b.y * a.z;
    q.y = a.w * b.y + b.w * a.y + a.z * b.x - b.z * a.x;
    q.z = a.w * b.z + b.w * a.z + a.x * b.y - b.x * a.y;

    return q;
}

FVector3 FMath::operator *(FQuaternion q, FVector3 v)
{
    FQuaternion pq = FQuaternion(v.x, v.y, v.z, Fix64::Zero);
    FQuaternion tq = q * pq * FQuaternion::Conjugate(q);

    return FVector3(tq.x, tq.y, tq.z);
}

FQuaternion FMath::operator *(FQuaternion q, Fix64 a)
{
    //return new FQuaternion(Fix64.Mul(a, q.x), Fix64.Mul(a, q.y), Fix64.Mul(a, q.z), Fix64.Mul(a, q.w));
    return FQuaternion(a*q.w, a*q.x, a*q.y, a*q.z);
}

bool FMath::operator ==(FQuaternion a, FQuaternion b)
{
    return a.w == b.w && a.x == b.x && a.y == b.y && a.z == b.z;
}

bool FMath::operator !=(FQuaternion a, FQuaternion b)
{
    return a.w != b.w || a.x != b.x || a.y != b.y || a.z != b.z;
}

FQuaternion FMath::operator -(FQuaternion q)
{
    return FQuaternion(-q.x, -q.y, -q.z, -q.w);
}

void FQuaternion::SetAngleAxis(Fix64 angle, FVector3 axis)
{
    Fix64 angle_over_2 = angle / 2;

    Fix64 sin_theta = Fix64::Sin(angle_over_2);
    Fix64 cos_theta = Fix64::Cos(angle_over_2);

    FVector3 v = axis.Normalized() * sin_theta;

    w = cos_theta;
    x = v.x;
    y = v.y;
    z = v.z;
}

void FQuaternion::ToAngleAxis(Fix64& angle, FVector3 axis)
{
    angle = Fix64::Acos(w) * 2;
    axis = FVector3(x, y, z);
    axis.Normalize();
}

Fix64 FQuaternion::Angle(FQuaternion a, FQuaternion b)
{
    FQuaternion ia = Inverse(a);
    FQuaternion d = ia * b;

    return Fix64::Acos(d.w) * 2;
}

FQuaternion FQuaternion::FromToRotation(FVector3 fromDir, FVector3 toDir)
{
    FQuaternion q = FQuaternion();
    q.SetFromToRotation(fromDir, toDir);

    return q;
}

void FQuaternion::SetFromToRotation(FVector3 fromDir, FVector3 toDir)
{
//            Debug.Assert(Fix64.one - fromDir.magnitude < Fix64.epsilon ||
//              Fix64.one - fromDir.magnitude > Fix64.epsilon,
//              "fromDir.magnitude != 1");
//
//            Debug.Assert(Fix64.one - toDir.magnitude < Fix64.epsilon ||
//               Fix64.one - toDir.magnitude > Fix64.epsilon,
//               "toDir.magnitude != 1");
    Fix64 cos_theta = FVector3::Dot(fromDir, toDir);
    Fix64 angle = Fix64::Acos(cos_theta);
    FVector3 axis = FVector3::Cross(fromDir, toDir);

    SetAngleAxis(angle, axis);
}

string FQuaternion::ToString()
{
    return x.ToString() + "," + y.ToString() + "," + z.ToString() + "," + w.ToString();
}
