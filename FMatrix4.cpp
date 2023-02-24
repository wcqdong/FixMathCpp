//
//  FMatrix4.cpp
//  MathLib
//
//  Created by christ on 2020/7/17.
//  Copyright © 2020 christ. All rights reserved.
//

#include "FMatrix4.h"

using namespace FMath;

const FMatrix4 FMatrix4::Identity = FMatrix4(
                                            Fix64::One, Fix64::Zero, Fix64::Zero, Fix64::Zero,
                                            Fix64::Zero, Fix64::One, Fix64::Zero, Fix64::Zero,
                                            Fix64::Zero, Fix64::Zero, Fix64::One, Fix64::Zero,
                                            Fix64::Zero, Fix64::Zero, Fix64::Zero, Fix64::One);

const FMatrix4 FMatrix4::Zero = FMatrix4(
                                            Fix64::Zero, Fix64::Zero, Fix64::Zero, Fix64::Zero,
                                            Fix64::Zero, Fix64::Zero, Fix64::Zero, Fix64::Zero,
                                            Fix64::Zero, Fix64::Zero, Fix64::Zero, Fix64::Zero,
                                            Fix64::Zero, Fix64::Zero, Fix64::Zero, Fix64::Zero);

Fix64 FMatrix4::Determinant() const
{
    Fix64 m00_22 = m00 * m22;
    Fix64 m01_23 = m01 * m23;
    Fix64 m02_20 = m02 * m20;
    Fix64 m03_21 = m03 * m21;
    Fix64 m10_32 = m10 * m32;
    Fix64 m11_33 = m11 * m33;
    Fix64 m12_30 = m12 * m30;
    Fix64 m13_31 = m13 * m31;

    Fix64 d1 = m00_22 * m11_33;
    Fix64 d2 = m01_23 * m12_30;
    Fix64 d3 = m02_20 * m13_31;
    Fix64 d4 = m03_21 * m10_32;
    Fix64 d5 = m00_22 * m13_31;
    Fix64 d6 = m01_23 * m10_32;
    Fix64 d7 = m02_20 * m11_33;
    Fix64 d8 = m03_21 * m12_30;

    return d1 + d2 + d3 + d4 - (d5 + d6 + d7 + d8);
}

bool FMatrix4::IsIdentity()
{
    return *this == Identity;
}

FMatrix4 FMatrix4::Transpose()
{
    FMatrix4 tmat = FMatrix4();

    tmat.m00 = m00; tmat.m01 = m10; tmat.m02 = m20; tmat.m03 = m30;
    tmat.m10 = m01; tmat.m11 = m11; tmat.m12 = m21; tmat.m13 = m31;
    tmat.m20 = m02; tmat.m21 = m12; tmat.m22 = m22; tmat.m23 = m32;
    tmat.m30 = m03; tmat.m31 = m13; tmat.m32 = m23; tmat.m33 = m33;

    return tmat;
}

Fix64 FMatrix4::Determinant(FMatrix4 m)
{
    return m.Determinant();
}

FVector4 FMatrix4::GetRow(int i)
{
    FVector4 row = FVector4();
    
    if (i == 0)
    {
        row.x = m00; row.y = m01; row.z = m02; row.w = m03;
    }
    else if (i == 1)
    {
        row.x = m10; row.y = m11; row.z = m12; row.w = m13;
    }
    else if (i == 2)
    {
        row.x = m20; row.y = m21; row.z = m22; row.w = m23;
    }
    else if (i == 3)
    {
        
        row.x = m30; row.y = m31; row.z = m32; row.w = m33;
    }

    return row;
}

void FMatrix4::SetRow(int i, FVector4 v)
{
    if (i == 0)
    {
        m00 = v.x; m01 = v.y; m02 = v.z; m03 = v.w;
    }
    else if (i == 1)
    {
        m10 = v.x; m11 = v.y; m12 = v.z; m13 = v.w;
    }
    else if (i == 2)
    {
        m20 = v.x; m21 = v.y; m22 = v.z; m23 = v.w;
    }
    else if (i == 3)
    {
        m30 = v.x; m31 = v.y; m32 = v.z; m33 = v.w;
    }
}

FVector4 FMatrix4::GetColumn(int i)
{
    FVector4 col = FVector4();

    if (i == 0)
    {
        col.x = m00; col.y = m10; col.z = m20; col.w = m30;
    }
    else if (i == 1)
    {
        col.x = m01; col.y = m11; col.z = m21; col.w = m31;
    }
    else if (i == 2)
    {
        col.x = m02; col.y = m12; col.z = m22; col.w = m32;
    }
    else if (i == 3)
    {

        col.x = m03; col.y = m13; col.z = m23; col.w = m33;
    }

    return col;
}

void FMatrix4::SetColumn(int i, FVector4 v)
{
    if (i == 0)
    {
        m00 = v.x; m10 = v.y; m20 = v.z; m30 = v.w;
    }
    else if (i == 1)
    {
        m01 = v.x; m11 = v.y; m21 = v.z; m31 = v.w;
    }
    else if (i == 2)
    {
        m02 = v.x; m12 = v.y; m22 = v.z; m32 = v.w;
    }
    else if (i == 3)
    {
        m03 = v.x; m13 = v.y; m23 = v.z; m33 = v.w;
    }
}

FMatrix4 FMatrix4::Scale(FVector3 v)
{
    FMatrix4 mat = Identity;

    mat.m00 = v.x;
    mat.m11 = v.y;
    mat.m22 = v.z;

    return mat;
}

FMatrix4 FMatrix4::Scale(Fix64 s)
{
    FMatrix4 mat = Identity;

    mat.m00 = s;
    mat.m11 = s;
    mat.m22 = s;

    return mat;
}

FVector3 FMatrix4::GetAxisX()
{
    return FVector3(m00, m01, m02);
}

FVector3 FMatrix4::GetAxisY()
{
    return FVector3(m10, m11, m12);
}

FVector3 FMatrix4::GetAxisZ()
{
    return FVector3(m20, m21, m22);
}

FVector3 FMatrix4::GetOrigin()
{
    return FVector3(m30, m31, m32);
}

FMatrix4 FMatrix4::TS(FVector3 pos, FVector3 scale)
{
    FMatrix4 mat = Identity;

    mat.m00 = scale.x;
    mat.m11 = scale.y;
    mat.m22 = scale.z;

    mat.m30 = pos.x;
    mat.m31 = pos.y;
    mat.m32 = pos.z;

    return mat;
}

FMatrix4 FMatrix4::Translate(FVector3 v)
{
    FMatrix4 mat = Identity;

    mat.m30 = v.x;
    mat.m31 = v.y;
    mat.m32 = v.z;

    return mat;
}

FMatrix4 FMatrix4::RotateX(Fix64 rad)
{
    FMatrix4 m = FMatrix4::Identity;

    Fix64 sin_theta = Fix64::Sin(rad);
    Fix64 cos_theta = Fix64::Cos(rad);

    //y
    m.m11 = cos_theta;
    m.m21 = -sin_theta;

    //z
    m.m12 = sin_theta;
    m.m22 = cos_theta;

    return m;
}

FMatrix4 FMatrix4::RotateY(Fix64 rad)
{
    FMatrix4 m = FMatrix4::Identity;

    Fix64 sin_theta = Fix64::Sin(rad);
    Fix64 cos_theta = Fix64::Cos(rad);

    // x
    m.m20 = cos_theta;
    m.m00 = -sin_theta;

    // z
    m.m22 = cos_theta;
    m.m02 = sin_theta;

    return m;
}

FMatrix4 FMatrix4::RotateZ(Fix64 rad)
{
    FMatrix4 m = FMatrix4::Identity;

    Fix64 sin_theta = Fix64::Sin(rad);
    Fix64 cos_theta = Fix64::Cos(rad);

    //x
    m.m00 = cos_theta;
    m.m10 = -sin_theta;

    //y
    m.m01 = sin_theta;
    m.m11 = cos_theta;

    return m;
}

FMatrix4 FMatrix4::RotateAxis(Fix64 theta, FVector3 n)
{
    Fix64 cos_theta = Fix64::Cos(theta);
    Fix64 sin_theta = Fix64::Sin(theta);

    Fix64 one_minus_cos_theta = Fix64::One - cos_theta;
    Fix64 nx_ny = n.x * n.y;
    Fix64 nx_nz = n.x * n.z;
    Fix64 ny_nz = n.y * n.z;
    Fix64 nx_sin_theta = n.x * sin_theta;
    Fix64 ny_sin_theta = n.y * sin_theta;
    Fix64 nz_sin_theta = n.z * sin_theta;

    FMatrix4 m = Identity;

    // row 1
    m.m00 = n.x * n.x * one_minus_cos_theta + cos_theta;
    m.m01 = nx_ny * one_minus_cos_theta + nz_sin_theta;
    m.m02 = nx_nz * one_minus_cos_theta - ny_sin_theta;

    // row 2
    m.m10 = nx_ny * one_minus_cos_theta - nz_sin_theta;
    m.m11 = n.y * n.y * one_minus_cos_theta + cos_theta;
    m.m12 = ny_nz * one_minus_cos_theta + nx_sin_theta;

    // row 3
    m.m20 = nx_nz * one_minus_cos_theta + ny_sin_theta;
    m.m21 = ny_nz * one_minus_cos_theta - nx_sin_theta;
    m.m22 = n.z * n.z * one_minus_cos_theta + cos_theta;

    return m;
}

FVector4 FMath::operator *(FMatrix4 lhs, FVector4 v)
{
    FVector4 vec = FVector4();

    vec.x = lhs.m00 * v.x + lhs.m01 * v.y + lhs.m02 * v.z + lhs.m03 * v.w;
    vec.y = lhs.m10 * v.x + lhs.m11 * v.y + lhs.m12 * v.z + lhs.m13 * v.w;
    vec.z = lhs.m20 * v.x + lhs.m21 * v.y + lhs.m22 * v.z + lhs.m23 * v.w;
    vec.w = lhs.m30 * v.x + lhs.m31 * v.y + lhs.m32 * v.z + lhs.m33 * v.w;
    
    //vec.x = Fix64.Mul(lhs.m00, v.x) + Fix64.Mul(lhs.m01, v.y) + Fix64.Mul(lhs.m02, v.z) + Fix64.Mul(lhs.m03, v.w);
    //vec.y = Fix64.Mul(lhs.m10, v.x) + Fix64.Mul(lhs.m11, v.y) + Fix64.Mul(lhs.m12, v.z) + Fix64.Mul(lhs.m13, v.w);
    //vec.z = Fix64.Mul(lhs.m20, v.x) + Fix64.Mul(lhs.m21, v.y) + Fix64.Mul(lhs.m22, v.z) + Fix64.Mul(lhs.m23, v.w);
    //vec.w = Fix64.Mul(lhs.m30, v.x) + Fix64.Mul(lhs.m31, v.y) + Fix64.Mul(lhs.m32, v.z) + Fix64.Mul(lhs.m33, v.w);

    return vec;
}

FMatrix4 FMath::operator *(FMatrix4 lhs, FMatrix4 rhs)
{
    FMatrix4 mat = FMatrix4();

    mat.m00 = lhs.m00 * rhs.m00 + lhs.m01 * rhs.m10 + lhs.m02 * rhs.m20 + lhs.m03 * rhs.m30;
    mat.m01 = lhs.m00 * rhs.m01 + lhs.m01 * rhs.m11 + lhs.m02 * rhs.m21 + lhs.m03 * rhs.m31;
    mat.m02 = lhs.m00 * rhs.m02 + lhs.m01 * rhs.m12 + lhs.m02 * rhs.m22 + lhs.m03 * rhs.m32;
    mat.m03 = lhs.m00 * rhs.m03 + lhs.m01 * rhs.m13 + lhs.m02 * rhs.m23 + lhs.m03 * rhs.m33;

    mat.m10 = lhs.m10 * rhs.m00 + lhs.m11 * rhs.m10 + lhs.m12 * rhs.m20 + lhs.m13 * rhs.m30;
    mat.m11 = lhs.m10 * rhs.m01 + lhs.m11 * rhs.m11 + lhs.m12 * rhs.m21 + lhs.m13 * rhs.m31;
    mat.m12 = lhs.m10 * rhs.m02 + lhs.m11 * rhs.m12 + lhs.m12 * rhs.m22 + lhs.m13 * rhs.m32;
    mat.m13 = lhs.m10 * rhs.m03 + lhs.m11 * rhs.m13 + lhs.m12 * rhs.m23 + lhs.m13 * rhs.m33;

    mat.m20 = lhs.m20 * rhs.m00 + lhs.m21 * rhs.m10 + lhs.m22 * rhs.m20 + lhs.m23 * rhs.m30;
    mat.m21 = lhs.m20 * rhs.m01 + lhs.m21 * rhs.m11 + lhs.m22 * rhs.m21 + lhs.m23 * rhs.m31;
    mat.m22 = lhs.m20 * rhs.m02 + lhs.m21 * rhs.m12 + lhs.m22 * rhs.m22 + lhs.m23 * rhs.m32;
    mat.m23 = lhs.m20 * rhs.m03 + lhs.m21 * rhs.m13 + lhs.m22 * rhs.m23 + lhs.m23 * rhs.m33;

    mat.m30 = lhs.m30 * rhs.m00 + lhs.m31 * rhs.m10 + lhs.m32 * rhs.m20 + lhs.m33 * rhs.m30;
    mat.m31 = lhs.m30 * rhs.m01 + lhs.m31 * rhs.m11 + lhs.m32 * rhs.m21 + lhs.m33 * rhs.m31;
    mat.m32 = lhs.m30 * rhs.m02 + lhs.m31 * rhs.m12 + lhs.m32 * rhs.m22 + lhs.m33 * rhs.m32;
    mat.m33 = lhs.m30 * rhs.m03 + lhs.m31 * rhs.m13 + lhs.m32 * rhs.m23 + lhs.m33 * rhs.m33;

    return mat;
}

FMatrix4 FMatrix4::Multiply(FMatrix4& lhs, FMatrix4& rhs)
{
    FMatrix4 mat = FMatrix4();

    mat.m00 = lhs.m00 * rhs.m00 + lhs.m01 * rhs.m10 + lhs.m02 * rhs.m20 + lhs.m03 * rhs.m30;
    mat.m01 = lhs.m00 * rhs.m01 + lhs.m01 * rhs.m11 + lhs.m02 * rhs.m21 + lhs.m03 * rhs.m31;
    mat.m02 = lhs.m00 * rhs.m02 + lhs.m01 * rhs.m12 + lhs.m02 * rhs.m22 + lhs.m03 * rhs.m32;
    mat.m03 = lhs.m00 * rhs.m03 + lhs.m01 * rhs.m13 + lhs.m02 * rhs.m23 + lhs.m03 * rhs.m33;

    mat.m10 = lhs.m10 * rhs.m00 + lhs.m11 * rhs.m10 + lhs.m12 * rhs.m20 + lhs.m13 * rhs.m30;
    mat.m11 = lhs.m10 * rhs.m01 + lhs.m11 * rhs.m11 + lhs.m12 * rhs.m21 + lhs.m13 * rhs.m31;
    mat.m12 = lhs.m10 * rhs.m02 + lhs.m11 * rhs.m12 + lhs.m12 * rhs.m22 + lhs.m13 * rhs.m32;
    mat.m13 = lhs.m10 * rhs.m03 + lhs.m11 * rhs.m13 + lhs.m12 * rhs.m23 + lhs.m13 * rhs.m33;

    mat.m20 = lhs.m20 * rhs.m00 + lhs.m21 * rhs.m10 + lhs.m22 * rhs.m20 + lhs.m23 * rhs.m30;
    mat.m21 = lhs.m20 * rhs.m01 + lhs.m21 * rhs.m11 + lhs.m22 * rhs.m21 + lhs.m23 * rhs.m31;
    mat.m22 = lhs.m20 * rhs.m02 + lhs.m21 * rhs.m12 + lhs.m22 * rhs.m22 + lhs.m23 * rhs.m32;
    mat.m23 = lhs.m20 * rhs.m03 + lhs.m21 * rhs.m13 + lhs.m22 * rhs.m23 + lhs.m23 * rhs.m33;

    mat.m30 = lhs.m30 * rhs.m00 + lhs.m31 * rhs.m10 + lhs.m32 * rhs.m20 + lhs.m33 * rhs.m30;
    mat.m31 = lhs.m30 * rhs.m01 + lhs.m31 * rhs.m11 + lhs.m32 * rhs.m21 + lhs.m33 * rhs.m31;
    mat.m32 = lhs.m30 * rhs.m02 + lhs.m31 * rhs.m12 + lhs.m32 * rhs.m22 + lhs.m33 * rhs.m32;
    mat.m33 = lhs.m30 * rhs.m03 + lhs.m31 * rhs.m13 + lhs.m32 * rhs.m23 + lhs.m33 * rhs.m33;

    return mat;
}

bool FMath::operator ==(FMatrix4 lhs, FMatrix4 rhs)
{
    return lhs.m00 == rhs.m00 && lhs.m01 == rhs.m01 && lhs.m02 == rhs.m02 && lhs.m03 == rhs.m03 &&
           lhs.m10 == rhs.m10 && lhs.m11 == rhs.m11 && lhs.m12 == rhs.m12 && lhs.m13 == rhs.m13 &&
           lhs.m20 == rhs.m20 && lhs.m21 == rhs.m21 && lhs.m22 == rhs.m22 && lhs.m23 == rhs.m23 &&
           lhs.m30 == rhs.m30 && lhs.m31 == rhs.m31 && lhs.m32 == rhs.m32 && lhs.m33 == rhs.m33;

}

bool FMath::operator !=(FMatrix4 lhs, FMatrix4 rhs)
{
    return lhs.m00 != rhs.m00 || lhs.m01 != rhs.m01 || lhs.m02 != rhs.m02 || lhs.m03 != rhs.m03 ||
           lhs.m10 != rhs.m10 || lhs.m11 != rhs.m11 || lhs.m12 != rhs.m12 || lhs.m13 != rhs.m13 ||
           lhs.m20 != rhs.m20 || lhs.m21 != rhs.m21 || lhs.m22 != rhs.m22 || lhs.m23 != rhs.m23 ||
           lhs.m30 != rhs.m30 || lhs.m31 != rhs.m31 || lhs.m32 != rhs.m32 || lhs.m33 != rhs.m33;
}
