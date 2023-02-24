//
//  FQuaternion.h
//  MathLib
//
//  Created by christ on 2020/7/17.
//  Copyright © 2020 christ. All rights reserved.
//

#ifndef FQuaternion_h
#define FQuaternion_h

#include "Fix64.h"
#include "FVector3.h"
using namespace FMath;

namespace FMath
{
    /// <summary>
    /// q=[w,v]=[w,xi+yj+zk]
    /// The general form to express quaternions is:
    ///         i^2 = j^2 = k^2 = ijk = -1
    /// and
    ///         ij = k, jk = i, ki = j,
    ///         ji = -k, kj = -i, ik = -j
    /// </summary>
    struct FQuaternion
    {
        Fix64 w;
        Fix64 x;
        Fix64 y;
        Fix64 z;

        FQuaternion(Fix64 x, Fix64 y, Fix64 z, Fix64 w): x(x), y(y), z(z), w(w)
        {
        }
        
        FQuaternion(): x(Fix64::Zero), y(Fix64::Zero), z(Fix64::Zero), w(Fix64::Zero)
        {
            
        }
        
        const static FQuaternion Identity;

        Fix64 Magnitude() const;

        Fix64 SqrMagnitude() const;

        FQuaternion Conjugate() const;

        FQuaternion Normalized() const;

        //static Fix64 Angle(FQuaternion a, FQuaternion b)
        //{
        //    FQuaternion na = a.normalized;
        //    FQuaternion nb = b.normalized;

        //    return ACos(Dot(na, nb));
        //}

        /// <summary>
        /// q^-1 = q^*/|q|^2
        /// q*q-1 = identity
        /// 如果是单位四元数，可以调用conjugate接口计算逆四元数
        /// </summary>
        /// <param name="q"></param>
        /// <returns></returns>
        static FQuaternion Inverse(FQuaternion q);

        /// <summary>
        /// builds a Quaternion by rotate axis and angle.
        /// </summary>
        /// <param name="axis">rotate axis.</param>
        /// <param name="angle"></param>
        /// <returns></returns>
        static FQuaternion AngleAxis(Fix64 angle, FVector3 axis);
        
        static FQuaternion Conjugate(FQuaternion q);

        friend FQuaternion operator +(FQuaternion a, FQuaternion b);

        friend FQuaternion operator -(FQuaternion a, FQuaternion b);

        /// <summary>
        /// a.b = [a.w*b.w + a.xi * b.xi + a.yi * b.yi + a.zi * b.zi]
        /// a.b = a.w*b.w - (ax*bx + ay*by + az*bz)
        /// </summary>
        /// <param name="a"></param>
        /// <param name="b"></param>
        /// <returns></returns>
        static Fix64 Dot(FQuaternion a, FQuaternion b);
        /// <summary>
        /// [wa,va]*[wb,vb] = [wa*wb - va.vb, wa * vb + wb*va + vaxvb]
        /// 四元数乘法满足结合律，不满足交换律.
        /// </summary>
        /// <param name="a"></param>
        /// <param name="b"></param>
        /// <returns></returns>
        friend FQuaternion operator *(FQuaternion a, FQuaternion b);

        /// <summary>
        /// 四元数乘向量=四元数表达的旋转应用到向量v上(v'=q*v*q^-1)
        /// </summary>
        /// <param name="q">q为单位四元数</param>
        /// <param name="v"></param>
        /// <returns></returns>
        friend FVector3 operator *(FQuaternion q, FVector3 v);

        /// <summary>
        /// q=[w,v]
        /// aq = [aw,av]
        /// </summary>
        /// <param name="q"></param>
        /// <param name="a"></param>
        /// <returns></returns>
        friend FQuaternion operator *(FQuaternion q, Fix64 a);

        friend bool operator ==(FQuaternion a, FQuaternion b);

        friend bool operator !=(FQuaternion a, FQuaternion b);

        friend FQuaternion operator -(FQuaternion q);

        void SetAngleAxis(Fix64 angle, FVector3 axis);

        void ToAngleAxis(Fix64& angle, FVector3 axis);

        /// <summary>
        /// caculates angle betweens a and b.
        /// </summary>
        /// <param name="a"></param>
        /// <param name="b"></param>
        /// <returns></returns>
        static Fix64 Angle(FQuaternion a, FQuaternion b);

        /// <summary>
        /// 在两个朝向之间构造一个四元数.
        /// </summary>
        /// <param name="fromDir">单位向量</param>
        /// <param name="toDir">单位向量</param>
        /// <returns></returns>
        static FQuaternion FromToRotation(FVector3 fromDir, FVector3 toDir);

        void SetFromToRotation(FVector3 fromDir, FVector3 toDir);
        
        string ToString();
    };
}


#endif /* FQuaternion_h */
