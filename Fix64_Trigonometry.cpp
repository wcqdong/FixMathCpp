//
//  Fix64_Trigonometry.cpp
//  MathLib
//
//  Created by christ on 2020/7/16.
//  Copyright © 2020 christ. All rights reserved.
//

#include "Fix64.h"
#include <fstream>
#include <cmath>
using namespace FMath;

Fix64 Fix64::Sin(Fix64 angle)
{
//    bool flipHorizontal;
//    bool flipVertical;
//    long num = ClampSinValue(angle.rawValue, out flipHorizontal, out flipVertical);
//    long range_max = pi.rawValue / 2;
//    if (num >= range_max)
//    {
//        num = range_max;
//    }
//    long value = SinLut[flipHorizontal ? ((SinLut.Length - 1) - ((int)num)) : ((int)num)];
//
//    return FromRawValue(flipVertical ? -value : value);
    return One;
}

int64_t Fix64::ClampSinValue(int64_t radian, int64_t& flipHorizontal, bool& flipVertical)
{
    return 0;
}

Fix64 Fix64::Cos(Fix64 angle)
{
    return One;
}

Fix64 Fix64::Tan(Fix64 angle)
{
    return One;
}

Fix64 Fix64::Cot(Fix64 val)
{
    return One;
}

Fix64 Fix64::Asin(Fix64 val)
{
    return One;
}

Fix64 Fix64::Acos(Fix64 val)
{
    return One;
}

Fix64 Fix64::Atan(Fix64 val)
{
    return One;
}

Fix64 Fix64::Acot(Fix64 val)
{
    return One;
}


#define Pi 3.1415926535897931

void Fix64::__GenerateSinLut()
{
    std::ofstream fileStream("Fix64SinLut.cpp");
    fileStream << "int64_t Fix64::sintable[] = {";
    
    int64_t range_max = PI.rawValue / 2;
    for (int64_t i = 0; i <= range_max; i++)
    {
        if ((i % 8) == 0)
        {
            fileStream << std::endl;
            fileStream << "     ";
        }
        double num = (double)i / range_max * Pi / 2;
        int64_t value = Fix64::FromDouble(sin(num)).rawValue;
        fileStream << value << "L,";
    }
    fileStream << "\n};";
    
    fileStream << "int Fix64::sintableLen = " << range_max + 1 << endl;
    
//    using (StreamWriter writer = ios("Fix64SinLut.cpp"))
//    {
//        writer.Write("namespace GameFramework.FixedMath {\r\n    partial struct Fix64 {\r\n        public static readonly long[] SinLut = new[] {");
//        long range_max = pi.rawValue / 2;
//        for (long i = 0; i <= range_max; i++)
//        {
//            if ((i % 8) == 0)
//            {
//                writer.WriteLine();
//                writer.Write("            ");
//            }
//            double num = (double)i / range_max * System.Math.PI / 2;
//            long value = Fix64.FromDouble(System.Math.Sin(num)).rawValue;
//            writer.Write(string.Format("0x{0:X}L, ", value));
//        }
//        writer.Write("\r\n        };\r\n    }\r\n}");
//    }
}

