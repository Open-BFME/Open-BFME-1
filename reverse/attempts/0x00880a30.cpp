// ?contains@BfmeBoxF0@@QBE_NPBUBfmePointF0@@M@Z
// partial score=0.9 date=2026-09-10
// cl: /DNDEBUG /MD /EHsc
// Open-BFME: rotated box point test helper, retail 0x00880A30.
//
// GeometryInfo's box collision helper builds this 0x20-byte rotated box and
// calls the predicate with a point and the other shape's major radius.

typedef float Real;

#define BfmeZero (*(const Real *)0x01084C3C)

struct BfmePointF0
{
	Real x;
	Real y;
};

class BfmeBoxF0
{
public:
	bool contains(const BfmePointF0 *point, Real radius) const;

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
				distance = -(delta.y * m_perpY) + -(delta.x * m_perpX) - m_extentY;
				break;
			case 3:
				distance = -(delta.y * m_axisY) + -(delta.x * m_axisX) - m_extentX;
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
