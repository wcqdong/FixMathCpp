//
//  Fix64.hpp
//  MathLib
//
//  Created by christ on 2020/7/8.
//  Copyright © 2020 christ. All rights reserved.
//

#ifndef Fix64_hpp
#define Fix64_hpp

#include <stdio.h>
#include <string>
#include <vector>
using namespace std;

namespace FMath
{
    /// <summary>
    /// 定点数类型
    /// 1.定点数(与数值类型的相互转换int<->fixed,float<->fixed),加减乘除运算(+、-、*、\)
    /// 2.位布局：第63位为符号位(1位)，第47-16位为整数位(32位)，第15-0位为小数位（16位）
    /// 3.小数精度：1/65536 = 0.0000152587890625
    /// 4.可以考虑的优化方式，提供一组针对rawvalue的计算函数，用户可以保存中间值，用于后续的计算。
    /// </summary>


    struct Fix64
    {
        static const int fractionBits = 16;
        static const int64_t fractionFactor = ((int64_t)1 << fractionBits);

        static const Fix64 Zero;
        static const Fix64 One;
        static const Fix64 Half;
        static const Fix64 MaxValue;
        static const Fix64 MinValue;
        static const Fix64 E;
        static const Fix64 PI;
        static const Fix64 Epsilon;
        static const Fix64 PositiveInfinity;
        static const Fix64 NegativeInfinity;
        
        static const Fix64 _degToRad;
        static const Fix64 _radToDeg;

        static const Fix64 EN1;
        static const Fix64 EN2;
        static const Fix64 EN3;
        static const Fix64 EN4;
        static const Fix64 EN5;

        int64_t rawValue;
        
        
        
        Fix64(int value);
        explicit Fix64(double value);
        Fix64(float value);
        Fix64(const Fix64& other);
        Fix64();
        
        static Fix64 FromInt(int val);

        static Fix64 FromSingle(float val);

        static Fix64 FromDouble(double val);
        
        //整数部分
        int64_t integer() const;
        
        //小数部分
        int64_t fraction() const;

        double ToDouble() const;

        float ToSingle() const;
        
        bool IsInfinity() const;
        bool IsPositiveInfinity() const;
        bool IsNegativeInfinity() const;

        static Fix64 FromRawValue(int64_t rawValue);
        
        static Fix64 DegToRad(const Fix64& angle);

        static Fix64 RadToDeg(const Fix64& angle);

        static Fix64 FromComponents(int64_t i, int64_t f);

        void GetIntegerAndFraction(int64_t& integer, int64_t& fraction) const;
        
        //operator char();

        Fix64 operator -() const;

        friend Fix64 operator +(const Fix64& a, const Fix64& b);

        friend const Fix64& operator +=(Fix64& a, const Fix64& b);
        
        friend Fix64 operator -(const Fix64& a, const Fix64& b);

        friend bool operator ==(const Fix64& a, const Fix64& b);

        friend bool operator !=(const Fix64& a, const Fix64& b);

        friend bool operator >(const Fix64& a, const Fix64& b);

        friend bool operator >=(const Fix64& a, const Fix64& b);

        friend bool operator <(const Fix64& a, const Fix64& b);

        friend bool operator <=(const Fix64& a, const Fix64& b);

        friend Fix64 operator *(const Fix64& a, const Fix64& b);

        friend Fix64 operator *(const float a, const Fix64& b);
        friend Fix64 operator *(const Fix64& a, const float b);

        friend Fix64 operator *(const Fix64& a, int b);
        friend Fix64 operator *(int a, const Fix64& b);
        friend const Fix64& operator *=(Fix64& a, const Fix64& b);
        

        friend Fix64 operator /(Fix64 a, Fix64 b);
        friend Fix64 operator /(const Fix64& a, int b);
        friend Fix64 operator /(const Fix64& a, float b);
        friend const Fix64& operator /=(Fix64& a, const Fix64 b);
        

        string ToString() const;

        inline int GetHashCode()
        {
            return (int)rawValue;
        }

        inline static Fix64 Max(Fix64 a, Fix64 b)
        {
            return a > b ? a : b;
        }

        inline static Fix64 Min(Fix64 a, Fix64 b)
        {
            return a <= b ? a : b;
        }


        inline static Fix64 Lerp(Fix64 a, Fix64 b, Fix64 t)
        {
            return a + (b - a) * t;
        }

        int32_t Sign();

        static int32_t Sign(int64_t rawValue);

        Fix64 Abs();

        inline static int64_t Abs(int64_t rawValue);

        Fix64 Sqrt();

        /// <summary>
        /// 1/sqrt(x)
        /// </summary>
        /// <returns></returns>
        Fix64 InvSqrt();

        /// <summary>
        /// 64位定点数开平方——用牛顿迭代法实现.
        /// </summary>
        /// <param name="rawValue"></param>
        /// <returns></returns>
        /// <remarks>
        /// sample_count = 1000000
        /// TestNewtonSqrt_Pref elapsedTime = 106471
        /// TestSqrt_Pref elapsedTime = 8140
        /// TestNewtonSqrtLong_Pref elapsedTime = 231810
        /// TestFastSqrt_Pref elapsedTime = 50450
        ///
        /// 结论：
        ///  1.系统库sqrt性能是NewtonSqrtLong的25倍左右
        ///  2.系统库sqrt性能是fastsqrt的5倍
        ///  3.浮点数由于其存储结构，可以迅速找到数量级上的平方数.
        ///
        /// double / double
        /// 00FB4414  movsd       xmm0,mmword ptr [eax+0FBE168h]
        /// 00FB441C  divsd       xmm0, mmword ptr[ecx + 0FBE168h]
        /// long / long
        /// 00FB44B1  mov         ecx, dword ptr samples(0FBE158h)[ecx]
        /// 00FB44B7  mov         eax, dword ptr samples(0FBE158h)[eax]
        /// 00FB44BD  cdq
        /// 00FB44BE  idiv        eax, ecx
        /// 00FB44C0  cdq

        /// int64/int64
        /// 000544CD  call        __alldiv (051352h)
        /// </remarks>
        
        static int64_t Sqrt(int64_t rawValue);

        /// <summary>
        /// 指定初始进行运算
        /// </summary>
        /// <param name="rawValue"></param>
        /// <param name="x0"></param>
        /// <returns></returns>
        static int64_t Sqrt(int64_t rawValue, int64_t x0);

        /// <summary>
        /// 增加一个counter，用于记录迭代的次数，该函数一般用于性能测试。
        /// sqrt性能优化的方向:
        /// 用最小的成本确定初始值，使得初始值距离真实集尽量接近,
        /// Quake3的做法是利用了浮点数表示法中，指数除2，使得初始解与真实解在数量级上一致，
        /// 后续再做一次牛顿迭代法，即可得到相对精确的解，如果需要增大精度，只需要多迭代几次。
        /// </summary>
        /// <param name="rawValue"></param>
        /// <param name="counter"></param>
        /// <returns></returns>
        /// 
        //static int64_t Sqrt(long rawValue, int& counter);

        static int64_t Sqrt(int64_t rawValue, int64_t x0, int& counter);

        static Fix64 Repeat(const Fix64& t, const Fix64& length);

        int Floor();
        
        
        /************ trigonometry ***********/
        static int64_t sintable[];
        static int sintableLen;
        
        
        static Fix64 Sin(Fix64 angle);
        
        static int64_t ClampSinValue(int64_t radian, int64_t& flipHorizontal, bool& flipVertical);
        
        static Fix64 Cos(Fix64 angle);
        
        static Fix64 Tan(Fix64 angle);
        
        static Fix64 Cot(Fix64 val);
        
        static Fix64 Asin(Fix64 val);
        
        static Fix64 Acos(Fix64 val);
        
        static Fix64 Atan(Fix64 val);
        
        static Fix64 Acot(Fix64 val);
        
        static void __GenerateSinLut();
        
        static void __GenerateTanLut();
        
        static void __GenerateAsinLut();
        
        static void __GenerateAtanLut();
    };
}

#endif /* Fix64_hpp */
