//
// Created by nam62 on 23.02.2020.
//
#include <stdlib.h>
#include <math.h>
#include "helpers.h"

int compareX(const void* a, const void* b)
{
    struct Point *p1 = (struct Point *)a,  *p2 = (struct Point *)b;
    return (int) (p1->x - p2->x);
}

int compareY(const void* a, const void* b)
{
    struct Point *p1 = (struct Point *)a,   *p2 = (struct Point *)b;
    return  (int) (p1->y - p2->y);
}


double stripClosest(struct Point strip[], int size, double d)
{
    double min = d;  // Initialize the minimum distance as d

    qsort(strip, size, sizeof(struct Point), compareY);

    // Pick all points one by one and try the next points till the difference
    // between y coordinates is smaller than d.
    // This is a proven fact that this loop runs at most 6 times
    for (int i = 0; i < size; ++i)
        for (int j = i+1; j < size; ++j)
            if (dist(strip[i],strip[j]) < min)
                min = dist(strip[i], strip[j]);

    return min;
}


double min(double x, double y)
{
    return (x < y)? x : y;
}


double dist(struct Point p1, struct Point p2)
{
    return sqrt( (p1.x - p2.x)*(p1.x - p2.x) +
                 (p1.y - p2.y)*(p1.y - p2.y)
    );
}