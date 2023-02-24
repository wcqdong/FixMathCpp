//
//  FVector2.h
//  MathLib
//
//  Created by christ on 2020/7/17.
//  Copyright © 2020 christ. All rights reserved.
//

#ifndef FVector2_h
#define FVector2_h

#include "Fix64.h"

namespace FMath
{
    struct FVector2
    {
        Fix64 x;
        Fix64 y;

        FVector2(const Fix64& x, const Fix64& y):x(x),y(y)
        {
        }

        const static FVector2 Down;

        const static FVector2 Left;

        const static FVector2 Right;

        const static FVector2 Up;

        const static FVector2 Zero;
        
        const static FVector2 One;

        /// <summary>
        /// length of vector.
        /// </summary>
        Fix64 Magnitude();
        /// <summary>
        /// squared of length.
        /// </summary>
        Fix64 SqrMagnitude();

        FVector2 Normalized();

        void Normalize();

        void Scale(const FVector2& scale);

        void ClampMagnitude(const Fix64& maxLength);

        bool Equals(const FVector2& obj);

        int GetHashCode();

        void Set(const Fix64& x, const Fix64& y);

        friend FVector2 operator +(const FVector2& a, const FVector2& b);

        friend FVector2 operator -(const FVector2& a);

        friend FVector2 operator -(const FVector2& a, const FVector2& b);

        friend FVector2 operator *(const Fix64& d, const FVector2& a);

        friend FVector2 operator *(const FVector2& a, const Fix64& d);

        friend FVector2 operator /(const FVector2& a, const Fix64& d);

        friend bool operator ==(const FVector2& lhs, const FVector2& rhs);

        friend bool operator !=(const FVector2& lhs, const FVector2& rhs);

        string ToString();

        /// <summary>
        /// 求两个向量的欧几里得距离.
        /// </summary>
        /// <returns></returns>
        static Fix64 Distance(const FVector2& a, const FVector2& b);

        /// <summary>
        /// 求两个向量的欧几里得距离的平方.
        /// </summary>
        /// <returns></returns>
        static Fix64 SqrDistance(const FVector2& a, const FVector2& b);

        static Fix64 Dot(const FVector2& a, const FVector2& b);

        static FVector2 Scale(const FVector2& a, const FVector2& b);
        
        static FVector2 Lerp(const FVector2& a, const FVector2& b, Fix64 t);

        static FVector2 LerpClamped(const FVector2& a, const FVector2& b, Fix64 t);

        static FVector2 Max(const FVector2& a, const FVector2& b);

        static FVector2 Min(const FVector2& a, const FVector2& b);

        /// <summary>
        /// 求两个向量的夹角.(依赖于反三角函数的实现)
        /// </summary>
        /// <param name="from"></param>
        /// <param name="to"></param>
        /// <returns></returns>
        //public static Fix64 Angle(FVector2 from, FVector2 to)
        //{
        //    Fix64 dot = Dot(from, to);
        //    Fix64 scale = Fix64.Mul(from.magnitude, to.magnitude);

        //    return Fix64.ACos(Fix64.Div(scale));
        //}


        /// <summary>
        /// 求反射向量.
        /// </summary>
        /// <param name="inDirection">单位向量</param>
        /// <param name="inNormal">单位向量</param>
        /// <returns></returns>
        static FVector2 Reflect(const FVector2& inDirection, const FVector2& inNormal);

        /// <summary>
        /// 向量v在n上的投影.
        /// </summary>
        /// <param name="v"></param>
        /// <param name="n">n为单位向量</param>
        /// <returns></returns>
        static FVector2 Project(const FVector2& v, const FVector2& n);
    };
}  // end namespace

#endif /* FVector2_h */
