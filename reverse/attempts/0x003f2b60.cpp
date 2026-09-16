// ?d_003f2b60@@YAXXZ
// partial score=0.55 date=2026-09-16
// cl: /DNDEBUG /MD
// Clean address-preserving reconstruction of retail RVA 0x003F2B60.

typedef int Int;
typedef unsigned char Bool;

class Object;
class LocomotorSet;
class PathfindCell;
struct Coord3D;

class Pathfinder
{
public:
	Bool checkForAdjust(Object *, const LocomotorSet &, Bool, Int, Int, Int,
		Int, Bool, Coord3D *, const Coord3D *, float, PathfindCell **, Int);
};

enum KindOfType { KINDOF_INFANTRY = 0x7C };

class Thing
{
public:
	bool isKindOf(KindOfType kind) const;
};

class Object : public Thing {};

extern unsigned char g_012F0239;
extern void *g_012ED4FC;
extern void __cdecl j_0003a17a(void *, const char *, ...);
class Rva003F2B60
{
public:
	bool isCheckForAdjust(Int cellX, Int cellY);

private:
	Pathfinder *m_pathfinder;
	Object *m_object;
	const LocomotorSet *m_locomotorSet;
	Bool m_isHuman;
	Bool m_center;
	unsigned char m_pad0E[2];
	Int m_radius;
	const Coord3D *m_groupDest;
	Int m_layer;
	float m_originalZ;
	Int m_bestCellX;
	Int m_bestCellY;
	Int m_foundWithAllies;
	Int m_onlyIfLayer;
	Coord3D *m_dest;
};

bool Rva003F2B60::isCheckForAdjust(Int cellX, Int cellY)
{
	if (g_012F0239 && g_012ED4FC)
		j_0003a17a(g_012ED4FC, (const char *)0x010EFD4C,
			cellX, cellY);

	if (!m_pathfinder->checkForAdjust(m_object,
		*m_locomotorSet, m_isHuman, cellX, cellY, m_layer, m_radius,
		m_center, m_dest, m_groupDest, m_originalZ,
		(PathfindCell **)&cellY, m_onlyIfLayer))
	{
		if (g_012F0239 && g_012ED4FC)
			j_0003a17a(g_012ED4FC, (const char *)0x010EFD0C);
		return 0;
	}

	Int allyCount = cellY;
	if (allyCount == 0 || m_object->isKindOf(KINDOF_INFANTRY))
	{
		if (g_012F0239 && g_012ED4FC)
			j_0003a17a(g_012ED4FC, (const char *)0x010EFC08,
				allyCount ? (const char *)0x0107FA58 : (const char *)0x01080180,
				m_object->isKindOf(KINDOF_INFANTRY)
					? (const char *)0x0107FA58 : (const char *)0x01080180);
		return 1;
	}

	if (allyCount >= m_foundWithAllies && m_foundWithAllies != 0)
	{
		if (g_012F0239 && g_012ED4FC)
			j_0003a17a(g_012ED4FC, (const char *)0x010EFC68,
				allyCount, m_foundWithAllies);
		return 0;
	}

	m_foundWithAllies = allyCount;
	m_bestCellX = cellX;
	m_bestCellY = cellY;

	if (g_012F0239 && g_012ED4FC)
		j_0003a17a(g_012ED4FC, (const char *)0x010EFCB8,
			allyCount, allyCount);
	if (g_012F0239 && g_012ED4FC)
		j_0003a17a(g_012ED4FC, (const char *)0x010EFC68,
			allyCount, m_foundWithAllies);
	return 0;
}
