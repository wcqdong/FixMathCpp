//
//  FMatrix4.h
//  MathLib
//
//  Created by christ on 2020/7/17.
//  Copyright © 2020 christ. All rights reserved.
//

#ifndef FMatrix4_h
#define FMatrix4_h

#include "Fix64.h"
#include "FVector4.h"
#include "FVector3.h"

namespace FMath
{
    struct FMatrix4
    {
        Fix64 m00, m01, m02, m03;
        Fix64 m10, m11, m12, m13;
        Fix64 m20, m21, m22, m23;
        Fix64 m30, m31, m32, m33;

        FMatrix4()
        {
            
        }
        
        FMatrix4(Fix64 m00, Fix64 m01, Fix64 m02, Fix64 m03,
                          Fix64 m10, Fix64 m11, Fix64 m12, Fix64 m13,
                          Fix64 m20, Fix64 m21, Fix64 m22, Fix64 m23,
                          Fix64 m30, Fix64 m31, Fix64 m32, Fix64 m33)
        {
            this->m00 = m00; this->m01 = m01; this->m02 = m02; this->m03 = m03;
            this->m10 = m10; this->m11 = m11; this->m12 = m12; this->m13 = m13;
            this->m20 = m20; this->m21 = m21; this->m22 = m22; this->m23 = m23;
            this->m30 = m30; this->m31 = m31; this->m32 = m32; this->m33 = m33;
        }

        const static FMatrix4 Identity;

        const static FMatrix4 Zero;

        Fix64 Determinant() const;

            
        /// <summary>
        /// 求逆矩阵
        /// </summary>
        //Fix64 inverse { get; }

        bool IsIdentity();
        
        /// <summary>
        /// 转置矩阵
        /// </summary>
        FMatrix4 Transpose();

        static Fix64 Determinant(FMatrix4 m);

        FVector4 GetRow(int i);

        void SetRow(int i, FVector4 v);

        FVector4 GetColumn(int i);

        void SetColumn(int i, FVector4 v);

        static FMatrix4 Scale(FVector3 v);
        
        static FMatrix4 Scale(Fix64 s);

        //
        // 摘要:
        //     ///
        //     Creates a translation, rotation and scaling matrix.
        //     ///
        //
        // 参数:
        //   pos:
        //
        //   q:
        //
        //   s:
        //static FMatrix4 TRS(FVector3 pos, FQuaternion q, FVector3 s)
        //{
          //  UnityEngine.Matrix4x4
       // }

        /// <summary>
        /// builds matrix4 from quaternion.
        /// </summary>
        /// <param name="q"></param>
        /// <returns></returns>
       // static FMatrix4 RotateAboutAxis(Fix64 angle, FVector3 axis)
        //{
            // theta =
        //}

        FVector3 GetAxisX();

        FVector3 GetAxisY();

        FVector3 GetAxisZ();

        FVector3 GetOrigin();

        static FMatrix4 TS(FVector3 pos, FVector3 scale);
        
        static FMatrix4 Translate(FVector3 v);

        static FMatrix4 RotateX(Fix64 rad);
        
        static FMatrix4 RotateY(Fix64 rad);
        
        static FMatrix4 RotateZ(Fix64 rad);

        /// <summary>
        /// 推导思路：
        /// 根据变换公式：
        /// v' = cos(theta)*(v - dot(v,n)*n) + sin(theta)*(cross(n,v))+dot(v,n)*n)
        /// 分别将三个基向量(X=(1,0,0),Y=(0,1,0),Z=(0,0,1))进行旋转，得到旋转后的子空间S'
        /// 由于v定义在S空间，经旋转之后，v'的值在s'空间中与v在s空间中的值相等，所以，只要将v’从s‘空间转到s空间，就可以得到旋转后的值v''
        /// </summary>
        /// <param name="theta">rotate angle in rad.</param>
        /// <param name="n"></param>
        /// <returns></returns>
        static FMatrix4 RotateAxis(Fix64 theta, FVector3 n);

        //void SetTRS(FVector3 pos, FQuaternion q, FVector3 s);

        //static FVector3 MultiplyVector

        /// <summary>
        /// 4x4 * 4x1 列向量
        /// </summary>
        /// <param name="lhs"></param>
        /// <param name="v"></param>
        /// <returns></returns>
        friend FVector4 operator *(FMatrix4 lhs, FVector4 v);

        friend FMatrix4 operator *(FMatrix4 lhs, FMatrix4 rhs);

        static FMatrix4 Multiply(FMatrix4& lhs, FMatrix4& rhs);
        
        friend bool operator ==(FMatrix4 lhs, FMatrix4 rhs);

        friend bool operator !=(FMatrix4 lhs, FMatrix4 rhs);
    };
}


#endif /* FMatrix4_h */
