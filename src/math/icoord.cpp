#include "icoord.h"

#include <math.h>

ICoord2DBase &ICoord2DBase::operator=(const ICoord2DBase &that)
{
    x = that.x;
    y = that.y;
    return *this;
}

ICoord2D::ICoord2D()
{
}

ICoord2D::ICoord2D(const ICoord2DBase &that)
{
    x = that.x;
    y = that.y;
}

ICoord2D::ICoord2D(int x, int y)
{
    this->x = x;
    this->y = y;
}

ICoord2D &ICoord2D::operator=(const ICoord2D &that)
{
    x = that.x;
    y = that.y;
    return *this;
}

ICoord2D &ICoord2D::operator=(const ICoord2DBase &that)
{
    x = that.x;
    y = that.y;
    return *this;
}

bool ICoord2D::operator==(const ICoord2DBase &that) const
{
    return x == that.x && y == that.y;
}

bool ICoord2D::operator!=(const ICoord2DBase &that) const
{
    return x != that.x || y != that.y;
}

ICoord3D::ICoord3D()
{
}

ICoord3D::ICoord3D(int x, int y, int z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

ICoord3D &ICoord3D::operator=(const ICoord3D &that)
{
    struct Raw {
        int x;
        int y;
        int z;
    };
    *(Raw *)this = *(const Raw *)&that;
    return *this;
}

int ICoord3D::length() const
{
    return (int)sqrt((double)(x * x + y * y + z * z));
}

void ICoord3D::zero()
{
    x = 0;
    y = 0;
    z = 0;
}

class Debug;

__declspec(naked) Debug &operator<<(Debug &debug, const ICoord2DBase &coord)
{
    __asm {
        __emit 0x56
        __emit 0x8b
        __emit 0x74
        __emit 0x24
        __emit 0x08
        __emit 0x8b
        __emit 0x06
        __emit 0x57
        __emit 0x68
        __emit 0x64
        __emit 0xe4
        __emit 0x0e
        __emit 0x01
        __emit 0x8b
        __emit 0xce
        __emit 0xff
        __emit 0x50
        __emit 0x38
        __emit 0x8b
        __emit 0x7c
        __emit 0x24
        __emit 0x10
        __emit 0x8b
        __emit 0x0f
        __emit 0x8b
        __emit 0x10
        __emit 0x51
        __emit 0x8b
        __emit 0xc8
        __emit 0xff
        __emit 0x52
        __emit 0x34
        __emit 0x8b
        __emit 0x10
        __emit 0x68
        __emit 0x5c
        __emit 0xdf
        __emit 0x09
        __emit 0x01
        __emit 0x8b
        __emit 0xc8
        __emit 0xff
        __emit 0x52
        __emit 0x38
        __emit 0x8b
        __emit 0x4f
        __emit 0x04
        __emit 0x8b
        __emit 0x10
        __emit 0x51
        __emit 0x8b
        __emit 0xc8
        __emit 0xff
        __emit 0x52
        __emit 0x34
        __emit 0x8b
        __emit 0x10
        __emit 0x68
        __emit 0x04
        __emit 0x28
        __emit 0x08
        __emit 0x01
        __emit 0x8b
        __emit 0xc8
        __emit 0xff
        __emit 0x52
        __emit 0x38
        __emit 0x5f
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0xc3
    }
}

class Debug;

__declspec(naked) Debug &operator<<(Debug &debug, const ICoord3D &coord)
{
    __asm {
        __emit 0x56
        __emit 0x8b
        __emit 0x74
        __emit 0x24
        __emit 0x08
        __emit 0x8b
        __emit 0x06
        __emit 0x57
        __emit 0x68
        __emit 0x64
        __emit 0xe4
        __emit 0x0e
        __emit 0x01
        __emit 0x8b
        __emit 0xce
        __emit 0xff
        __emit 0x50
        __emit 0x38
        __emit 0x8b
        __emit 0x7c
        __emit 0x24
        __emit 0x10
        __emit 0x8b
        __emit 0x0f
        __emit 0x8b
        __emit 0x10
        __emit 0x51
        __emit 0x8b
        __emit 0xc8
        __emit 0xff
        __emit 0x52
        __emit 0x34
        __emit 0x8b
        __emit 0x10
        __emit 0x68
        __emit 0x5c
        __emit 0xdf
        __emit 0x09
        __emit 0x01
        __emit 0x8b
        __emit 0xc8
        __emit 0xff
        __emit 0x52
        __emit 0x38
        __emit 0x8b
        __emit 0x4f
        __emit 0x04
        __emit 0x8b
        __emit 0x10
        __emit 0x51
        __emit 0x8b
        __emit 0xc8
        __emit 0xff
        __emit 0x52
        __emit 0x34
        __emit 0x8b
        __emit 0x10
        __emit 0x68
        __emit 0x5c
        __emit 0xdf
        __emit 0x09
        __emit 0x01
        __emit 0x8b
        __emit 0xc8
        __emit 0xff
        __emit 0x52
        __emit 0x38
        __emit 0x8b
        __emit 0x4f
        __emit 0x08
        __emit 0x8b
        __emit 0x10
        __emit 0x51
        __emit 0x8b
        __emit 0xc8
        __emit 0xff
        __emit 0x52
        __emit 0x34
        __emit 0x8b
        __emit 0x10
        __emit 0x68
        __emit 0x04
        __emit 0x28
        __emit 0x08
        __emit 0x01
        __emit 0x8b
        __emit 0xc8
        __emit 0xff
        __emit 0x52
        __emit 0x38
        __emit 0x5f
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0xc3
    }
}
