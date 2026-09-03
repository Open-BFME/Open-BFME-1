// ?getWaterHeight@WaterRenderObjClass@@QAEMMM@Z
// partial score=0.96 date=2026-09-03
// cl: /ICode/GameEngine/Include /DNDEBUG /DWIN32 /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// Clean BFME reconstruction of WaterRenderObjClass::getWaterHeight at 0x007A4B40.

extern "C" __declspec(dllimport) double __cdecl floor(double value);

typedef float Real;
typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;

__forceinline long bfme_fistp(Real value)
{
	long result;
	__asm {
		fld [value]
		fistp [result]
	}
	return result;
}

struct ICoord3D
{
	Int x;
	Int y;
	Int z;
};

struct BfmeWaterHeightPoint
{
	Int x;
	Int y;
	Int z;
};

struct BfmeWaterHandle;

class BfmePolygonTrigger
{
public:
	void *m_vtable;
	BfmePolygonTrigger *m_next;
	char m_beforePoints[8];
	BfmeWaterHeightPoint *m_points;
	Int m_numPoints;
	char m_beforeWaterFlag[0x1a];
	Bool m_isWaterArea;
	char m_beforeHandle[9];
	BfmeWaterHandle *m_waterHandle;

	Bool pointInTrigger(ICoord3D &point) const;
	const BfmeWaterHandle *getWaterHandle(void) const;
	const BfmeWaterHeightPoint *getPoint(Int index) const
	{
		if (index < 0)
			index = 0;
		if (index >= m_numPoints)
			index = m_numPoints - 1;
		return m_points + index;
	}
};

struct BfmeWaterHandle
{
	BfmePolygonTrigger *m_polygon;
};

struct BfmeWaterGridPoint2
{
	Real x;
	Real y;
};

struct BfmeWaterGridPoint3
{
	Real X;
	Real Y;
	Real Z;
};

class BfmeWaterGridPolygon
{
public:
	Bool containsPoint(const BfmeWaterGridPoint2 *point);

	char m_beforePoints[0x54];
	BfmeWaterGridPoint3 *m_points;
	Int m_numPoints;
};

struct BfmeWaterGridNode
{
	BfmeWaterGridNode *m_next;
	BfmeWaterGridNode *m_previous;
	BfmeWaterGridPolygon *m_grid;
};

struct BfmeWaterGridList
{
	BfmeWaterGridNode *m_head;
};

struct BfmePolygonTriggerTable
{
	BfmePolygonTrigger *m_head;
};

extern "C" BfmePolygonTriggerTable *g_bfmePolygonTriggerTable;

class WaterRenderObjClass
{
public:
	Real getWaterHeight(Real x, Real y);

private:
	char m_beforeWaterGridList[0x2ac];
	BfmeWaterGridList *m_waterGridList;
};

Real WaterRenderObjClass::getWaterHeight(Real x, Real y)
{
	const BfmeWaterHandle *waterHandle = 0;
	Real waterZ = 0.0f;
	ICoord3D iLoc;
	iLoc.x = (Int)bfme_fistp((Real)floor((double)(x + 0.5f)));
	iLoc.y = (Int)bfme_fistp((Real)floor((double)(y + 0.5f)));
	iLoc.z = 0;

	for (BfmePolygonTrigger *trigger = g_bfmePolygonTriggerTable->m_head;
		trigger != 0; trigger = trigger->m_next) {
		if (!trigger->m_isWaterArea)
			continue;
		if (!trigger->pointInTrigger(iLoc))
			continue;

		if (waterZ <= (Real)trigger->getPoint(0)->z) {
			waterZ = (Real)trigger->getPoint(0)->z;
			waterHandle = trigger->getWaterHandle();
		}
	}

	if (waterHandle != 0) {
		BfmePolygonTrigger *polygon = waterHandle->m_polygon;
		Int pointIndex = 0;
		if (polygon->m_numPoints <= 0)
			pointIndex = polygon->m_numPoints - 1;
	waterZ = (Real)polygon->m_points[pointIndex].z;
	} else {
		waterZ = 0.0f;
	}

	BfmeWaterGridPoint3 gridLocation;
	BfmeWaterGridNode *node;
	BfmeWaterGridList *gridList = *(BfmeWaterGridList * volatile *)&m_waterGridList;
	gridLocation.Y = y;
	node = gridList->m_head;
	gridLocation.X = x;
	gridLocation.Z = 0.0f;
	if (node != (BfmeWaterGridNode *)gridList) {
		while ((node = node->m_next) != (BfmeWaterGridNode *)gridList) {
		}
	}

	BfmeWaterGridList *mainList = m_waterGridList;
	BfmeWaterGridPolygon *grid = 0;
	node = mainList->m_head;
	while (node != (BfmeWaterGridNode *)mainList) {
		grid = node->m_grid;
		if (grid->containsPoint((const BfmeWaterGridPoint2 *)&gridLocation))
			goto gridHit;
		node = node->m_next;
	}
	return waterZ;

gridHit:
	if (waterZ == grid->m_points[0].Z)
		return waterZ - 0.01f;
	return waterZ;
}
