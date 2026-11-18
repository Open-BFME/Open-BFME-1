// cl: /DNDEBUG /MD /EHsc
// Open-BFME: rotated box point test helper, retail 0x00880A30.

#include "../../Include/Common/ScalarTypes.h"

#define BfmeZero (3.402823466e+38f)

struct BfmePointF0
{
	Real x;
	Real y;
};

class BfmeBoxF0
{
public:
	bool contains(const BfmePointF0 *point, Real radius) const;
	bool rva00880AF0(const BfmeBoxF0 *other) const;

	Real m_centerX;
	Real m_centerY;
	Real m_axisX;
	Real m_axisY;
	Real m_perpX;
	Real m_perpY;
	Real m_extentX;
	Real m_extentY;
};

bool BfmeBoxF0::contains(const BfmePointF0 *point, Real radius) const
{
	BfmePointF0 delta;
	delta.x = point->x - m_centerX;
	delta.y = point->y - m_centerY;
	for (unsigned int side = 0; side < 4; ++side)
	{
		Real distance;
		switch (side)
		{
			case 0:
				distance = delta.y * m_perpY + delta.x * m_perpX - m_extentY;
				break;
			case 1:
				distance = delta.y * m_axisY + delta.x * m_axisX - m_extentX;
				break;
			case 2:
				distance = -(delta.y * m_perpY);
				{
					Real term = delta.x * m_perpX;
					term = -term;
					distance += term;
				}
				distance -= m_extentY;
				break;
			case 3:
				distance = -(delta.y * m_axisY);
				{
					Real term = delta.x * m_axisX;
					term = -term;
					distance += term;
				}
				distance -= m_extentX;
				break;
			default:
				distance = BfmeZero;
				break;
		}

		if (distance > radius)
			return false;
	}
	return true;
}

extern "C" double __cdecl fabs(double);
#pragma intrinsic(fabs)

// ?Rva00880AF0DotArray@@YAMMMMM@Z absent-from-retail
static __forceinline float Rva00880AF0DotArray(float ax, float ay, float bx, float by)
{
    return ax * bx + ay * by;
}

// ?absf@@YAMM@Z absent-from-retail
static __forceinline float absf(float x)
{
    return (float)fabs(x);
}

// ?rva00880AF0@BfmeBoxF0@@QBE_NPBV1@@Z
// Open BFME 2 Code/GameEngine/Source/Common/Rva006C0630Cluster.cpp.
bool BfmeBoxF0::rva00880AF0(const BfmeBoxF0 *other) const
{
    Real delta[2];
    Real y = (this ? other->m_centerY : other->m_centerY);
    Real x = (other ? other : other)->m_centerX;
    delta[0] = x - m_centerX;
    delta[1] = y - m_centerY;
    Real coefficients[4];

    coefficients[0] = (Real)absf(Rva00880AF0DotArray(other->m_axisX, other->m_axisY, m_axisX, m_axisY));
    coefficients[1] = (Real)absf(Rva00880AF0DotArray(other->m_perpX, other->m_perpY, m_axisX, m_axisY));
    if (absf(Rva00880AF0DotArray(delta[0], delta[1], m_axisX, m_axisY)) >
        coefficients[1] * other->m_extentY + coefficients[0] * other->m_extentX + m_extentX)
        return false;

    coefficients[2] = (Real)absf(Rva00880AF0DotArray(other->m_axisX, other->m_axisY, m_perpX, m_perpY));
    coefficients[3] = (Real)absf(Rva00880AF0DotArray(other->m_perpX, other->m_perpY, m_perpX, m_perpY));
    if (absf(Rva00880AF0DotArray(delta[0], delta[1], m_perpX, m_perpY)) >
        coefficients[3] * other->m_extentY + coefficients[2] * other->m_extentX + m_extentY)
        return false;

    if (absf(Rva00880AF0DotArray(delta[0], delta[1], other->m_axisX, other->m_axisY)) >
        coefficients[0] * m_extentX + coefficients[2] * m_extentY + other->m_extentX)
        return false;

    if (absf(Rva00880AF0DotArray(delta[0], delta[1], other->m_perpX, other->m_perpY)) >
        coefficients[1] * m_extentX + coefficients[3] * m_extentY + other->m_extentY)
        return false;
    return true;
}
