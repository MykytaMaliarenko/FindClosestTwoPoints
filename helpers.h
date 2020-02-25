//
// Created by nam62 on 23.02.2020.
//

#ifndef FINDCLOSESTTWOPOINTS_HELPERS_H
#define FINDCLOSESTTWOPOINTS_HELPERS_H

struct Point {
    double x;
    double y;
};

int compareX(const void* a, const void* b);

int compareY(const void* a, const void* b);

double dist(struct Point p1, struct Point p2);

double stripClosest(struct Point strip[], int size, double d);

double min(double x, double y);

#endif //FINDCLOSESTTWOPOINTS_HELPERS_H