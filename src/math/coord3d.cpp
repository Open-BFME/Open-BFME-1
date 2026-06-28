#include "coord3d.h"

Coord3D::~Coord3D()
{
}

void Coord3D::zero()
{
    ((unsigned int *)this)[0] = 0;
    ((unsigned int *)this)[1] = 0;
    ((unsigned int *)this)[2] = 0;
}
