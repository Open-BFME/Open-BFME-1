// ?d_003df580@@YAXXZ
// partial score=0.481 date=2026-09-28
// ?d_003df580@@YAXXZ
// partial score=0.4810 date=2026-09-28 model=opus-5.5
// probe symbol: ?checkDestination@Pathfinder@@QAE_NPBVObject@@HHW4PathfindLayerEnum@@H_NPAH2@Z
// cl: /DNDEBUG /MD
//
// Retail 0x003DF580, 2029 bytes, ret 0x20: the BFME Pathfinder::CheckDestination
// (string 0x010EEA60 "Pathfinder::CheckDestination called with: obj=%s(%d),
// cell=%d,%d, layer=%d, iRadius=%d, centerInCell=%s").  Fresh rewrite from the
// retail instructions over the Zero Hour checkDestination twin
// (AIPathfind.cpp:4924) with every BFME log string decoded:
//  - horde (template+D4 bit12) / path-through-infantry (D4 bit28) prologue
//    sets ursurpAllyGoalCells [esp+12] and canPathThroughInfantry [esp+13];
//  - the horde ground case builds pos=(cell+0.5)*10, pos.z = TerrainLogic
//    vslot7 getLayerHeight(x,y,LAYER_GROUND,NULL,true) and asks vslot47(&pos)
//    ("narrow passage area");
//  - D0 bit25 + C8 bit8 off-ground forces radius 1 / centre false;
//  - j_00010ea1 true ("human controlled") range-checks m_logicalExtent (+24);
//  - arg7 counts allied goal cells, arg8 skips the unit lookup.
// The override walker body is visible in the TU (noinline, pinned name
// ?friend_getFinalOverride@BfmeOverridable@@QAEPAV1@XZ -> ILT 0x22BB) so the
// flag/logger stay cached in BL/EBP across it exactly as retail does; the
// template pointer is read volatile because retail re-reads it each time.
// OFF THE MAP is the else of if(cell), as in ZH, which puts its tail last.
// The two IMPASSABLE tests (5, then 6) are separate ifs with the same log so
// the merged tail lands after CELL_CLIFF as in retail (a 5||6 test put it last).
// Remaining (6 structural diffs, 2015 vs 2029 bytes, 1025 differing): +264
// radius/centre load order; +2CC retail reloads this into EDX and uses ECX as
// temp; +3A7 retail reloads TheCRCParameterCheck for the BEGIN-iteration log;
// +44C this-copy register choice in inlined getCell; the +3E7 loop-alignment
// jmp/pad only follows from the earlier size deficit.
typedef int Int;
typedef bool Bool;
typedef float Real;
typedef unsigned int ObjectID;

const ObjectID INVALID_ID = 0;

struct ICoord2D { Int x, y; };
struct IRegion2D { ICoord2D lo, hi; };
struct Coord3D { Real x, y, z; };

enum PathfindLayerEnum { LAYER_INVALID = 0, LAYER_GROUND = 1, LAYER_LAST = 15 };
enum Relationship { ENEMIES = 0, NEUTRAL = 1, ALLIES = 2 };

class CRCParameterCheck;
extern CRCParameterCheck *TheCRCParameterCheck;
extern bool Glo012F0239;
extern "C" void __cdecl bfmeRetailCritterDesyncLog(CRCParameterCheck *, const char *, ...);

#define CHECKDEST_LOG(args) \
	do { if (Glo012F0239 && TheCRCParameterCheck) bfmeRetailCritterDesyncLog args; } while (0)

extern void j_00010ea1();
extern void j_0001a36b();
extern void j_00024c99();
extern void j_0003251f();
extern void j_000420aa();

class Rva003DF580Call {};
template<class P> __forceinline P rva003DF580Pmf(void (*f)())
{
	union { void (*raw)(); P member; } u;
	u.raw = f;
	return u.member;
}
#define RVA003DF580_CALL(T,obj,fn) (((Rva003DF580Call*)(obj))->*rva003DF580Pmf<T>(fn))

class BfmeOverridable
{
public:
	__declspec(noinline) BfmeOverridable *friend_getFinalOverride();
	Int m_unknown00;
	BfmeOverridable *m_override;
};
BfmeOverridable *BfmeOverridable::friend_getFinalOverride()
{
	if (m_override) return m_override->friend_getFinalOverride();
	return this;
}

struct Rva003DF580AsciiData { char m_pad[8]; char m_chars[1]; };
struct Rva003DF580Template : public BfmeOverridable
{
	char m_pad08[0x20 - 8];
	Rva003DF580AsciiData *m_name;
	char m_pad24[0xc8 - 0x24];
	unsigned int m_flagsC8;
	unsigned int m_flagsCC;
	unsigned int m_flagsD0;
	unsigned int m_flagsD4;
	const char *getNameStr() const { return m_name ? m_name->m_chars : ""; }
};

class Rva003DF580AI {};

class Object
{
public:
	Relationship getRelationship(const Object *that) const;

	Rva003DF580Template *getTemplate() const
	{
		BfmeOverridable *t = *(BfmeOverridable * volatile *)&m_template;
		if (t && t->m_override) t = t->m_override->friend_getFinalOverride();
		return (Rva003DF580Template *)t;
	}
	ObjectID getID() const { return m_id; }
	Rva003DF580AI *getAI() const { return m_ai; }

	void *m_vtable;
	Rva003DF580Template *m_template;
	char m_pad08[0x74 - 8];
	ObjectID m_id;
	char m_pad78[0x204 - 0x78];
	Rva003DF580AI *m_ai;
};

typedef Bool (Rva003DF580Call::*Rva001BE410)() const;
typedef Int (Rva003DF580Call::*Rva0026F940)();
typedef Bool (Rva003DF580Call::*Rva00271450)() const;
typedef Bool (Rva003DF580Call::*Rva001CC790)(const Object *, Int) const;
typedef Bool (Rva003DF580Call::*Rva000A2CF0)(Int) const;

class GameLogic
{
public:
	Object *findObjectByID(Int id);
};
extern GameLogic *TheBfmeGameLogic;

class TerrainLogic
{
public:
	virtual void slot0(); virtual void slot1(); virtual void slot2();
	virtual void slot3(); virtual void slot4(); virtual void slot5(); virtual void slot6();
	virtual Real getLayerHeight(Real x, Real y, PathfindLayerEnum layer, Coord3D *normal = 0, Bool clip = true) const;
	virtual void slot8(); virtual void slot9(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
	virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39();
	virtual void slot40(); virtual void slot41(); virtual void slot42(); virtual void slot43();
	virtual void slot44(); virtual void slot45(); virtual void slot46();
	virtual Bool slot47(const Coord3D *pos);
};
extern TerrainLogic *TheTerrainLogic;

struct PathfindCellInfo
{
	char m_pad00[0x14];
	ObjectID m_goalUnitID;
	char m_pad18[4];
	ObjectID m_goalAircraftID;
	ObjectID m_obstacleID;
};

class PathfindCell
{
public:
	Int getType() const { return m_packed & 7; }
	Int getFlags() const { return m_packed & 0x38; }
	unsigned char getAircraftGoalByte() const { return (unsigned char)(m_packed >> 19); }
	unsigned char getPlayerImpassableByte() const { return (unsigned char)(m_packed >> 21); }
	ObjectID getGoalUnit() const { return m_info ? m_info->m_goalUnitID : INVALID_ID; }
	ObjectID getGoalAircraft() const { return m_info ? m_info->m_goalAircraftID : INVALID_ID; }
	Bool isObstaclePresent(ObjectID id) const
	{
		if (id != INVALID_ID && m_info && m_info->m_obstacleID == id) return true;
		return false;
	}

	PathfindCellInfo *m_info;
	Int m_unused04;
	Int m_unused08;
	unsigned int m_packed;
};

class PathfindLayer
{
public:
	PathfindCell *getCell(Int x, Int y);
private:
	unsigned char m_body[0x44];
};

class Pathfinder
{
public:
	Bool checkDestination(const Object *obj, Int cellX, Int cellY, PathfindLayerEnum layer,
		Int iRadius, Bool centerInCell, Int *allyGoalCount, Bool skipUnitCheck);

	PathfindCell *getCell(PathfindLayerEnum layer, Int x, Int y)
	{
		if (x >= m_extent.lo.x && x <= m_extent.hi.x &&
			y >= m_extent.lo.y && y <= m_extent.hi.y)
		{
			PathfindCell *cell = 0;
			if (layer > LAYER_GROUND && layer <= LAYER_LAST)
			{
				cell = m_layers[layer].getCell(x, y);
				if (cell)
					return cell;
			}
			return &m_map[x][y];
		}
		else
		{
			return 0;
		}
	}

	unsigned char m_prefix[0x10];
	PathfindCell **m_map;
	IRegion2D m_extent;
	IRegion2D m_logicalExtent;
	unsigned char m_mid[0x85c - 0x34];
	PathfindLayer m_layers[16];
};

Bool Pathfinder::checkDestination(const Object *obj, Int cellX, Int cellY, PathfindLayerEnum layer,
	Int iRadius, Bool centerInCell, Int *allyGoalCount, Bool skipUnitCheck)
{
	CHECKDEST_LOG((TheCRCParameterCheck,
		"          Pathfinder::CheckDestination called with: obj=%s(%d), cell=%d,%d, layer=%d, iRadius=%d, centerInCell=%s",
		obj->getTemplate()->getNameStr(), obj->getID(), cellX, cellY, layer, iRadius,
		centerInCell ? "TRUE" : "FALSE"));

	Bool ursurpAllyGoalCells = false;
	Bool canPathThroughInfantry = false;
	if (obj->getTemplate()->m_flagsD4 & 0x1000)
	{
		CHECKDEST_LOG((TheCRCParameterCheck, "          horde"));
		if (layer == LAYER_GROUND && !skipUnitCheck)
		{
			CHECKDEST_LOG((TheCRCParameterCheck, "          layer is LAYER_GROUND"));
			Coord3D pos;
			pos.x = ((Real)cellX + 0.5f) * 10.0f;
			pos.y = ((Real)cellY + 0.5f) * 10.0f;
			pos.z = TheTerrainLogic->getLayerHeight(pos.x, pos.y, LAYER_GROUND);
			if (TheTerrainLogic->slot47(&pos))
			{
				CHECKDEST_LOG((TheCRCParameterCheck, "          narrow passage area"));
				iRadius = 1;
				centerInCell = true;
			}
		}
		else
		{
			CHECKDEST_LOG((TheCRCParameterCheck, "          layer != LAYER_GROUND, layer=%d", layer));
			iRadius = 1;
			centerInCell = true;
		}
		ursurpAllyGoalCells = true;
	}
	else if (obj->getTemplate()->m_flagsD4 & 0x10000000)
	{
		CHECKDEST_LOG((TheCRCParameterCheck, "          I'm a path through infantry kindof"));
		canPathThroughInfantry = true;
		ursurpAllyGoalCells = true;
	}

	if ((obj->getTemplate()->m_flagsD0 & 0x2000000) &&
		(obj->getTemplate()->m_flagsC8 & 0x100) &&
		layer != LAYER_GROUND)
	{
		iRadius = 1;
		centerInCell = false;
	}

	Int numCellsAbove = iRadius;
	if (centerInCell) numCellsAbove++;

	if (RVA003DF580_CALL(Rva001BE410, obj, j_00010ea1)())
	{
		CHECKDEST_LOG((TheCRCParameterCheck, "          human controlled"));
		if (cellX - iRadius < m_logicalExtent.lo.x || cellX + numCellsAbove > m_logicalExtent.hi.x ||
			cellY - iRadius < m_logicalExtent.lo.y || cellY + numCellsAbove > m_logicalExtent.hi.y)
		{
			CHECKDEST_LOG((TheCRCParameterCheck, "            returning false"));
			return false;
		}
	}

	Bool checkForAircraft = false;
	Int i, j;
	ObjectID ignoreId = INVALID_ID;
	ObjectID objID = INVALID_ID;
	if (obj->getAI())
	{
		CHECKDEST_LOG((TheCRCParameterCheck, "          I have an AI"));
		ignoreId = RVA003DF580_CALL(Rva0026F940, obj->getAI(), j_0001a36b)();
		checkForAircraft = RVA003DF580_CALL(Rva00271450, obj->getAI(), j_00024c99)();
		objID = obj->getID();
	}
	*allyGoalCount = 0;

	CHECKDEST_LOG((TheCRCParameterCheck,
		"          BEGIN cell iteration (deep innards), i from %d to %d, j from %d to %d",
		cellX - iRadius, cellX + numCellsAbove, cellY - iRadius, cellY + numCellsAbove));

	for (i = cellX - iRadius; i < cellX + numCellsAbove; i++)
	{
		for (j = cellY - iRadius; j < cellY + numCellsAbove; j++)
		{
			PathfindCell *cell = getCell(layer, i, j);
			if (cell)
			{
				if (checkForAircraft)
				{
					if (!(cell->getAircraftGoalByte() & 1)) continue;
					if (cell->getGoalAircraft() == objID) continue;
					CHECKDEST_LOG((TheCRCParameterCheck, "          checkForAircraft=TRUE, return false: i=%d, j=%d", i, j));
					return false;
				}
				if (cell->getType() == 5)
				{
					CHECKDEST_LOG((TheCRCParameterCheck, "          cell is CELL_IMPASSABLE, return false: i=%d, j=%d", i, j));
					return false;
				}
				if ((cell->getPlayerImpassableByte() & 1) && RVA003DF580_CALL(Rva001BE410, obj, j_00010ea1)())
				{
					CHECKDEST_LOG((TheCRCParameterCheck, "          cell is playerImpassable and obj is human controlled, return false: i=%d, j=%d", i, j));
					return false;
				}
				if (cell->getType() == 2)
				{
					CHECKDEST_LOG((TheCRCParameterCheck, "          cell is CELL_CLIFF, return false: i=%d, j=%d", i, j));
					return false;
				}
				if (cell->getType() == 4)
				{
					if (cell->isObstaclePresent(ignoreId))
						continue;
					CHECKDEST_LOG((TheCRCParameterCheck, "          cell is CELL_OBSTACLE, return false: i=%d, j=%d", i, j));
					return false;
				}
				if (cell->getType() == 5)
				{
					CHECKDEST_LOG((TheCRCParameterCheck, "          cell is CELL_IMPASSABLE, return false: i=%d, j=%d", i, j));
					return false;
				}
				if (cell->getType() == 6)
				{
					CHECKDEST_LOG((TheCRCParameterCheck, "          cell is CELL_IMPASSABLE, return false: i=%d, j=%d", i, j));
					return false;
				}
				if (cell->getFlags() == 0)
					continue;
				ObjectID goalUnitID = cell->getGoalUnit();
				if (goalUnitID == objID)
					continue;
				else if (ignoreId == goalUnitID)
					continue;
				else if (goalUnitID != INVALID_ID)
				{
					if (skipUnitCheck)
						continue;
					Object *unit = TheBfmeGameLogic->findObjectByID(goalUnitID);
					if (unit)
					{
						if (obj->getRelationship(unit) == ALLIES)
						{
							if (!ursurpAllyGoalCells)
							{
								CHECKDEST_LOG((TheCRCParameterCheck, "          cell is !ursurpAllyGoalCells, return false: i=%d, j=%d", i, j));
								return false;
							}
							(*allyGoalCount)++;
							continue;
						}
						if (cell->getFlags() == 0x18)
						{
							if (!RVA003DF580_CALL(Rva001CC790, obj, j_000420aa)(unit, 2))
							{
								if (!canPathThroughInfantry)
								{
									CHECKDEST_LOG((TheCRCParameterCheck, "          !canPathThroughInfantry, return false: i=%d, j=%d", i, j));
									return false;
								}
								if (!RVA003DF580_CALL(Rva000A2CF0, unit, j_0003251f)(8))
								{
									CHECKDEST_LOG((TheCRCParameterCheck, "          Sorry no luck (not infantry), return false: i=%d, j=%d", i, j));
									return false;
								}
							}
						}
					}
				}
			}
			else
			{
				CHECKDEST_LOG((TheCRCParameterCheck, "          OFF THE MAP, return false: i=%d, j=%d", i, j));
				return false;
			}
		}
	}
	return true;
}
