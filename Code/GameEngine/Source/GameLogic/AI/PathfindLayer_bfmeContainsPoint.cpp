// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: BFME-only PathfindLayer point-in-trigger-list query, retail
// 0x003FC300. The second layer owner at +0x3C is a PolygonTrigger chain;
// each point component is truncated to an integer before the chain is tested.

typedef bool Bool;
typedef int Int;
typedef float Real;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct ICoord3D
{
	Int x;
	Int y;
	Int z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/PolygonTrigger.h
class PolygonTrigger
{
public:
	Bool pointInTrigger(ICoord3D &point) const;
	PolygonTrigger *getNext(void) const { return m_next; }

private:
	char m_bfmeHead[4];
	PolygonTrigger *m_next;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class PathfindLayer
{
public:
	Bool bfmeContainsPoint(const Coord3D *point);

private:
	char m_bfmeHead[0x3c];
	PolygonTrigger *m_triggers;
};

// ?bfmeContainsPoint@PathfindLayer@@QAE_NPBUCoord3D@@@Z
Bool PathfindLayer::bfmeContainsPoint(const Coord3D *point)
{
	ICoord3D cell;
	cell.x = point->x;
	cell.y = point->y;
	cell.z = point->z;

	for (PolygonTrigger *trigger = m_triggers;
		trigger != 0;
		trigger = trigger->getNext())
	{
		if (trigger->pointInTrigger(cell))
			return true;
	}

	return false;
}
