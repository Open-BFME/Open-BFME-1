// cl: /O2

typedef int Int;
typedef float Real;
typedef bool Bool;

struct Coord3D
{
	Real x, y, z;
};

struct ICoord3D
{
	Int x, y, z;
};

class PolygonTrigger
{
public:
	Bool pointInTrigger(ICoord3D &point) const;
};

class Rva001A3390Counter
{
public:
	void consider(const Coord3D *pos, int unused);

private:
	Int m_count;
	PolygonTrigger *m_trigger;
};

void Rva001A3390Counter::consider(const Coord3D *pos, int unused)
{
	const Coord3D *p = pos;
	ICoord3D ic;
	ic.x = (Int)p->x;
	ic.y = (Int)p->y;
	ic.z = (Int)p->z;
	if (m_trigger->pointInTrigger(ic))
		++m_count;
}
