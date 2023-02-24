//
//  FVector3.h
//  MathLib
//
//  Created by christ on 2020/7/17.
//  Copyright © 2020 christ. All rights reserved.
//

#ifndef FVector3_h
#define FVector3_h

#include "Fix64.h"

namespace FMath
{
    struct FVector3
    {
        Fix64 x;
        Fix64 y;
        Fix64 z;

        FVector3(Fix64 x, Fix64 y): x(x), y(y), z(Fix64::Zero)
        {
        }

        FVector3(Fix64 x, Fix64 y, Fix64 z): x(x), y(y), z(z)
        {
        }

        const static FVector3 Back;

        const static FVector3 Forward;

        const static FVector3 Down;

        const static FVector3 Up;

        const static FVector3 Left;

        const static FVector3 Right;
        
        const static FVector3 Zero;

        const static FVector3 One;

        /// <summary>
        /// length of vector.
        /// </summary>
        Fix64 Magnitude() const;

        /// <summary>
        /// squared of length.
        /// </summary>
        Fix64 SqrMagnitude() const;

        FVector3 Normalized() const;

        string ToString();

        bool Equals(const FVector3& obj);

        int GetHashCode();

        void Normalize();

        void Scale(const FVector3& scale);

        void Set(const Fix64& x, const Fix64& y, const Fix64& z);

        friend FVector3 operator +(const FVector3& a, const FVector3& b);

        friend FVector3 operator -(const FVector3& a);

        friend FVector3 operator -(const FVector3& a, const FVector3& b);

        friend FVector3 operator *(const Fix64& d, const FVector3& a);

        friend FVector3 operator *(const FVector3& a, const Fix64& d);

        friend FVector3 operator /(const FVector3& a, const Fix64& d);

        friend bool operator ==(const FVector3& lhs, const FVector3& rhs);

        friend bool operator !=(const FVector3& lhs, const FVector3& rhs);

        void ClampMagnitude(const Fix64& maxLength);

        /// <summary>
        /// 求两个向量的欧几里得距离.
        /// </summary>
        /// <returns></returns>
        static Fix64 Distance(const FVector3& a, const FVector3& b);

        /// <summary>
        /// 求两个向量的欧几里得距离的平方.
        /// </summary>
        /// <returns></returns>
        static Fix64 SqrDistance(const FVector3& a, const FVector3& b);
        
        static Fix64 Dot(const FVector3& a, const FVector3& b);

        /// <summary>
        /// ax bx
        /// ay by
        /// az bz
        /// </summary>
        /// <param name="a"></param>
        /// <param name="b"></param>
        /// <returns></returns>
        static FVector3 Cross(const FVector3& a, const FVector3& b);
        
        static FVector3 Scale(const FVector3& a, const FVector3& b);

        static FVector3 Lerp(const FVector3& a, const FVector3& b, const Fix64& t);
        
        static FVector3 LerpClamped(const FVector3& a, const FVector3& b, Fix64 t);

        static FVector3 Max(const FVector3& a, const FVector3& b);
        
        static FVector3 Min(const FVector3& a, const FVector3& b);

        /// <summary>
        /// 求两个向量的夹角.(依赖于反三角函数的实现)
        /// </summary>
        /// <param name="from"></param>
        /// <param name="to"></param>
        /// <returns></returns>
        static Fix64 Angle(const FVector3& from, const FVector3& to);


        /// <summary>
        /// 求反射向量.
        /// </summary>
        /// <param name="inDirection">单位向量</param>
        /// <param name="inNormal">单位向量</param>
        /// <returns></returns>
        static FVector3 Reflect(const FVector3& inDirection, const FVector3& inNormal);

        /// <summary>
        /// 向量v在n上的投影.
        /// </summary>
        /// <param name="v"></param>
        /// <param name="n">n为单位向量</param>
        /// <returns></returns>
        static FVector3 Project(const FVector3& v, const FVector3& n);

        static FVector3 ProjectOnPlane(const FVector3& v, const FVector3& n);

        static FVector3 Slerp(const FVector3& a, const FVector3& b, const Fix64& t);
    };
}


#endif /* FVector3_h */
