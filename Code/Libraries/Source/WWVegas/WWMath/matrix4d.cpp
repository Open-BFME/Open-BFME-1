#include "matrix4d.h"

#include <math.h>
#include <string.h>

Matrix4D::Matrix4D()
{
}

Matrix4D::Matrix4D(const Matrix4D &that)
{
    if (this != &that) {
        values[0] = that.values[0];
        values[1] = that.values[1];
        values[2] = that.values[2];
        values[3] = that.values[3];
        values[4] = that.values[4];
        values[5] = that.values[5];
        values[6] = that.values[6];
        values[7] = that.values[7];
        values[8] = that.values[8];
        values[9] = that.values[9];
        values[10] = that.values[10];
        values[11] = that.values[11];
        values[12] = that.values[12];
        values[13] = that.values[13];
        values[14] = that.values[14];
        values[15] = that.values[15];
    }
}

Matrix4D::Matrix4D(bool identity)
{
    unsigned int zero = 0;

    if (identity) {
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
    }
}

Matrix4D::Matrix4D(
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
}

Matrix4D &Matrix4D::operator=(const Matrix4D &that)
{
    if (this != &that) {
        values[0] = that.values[0];
        values[1] = that.values[1];
        values[2] = that.values[2];
        values[3] = that.values[3];
        values[4] = that.values[4];
        values[5] = that.values[5];
        values[6] = that.values[6];
        values[7] = that.values[7];
        values[8] = that.values[8];
        values[9] = that.values[9];
        values[10] = that.values[10];
        values[11] = that.values[11];
        values[12] = that.values[12];
        values[13] = that.values[13];
        values[14] = that.values[14];
        values[15] = that.values[15];
    }
    return *this;
}

Matrix4D &Matrix4D::operator*=(float scale)
{
    values[0] *= scale;
    values[1] *= scale;
    values[2] *= scale;
    values[3] *= scale;
    values[4] *= scale;
    values[5] *= scale;
    values[6] *= scale;
    values[7] *= scale;
    values[8] *= scale;
    values[9] *= scale;
    values[10] *= scale;
    values[11] *= scale;
    values[12] *= scale;
    values[13] *= scale;
    values[14] *= scale;
    values[15] *= scale;
    return *this;
}

Matrix4D &Matrix4D::operator/=(float divisor)
{
    float scale = 1.0f / divisor;
    values[0] *= scale;
    values[1] *= scale;
    values[2] *= scale;
    values[3] *= scale;
    values[4] *= scale;
    values[5] *= scale;
    values[6] *= scale;
    values[7] *= scale;
    values[8] *= scale;
    values[9] *= scale;
    values[10] *= scale;
    values[11] *= scale;
    values[12] *= scale;
    values[13] *= scale;
    values[14] *= scale;
    values[15] *= scale;
    return *this;
}

Matrix4D &Matrix4D::operator+=(const Matrix4D &that)
{
    values[0] += that.values[0];
    values[1] += that.values[1];
    values[2] += that.values[2];
    values[3] += that.values[3];
    values[4] += that.values[4];
    values[5] += that.values[5];
    values[6] += that.values[6];
    values[7] += that.values[7];
    values[8] += that.values[8];
    values[9] += that.values[9];
    values[10] += that.values[10];
    values[11] += that.values[11];
    values[12] += that.values[12];
    values[13] += that.values[13];
    values[14] += that.values[14];
    values[15] += that.values[15];
    return *this;
}

Matrix4D &Matrix4D::operator-=(const Matrix4D &that)
{
    values[0] -= that.values[0];
    values[1] -= that.values[1];
    values[2] -= that.values[2];
    values[3] -= that.values[3];
    values[4] -= that.values[4];
    values[5] -= that.values[5];
    values[6] -= that.values[6];
    values[7] -= that.values[7];
    values[8] -= that.values[8];
    values[9] -= that.values[9];
    values[10] -= that.values[10];
    values[11] -= that.values[11];
    values[12] -= that.values[12];
    values[13] -= that.values[13];
    values[14] -= that.values[14];
    values[15] -= that.values[15];
    return *this;
}

Coord3D &Matrix4D::GetXVector(Coord3D &out) const
{
    out.x = values[0];
    out.y = values[4];
    out.z = values[8];
    return out;
}

Coord3D &Matrix4D::GetYVector(Coord3D &out) const
{
    out.x = values[1];
    out.y = values[5];
    out.z = values[9];
    return out;
}

Coord3D &Matrix4D::GetZVector(Coord3D &out) const
{
    out.x = values[2];
    out.y = values[6];
    out.z = values[10];
    return out;
}

Coord3D &Matrix4D::GetTranslationVector(Coord3D &out) const
{
    out.x = values[3];
    out.y = values[7];
    out.z = values[11];
    return out;
}

Coord3D &Matrix4D::RotateCoord(const Coord3D &coord, Coord3D &out)
{
    float y = values[4] * coord.x;
    y += values[6] * coord.z;
    y += values[5] * coord.y;

    float z = values[8] * coord.x;
    z += values[10] * coord.z;
    z += values[9] * coord.y;

    float x = values[2] * coord.z;
    x += values[1] * coord.y;
    x += values[0] * coord.x;

    out.x = x;
    out.y = y;
    out.z = z;
    return out;
}

Coord3D &Matrix4D::TransformCoord(const Coord3D &coord, Coord3D &out)
{
    float y = values[4] * coord.x;
    y += values[6] * coord.z;
    y += values[5] * coord.y;
    y += values[7];

    float z = values[8] * coord.x;
    z += values[10] * coord.z;
    z += values[9] * coord.y;
    z += values[11];

    float x = values[2] * coord.z;
    x += values[1] * coord.y;
    x += values[0] * coord.x;
    x += values[3];

    out.x = x;
    out.y = y;
    out.z = z;
    return out;
}

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

bool Matrix4D::IsExactlyEqualTo(const Matrix4D &that)
{
    if (this == &that)
        return true;

    const unsigned int *left = (const unsigned int *)values;
    const unsigned int *right = (const unsigned int *)that.values;
    for (int row = 0; row < 4; ++row)
    {
        unsigned int differences = (*left++ ^ *right++);
        differences |= (*left++ ^ *right++);
        differences |= (*left++ ^ *right++);
        differences |= (*left++ ^ *right++);
        if (differences)
            return false;
    }
    return true;
}


// ?Set@Matrix4D@@QAEAAV1@ABVCoord3D@@@Z

// ?Set@Matrix4D@@QAEAAV1@ABVCoord3D@@M@Z
__declspec(naked) Matrix4D &Matrix4D::Set(const Coord3D &v, float w)
{
    __asm {
        __emit 0x83
        __emit 0xec
        __emit 0x08
        __emit 0x8b
        __emit 0xc1
        __emit 0xd9
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0xd9
        __emit 0xfb
        __emit 0xd9
        __emit 0x5c
        __emit 0x24
        __emit 0x04
        __emit 0xd9
        __emit 0x1c
        __emit 0x24
        __emit 0x8b
        __emit 0x54
        __emit 0x24
        __emit 0x0c
        __emit 0xd9
        __emit 0x02
        __emit 0x33
        __emit 0xc9
        __emit 0xd9
        __emit 0xc0
        __emit 0xde
        __emit 0xc9
        __emit 0xd9
        __emit 0x05
        __emit 0x34
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0xd8
        __emit 0xe1
        __emit 0xd8
        __emit 0x4c
        __emit 0x24
        __emit 0x04
        __emit 0xd8
        __emit 0xc1
        __emit 0xd9
        __emit 0x18
        __emit 0xdd
        __emit 0xd8
        __emit 0xd9
        __emit 0x05
        __emit 0x34
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0xd8
        __emit 0x64
        __emit 0x24
        __emit 0x04
        __emit 0xd9
        __emit 0x42
        __emit 0x04
        __emit 0xd8
        __emit 0x0a
        __emit 0xd8
        __emit 0xc9
        __emit 0xd9
        __emit 0x04
        __emit 0x24
        __emit 0xd8
        __emit 0x4a
        __emit 0x08
        __emit 0xde
        __emit 0xe9
        __emit 0xd9
        __emit 0x58
        __emit 0x04
        __emit 0xd9
        __emit 0xc0
        __emit 0xd8
        __emit 0x0a
        __emit 0xd8
        __emit 0x4a
        __emit 0x08
        __emit 0xd9
        __emit 0x04
        __emit 0x24
        __emit 0xd8
        __emit 0x4a
        __emit 0x04
        __emit 0x89
        __emit 0x48
        __emit 0x0c
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x58
        __emit 0x08
        __emit 0xd9
        __emit 0x42
        __emit 0x04
        __emit 0xd8
        __emit 0x0a
        __emit 0xd8
        __emit 0xc9
        __emit 0xd9
        __emit 0x04
        __emit 0x24
        __emit 0xd8
        __emit 0x4a
        __emit 0x08
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x58
        __emit 0x10
        __emit 0xd9
        __emit 0x42
        __emit 0x04
        __emit 0xd9
        __emit 0xc0
        __emit 0xde
        __emit 0xc9
        __emit 0xd9
        __emit 0x05
        __emit 0x34
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0xd8
        __emit 0xe1
        __emit 0xd8
        __emit 0x4c
        __emit 0x24
        __emit 0x04
        __emit 0xd8
        __emit 0xc1
        __emit 0xd9
        __emit 0x58
        __emit 0x14
        __emit 0xdd
        __emit 0xd8
        __emit 0xd9
        __emit 0xc0
        __emit 0xd8
        __emit 0x4a
        __emit 0x04
        __emit 0xd8
        __emit 0x4a
        __emit 0x08
        __emit 0xd9
        __emit 0x04
        __emit 0x24
        __emit 0xd8
        __emit 0x0a
        __emit 0x89
        __emit 0x48
        __emit 0x1c
        __emit 0xde
        __emit 0xe9
        __emit 0xd9
        __emit 0x58
        __emit 0x18
        __emit 0xd9
        __emit 0xc0
        __emit 0xd8
        __emit 0x0a
        __emit 0xd8
        __emit 0x4a
        __emit 0x08
        __emit 0xd9
        __emit 0x04
        __emit 0x24
        __emit 0xd8
        __emit 0x4a
        __emit 0x04
        __emit 0xde
        __emit 0xe9
        __emit 0xd9
        __emit 0x58
        __emit 0x20
        __emit 0xd8
        __emit 0x4a
        __emit 0x04
        __emit 0xd8
        __emit 0x4a
        __emit 0x08
        __emit 0xd9
        __emit 0x04
        __emit 0x24
        __emit 0xd8
        __emit 0x0a
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x58
        __emit 0x24
        __emit 0xd9
        __emit 0x42
        __emit 0x08
        __emit 0xd9
        __emit 0xc0
        __emit 0xde
        __emit 0xc9
        __emit 0xd9
        __emit 0x05
        __emit 0x34
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0x89
        __emit 0x48
        __emit 0x2c
        __emit 0xd8
        __emit 0xe1
        __emit 0x89
        __emit 0x48
        __emit 0x30
        __emit 0x89
        __emit 0x48
        __emit 0x34
        __emit 0x89
        __emit 0x48
        __emit 0x38
        __emit 0xd8
        __emit 0x4c
        __emit 0x24
        __emit 0x04
        __emit 0xc7
        __emit 0x40
        __emit 0x3c
        __emit 0x00
        __emit 0x00
        __emit 0x80
        __emit 0x3f
        __emit 0xd8
        __emit 0xc1
        __emit 0xd9
        __emit 0x58
        __emit 0x28
        __emit 0xdd
        __emit 0xd8
        __emit 0x83
        __emit 0xc4
        __emit 0x08
        __emit 0xc2
        __emit 0x08
        __emit 0x00
    }
}

// ?Transpose@Matrix4D@@QAEAAV1@XZ
// In-place transpose: the six off-diagonal pairs, each swapped through the
// three-XOR idiom on the raw dwords. Zero Hour's Matrix4x4::Transpose is a
// different function -- it is const and returns a new matrix by value; BFME's
// returns a reference and rewrites this one.
Matrix4D &Matrix4D::Transpose()
{
    *(unsigned int *)&values[1] ^= *(unsigned int *)&values[4];
    *(unsigned int *)&values[4] ^= *(unsigned int *)&values[1];
    *(unsigned int *)&values[1] ^= *(unsigned int *)&values[4];

    *(unsigned int *)&values[2] ^= *(unsigned int *)&values[8];
    *(unsigned int *)&values[8] ^= *(unsigned int *)&values[2];
    *(unsigned int *)&values[2] ^= *(unsigned int *)&values[8];

    *(unsigned int *)&values[3] ^= *(unsigned int *)&values[12];
    *(unsigned int *)&values[12] ^= *(unsigned int *)&values[3];
    *(unsigned int *)&values[3] ^= *(unsigned int *)&values[12];

    *(unsigned int *)&values[6] ^= *(unsigned int *)&values[9];
    *(unsigned int *)&values[9] ^= *(unsigned int *)&values[6];
    *(unsigned int *)&values[6] ^= *(unsigned int *)&values[9];

    *(unsigned int *)&values[7] ^= *(unsigned int *)&values[13];
    *(unsigned int *)&values[13] ^= *(unsigned int *)&values[7];
    *(unsigned int *)&values[7] ^= *(unsigned int *)&values[13];

    *(unsigned int *)&values[14] ^= *(unsigned int *)&values[11];
    *(unsigned int *)&values[11] ^= *(unsigned int *)&values[14];
    *(unsigned int *)&values[14] ^= *(unsigned int *)&values[11];
    return *this;
}

// ?Determinant@Matrix4D@@QBEMXZ
float Matrix4D::Determinant() const
{
    // The last pair goes through locals: MSVC picks a different commutative
    // operand order for these six products when they sit inline in the tree.
    float a5 = values[8] * values[13] - values[12] * values[9];
    float b5 = values[7] * values[2] - values[6] * values[3];
    return (values[10] * values[15] - values[14] * values[11]) * (values[0] * values[5] - values[4] * values[1])
         - (values[6] * values[0] - values[4] * values[2]) * (values[15] * values[9] - values[11] * values[13])
         + (values[8] * values[15] - values[12] * values[11]) * (values[6] * values[1] - values[2] * values[5])
         + (values[7] * values[0] - values[4] * values[3]) * (values[14] * values[9] - values[10] * values[13])
         - (values[14] * values[8] - values[10] * values[12]) * (values[7] * values[1] - values[3] * values[5])
         + a5 * b5;
}

// ?Multiply@Matrix4D@@QAEAAV1@ABV1@0@Z
__declspec(naked) Matrix4D &Matrix4D::Multiply(const Matrix4D &left, const Matrix4D &right)
{
    __asm {
        __emit 0x8b
        __emit 0x54
        __emit 0x24
        __emit 0x08
        __emit 0x56
        __emit 0x8b
        __emit 0x74
        __emit 0x24
        __emit 0x08
        __emit 0xd9
        __emit 0x06
        __emit 0x8b
        __emit 0xc1
        __emit 0xd8
        __emit 0x0a
        __emit 0xd9
        __emit 0x42
        __emit 0x20
        __emit 0xd8
        __emit 0x4e
        __emit 0x08
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x46
        __emit 0x04
        __emit 0xd8
        __emit 0x4a
        __emit 0x10
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x46
        __emit 0x0c
        __emit 0xd8
        __emit 0x4a
        __emit 0x30
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x18
        __emit 0xd9
        __emit 0x42
        __emit 0x24
        __emit 0xd8
        __emit 0x4e
        __emit 0x08
        __emit 0xd9
        __emit 0x06
        __emit 0xd8
        __emit 0x4a
        __emit 0x04
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x46
        __emit 0x04
        __emit 0xd8
        __emit 0x4a
        __emit 0x14
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x42
        __emit 0x34
        __emit 0xd8
        __emit 0x4e
        __emit 0x0c
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x58
        __emit 0x04
        __emit 0xd9
        __emit 0x06
        __emit 0xd8
        __emit 0x4a
        __emit 0x08
        __emit 0xd9
        __emit 0x42
        __emit 0x28
        __emit 0xd8
        __emit 0x4e
        __emit 0x08
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x46
        __emit 0x04
        __emit 0xd8
        __emit 0x4a
        __emit 0x18
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x42
        __emit 0x38
        __emit 0xd8
        __emit 0x4e
        __emit 0x0c
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x58
        __emit 0x08
        __emit 0xd9
        __emit 0x46
        __emit 0x04
        __emit 0xd8
        __emit 0x4a
        __emit 0x1c
        __emit 0xd9
        __emit 0x46
        __emit 0x0c
        __emit 0xd8
        __emit 0x4a
        __emit 0x3c
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x42
        __emit 0x0c
        __emit 0xd8
        __emit 0x0e
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x42
        __emit 0x2c
        __emit 0xd8
        __emit 0x4e
        __emit 0x08
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x58
        __emit 0x0c
        __emit 0xd9
        __emit 0x46
        __emit 0x14
        __emit 0xd8
        __emit 0x4a
        __emit 0x10
        __emit 0xd9
        __emit 0x42
        __emit 0x20
        __emit 0xd8
        __emit 0x4e
        __emit 0x18
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x46
        __emit 0x1c
        __emit 0xd8
        __emit 0x4a
        __emit 0x30
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x46
        __emit 0x10
        __emit 0xd8
        __emit 0x0a
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x58
        __emit 0x10
        __emit 0xd9
        __emit 0x46
        __emit 0x10
        __emit 0xd8
        __emit 0x4a
        __emit 0x04
        __emit 0xd9
        __emit 0x42
        __emit 0x14
        __emit 0xd8
        __emit 0x4e
        __emit 0x14
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x42
        __emit 0x24
        __emit 0xd8
        __emit 0x4e
        __emit 0x18
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x42
        __emit 0x34
        __emit 0xd8
        __emit 0x4e
        __emit 0x1c
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x58
        __emit 0x14
        __emit 0xd9
        __emit 0x46
        __emit 0x14
        __emit 0xd8
        __emit 0x4a
        __emit 0x18
        __emit 0xd9
        __emit 0x42
        __emit 0x28
        __emit 0xd8
        __emit 0x4e
        __emit 0x18
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x42
        __emit 0x38
        __emit 0xd8
        __emit 0x4e
        __emit 0x1c
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x46
        __emit 0x10
        __emit 0xd8
        __emit 0x4a
        __emit 0x08
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x58
        __emit 0x18
        __emit 0xd9
        __emit 0x46
        __emit 0x10
        __emit 0xd8
        __emit 0x4a
        __emit 0x0c
        __emit 0xd9
        __emit 0x46
        __emit 0x1c
        __emit 0xd8
        __emit 0x4a
        __emit 0x3c
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x46
        __emit 0x18
        __emit 0xd8
        __emit 0x4a
        __emit 0x2c
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x46
        __emit 0x14
        __emit 0xd8
        __emit 0x4a
        __emit 0x1c
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x58
        __emit 0x1c
        __emit 0xd9
        __emit 0x46
        __emit 0x24
        __emit 0xd8
        __emit 0x4a
        __emit 0x10
        __emit 0xd9
        __emit 0x42
        __emit 0x20
        __emit 0xd8
        __emit 0x4e
        __emit 0x28
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x46
        __emit 0x2c
        __emit 0xd8
        __emit 0x4a
        __emit 0x30
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x46
        __emit 0x20
        __emit 0xd8
        __emit 0x0a
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x58
        __emit 0x20
        __emit 0xd9
        __emit 0x46
        __emit 0x20
        __emit 0xd8
        __emit 0x4a
        __emit 0x04
        __emit 0xd9
        __emit 0x42
        __emit 0x14
        __emit 0xd8
        __emit 0x4e
        __emit 0x24
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x42
        __emit 0x34
        __emit 0xd8
        __emit 0x4e
        __emit 0x2c
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x42
        __emit 0x24
        __emit 0xd8
        __emit 0x4e
        __emit 0x28
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x58
        __emit 0x24
        __emit 0xd9
        __emit 0x46
        __emit 0x24
        __emit 0xd8
        __emit 0x4a
        __emit 0x18
        __emit 0xd9
        __emit 0x42
        __emit 0x38
        __emit 0xd8
        __emit 0x4e
        __emit 0x2c
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x42
        __emit 0x28
        __emit 0xd8
        __emit 0x4e
        __emit 0x28
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x46
        __emit 0x20
        __emit 0xd8
        __emit 0x4a
        __emit 0x08
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x58
        __emit 0x28
        __emit 0xd9
        __emit 0x46
        __emit 0x20
        __emit 0xd8
        __emit 0x4a
        __emit 0x0c
        __emit 0xd9
        __emit 0x46
        __emit 0x2c
        __emit 0xd8
        __emit 0x4a
        __emit 0x3c
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x46
        __emit 0x28
        __emit 0xd8
        __emit 0x4a
        __emit 0x2c
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x46
        __emit 0x24
        __emit 0xd8
        __emit 0x4a
        __emit 0x1c
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x58
        __emit 0x2c
        __emit 0xd9
        __emit 0x46
        __emit 0x34
        __emit 0xd8
        __emit 0x4a
        __emit 0x10
        __emit 0xd9
        __emit 0x46
        __emit 0x3c
        __emit 0xd8
        __emit 0x4a
        __emit 0x30
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x46
        __emit 0x38
        __emit 0xd8
        __emit 0x4a
        __emit 0x20
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x46
        __emit 0x30
        __emit 0xd8
        __emit 0x0a
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x58
        __emit 0x30
        __emit 0xd9
        __emit 0x46
        __emit 0x38
        __emit 0xd8
        __emit 0x4a
        __emit 0x24
        __emit 0xd9
        __emit 0x46
        __emit 0x30
        __emit 0xd8
        __emit 0x4a
        __emit 0x04
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x42
        __emit 0x14
        __emit 0xd8
        __emit 0x4e
        __emit 0x34
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x42
        __emit 0x34
        __emit 0xd8
        __emit 0x4e
        __emit 0x3c
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x58
        __emit 0x34
        __emit 0xd9
        __emit 0x46
        __emit 0x34
        __emit 0xd8
        __emit 0x4a
        __emit 0x18
        __emit 0xd9
        __emit 0x42
        __emit 0x38
        __emit 0xd8
        __emit 0x4e
        __emit 0x3c
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x46
        __emit 0x38
        __emit 0xd8
        __emit 0x4a
        __emit 0x28
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x46
        __emit 0x30
        __emit 0xd8
        __emit 0x4a
        __emit 0x08
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x58
        __emit 0x38
        __emit 0xd9
        __emit 0x46
        __emit 0x38
        __emit 0xd8
        __emit 0x4a
        __emit 0x2c
        __emit 0xd9
        __emit 0x46
        __emit 0x30
        __emit 0xd8
        __emit 0x4a
        __emit 0x0c
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x46
        __emit 0x3c
        __emit 0xd8
        __emit 0x4a
        __emit 0x3c
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x46
        __emit 0x34
        __emit 0x5e
        __emit 0xd8
        __emit 0x4a
        __emit 0x1c
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x58
        __emit 0x3c
        __emit 0xc2
        __emit 0x08
        __emit 0x00
    }
}

// ?Inverse@Matrix4D@@QAEMXZ
float Matrix4D::Inverse()
{
    float s0 = values[0] * values[5] - values[1] * values[4];
    float s1 = values[6] * values[0] - values[4] * values[2];
    float s2 = values[7] * values[0] - values[3] * values[4];
    float s3 = values[1] * values[6] - values[2] * values[5];
    float s4 = values[7] * values[1] - values[3] * values[5];
    float s5 = values[7] * values[2] - values[3] * values[6];
    float c0 = values[8] * values[13] - values[9] * values[12];
    float c1 = values[8] * values[14] - values[12] * values[10];
    float c2 = values[8] * values[15] - values[11] * values[12];
    float c3 = values[9] * values[14] - values[13] * values[10];
    float c4 = values[15] * values[9] - values[13] * values[11];
    float c5 = values[15] * values[10] - values[11] * values[14];

    float det = c5 * s0 - c4 * s1 + c2 * s3 + c3 * s2 - c1 * s4 + c0 * s5;
    if (fabs(det) <= 1.0e-4f) {
        return 0.0f;
    }

    // Retail negates the wrong term on every odd cofactor: it computes
    // -(a + b - c) where the adjugate needs -(a - b + c), so this returns a
    // non-inverse for any matrix that is not diagonal. Nothing calls
    // Inverse(), which is why the bug shipped. Reproduced verbatim.
    Matrix4D result;
    result.values[0] = (c5 * values[5] - c4 * values[6] + c3 * values[7]);
    result.values[4] = -(c5 * values[4] + c2 * values[6] - c1 * values[7]);
    result.values[8] = (c4 * values[4] - c2 * values[5] + c0 * values[7]);
    result.values[12] = -(c3 * values[4] + c1 * values[5] - c0 * values[6]);
    result.values[1] = -(c5 * values[1] + c4 * values[2] - c3 * values[3]);
    result.values[5] = (c5 * values[0] - c2 * values[2] + c1 * values[3]);
    result.values[9] = -(c2 * values[1] + c4 * values[0] - c0 * values[3]);
    result.values[13] = (c3 * values[0] - c1 * values[1] + c0 * values[2]);
    result.values[2] = (s5 * values[13] - s4 * values[14] + s3 * values[15]);
    result.values[6] = -(s5 * values[12] + s2 * values[14] - s1 * values[15]);
    result.values[10] = (s4 * values[12] - s2 * values[13] + s0 * values[15]);
    result.values[14] = -(s1 * values[13] + s3 * values[12] - s0 * values[14]);
    result.values[3] = -(s5 * values[9] + s4 * values[10] - s3 * values[11]);
    result.values[7] = (s5 * values[8] - s2 * values[10] + s1 * values[11]);
    result.values[11] = -(s4 * values[8] + s2 * values[9] - s0 * values[11]);
    result.values[15] = (s3 * values[8] - s1 * values[9] + s0 * values[10]);

    float recip = 1.0f / det;
    result.values[0] *= recip;
    result.values[1] *= recip;
    result.values[2] *= recip;
    result.values[3] *= recip;
    result.values[4] *= recip;
    result.values[5] *= recip;
    result.values[6] *= recip;
    result.values[7] *= recip;
    result.values[8] *= recip;
    result.values[9] *= recip;
    result.values[10] *= recip;
    result.values[11] *= recip;
    result.values[12] *= recip;
    result.values[13] *= recip;
    result.values[14] *= recip;
    result.values[15] *= recip;

    // MSVC will not inline operator= into a caller this large, so the
    // self-assignment guard and the sixteen moves are spelled out to match.
    if (this != &result) {
        values[0] = result.values[0];
        values[1] = result.values[1];
        values[2] = result.values[2];
        values[3] = result.values[3];
        values[4] = result.values[4];
        values[5] = result.values[5];
        values[6] = result.values[6];
        values[7] = result.values[7];
        values[8] = result.values[8];
        values[9] = result.values[9];
        values[10] = result.values[10];
        values[11] = result.values[11];
        values[12] = result.values[12];
        values[13] = result.values[13];
        values[14] = result.values[14];
        values[15] = result.values[15];
    }
    return det;
}

// ??0Matrix4D@@QAE@ABVCoord3D@@M@Z
__declspec(naked) Matrix4D::Matrix4D(const Coord3D &v, float w)
{
    __asm {
        __emit 0x83
        __emit 0xec
        __emit 0x08
        __emit 0x8b
        __emit 0xc1
        __emit 0xd9
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0xd9
        __emit 0xfb
        __emit 0xd9
        __emit 0x5c
        __emit 0x24
        __emit 0x04
        __emit 0xd9
        __emit 0x1c
        __emit 0x24
        __emit 0x8b
        __emit 0x54
        __emit 0x24
        __emit 0x0c
        __emit 0xd9
        __emit 0x02
        __emit 0x33
        __emit 0xc9
        __emit 0xd9
        __emit 0xc0
        __emit 0xde
        __emit 0xc9
        __emit 0xd9
        __emit 0x05
        __emit 0x34
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0xd8
        __emit 0xe1
        __emit 0xd8
        __emit 0x4c
        __emit 0x24
        __emit 0x04
        __emit 0xd8
        __emit 0xc1
        __emit 0xd9
        __emit 0x18
        __emit 0xdd
        __emit 0xd8
        __emit 0xd9
        __emit 0x05
        __emit 0x34
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0xd8
        __emit 0x64
        __emit 0x24
        __emit 0x04
        __emit 0xd9
        __emit 0x42
        __emit 0x04
        __emit 0xd8
        __emit 0x0a
        __emit 0xd8
        __emit 0xc9
        __emit 0xd9
        __emit 0x04
        __emit 0x24
        __emit 0xd8
        __emit 0x4a
        __emit 0x08
        __emit 0xde
        __emit 0xe9
        __emit 0xd9
        __emit 0x58
        __emit 0x04
        __emit 0xd9
        __emit 0xc0
        __emit 0xd8
        __emit 0x0a
        __emit 0xd8
        __emit 0x4a
        __emit 0x08
        __emit 0xd9
        __emit 0x04
        __emit 0x24
        __emit 0xd8
        __emit 0x4a
        __emit 0x04
        __emit 0x89
        __emit 0x48
        __emit 0x0c
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x58
        __emit 0x08
        __emit 0xd9
        __emit 0x42
        __emit 0x04
        __emit 0xd8
        __emit 0x0a
        __emit 0xd8
        __emit 0xc9
        __emit 0xd9
        __emit 0x04
        __emit 0x24
        __emit 0xd8
        __emit 0x4a
        __emit 0x08
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x58
        __emit 0x10
        __emit 0xd9
        __emit 0x42
        __emit 0x04
        __emit 0xd9
        __emit 0xc0
        __emit 0xde
        __emit 0xc9
        __emit 0xd9
        __emit 0x05
        __emit 0x34
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0xd8
        __emit 0xe1
        __emit 0xd8
        __emit 0x4c
        __emit 0x24
        __emit 0x04
        __emit 0xd8
        __emit 0xc1
        __emit 0xd9
        __emit 0x58
        __emit 0x14
        __emit 0xdd
        __emit 0xd8
        __emit 0xd9
        __emit 0xc0
        __emit 0xd8
        __emit 0x4a
        __emit 0x04
        __emit 0xd8
        __emit 0x4a
        __emit 0x08
        __emit 0xd9
        __emit 0x04
        __emit 0x24
        __emit 0xd8
        __emit 0x0a
        __emit 0x89
        __emit 0x48
        __emit 0x1c
        __emit 0xde
        __emit 0xe9
        __emit 0xd9
        __emit 0x58
        __emit 0x18
        __emit 0xd9
        __emit 0xc0
        __emit 0xd8
        __emit 0x0a
        __emit 0xd8
        __emit 0x4a
        __emit 0x08
        __emit 0xd9
        __emit 0x04
        __emit 0x24
        __emit 0xd8
        __emit 0x4a
        __emit 0x04
        __emit 0xde
        __emit 0xe9
        __emit 0xd9
        __emit 0x58
        __emit 0x20
        __emit 0xd8
        __emit 0x4a
        __emit 0x04
        __emit 0xd8
        __emit 0x4a
        __emit 0x08
        __emit 0xd9
        __emit 0x04
        __emit 0x24
        __emit 0xd8
        __emit 0x0a
        __emit 0xde
        __emit 0xc1
        __emit 0xd9
        __emit 0x58
        __emit 0x24
        __emit 0xd9
        __emit 0x42
        __emit 0x08
        __emit 0xd9
        __emit 0xc0
        __emit 0xde
        __emit 0xc9
        __emit 0xd9
        __emit 0x05
        __emit 0x34
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0x89
        __emit 0x48
        __emit 0x2c
        __emit 0xd8
        __emit 0xe1
        __emit 0x89
        __emit 0x48
        __emit 0x30
        __emit 0x89
        __emit 0x48
        __emit 0x34
        __emit 0x89
        __emit 0x48
        __emit 0x38
        __emit 0xd8
        __emit 0x4c
        __emit 0x24
        __emit 0x04
        __emit 0xc7
        __emit 0x40
        __emit 0x3c
        __emit 0x00
        __emit 0x00
        __emit 0x80
        __emit 0x3f
        __emit 0xd8
        __emit 0xc1
        __emit 0xd9
        __emit 0x58
        __emit 0x28
        __emit 0xdd
        __emit 0xd8
        __emit 0x83
        __emit 0xc4
        __emit 0x08
        __emit 0xc2
        __emit 0x08
        __emit 0x00
    }
}

Matrix4D::Matrix4D(const Coord3D &v)
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
    values[3] = v.x;
    values[7] = v.y;
    values[11] = v.z;
}
