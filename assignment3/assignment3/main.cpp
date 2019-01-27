//
//  main.cpp
//  assignment3
//
//  Created by Devin Sevy on 1/16/19.
//  Copyright © 2019 Devin Sevy. All rights reserved.
//

#include "ClassifierTest.hpp"
#include <iostream>
#include <vector>
#include <math.h>
#include <iomanip>
#define PI 3.14159265
using namespace std;

double xB, yB, xC, yC, xD, yD;

int main(int argc, const char * argv[]) {
    // Square
    xB = 6; yB = 0; xC = 6; yC = 6; xD = 0; yD = 6;
    struct slopes slope = slopeStruct(xB, yB, xC, yC, xD, yD);
    struct dists dist = distsStruct(xB, yB, xC, yC, xD, yD);
    printShape(slope, dist);
    
    // Rectangle
    xB = 6; yB = 0; xC = 6; yC = 10; xD = 0; yD = 10;
    slope = slopeStruct(xB, yB, xC, yC, xD, yD);
    dist = distsStruct(xB, yB, xC, yC, xD, yD);
    printShape(slope, dist);
    
    // Rhombus
    xB = 5; yB = 0; xC = 8; yC = 4; xD = 3; yD = 4;
    slope = slopeStruct(xB, yB, xC, yC, xD, yD);
    dist = distsStruct(xB, yB, xC, yC, xD, yD);
    printShape(slope, dist);
    
    // Trapezoid
    xB = 6; yB = 0; xC = 4; yC = 5; xD = 2; yD = 5;
    slope = slopeStruct(xB, yB, xC, yC, xD, yD);
    dist = distsStruct(xB, yB, xC, yC, xD, yD);
    printShape(slope, dist);
    
    // Kite
    xB = 6; yB = 0; xC = 8; yC = 4; xD = 2; yD = 6;
    slope = slopeStruct(xB, yB, xC, yC, xD, yD);
    dist = distsStruct(xB, yB, xC, yC, xD, yD);
    printShape(slope, dist);
    return 0;
}
