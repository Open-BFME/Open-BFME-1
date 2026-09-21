// ?move@Rva001BB530Mover@@QAEXPAVObject@@PBUCoord3D@@MM@Z
// partial score=0.16 date=2026-09-18
// cl: /O2 /GR- /DNDEBUG /DWIN32 /MD /EHsc-
// Retail RVA 0x001BB530, size 0x539.  The typed name is address-qualified:
// the locomotor caller proves the four-argument mover ABI, while the body
// evidence proves the path-result, horde, and movement-helper contracts.

typedef bool Bool;
typedef float Real;
typedef int Int;
typedef unsigned UnsignedInt;

#include <math.h>

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Matrix3D
{
};

struct Mat12
{
	Real m[12];
};

class Object;
class Rva001B7200Path;

class Thing
{
public:
	char m_pad000[0x38];
	void setTransformMatrix(const Matrix3D *matrix);
};

class Rva001BB530Horde;

class Rva001BB530Contain
{
public:
#define RVA_BB530_SLOT(n) virtual void slot##n() = 0;
	RVA_BB530_SLOT(00); RVA_BB530_SLOT(01); RVA_BB530_SLOT(02);
	RVA_BB530_SLOT(03); RVA_BB530_SLOT(04); RVA_BB530_SLOT(05);
	RVA_BB530_SLOT(06); RVA_BB530_SLOT(07); RVA_BB530_SLOT(08);
	RVA_BB530_SLOT(09); RVA_BB530_SLOT(10); RVA_BB530_SLOT(11);
	RVA_BB530_SLOT(12); RVA_BB530_SLOT(13); RVA_BB530_SLOT(14);
	RVA_BB530_SLOT(15); RVA_BB530_SLOT(16); RVA_BB530_SLOT(17);
	RVA_BB530_SLOT(18); RVA_BB530_SLOT(19); RVA_BB530_SLOT(20);
	RVA_BB530_SLOT(21); RVA_BB530_SLOT(22); RVA_BB530_SLOT(23);
	RVA_BB530_SLOT(24); RVA_BB530_SLOT(25);
	virtual Rva001BB530Horde *getHordeContainInterface() = 0;
#undef RVA_BB530_SLOT
};

class Rva001BB530Horde
{
public:
#define RVA_BB530_HORDE_SLOT(n) virtual void slot##n() = 0;
	RVA_BB530_HORDE_SLOT(00); RVA_BB530_HORDE_SLOT(01);
	RVA_BB530_HORDE_SLOT(02); RVA_BB530_HORDE_SLOT(03);
	RVA_BB530_HORDE_SLOT(04); RVA_BB530_HORDE_SLOT(05);
	RVA_BB530_HORDE_SLOT(06); RVA_BB530_HORDE_SLOT(07);
	RVA_BB530_HORDE_SLOT(08); RVA_BB530_HORDE_SLOT(09);
	RVA_BB530_HORDE_SLOT(10); RVA_BB530_HORDE_SLOT(11);
	RVA_BB530_HORDE_SLOT(12); RVA_BB530_HORDE_SLOT(13);
	RVA_BB530_HORDE_SLOT(14);
	virtual void slot15() = 0;
	virtual Bool slot16() = 0;
	RVA_BB530_HORDE_SLOT(17);
	RVA_BB530_HORDE_SLOT(18); RVA_BB530_HORDE_SLOT(19);
	RVA_BB530_HORDE_SLOT(20); RVA_BB530_HORDE_SLOT(21);
	RVA_BB530_HORDE_SLOT(22); RVA_BB530_HORDE_SLOT(23);
	RVA_BB530_HORDE_SLOT(24); RVA_BB530_HORDE_SLOT(25);
	RVA_BB530_HORDE_SLOT(26); RVA_BB530_HORDE_SLOT(27);
	RVA_BB530_HORDE_SLOT(28); RVA_BB530_HORDE_SLOT(29);
	RVA_BB530_HORDE_SLOT(30); RVA_BB530_HORDE_SLOT(31);
	RVA_BB530_HORDE_SLOT(32); RVA_BB530_HORDE_SLOT(33);
	RVA_BB530_HORDE_SLOT(34); RVA_BB530_HORDE_SLOT(35);
	RVA_BB530_HORDE_SLOT(36); RVA_BB530_HORDE_SLOT(37);
	RVA_BB530_HORDE_SLOT(38); RVA_BB530_HORDE_SLOT(39);
	RVA_BB530_HORDE_SLOT(40); RVA_BB530_HORDE_SLOT(41);
	RVA_BB530_HORDE_SLOT(42); RVA_BB530_HORDE_SLOT(43);
	RVA_BB530_HORDE_SLOT(44); RVA_BB530_HORDE_SLOT(45);
	RVA_BB530_HORDE_SLOT(46); RVA_BB530_HORDE_SLOT(47);
	RVA_BB530_HORDE_SLOT(48); RVA_BB530_HORDE_SLOT(49);
	RVA_BB530_HORDE_SLOT(50); RVA_BB530_HORDE_SLOT(51);
	RVA_BB530_HORDE_SLOT(52); RVA_BB530_HORDE_SLOT(53);
	RVA_BB530_HORDE_SLOT(54); RVA_BB530_HORDE_SLOT(55);
	RVA_BB530_HORDE_SLOT(56); RVA_BB530_HORDE_SLOT(57);
	RVA_BB530_HORDE_SLOT(58); RVA_BB530_HORDE_SLOT(59);
	RVA_BB530_HORDE_SLOT(60); RVA_BB530_HORDE_SLOT(61);
	RVA_BB530_HORDE_SLOT(62); RVA_BB530_HORDE_SLOT(63);
	RVA_BB530_HORDE_SLOT(64); RVA_BB530_HORDE_SLOT(65);
	RVA_BB530_HORDE_SLOT(66); RVA_BB530_HORDE_SLOT(67);
	RVA_BB530_HORDE_SLOT(68); RVA_BB530_HORDE_SLOT(69);
	RVA_BB530_HORDE_SLOT(70); RVA_BB530_HORDE_SLOT(71);
	RVA_BB530_HORDE_SLOT(72); RVA_BB530_HORDE_SLOT(73);
	RVA_BB530_HORDE_SLOT(74); RVA_BB530_HORDE_SLOT(75);
	RVA_BB530_HORDE_SLOT(76); RVA_BB530_HORDE_SLOT(77);
	RVA_BB530_HORDE_SLOT(78); RVA_BB530_HORDE_SLOT(79);
	RVA_BB530_HORDE_SLOT(80); RVA_BB530_HORDE_SLOT(81);
	RVA_BB530_HORDE_SLOT(82); RVA_BB530_HORDE_SLOT(83);
	RVA_BB530_HORDE_SLOT(84); RVA_BB530_HORDE_SLOT(85);
	RVA_BB530_HORDE_SLOT(86); RVA_BB530_HORDE_SLOT(87);
	RVA_BB530_HORDE_SLOT(88); RVA_BB530_HORDE_SLOT(89);
	RVA_BB530_HORDE_SLOT(90); RVA_BB530_HORDE_SLOT(91);
	RVA_BB530_HORDE_SLOT(92); RVA_BB530_HORDE_SLOT(93);
	RVA_BB530_HORDE_SLOT(94); RVA_BB530_HORDE_SLOT(95);
	virtual Bool slot96(Int value) = 0;
	RVA_BB530_HORDE_SLOT(97); RVA_BB530_HORDE_SLOT(98);
	RVA_BB530_HORDE_SLOT(99); RVA_BB530_HORDE_SLOT(100);
	RVA_BB530_HORDE_SLOT(101);
	virtual Bool slot102(Real value) = 0;
	RVA_BB530_HORDE_SLOT(103); RVA_BB530_HORDE_SLOT(104);
	virtual Bool slot105() = 0;
	RVA_BB530_HORDE_SLOT(106);
	virtual void slot107(Coord3D *point, Int objectID) = 0;
#undef RVA_BB530_HORDE_SLOT
};

class Rva001BB530AIUpdate
{
public:
	char m_pad000[0x140];
	Rva001B7200Path *m_path;
};

class Object : public Thing
{
public:
	Coord3D m_position;
	Real m_orientation;
	char m_pad048[0x118 - 0x48];
	unsigned char m_field118;
	char m_pad119[0x1fc - 0x119];
	Rva001BB530Contain *m_contain;
	char m_pad200[4];
	Rva001BB530AIUpdate *m_ai;
};

class Overridable
{
public:
	void *m_vtable;
	Overridable *m_nextOverride;
	Overridable *getFinalOverride();
};

class Rva001BB530Template : public Overridable
{
public:
	char m_pad008[0x80 - 0x08];
	Real m_field80;
	char m_pad084[0xc8 - 0x84];
	UnsignedInt m_fieldc8;
	char m_pad0cc[0xd4 - 0xcc];
	void *m_fieldd4;
};

class Rva001BB530Mover;

class Rva001B7200PointInfo
{
public:
	Real m_distance;
	Coord3D m_position;
	Real m_unknown10;
	Real m_unknown14;
	Real m_unknown18;
	Int m_layer;
	Int m_objectID;
	char m_retailPad024[4];
};

class Rva001B7200TerrainResult
{
public:
	virtual void v00() = 0;
	virtual void v01() = 0;
	virtual void v02() = 0;
	virtual void v03() = 0;
	virtual void v04() = 0;
	virtual void v05() = 0;
	virtual void v06() = 0;
	virtual void v07() = 0;
	virtual void v08() = 0;
	virtual void v09() = 0;
	virtual void v10() = 0;
	virtual void v11() = 0;
	virtual void v12() = 0;
	virtual void v13() = 0;
	virtual void v14() = 0;
	virtual void v15() = 0;
	virtual void v16() = 0;
	virtual void v17() = 0;
	virtual void v18() = 0;
	virtual void v19() = 0;
	virtual void v20() = 0;
	virtual void v21() = 0;
	virtual void v22() = 0;
	virtual void v23() = 0;
	virtual void v24() = 0;
	virtual void v25() = 0;
	virtual void v26() = 0;
	virtual void v27() = 0;
	virtual void v28() = 0;
	virtual void v29() = 0;
	virtual void v30() = 0;
	virtual void v31() = 0;
	virtual void v32() = 0;
	virtual void v33() = 0;
	virtual void v34() = 0;
	virtual void v35() = 0;
	virtual void v36() = 0;
	virtual void v37() = 0;
	virtual void v38() = 0;
	virtual void v39() = 0;
	virtual void v40() = 0;
	virtual void v41() = 0;
	virtual void v42() = 0;
	virtual void v43() = 0;
	virtual void v44() = 0;
	virtual void v45() = 0;
	virtual void v46() = 0;
	virtual void v47() = 0;
	virtual void v48() = 0;
	virtual void v49() = 0;
	virtual void v50() = 0;
	virtual void v51() = 0;
	virtual void v52() = 0;
	virtual void v53() = 0;
	virtual void v54() = 0;
	virtual void v55() = 0;
	virtual void v56() = 0;
	virtual void v57() = 0;
	virtual void v58() = 0;
	virtual void v59() = 0;
	virtual void v60() = 0;
	virtual void v61() = 0;
	virtual void v62() = 0;
	virtual void v63() = 0;
	virtual void v64() = 0;
	virtual void v65() = 0;
	virtual void v66() = 0;
	virtual void v67() = 0;
	virtual void v68() = 0;
	virtual void v69() = 0;
	virtual void v70() = 0;
	virtual void v71() = 0;
	virtual void v72() = 0;
	virtual void v73() = 0;
	virtual void v74() = 0;
	virtual void v75() = 0;
	virtual void v76() = 0;
	virtual void v77() = 0;
	virtual void v78() = 0;
	virtual void v79() = 0;
	virtual void v80() = 0;
	virtual void v81() = 0;
	virtual void v82() = 0;
	virtual void v83() = 0;
	virtual void v84() = 0;
	virtual void v85() = 0;
	virtual void v86() = 0;
	virtual void v87() = 0;
	virtual void v88() = 0;
	virtual void v89() = 0;
	virtual void v90() = 0;
	virtual void v91() = 0;
	virtual void v92() = 0;
	virtual void v93() = 0;
	virtual void v94() = 0;
	virtual void v95() = 0;
	virtual void v96() = 0;
	virtual void v97() = 0;
	virtual void v98() = 0;
	virtual void v99() = 0;
	virtual void v100() = 0;
	virtual void v101() = 0;
	virtual Bool v102(Int value) = 0;

	Real m_value;
	char m_pad008[4];
	Coord3D m_position;
	char m_pad018[0x60 - 0x18];
	Int m_state;
	char m_pad064[0xa8 - 0x64];
	Int m_objectID;
};

class Rva001BB530TerrainLogic
{
public:
#define RVA_BB530_TERRAIN_SLOT(n) virtual void slot##n() = 0;
	RVA_BB530_TERRAIN_SLOT(00); RVA_BB530_TERRAIN_SLOT(01);
	RVA_BB530_TERRAIN_SLOT(02); RVA_BB530_TERRAIN_SLOT(03);
	RVA_BB530_TERRAIN_SLOT(04); RVA_BB530_TERRAIN_SLOT(05);
	RVA_BB530_TERRAIN_SLOT(06); RVA_BB530_TERRAIN_SLOT(07);
	RVA_BB530_TERRAIN_SLOT(08); RVA_BB530_TERRAIN_SLOT(09);
	RVA_BB530_TERRAIN_SLOT(10); RVA_BB530_TERRAIN_SLOT(11);
	RVA_BB530_TERRAIN_SLOT(12); RVA_BB530_TERRAIN_SLOT(13);
	RVA_BB530_TERRAIN_SLOT(14); RVA_BB530_TERRAIN_SLOT(15);
	RVA_BB530_TERRAIN_SLOT(16); RVA_BB530_TERRAIN_SLOT(17);
	RVA_BB530_TERRAIN_SLOT(18); RVA_BB530_TERRAIN_SLOT(19);
	RVA_BB530_TERRAIN_SLOT(20); RVA_BB530_TERRAIN_SLOT(21);
	RVA_BB530_TERRAIN_SLOT(22); RVA_BB530_TERRAIN_SLOT(23);
	RVA_BB530_TERRAIN_SLOT(24); RVA_BB530_TERRAIN_SLOT(25);
	RVA_BB530_TERRAIN_SLOT(26); RVA_BB530_TERRAIN_SLOT(27);
	RVA_BB530_TERRAIN_SLOT(28); RVA_BB530_TERRAIN_SLOT(29);
	RVA_BB530_TERRAIN_SLOT(30); RVA_BB530_TERRAIN_SLOT(31);
	virtual Rva001B7200TerrainResult *query(Int value) = 0;
#undef RVA_BB530_TERRAIN_SLOT
};

extern Rva001BB530TerrainLogic *TheTerrainLogic;
extern const Real BfmeZeroRange;
extern const Real g_bfmeScaleBK;
extern Real normalizeAngle(Real angle);
extern void *Rva001B4750Get(void *object);
#define Rva01083B6C (*(const Real *)0x01083B6C)

class Rva001B7200Path
{
public:
	void computePointOnPath(Object *object, Rva001BB530Mover *locomotor,
		Rva001B7200PointInfo *point, Bool useCache);
};

class BfmeHelpD820
{
public:
	void bfmeGoD820(Object *object, const Coord3D *goal, Int value);
};

class Rva001B7200Locomotor
{
public:
	Bool move(Object *object, Rva001B7200TerrainResult *result);
	void updatePosition(const Coord3D *position);
};

class AIUpdateInterface
{
public:
	Real getFormationMovementSpeed(Object *object);
};

class BfmeSub1CC_EC3
{
public:
	Real query(void *object);
	void queryClamp(Real value, void *object);
	void finish(Mat12 *matrix, Int a, Int b, Int c);
};

class BfmeD1054
{
};

class BfmeC1054
{
public:
	void bfmeStep1054(BfmeD1054 *object, Int value, Int zero);
};

class BfmeQ1282
{
};

class BfmeA1282
{
public:
	void bfmeFinish1282(BfmeQ1282 *object, const Coord3D *goal,
		Real onPathDistToGoal, Real desiredSpeed);
};

class Locomotor
{
public:
	Real getMaxTurnRate(Object *object) const;
};

class Gen_uw_0002ab7b
{
public:
	~Gen_uw_0002ab7b() throw();
	void *m_begin;
	void *m_end;
	void *m_unused;
};

class Rva001B4A50Locomotor
{
public:
	void apply(Real angle);
};

class Rva001BB530Mover
{
public:
	void move(Object *object, const Coord3D *goalPos,
		Real onPathDistToGoal, Real desiredSpeed);

	private:
	char m_pad000[4];
	Rva001BB530Template *m_template;
	char m_pad008[0x3c - 0x08];
	Real m_cachedAngle;
	UnsignedInt m_flags;
	char m_pad044[0x94 - 0x44];
	unsigned char m_field094;
	char m_pad095[1];
	unsigned char m_field096;
};

// These four direct calls are still anonymous in the ledger.  Their names
// retain the retail target address and only describe the ABI visible here.
class Rva00401B10Owner
{
public:
	void fill(Real value, Gen_uw_0002ab7b *range);
};

#pragma comment(linker, "/alternatename:?computePointOnPath@Rva001B7200Path@@QAEXPAVObject@@PAVRva001BB530Mover@@PAURva001B7200PointInfo@@_N@Z=?j_00008a9e@@YAXXZ")
#pragma comment(linker, "/alternatename:?updatePosition@Rva001B7200Locomotor@@QAEXPBUCoord3D@@@Z=?j_0000c1b7@@YAXXZ")
#pragma comment(linker, "/alternatename:?move@Rva001B7200Locomotor@@QAE_NPAVObject@@PAVRva001B7200TerrainResult@@@Z=?j_00018a6b@@YAXXZ")
#pragma comment(linker, "/alternatename:?fill@Rva00401B10Owner@@QAEXMPAVGen_uw_0002ab7b@@@Z=?j_0001cc1f@@YAXXZ")
#pragma comment(linker, "/alternatename:?apply@Rva001B4A50Locomotor@@QAEXM@Z=?j_0003acc4@@YAXXZ")
#pragma comment(linker, "/alternatename:?finish@BfmeSub1CC_EC3@@QAEXPAUMat12@@HHH@Z=?j_00033861@@YAXXZ")

void Rva001BB530Mover::move(Object *obj, const Coord3D *goalPos,
	Real onPathDistToGoal, Real desiredSpeed)
{
	Object *object = obj;
	Rva001BB530Contain *contain = object->m_contain;
	volatile Rva001BB530Horde *hordeSlot;
	if (contain != 0)
		hordeSlot = contain->getHordeContainInterface();
	else
		hordeSlot = 0;
	Rva001BB530Horde *horde = (Rva001BB530Horde *)hordeSlot;

	Bool pathResult = false;
	Rva001BB530AIUpdate *ai = object->m_ai;
	Rva001B7200Path *path;
	Rva001B7200TerrainResult *terrainResult;
	if (ai != 0)
		path = ai->m_path;
	else
		path = 0;
	if (path == 0)
	{
		if (horde != 0)
			horde->slot96(0);
		goto movement;
	}
	{
		Rva001B7200PointInfo point;
		path->computePointOnPath(object, this, &point, false);
		if (m_field096 != 0 && horde != 0 && !horde->slot105())
		{
			((BfmeHelpD820 *)this)->bfmeGoD820(object, goalPos, 0);
			return;
		}
		m_field096 = 0;
		if (point.m_objectID == 0x7fffffff)
		{
			if (horde != 0)
				horde->slot96(0);
			goto movement;
		}

			terrainResult = TheTerrainLogic->query(point.m_objectID);
		if (terrainResult != 0)
		{
			Int state = terrainResult->m_state;
			pathResult = true;
			if (state == 3)
			{
				if (((Rva001B7200Locomotor *)this)->move(object, terrainResult))
					return;
			}
			if (state == 4)
				goto movement;
			if (state != 2)
				goto movement;
			if (horde == 0)
				goto movement;
			if (!horde->slot105())
				return;

			{
				Gen_uw_0002ab7b range;
				range.m_begin = 0;
				range.m_end = 0;
				range.m_unused = 0;
				void *nested = Rva001B4750Get(object);
				if (nested == 0)
					return;
				((Rva00401B10Owner *)nested)->fill(terrainResult->m_value,
					&range);
				*(Int *)&desiredSpeed = 0x7fffffff;
				for (Int *item = (Int *)range.m_begin;
					item != (Int *)range.m_end; ++item)
			{
				Rva001B7200TerrainResult *entry =
						TheTerrainLogic->query(*item);
				if (entry != 0)
				{
					horde->slot107(&entry->m_position,
						entry->m_value);
					desiredSpeed = entry->m_value;
				}
			}
			Rva001B7200Path *nestedPath =
				(Rva001B7200Path *)Rva001B4750Get(object);
			if (nestedPath == 0)
				return;
				nestedPath->computePointOnPath(object, this, &point, false);
			((BfmeC1054 *)this)->bfmeStep1054(
				(BfmeD1054 *)object, (Int)&point.m_position, 0);
			Coord3D copied = point.m_position;
			Rva001B7200Path *repeatPath =
				(Rva001B7200Path *)Rva001B4750Get(object);
			if (repeatPath == 0)
				return;
			for (Int pass = 0; pass != 3; ++pass)
			{
				Real speed = ((AIUpdateInterface *)this)->getFormationMovementSpeed(object);
				((BfmeSub1CC_EC3 *)this)->queryClamp(speed, object);
				repeatPath->computePointOnPath(object, this, &point,
					true);
			}
			((Rva001B7200Locomotor *)this)->updatePosition(
				&point.m_position);
			m_field096 = 1;
			horde->slot107(&copied, desiredSpeed);
			return;
		}
	}
	}

movement:
	Real formationSpeed = ((AIUpdateInterface *)this)->getFormationMovementSpeed(object);
	Real maxTurnRate = ((Locomotor *)this)->getMaxTurnRate(object);
	if (desiredSpeed > formationSpeed)
		desiredSpeed = formationSpeed;

	Real desiredAngle = (Real)atan2(goalPos->y - object->m_position.y,
		goalPos->x - object->m_position.x);
	desiredAngle = normalizeAngle(desiredAngle - object->m_orientation);
	Coord3D desired = *goalPos;

	Rva001BB530Template *templ = m_template;
	if (templ != 0 && templ->m_nextOverride != 0)
		templ = (Rva001BB530Template *)templ->getFinalOverride();
	Bool useFormation = false;
	if (templ != 0 && templ->m_fieldd4 != 0 &&
				(object->m_field118 & 1) != 0)
		useFormation = true;

	if (m_cachedAngle == BfmeZeroRange)
	{
		if (useFormation)
			m_flags |= 0x80;
		else
			m_flags &= ~0x80u;
		m_field094 = 0;
	}
	if ((m_flags & 0x80) != 0 && !useFormation)
		m_flags &= ~0x80u;

	if ((m_flags & 0x80) != 0)
	{
		Real adjusted = normalizeAngle(desiredAngle - 3.1415927f);
		adjusted = normalizeAngle(adjusted - object->m_orientation);
		desired.x = object->m_position.x * 2.0f - goalPos->x;
		desired.y = object->m_position.y * 2.0f - goalPos->y;
		desired.z = object->m_position.z * 2.0f - goalPos->z;
	}

	if (templ != 0 && templ->m_nextOverride != 0)
		templ = (Rva001BB530Template *)templ->getFinalOverride();
	(void)cosf(formationSpeed);

	if ((Real)cosf(templ != 0 ? templ->m_field80 : BfmeZeroRange) >
		(templ != 0 ? templ->m_field80 : BfmeZeroRange) &&
		pathResult == 0 && horde != 0)
	{
		horde->slot15();
		((Rva001B4A50Locomotor *)this)->apply(desiredSpeed);
		((Thing *)object)->setTransformMatrix((const Matrix3D *)((char *)this + 0x64));
		if (horde->slot16())
			desired.z = object->m_orientation;
	}
	else if (pathResult != 0)
	{
		desired.z = object->m_orientation;
	}

	Int finishBits = *(Int *)&maxTurnRate;
	if (templ != 0)
		finishBits = *(Int *)&templ->m_field80;
	((BfmeSub1CC_EC3 *)this)->finish((Mat12 *)object,
		(Int)&desired, finishBits, (Int)&formationSpeed);

	if (templ != 0 && templ->m_nextOverride != 0)
		templ = (Rva001BB530Template *)templ->getFinalOverride();
	Real speed = ((AIUpdateInterface *)this)->getFormationMovementSpeed(object);
	if (speed * Rva01083B6C <= m_cachedAngle && templ != 0 &&
		(templ->m_fieldc8 & 0x200) != 0 && horde != 0 &&
		!horde->slot102(desiredSpeed))
	{
		desiredSpeed *= g_bfmeScaleBK;
	}
	((BfmeA1282 *)this)->bfmeFinish1282((BfmeQ1282 *)object,
		&desired, onPathDistToGoal, desiredSpeed);
}
