// BFME-only bridge-layer region overlap test, retail 0x003FBA10 (110 bytes).

typedef bool Bool;
typedef int Int;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct ICoord2D
{
	Int x;
	Int y;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Region2D
{
	ICoord2D lo;
	ICoord2D hi;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/TerrainLogic.h
class Bridge
{
public:
	void getBounds(Region2D *bounds) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
class PathfindLayer
{
public:
	Bool bfmeContainsRegion(const Region2D *region);

private:
	char m_pad00[0x3c];
	Bridge *m_bfmeOther;
};

Bool PathfindLayer::bfmeContainsRegion(const Region2D *region)
{
	Region2D bounds;
	register const Region2D *input = region;
	Bridge *bridge = m_bfmeOther;
	if (bridge != 0) {
		do {
			bridge->getBounds(&bounds);
			if (input->hi.x + 10 <= bounds.lo.x ||
				input->hi.y + 10 <= bounds.lo.y ||
				input->lo.x - 10 >= bounds.hi.x ||
				input->lo.y - 10 >= bounds.hi.y) {
				bridge = *(Bridge **)((const char *)bridge + 4);
				continue;
			}
			return true;
		} while (bridge != 0);
	}
	return false;
}
