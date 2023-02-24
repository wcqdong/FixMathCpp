//
//  main.cpp
//  MathLib
//
//  Created by christ on 2020/7/8.
//  Copyright © 2020 christ. All rights reserved.
//

#include <iostream>
#include "Fix64.h"
using namespace FMath;
using namespace std;

void Case1()
{
    Fix64 f1(0.1);
    Fix64 f2(0.2);
    std::cout << (f1 + f2).ToString() << endl;
    //cout << true << endl;
    std::cout << ((f1 + f2)==Fix64(0.3)) << endl;

}

void Case2()
{
    Fix64 f1(-0.1);
    // 取符号位 1位正  -1为负
    std::cout << f1.Sign() << endl;

    std::cout << Fix64::PI.rawValue << endl;

    Fix64 f2(3.1415926);
    std::cout << f2.rawValue << endl;


}

int main(int argc, const char * argv[]) {
    // insert code here...
//    Case1();
    Case2();
    Fix64::__GenerateSinLut();
    return 0;
}
