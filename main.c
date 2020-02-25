#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <float.h>
#include "math.h"
#include <time.h>
#include "./helpers.h"

#define testN 50000

struct Boundaries
{
    double maxX;
    double minX;

    double maxY;
    double minY;
};

double doubleRand ( double low, double high )
{
    return ( (double)rand() * ( high - low ) ) / (double)RAND_MAX + low;
}

struct Point* generatePoints(int n, struct Boundaries boundaries);

double bruteForce(struct Point* points, int n);

double closestUtil(struct Point points[], int n);

double closest(struct Point P[], int n);


int main() {
    srand( time ( NULL));
    struct Boundaries boundaries = {
            .maxY = testN*10,
            .minY = -testN,
            .maxX = testN,
            .minX = -testN
    };

    struct Point* points = generatePoints(testN, boundaries);

    clock_t start, end;
    double cpu_time_used;

    start = clock();
    double b = bruteForce(points, testN);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Brute Force took: %lf\n", cpu_time_used);

    start = clock();
    double c = closest(points, testN);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Smart took: %lf\n", cpu_time_used);

    printf("brute: %lf smart: %lf", b, c);

    return 0;
}

struct Point* generatePoints(int n, struct Boundaries boundaries)
{
    struct Point *res = malloc(n * sizeof(struct Point));
    for (int i = 0; i < n; i++)
    {
        struct Point t = {
                .x=doubleRand(boundaries.minX, boundaries.maxX),
                .y=doubleRand(boundaries.minY, boundaries.maxY)
        };
        res[i] = t;
    }

    return res;
}

double bruteForce(struct Point* points, int n)
{
    double min = FLT_MAX;
    for (int i = 0; i < n; ++i)
        for (int j = i+1; j < n; ++j)
            if (dist(points[i], points[j]) < min)
                min = dist(points[i], points[j]);

    return min;
}

double closestUtil(struct Point points[], int n)
{
    // If there are 2 or 3 points, then use brute force
    if (n <= 3)
        return bruteForce(points, n);

    // Find the middle point
    int mid = n/2;
    struct Point midPoint = points[mid];

    // Consider the vertical line passing through the middle point
    // calculate the smallest distance dl on left of middle point and
    // dr on right side

    struct Point* slice = malloc((n-mid) * sizeof(struct Point));
    for (int i = 0; i < (n - mid); i++)
        slice[i] = points[mid + i];


    double dl = closestUtil(points, mid);
    double dr = closestUtil(slice, n-mid);

    free(slice);

    // Find the smaller of two distances
    double d = min(dl, dr);

    // Build an array strip[] that contains points close (closer than d)
    // to the line passing through the middle point
    struct Point strip[n];
    int j = 0;
    for (int i = 0; i < n; i++)
        if (fabs(points[i].x - midPoint.x) < d)
            strip[j] = points[i], j++;

    // Find the closest points in strip.  Return the minimum of d and closest
    // distance is strip[]
    return min(d, stripClosest(strip, j, d) );
}


double closest(struct Point P[], int n)
{
    qsort(P, n, sizeof(struct Point), compareX);
    return closestUtil(P, n);
}