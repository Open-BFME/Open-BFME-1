// cl: /O2

typedef int Int;
typedef float Real;
typedef bool Bool;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	Real x, y, z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct ICoord3D
{
	Int x, y, z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/PolygonTrigger.h
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
