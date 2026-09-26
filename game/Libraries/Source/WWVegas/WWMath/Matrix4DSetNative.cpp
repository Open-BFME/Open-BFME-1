// Native matrix setters share this TU so Set(Coord3D) can inline SetIdentity.
// The unrelated naked Set(Coord3D,float) remains in matrix4d.cpp.
#include "matrix4d.h"

Matrix4D &Matrix4D::Set(
    float m00, float m01, float m02, float m03,
    float m10, float m11, float m12, float m13,
    float m20, float m21, float m22, float m23,
    float m30, float m31, float m32, float m33)
{
    values[0] = m00;
    values[1] = m01;
    values[2] = m02;
    values[3] = m03;
    values[4] = m10;
    values[5] = m11;
    values[6] = m12;
    values[7] = m13;
    values[8] = m20;
    values[9] = m21;
    values[10] = m22;
    values[11] = m23;
    values[12] = m30;
    values[13] = m31;
    values[14] = m32;
    values[15] = m33;
    return *this;
}

Matrix4D &Matrix4D::SetIdentity()
{
    unsigned int zero = 0;
    unsigned int one = 0x3f800000;

    ((unsigned int *)values)[0] = one;
    ((unsigned int *)values)[1] = zero;
    ((unsigned int *)values)[2] = zero;
    ((unsigned int *)values)[3] = zero;
    ((unsigned int *)values)[4] = zero;
    ((unsigned int *)values)[5] = one;
    ((unsigned int *)values)[6] = zero;
    ((unsigned int *)values)[7] = zero;
    ((unsigned int *)values)[8] = zero;
    ((unsigned int *)values)[9] = zero;
    ((unsigned int *)values)[10] = one;
    ((unsigned int *)values)[11] = zero;
    ((unsigned int *)values)[12] = zero;
    ((unsigned int *)values)[13] = zero;
    ((unsigned int *)values)[14] = zero;
    ((unsigned int *)values)[15] = one;
    return *this;
}

Matrix4D &Matrix4D::Set(const Coord3D &translation)
{
    SetIdentity();
    values[3] = translation.x;
    values[7] = translation.y;
    values[11] = translation.z;
    return *this;
}
