// ?d_0043e260@@YAXXZ
// partial score=0.3399209486 date=2026-09-28
struct Point0043E260 { int x,y; };
// ?d_0043e260@@YAXXZ
// partial score=0.221344 date=2026-09-25
// ?testPoint@Rva0043E260Owner@@QBE_NPBH@Z
// cl: /O2 /Ob2 /DNDEBUG /MD /D_STLP_NO_EXCEPTIONS
// stlport
#include <list>

struct Rva0043E260Node
{
	Rva0043E260Node *next;
	int unused;
	int x;
	int y;
};

class Rva0043E260Owner
{
public:
	bool testPoint(const int *point) const;

	char m_unknown0000[0x1304];
	_STL::list<Point0043E260> m_points;
	int m_minX;
	int m_minY;
	int m_maxX;
	int m_maxY;
};

bool Rva0043E260Owner::testPoint(const int *point) const
{
	Point0043E260 query;
	query.x = point[0];
	if (query.x < m_minX)
		return false;

	query.y = point[1];
	if (query.y < m_minY)
		return false;
	if (query.x > m_maxX)
		return false;
	if (query.y > m_maxY)
		return false;

    bool inside=false;
    for (_STL::list<Point0043E260>::const_iterator node=m_points.begin();node!=m_points.end();++node) {
        Point0043E260 p0=*node;
        _STL::list<Point0043E260>::const_iterator next=node;
        ++next;
        Point0043E260 p1;
        if(next!=m_points.end()) p1=*next;
        else p1=*m_points.begin();
        if (p0.y != p1.y) {
            if (p0.y < query.y ? p1.y >= query.y : p1.y < query.y) {
                if (p0.x >= query.x || p1.x >= query.x) { int numerator = (query.y-p0.y)*(p1.x-p0.x);
            int denominator = p1.y-p0.y;
            double crossing = (double)numerator/(double)denominator + (double)p0.x;
            if (crossing >= (double)query.x) inside=!inside; }
            }
        }
    nextEdge:

;
	}
	return inside;
}
