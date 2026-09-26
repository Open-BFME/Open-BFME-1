// ?intersects@BfmeBoxF0@@QBE_NPBV1@@Z
// partial score=0.6 date=2026-09-21
// cl: /DNDEBUG /MD /EHsc
// Open-BFME: rotated box vs rotated box overlap test (separating axis
// theorem over the box's own axis/perp and the argument box's axis/perp),
// retail 0x00880AF0. Sibling of the landed point-containment test in
// BfmeBoxContains.cpp (retail 0x00880A30), reusing its BfmeBoxF0 layout.

typedef float Real;

class BfmeBoxF0
{
public:
	bool intersects(const BfmeBoxF0 *other) const;

	Real m_centerX;
	Real m_centerY;
	Real m_axisX;
	Real m_axisY;
	Real m_perpX;
	Real m_perpY;
	Real m_extentX;
	Real m_extentY;
};

extern "C" double __cdecl fabs(double value);
#pragma intrinsic(fabs)

bool BfmeBoxF0::intersects(const BfmeBoxF0 *other) const
{
	Real dx = other->m_centerX - m_centerX;
	Real dy = other->m_centerY - m_centerY;

	Real absBaxisDotAaxis = (Real)fabs(other->m_axisY * m_axisY + other->m_axisX * m_axisX);
	Real absBperpDotAaxis = (Real)fabs(other->m_perpY * m_axisY + other->m_perpX * m_axisX);
	if ((Real)fabs(dy * m_axisY + dx * m_axisX) >
		absBperpDotAaxis * other->m_extentY + absBaxisDotAaxis * other->m_extentX + m_extentX)
		return false;

	Real absBaxisDotAperp = (Real)fabs(other->m_axisY * m_perpY + other->m_axisX * m_perpX);
	Real absBperpDotAperp = (Real)fabs(other->m_perpY * m_perpY + other->m_perpX * m_perpX);
	if ((Real)fabs(dy * m_perpY + dx * m_perpX) >
		absBperpDotAperp * other->m_extentY + absBaxisDotAperp * other->m_extentX + m_extentY)
		return false;

	if ((Real)fabs(dy * other->m_axisY + dx * other->m_axisX) >
		absBaxisDotAaxis * m_extentX + absBaxisDotAperp * m_extentY + other->m_extentX)
		return false;

	if ((Real)fabs(dy * other->m_perpY + dx * other->m_perpX) >
		absBperpDotAaxis * m_extentX + absBperpDotAperp * m_extentY + other->m_extentY)
		return false;

	return true;
}
