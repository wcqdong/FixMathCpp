//
//  FVector4.h
//  MathLib
//
//  Created by christ on 2020/7/17.
//  Copyright © 2020 christ. All rights reserved.
//

#ifndef FVector4_h
#define FVector4_h

#include "Fix64.h"

namespace FMath
{
    struct FVector4
    {
        Fix64 x;
        Fix64 y;
        Fix64 z;
        Fix64 w;

        FVector4()
        {
            
        }
        
        FVector4(Fix64 x, Fix64 y, Fix64 z): x(x), y(y), z(z), w(Fix64::Zero)
        {
        }

        FVector4(Fix64 x, Fix64 y, Fix64 z, Fix64 w): x(x), y(y), z(z), w(w)
        {
        }

        const static FVector4 Zero;

        const static FVector4 One;

        /// <summary>
        /// length of vector.
        /// </summary>
        Fix64 Magnitude() const;

        /// <summary>
        /// squared of length.
        /// </summary>
        Fix64 SqrMagnitude() const;
        
        FVector4 Normalized() const;

        string ToString();

        bool Equals(const FVector4& obj);

        int GetHashCode();

        void Normalize();

        void Scale(const FVector4& scale);

        void Set(const Fix64& x, const Fix64& y, const Fix64& z, const Fix64& w);

        friend FVector4 operator +(const FVector4& a, const FVector4& b);

        friend FVector4 operator -(const FVector4& a);

        friend FVector4 operator -(const FVector4& a, const FVector4& b);

        friend FVector4 operator *(const Fix64& d, const FVector4& a);

        friend FVector4 operator *(const FVector4& a, const Fix64& d);

        friend FVector4 operator /(const FVector4& a, const Fix64& d);

        friend bool operator ==(const FVector4& lhs, const FVector4& rhs);

        friend bool operator !=(const FVector4& lhs, const FVector4& rhs);

        void ClampMagnitude(const Fix64& maxLength);
        /// <summary>
        /// 求两个向量的欧几里得距离.
        /// </summary>
        /// <returns></returns>
        static Fix64 Distance(FVector4 a, FVector4 b);

        /// <summary>
        /// 求两个向量的欧几里得距离的平方.
        /// </summary>
        /// <returns></returns>
        Fix64 SqrDistance(FVector4 a, FVector4 b);

        static Fix64 Dot(FVector4 a, FVector4 b);

        static FVector4 Scale(FVector4 a, FVector4 b);

        static FVector4 Lerp(FVector4 a, FVector4 b, Fix64 t);

        static FVector4 LerpClamped(FVector4 a, FVector4 b, Fix64 t);

        static FVector4 Max(FVector4 a, FVector4 b);

        static FVector4 Min(FVector4 a, FVector4 b);
    };
}


#endif /* FVector4_h */
