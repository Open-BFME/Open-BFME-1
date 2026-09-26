// cl: /O2

typedef int Int;
typedef float Real;
typedef bool Bool;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	Real x, y, z;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct ICoord3D
{
	Int x, y, z;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/PolygonTrigger.h
class PolygonTrigger
{
public:
	Bool pointInTrigger(ICoord3D &point) const;
};

class Rva001A3390Counter
{
public:
	void consider(const Coord3D *inputPosition, int unused);

private:
	Int m_count;
	PolygonTrigger *m_trigger;
};

void Rva001A3390Counter::consider(const Coord3D *inputPosition, int unused)
{
	const Coord3D *position = inputPosition;
	ICoord3D integerPosition;
	integerPosition.x = (Int)position->x;
	integerPosition.y = (Int)position->y;
	integerPosition.z = (Int)position->z;
	if (m_trigger->pointInTrigger(integerPosition))
		++m_count;
}
