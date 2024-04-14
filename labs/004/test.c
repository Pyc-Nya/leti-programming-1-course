#include <math.h>

float square(float a, float b, float c) {
    float p;
    p = (a + b + c) / 2;
    
    return sqrt(p * (p - a) * (p - b) * (p - c));
}