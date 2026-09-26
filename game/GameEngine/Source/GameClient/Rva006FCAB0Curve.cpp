// cl: /O2
#include <math.h>

float Rva006FCAB0Curve(float value)
{
    float square = value * value;
    return square + (sqrtf(value) - square) * value;
}
