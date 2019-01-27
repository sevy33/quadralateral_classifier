//
//  ClassifierTest.cpp
//  assignment3
//
//  Created by Devin Sevy on 1/26/19.
//  Copyright © 2019 Devin Sevy. All rights reserved.
//

#include "ClassifierTest.hpp"
#include <iostream>
#include <vector>
#include <math.h>
#include <iomanip>
#define PI 3.14159265
using namespace std;


struct slopes slopeStruct(double xB, double yB, double xC, double yC, double xD, double yD) {
    struct slopes slope;
    
    slope.slopeAB = findSlope(0, 0, xB, yB);
    slope.slopeBC = findSlope(xB, yB, xC, yC);
    slope.slopeCD = findSlope(xC, yC, xD, yD);
    slope.slopeDA = findSlope(xD, yD, 0, 0);
    
    return slope;
}

struct dists distsStruct(double xB, double yB, double xC, double yC, double xD, double yD) {
    struct dists dist;
    
    dist.distAB = findDist(0, 0, xB, yB);
    dist.distBC = findDist(xB, yB, xC, yC);
    dist.distCD = findDist(xC, yC, xD, yD);
    dist.distDA = findDist(xD, yD, 0, 0);
    
    return dist;
}

double findSlope(double x1, double y1, double x2, double y2) {
    double slope = ((y2 - y1)/(x2 - x1));
    if(slope == +INFINITY || slope == -INFINITY) slope = 0;
    return slope;
}

double findDist(double x1, double y1, double x2, double y2) {
    double powX = pow((x2 - x1), 2);
    double powY = pow((y2 - y1), 2);
    double dist = sqrt((powX + powY));
    return dist;
}

bool isParallelograms(slopes &slope) {
    if(slope.slopeAB == slope.slopeCD && slope.slopeBC == slope.slopeDA) return true;
    return false;
}

bool isTrapezoid(slopes &slope) {
    if(slope.slopeAB == slope.slopeCD && slope.slopeBC != slope.slopeDA) return true;
    else if(slope.slopeAB != slope.slopeCD && slope.slopeBC == slope.slopeDA) return true;
    return false;
}

bool isSquareOrRhom(dists &dist) {
    double sideTotal = 4 * dist.distAB;
    double sum = dist.distAB + dist.distBC + dist.distCD + dist.distDA;
    if(sideTotal == sum) return true;
    return false;
}

bool isSquare(dists &dist) {
    int ang1 = atan((dist.distDA/dist.distAB)) * (180/PI);
    int ang2 = atan((dist.distCD/dist.distBC)) * (180/PI);
    
    if((ang1 + ang2) == 90.000) return true;
    return false;
}

void printShape(slopes &slope, dists &dist) {
    if(isParallelograms(slope)) {
        if(isSquareOrRhom(dist)) {
            if(isSquare(dist)) cout << "Square" << endl;
            else cout << "Rhombus" << endl;
        } else {
            cout << "Rectangle" << endl;
        }
    } else {
        if(isTrapezoid(slope)) cout << "Trapezoid" << endl;
        else cout << "Kite" << endl;
    }
}
