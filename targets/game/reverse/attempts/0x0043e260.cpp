// ?rva0043e260@InGameUI@@QAE_NPBUICoord2D@@@Z
// partial score=0.9209 date=2026-10-30
// cl: /O2 /Ob2 /DNDEBUG /MD /D_STLP_NO_EXCEPTIONS
// stlport
#include <list>

struct ICoord2D { int x, y; };
struct IRegion2D { ICoord2D lo, hi; };

class InGameUI
{
public:
	bool rva0043e260(const ICoord2D *point);

	char m_unknown0000[0x1304];
	_STL::list<ICoord2D> m_lassoPoints;
	IRegion2D m_lassoRegion;
};

// ?rva0043e260@InGameUI@@QAE_NPBUICoord2D@@@Z
bool InGameUI::rva0043e260(const ICoord2D *point)
{
	if (point->x < m_lassoRegion.lo.x)
		return false;
	if (point->y < m_lassoRegion.lo.y)
		return false;
	if (point->x > m_lassoRegion.hi.x)
		return false;
	if (point->y > m_lassoRegion.hi.y)
		return false;

	bool inside = false;
	_STL::list<ICoord2D>::iterator end = m_lassoPoints.end();
	_STL::list<ICoord2D>::iterator it = end;
	++it;
	_STL::list<ICoord2D>::iterator next;
	for (; it != end; it = next)
	{
		next = it;
		++next;
		ICoord2D p1 = *it;
		int x1 = p1.x;
		int y1 = p1.y;
		int x2, y2;
		if (next != end)
		{
			x2 = next->x;
			y2 = next->y;
		}
		else
		{
			_STL::list<ICoord2D>::iterator first = end;
			++first;
			x2 = first->x;
			y2 = first->y;
		}
		if (y1 == y2)
			continue;
		if (y1 < point->y)
		{
			if (y2 < point->y)
				continue;
		}
		else
		{
			if (y2 >= point->y)
				continue;
		}
		if (x1 < point->x && x2 < point->x)
			continue;
		double crossing = (double)((point->y - y1) * (x2 - x1)) / (double)(y2 - y1) + x1;
		if (crossing >= point->x)
			inside = !inside;
	}
	return inside;
}
