// ?checkForAdjust@Pathfinder@@QAEEPAVObject@@ABVLocomotorSet@@EHHHHEPAUCoord3D@@PBU4@MPAPAVPathfindCell@@H@Z
// partial score=0.65 date=2026-09-09
// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD
//
// BFME's 13-argument Pathfinder::checkForAdjust, retail 0x003F0F40.
// The additional arguments are used by the BFME tighten-path callback; this is
// a separate overload from the older eight-argument adjust cascade.

#include <math.h>
#pragma intrinsic(fabs)

typedef int Int;
typedef unsigned char Bool;
typedef float Real;

extern unsigned char g_012F0239;
extern void *g_012ED4FC;
extern const Real BfmeZeroRange;
extern "C" void __cdecl bfmeRetailCritterDesyncLog(
	void *context, const char *format, ...);

struct Coord3D
{
	Real x, y, z;
};

class AsciiString
{
public:
	char *m_data;

	__forceinline const char *str(void) const
	{
		return m_data != 0 ? m_data + 8 : "";
	}
};

class Overridable
{
public:
	virtual ~Overridable();
	const Overridable *getFinalOverride(void) const;

	Overridable *m_nextOverride;
	char m_pad08[0x18];
	AsciiString m_name;
};

struct ICoord2D
{
	Int x, y;
};

struct IRegion2D
{
	ICoord2D lo, hi;
};

enum PathfindLayerEnum
{
	PATHFIND_LAYER_UNKNOWN = 0
};

enum KindOfType
{
	KINDOF_AIRCRAFT = 12
};

class LocomotorSet;

class Thing
{
public:
	bool isKindOf(KindOfType kind) const;
};

class Object : public Thing
{
public:
	char m_pad00[4];
	Overridable *m_template;
	char m_pad08[0x30];
	Coord3D m_position;
	char m_pad44[0x30];
	Int m_id;
};

class LocomotorSet
{
public:
	char m_pad00[0x18];
	AsciiString m_name;
};

class PathfindCell
{
public:
	Int getLayer(void) const { return (m_word >> 6) & 0x3f; }
	Int getType(void) const { return m_word & 7; }

private:
	char m_pad00[0x0c];
	unsigned int m_word;
};

class Pathfinder
{
public:
	Bool checkForAdjust(Object *obj, const LocomotorSet &set, Bool human,
		Int x, Int y, Int layer, Int radius, Bool center, Coord3D *dest,
		const Coord3D *groupDest, Real originalZ,
		PathfindCell **fromSlot, Int onlyIfLayer);

	PathfindCell *getCell(PathfindLayerEnum layer, Int x, Int y);
	Bool bfmeInnerE6E90(void *a1, void *a2, void *a3, void *a4, void *a5,
		void *a6, void **a7, int a8);
	bool slowDoesPathExist(Object *obj, const Coord3D *from,
		const Coord3D *to, int ignoreObject);

protected:
	void adjustCoordToCell(Int x, Int y, Bool center, Coord3D &pos,
		PathfindLayerEnum layer);

	char m_pad00[0x24];
	IRegion2D m_logicalExtent;
};

// ?checkForAdjust@Pathfinder@@QAEEPAVObject@@ABVLocomotorSet@@EHHHHEPAUCoord3D@@PBU4@MPAPAVPathfindCell@@H@Z
Bool Pathfinder::checkForAdjust(Object *obj, const LocomotorSet &set,
	Bool human, Int x, Int y, Int layer, Int radius, Bool center,
	Coord3D *dest, const Coord3D *groupDest, Real originalZ,
	PathfindCell **fromSlot, Int onlyIfLayer)
{
	Coord3D adjustDest;
	if (g_012F0239 && g_012ED4FC)
	{
		const Overridable *templateObject = obj->m_template;
		if (templateObject != 0 && templateObject->m_nextOverride != 0)
			templateObject = templateObject->m_nextOverride->getFinalOverride();
		const char *objectName = templateObject->m_name.str();
		Real groupXValue = -1.0f;
		Real groupYValue = -1.0f;
		Real groupZValue = -1.0f;
		if (groupDest != 0)
		{
			groupXValue = groupDest->x;
			groupYValue = groupDest->y;
			groupZValue = groupDest->z;
		}
		bfmeRetailCritterDesyncLog(g_012ED4FC,
			"\t\t  Pathfinder::CheckForAdjust called with: obj=%s(%d), loco=%s, isHuman=%s, cell=%d,%d, layer=%d, iRadius=%d, center=%s, groupDest=%g,%g,%g, originalZ=%g, onlyIfLayer=%d",
			objectName, obj->m_id, set.m_name.str(), human ? "TRUE" : "FALSE",
			x, y, layer, radius, center ? "TRUE" : "FALSE",
			groupXValue, groupYValue, groupZValue,
			originalZ, onlyIfLayer);
	}

	PathfindCell *cell = getCell((PathfindLayerEnum)layer, x, y);
	if (cell == 0)
	{
		if (g_012F0239 && g_012ED4FC)
			bfmeRetailCritterDesyncLog(g_012ED4FC,
				"        cellP is NULL, return FALSE.");
		return 0;
	}
	if (cell->getType() == 2)
	{
		if (g_012F0239 && g_012ED4FC)
			bfmeRetailCritterDesyncLog(g_012ED4FC,
				"        cellP is CLIFF, return FALSE.");
		return 0;
	}

	if (human && g_012F0239 && g_012ED4FC)
		bfmeRetailCritterDesyncLog(g_012ED4FC, "        isHuman is TRUE");
	if (human && (x < m_logicalExtent.lo.x || y < m_logicalExtent.lo.y ||
		x > m_logicalExtent.hi.x || y > m_logicalExtent.hi.y))
	{
		if (g_012F0239 && g_012ED4FC)
			bfmeRetailCritterDesyncLog(g_012ED4FC,
				"        cell %d,%d is outside m_logicalExtent lo:%d,%d hi:%d,%d",
				x, y, m_logicalExtent.lo.x, m_logicalExtent.lo.y,
				m_logicalExtent.hi.x, m_logicalExtent.hi.y);
		return 0;
	}

	if (!bfmeInnerE6E90((void *)obj, (void *)x, (void *)y, (void *)layer,
		(void *)radius, (void *)center, (void **)fromSlot, 0))
	{
		if (g_012F0239 && g_012ED4FC)
			bfmeRetailCritterDesyncLog(g_012ED4FC,
				"        CheckDestination failed, return false");
		return 0;
	}
	if (g_012F0239 && g_012ED4FC)
		bfmeRetailCritterDesyncLog(g_012ED4FC,
			"        CheckDestination passed");

	adjustCoordToCell(x, y, center, adjustDest,
		(PathfindLayerEnum)cell->getLayer());

	if (!obj->isKindOf(KINDOF_AIRCRAFT))
	{
		if (g_012F0239 && g_012ED4FC)
			bfmeRetailCritterDesyncLog(g_012ED4FC,
				"        object is not kindof aircraft");
		if (onlyIfLayer)
		{
			if (g_012F0239 && g_012ED4FC)
				bfmeRetailCritterDesyncLog(g_012ED4FC,
					"        onlyIfLayer=%d", onlyIfLayer);
			Int x0 = x - radius;
			Int x1 = x + radius + (center ? 1 : 0);
			Int y0 = y - radius;
			Int y1 = y + radius + (center ? 1 : 0);
			for (Int ix = x0; ix < x1; ++ix)
			{
				for (Int iy = y0; iy < y1; ++iy)
				{
					PathfindCell *near = getCell(
						(PathfindLayerEnum)onlyIfLayer, ix, iy);
					if (near == 0)
					{
						if (g_012F0239 && g_012ED4FC)
							bfmeRetailCritterDesyncLog(g_012ED4FC,
								"        ground unit failed iteration: i=%d, j=%d, cell=NULL, onlyIfLayer",
								ix, iy, onlyIfLayer);
						return 0;
					}
					if (near->getLayer() != onlyIfLayer)
					{
						if (g_012F0239 && g_012ED4FC)
							bfmeRetailCritterDesyncLog(g_012ED4FC,
								"        ground unit failed iteration: i=%d, j=%d, cell=VALID, cellLayer=%d, onlyIfLayer",
								ix, iy, near->getLayer(), onlyIfLayer);
						return 0;
					}
				}
			}

			if (originalZ > BfmeZeroRange)
			{
				if (fabs(adjustDest.z - originalZ) > 50.0f)
				{
					if (g_012F0239 && g_012ED4FC)
						bfmeRetailCritterDesyncLog(g_012ED4FC,
							"        MinasTirith check failed, return FALSE: originalZ=%g, adjustDest.z=%g",
							originalZ, adjustDest.z);
					return 0;
				}
			}
		}

		const Coord3D *position = &obj->m_position;
		Bool adjustedPathExists = (Bool)slowDoesPathExist(
			obj, position, &adjustDest, 0);
		if (g_012F0239 && g_012ED4FC)
			bfmeRetailCritterDesyncLog(g_012ED4FC,
				"        adjustedPathExists=%s",
				adjustedPathExists ? "TRUE" : "FALSE");
		Bool pathExists = (Bool)slowDoesPathExist(obj, position, dest, 0);
		if (pathExists)
		{
			if (g_012F0239 && g_012ED4FC)
				bfmeRetailCritterDesyncLog(g_012ED4FC,
					"        QuickDoesPathExist1 succeeds");
		}
		else
		{
			if (g_012F0239 && g_012ED4FC)
				bfmeRetailCritterDesyncLog(g_012ED4FC,
					"        QuickDoesPathExist1 fails. Try adjusted destination");
			if (slowDoesPathExist(obj, dest, &adjustDest, 0))
			{
				adjustedPathExists = 1;
				if (g_012F0239 && g_012ED4FC)
					bfmeRetailCritterDesyncLog(g_012ED4FC,
						"        QuickDoesPathExist2 succeeds. adjustedPathExists");
			}
		}
		if (!adjustedPathExists)
		{
			if (g_012F0239 && g_012ED4FC)
				bfmeRetailCritterDesyncLog(g_012ED4FC,
					"        returning false because adjustedPathExists is false");
			return 0;
		}
	}

	if (g_012F0239 && g_012ED4FC)
		bfmeRetailCritterDesyncLog(g_012ED4FC,
			"        dest calculated to be %g,%g,%g and returning true",
			adjustDest.x, adjustDest.y, adjustDest.z);
	*dest = adjustDest;
	return 1;
}
