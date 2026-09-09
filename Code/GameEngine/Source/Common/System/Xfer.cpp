// cl: /ICode/GameEngine/Include/Common /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib
#include "xfer.h"
#include "ascii_string.h"
#include "unicode_string.h"
#include "snapshot.h"
#include "coord3d.h"
#include "coord2d.h"
#include "icoord.h"
#include "region.h"
#include "color.h"

Xfer::Xfer()
{
}

Xfer::~Xfer()
{
}

bool Xfer::IsLoading() const
{
    return false;
}

bool Xfer::IsStoring() const
{
    return false;
}

bool Xfer::IsCRC() const
{
    return false;
}

bool Xfer::IsLightCRC() const
{
    return false;
}

void Xfer::SkipBadBlock(Snapshot &snapshot, unsigned int size)
{
}

Xfer &Xfer::operator==(char &c)
{
    XferEnum((const char *)0x62797465, &c, 1);
    return *this;
}

Xfer &Xfer::operator==(unsigned char &c)
{
    XferEnum((const char *)0x75627974, &c, 1);
    return *this;
}

Xfer &Xfer::operator==(short &s)
{
    XferEnum((const char *)0x73687274, &s, 2);
    return *this;
}

Xfer &Xfer::operator==(unsigned short &s)
{
    XferEnum((const char *)0x75736874, &s, 2);
    return *this;
}

Xfer &Xfer::operator==(int &i)
{
    XferEnum((const char *)0x696e74, &i, 4);
    return *this;
}

Xfer &Xfer::operator==(unsigned int &i)
{
    XferEnum((const char *)0x75696e74, &i, 4);
    return *this;
}

Xfer &Xfer::operator==(float &f)
{
    XferEnum((const char *)0x7265616c, &f, 4);
    return *this;
}

Xfer &Xfer::operator==(__int64 &i)
{
    XferEnum((const char *)0x693634, &i, 8);
    return *this;
}

Xfer &Xfer::operator==(bool &b)
{
    XferEnum((const char *)0x626f6f6c, &b, 1);
    return *this;
}

Xfer &Xfer::operator==(Snapshot &snapshot)
{
    snapshot.DoXfer(*this);
    return *this;
}

Xfer &Xfer::operator==(Coord3DBase& v)
{
    XferEnum((const char *)0x00633364, 0, 0);
    XferEnum(0, &v, 12);
    return *this;
}

Xfer &Xfer::operator==(ICoord3D& v)
{
    XferEnum((const char *)0x69633364, 0, 0);
    XferEnum(0, &v, 12);
    return *this;
}

Xfer &Xfer::operator==(Region3D& v)
{
    XferEnum((const char *)0x00723364, 0, 0);
    XferEnum(0, &v.x_min, 12);
    XferEnum(0, &v.x_max, 12);
    return *this;
}

Xfer &Xfer::operator==(IRegion3D& v)
{
    XferEnum((const char *)0x69723364, 0, 0);
    XferEnum(0, &v.x_min, 12);
    XferEnum(0, &v.x_max, 12);
    return *this;
}

Xfer &Xfer::operator==(Coord2D& v)
{
    XferEnum((const char *)0x00633264, 0, 0);
    XferEnum(0, &v, 8);
    return *this;
}

Xfer &Xfer::operator==(ICoord2D& v)
{
    XferEnum((const char *)0x69633264, 0, 0);
    XferEnum(0, &v, 8);
    return *this;
}

Xfer &Xfer::operator==(Region2D& v)
{
    XferEnum((const char *)0x00723264, 0, 0);
    XferEnum(0, &v.x_min, 8);
    XferEnum(0, &v.x_max, 8);
    return *this;
}

Xfer &Xfer::operator==(IRegion2D& v)
{
    XferEnum((const char *)0x69723264, 0, 0);
    XferEnum(0, &v.x_min, 8);
    XferEnum(0, &v.x_max, 8);
    return *this;
}

Xfer &Xfer::operator==(RealRange& v)
{
    XferEnum((const char *)0x726e6765, 0, 0);
    XferEnum(0, &v, 8);
    return *this;
}

Xfer &Xfer::operator==(RGBColor& v)
{
    XferEnum((const char *)0x00726762, 0, 0);
    XferEnum(0, &v, 12);
    return *this;
}

Xfer &Xfer::operator==(RGBAColorReal& v)
{
    XferEnum((const char *)0x72676272, 0, 0);
    XferEnum(0, &v, 16);
    return *this;
}

Xfer &Xfer::operator==(RGBAColorInt& v)
{
    XferEnum((const char *)0x72676269, 0, 0);
    XferEnum(0, &v, 16);
    return *this;
}

void Xfer::Version1()
{
    Version v;
    v.data[0] = 1;
    v.data[1] = 1;
    *this == v;
}







__declspec(naked) Xfer &Xfer::XferRawBytes(void *data, unsigned int size)
{
    __asm {
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x08
        __emit 0x85
        __emit 0xc0
        __emit 0x56
        __emit 0x57
        __emit 0x8b
        __emit 0x7c
        __emit 0x24
        __emit 0x0c
        __emit 0x8b
        __emit 0xf1
        __emit 0x74
        __emit 0x04
        __emit 0x85
        __emit 0xff
        __emit 0x74
        __emit 0x28
        __emit 0x8b
        __emit 0x06
        __emit 0x6a
        __emit 0x04
        __emit 0x8d
        __emit 0x4c
        __emit 0x24
        __emit 0x14
        __emit 0x51
        __emit 0x68
        __emit 0x77
        __emit 0x61
        __emit 0x72
        __emit 0x00
        __emit 0x8b
        __emit 0xce
        __emit 0xff
        __emit 0x90
        __emit 0x94
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x8b
        __emit 0x44
        __emit 0x24
        __emit 0x10
        __emit 0x8b
        __emit 0x16
        __emit 0x50
        __emit 0x57
        __emit 0x6a
        __emit 0x00
        __emit 0x8b
        __emit 0xce
        __emit 0xff
        __emit 0x92
        __emit 0x94
        __emit 0x00
        __emit 0x00
        __emit 0x00
        __emit 0x5f
        __emit 0x8b
        __emit 0xc6
        __emit 0x5e
        __emit 0xc2
        __emit 0x08
        __emit 0x00
    }
}


