// Retail 0x003F2B60, 355 bytes: the "Pathfinder_IsCheckForAdjust" cell predicate
// that 0x003F4F70 and 0x003F5340 call through ILT 00046E6B on the 0x003E6110 record.
// cl: /DNDEBUG /MD
typedef int Int;
typedef unsigned char Bool;
typedef float Real;

class Object;
class LocomotorSet;
class PathfindCell;
struct Coord3D { Real x, y, z; };
class CRCParameterCheck;

extern CRCParameterCheck *TheCRCParameterCheck;
extern bool Glo012F0239;
extern "C" void __cdecl bfmeRetailCritterDesyncLog(CRCParameterCheck *, const char *, ...);

class Pathfinder
{
public:
	Bool checkForAdjust(Object *, const LocomotorSet &, Bool, Int, Int, Int,
		Int, Bool, Coord3D *, const Coord3D *, Real, PathfindCell **, Int);
};

enum KindOfType { KINDOF_INFANTRY = 0x7C };

class Thing
{
public:
	bool isKindOf(KindOfType kind) const;
};

class Object : public Thing {};

// Same 60-byte record as Rva003E6110Info in PathfinderAdjustDestination003F6090.cpp.
class BfmeCellTesterRva003F5340
{
public:
	bool test(Int cellX, Int cellY);

	Pathfinder *m_pathfinder;
	Object *m_obj;
	const LocomotorSet *m_arg3;
	Bool m_notComputer, m_center;
	Int m_radius;
	const Coord3D *m_groupPos;
	Int m_layer;
	Real m_arg6;
	Int m_bestCellX, m_bestCellY, m_zero28;
	Int m_arg7;
	Coord3D m_pos;
};

bool BfmeCellTesterRva003F5340::test(Int cellX, Int cellY)
{
	if (Glo012F0239 && TheCRCParameterCheck)
		bfmeRetailCritterDesyncLog(TheCRCParameterCheck, "\t\t  Pathfinder_IsCheckForAdjust() called with cell=%d,%d", cellX, cellY);
	Int count;
	if (!m_pathfinder->checkForAdjust(m_obj, *m_arg3, m_notComputer, cellX, cellY, m_layer, m_radius,
			m_center, &m_pos, m_groupPos, m_arg6, (PathfindCell **)&count, m_arg7))
	{
		if (Glo012F0239 && TheCRCParameterCheck)
			bfmeRetailCritterDesyncLog(TheCRCParameterCheck, "\t\t  Pathfinder_IsCheckForAdjust() checkAdjust failed");
		return false;
	}
	Int allyCount = count;
	if (allyCount == 0 || m_obj->isKindOf(KINDOF_INFANTRY))
	{
		// A local keeps the logger pointer in EBX across the isKindOf call, as retail does.
		CRCParameterCheck *check;
		if (Glo012F0239 && (check = TheCRCParameterCheck) != 0)
			bfmeRetailCritterDesyncLog(check, "\t\t  Pathfinder_IsCheckForAdjust() allyCount=%s, isInfantry=%s, returning true",
				allyCount ? "TRUE" : "FALSE", m_obj->isKindOf(KINDOF_INFANTRY) ? "TRUE" : "FALSE");
		return true;
	}
	if (allyCount < m_zero28 || m_zero28 == 0)
	{
		m_zero28 = allyCount;
		m_bestCellX = cellX;
		m_bestCellY = cellY;
		if (Glo012F0239 && TheCRCParameterCheck)
			bfmeRetailCritterDesyncLog(TheCRCParameterCheck, "\t\t  Pathfinder_IsCheckForAdjust() allyCount=%d, m_foundWithAllies=%d", allyCount, m_zero28);
	}
	if (Glo012F0239 && TheCRCParameterCheck)
		bfmeRetailCritterDesyncLog(TheCRCParameterCheck, "\t\t  Pathfinder_IsCheckForAdjust() total failure, return false", allyCount, m_zero28);
	return false;
}
