// cl: /O2 /Ob2 /DNDEBUG /MD /D_STLP_NO_EXCEPTIONS
// stlport
// InGameUI lasso point test, retail 0x0043E260 (253 B, thiscall, ret 4). The
// matched lasso drawable walk ?rva00442fd0@InGameUI (InGameUIRva00442FD0.cpp)
// calls it per drawable with the drawable's screen point: reject points
// outside the lasso bounds at +0x1308..+0x1314, then run an even-odd crossing
// test over the lasso polygon, the ICoord2D list at +0x1304 (the last vertex
// wraps to the first). Zero Hour has no such method, so the name keeps the
// address. Shape notes: the query point is read through the pointer (retail
// keeps x/y in frame slots), each vertex is copied before the next iterator is
// formed, the three trailing bounds tests are separate returns, and the loop
// advances with ++it.
#include <list>

struct ICoord2D { int x, y; };
struct IRegion2D { ICoord2D lo, hi; };

class InGameUI
{
public:
	bool rva0043e260(const ICoord2D *point);

	char m_unmodelled_0000[0x1304];
	_STL::list<ICoord2D> m_list_1304;	// +0x1304 lasso polygon
	IRegion2D m_region_1308;		// +0x1308 lasso bounds
};

// ?rva0043e260@InGameUI@@QAE_NPBUICoord2D@@@Z
bool InGameUI::rva0043e260(const ICoord2D *point)
{
	if (point->x < m_region_1308.lo.x)
		return false;
	if (point->y < m_region_1308.lo.y)
		return false;
	if (point->x > m_region_1308.hi.x)
		return false;
	if (point->y > m_region_1308.hi.y)
		return false;

	bool inside = false;
	_STL::list<ICoord2D>::iterator end = m_list_1304.end();
	_STL::list<ICoord2D>::iterator it = end;
	++it;
	_STL::list<ICoord2D>::iterator next;
	for (; it != end; ++it)
	{
		ICoord2D p1 = *it;
		next = it;
		++next;
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
