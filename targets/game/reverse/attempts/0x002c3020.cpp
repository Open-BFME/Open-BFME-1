// ?onEnter@AIGiantBirdSwoopState@@UAE?AW4StateReturnType@@XZ
// partial score=0.9981 date=2026-09-28
// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// ?onEnter@AIGiantBirdSwoopState@@UAE?AW4StateReturnType@@XZ
// partial 2026-09-28 opus-5.5: 1057/1057 B, 2 differing bytes, shape 1.000.
// Residue: the inlined GeometryInfo destructor's EH state numbers (retail 3
// then 2 at +0xBD/+0xCE, ours 2 then 1). Retail's unwind map (tools/eh_info.py
// 0x002C3020) has a state for the +0x08 Coord2D member (cleanup 0x0005BD90,
// ??1Coord2D@@QAE@XZ, out of line in coord2d.cpp) while its main path emits no
// call: consistent with the empty out-of-line dtor being removed after state
// numbering (link-time inlining). Tried: in-class/forceinline/late-inline/
// Coord2DBase-derived/dead-store/helper-call dtors (2 diffs), decl-only (3/2
// states but an extra call, 687 diffs).
// To land: rename 0x000D3F10 ?test@Rva000D3F10@@QAEHI@Z to the bool-returning
// ?test@Rva000D3F10@@QAE_NI@Z (this caller tests al; the 41 B body matches
// either way) in the same commit.
//
// AIGiantBirdSwoopState::onEnter, retail RVA 0x002C3020, 1057 bytes.
// The constructor at 0x002BE230 installs vtable 0x010C7868; its slot 4 thunk
// 0x0042DCC7 jumps here (slot 5 is the matched onExit at 0x002BE320).  The
// state and owner layouts follow the matched Giant Bird siblings
// (AIGiantBirdSwoopStateOnExit.cpp, AIGiantBirdFollowThruStateUpdate.cpp,
// GiantBirdStateConstructors.cpp); fields no caller names keep their offsets.

#include <vector>

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef int ObjectID;

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

enum WeaponChoiceCriteria { PREFER_MOST_DAMAGE = 0 };
enum CommandSourceType { CMD_FROM_PLAYER = 0, CMD_FROM_AI = 2 };
enum WeaponSlotType { PRIMARY_WEAPON = 0 };
enum KindOfType { KINDOF_FIRST = 0 };

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

// GeometryInfo as the matched copy constructor 0x000FFCA0/0x000FFD10 pair
// lays it out: a polymorphic Snapshot part at +0x00, scalars, the shape
// vector at +0x2C, the record vector at +0x38 and the cached extent tail.
// Retail's destructor (0x000FFCA0, reproduced byte for byte by the
// compiler-generated one) destroys the two vectors and ends with the Snapshot
// vftable store, with no opening reset. Inlined here it needs the same shape,
// so the view keeps the polymorphic part as its first member, the spelling
// R4VptrTailDestructors.cpp uses for 0x000FFCA0.
class Snapshot
{
public:
	virtual __forceinline ~Snapshot() {}
	virtual void loadPostProcess();
	virtual const char *getSnapshotName();
	virtual void xfer(class Xfer &xfer);
};

struct Gen000FF700 { char m_bytes[0x24]; };
struct Gen000FF7D0 { char m_bytes[0x10]; };

namespace _STL
{
	template <> vector<Gen000FF700, allocator<Gen000FF700> >::~vector();
	template <> vector<Gen000FF7D0, allocator<Gen000FF7D0> >::~vector();
}

// Retail's unwind map for this body destroys a subobject at +0x08 through
// the empty destructor 0x0005BD90 (??1Coord2D@@QAE@XZ) between the shape
// vector and the Snapshot part.
struct Coord2D
{
	Real x;
	Real y;
	~Coord2D() {}
};

class GeometryInfo
{
public:
	GeometryInfo(const GeometryInfo &other);
	__forceinline ~GeometryInfo() {}

private:
	Snapshot m_snapshot;
	Bool m_isSmall;
	Coord2D m_coord08;
	int m_scalars[7];
	_STL::vector<Gen000FF700> m_shapes;
	_STL::vector<Gen000FF7D0> m_records;
	int m_cached[6];
};

// The matched 0x0087DBF0 body reads the geometry's vertical center offset.
class BfmeBoundaryGeometry3D
{
public:
	Real bfmeZDeltaToCenter(void) const;
};

class Weapon;
class AIUpdateInterface;

class Thing
{
public:
	Bool isKindOf(KindOfType kindOf) const;
};

class Object : public Thing
{
public:
	Bool chooseBestWeaponForTarget(const Object *target,
		WeaponChoiceCriteria criteria, CommandSourceType cmdSource);
	Weapon *getCurrentWeapon(WeaponSlotType *slot);
	Object *bfmePostClosest(const Object *other, Bool flag);
	Bool getWorldspaceBestContactPoint(Coord3D *pointOut,
		const Coord3D *callerPos, const char *preferredPoint, Int arg4,
		Int seed, Bool skipCollideTest) const;

	char m_before38[0x38];
	Coord3D m_position38;
	char m_before74[0x74 - 0x44];
	ObjectID m_id;
	char m_before90[0x90 - 0x78];
	UnsignedInt m_status[3];
	char m_beforeAC[0xac - 0x9c];
	GeometryInfo m_geometryInfo;
	char m_before1FC[0x1fc - 0xac - sizeof(GeometryInfo)];
	class Rva002C3020Contain *m_contain1fc;
	char m_before204[4];
	AIUpdateInterface *m_ai204;
	char m_before214[0x214 - 0x208];
	Object *m_container214;
	char m_before344[0x344 - 0x218];
	unsigned char m_privateStatus;
};

class Rva002C3020Contain
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14();
	virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot20();
	virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25();
	virtual Int slot68();
};

// Flag-array test at Object+0x110 (matched 0x000D3F10).
class Rva000D3F10
{
public:
	Bool test(unsigned index);
};

class WeaponTemplate
{
public:
	char m_before4ac[0x4ac];
	Int m_field4ac;
};

class Weapon
{
public:
	char m_before04[4];
	WeaponTemplate *m_template;
};

class BfmeOtherMG;

class BfmeThingMG
{
public:
	unsigned char bfmeTellMG(BfmeOtherMG *source, void *target);
};

template <int N>
class BfmeVirtualSlots : public BfmeVirtualSlots<N - 1>
{
public:
	virtual void unused(char (*)[N]) = 0;
};

template <>
class BfmeVirtualSlots<0>
{
};

class Rva002C3020Terrain
{
public:
	char m_before44[0x44];
	Real m_height44;
};

class AIUpdateInterface : public BfmeVirtualSlots<84>
{
public:
	virtual AIUpdateInterface *slot150() = 0;
	virtual void slot151() = 0; virtual void slot152() = 0;
	virtual void slot153() = 0; virtual void slot154() = 0;
	virtual void slot155() = 0; virtual void slot156() = 0;
	virtual void slot157() = 0; virtual void slot158() = 0;
	virtual void slot159() = 0; virtual void slot160() = 0;
	virtual void slot161() = 0; virtual void slot162() = 0;
	virtual void slot163() = 0; virtual void slot164() = 0;
	virtual void slot165() = 0; virtual void slot166() = 0;
	virtual void slot167() = 0; virtual void slot168() = 0;
	virtual void slot169() = 0; virtual void slot170() = 0;
	virtual void slot171() = 0; virtual void slot172() = 0;
	virtual void slot173() = 0; virtual void slot174() = 0;
	virtual void slot175() = 0; virtual void slot176() = 0;
	virtual void slot177() = 0; virtual void slot178() = 0;
	virtual void slot179() = 0; virtual void slot180() = 0;
	virtual void slot181() = 0; virtual void slot182() = 0;
	virtual void slot183() = 0; virtual void slot184() = 0;
	virtual void slot185() = 0; virtual void slot186() = 0;
	virtual void slot187() = 0; virtual void slot188() = 0;
	virtual void slot189() = 0; virtual void slot190() = 0;
	virtual void slot191() = 0; virtual void slot192() = 0;
	virtual void setLocomotorSet(Int set) = 0;

	Bool testFlag3f0(Int bit) const { return (m_flags3f0 >> bit) & 1; }
	void setCurrentVictim(const Object *victim);
	Object *getCurrentVictim() const;
	Bool findNearestLabeledContactPointOnTarget(Object *target,
		Coord3D *pointOut, const Coord3D *callerPos, Bool flag);

	char m_before1cc[0x1cc - 4];
	Rva002C3020Terrain *m_field1cc;
	char m_before3f0[0x3f0 - 0x1d0];
	UnsignedInt m_flags3f0;
	char m_before3f8[4];
	ObjectID m_targetID3f8;
	char m_before424[0x424 - 0x3fc];
	unsigned char m_continue424;
	char m_before48c[0x48c - 0x425];
	ObjectID m_targetID48c;
	char m_before494[4];
	Int m_mode494;
};

class Rva002BC260Owner
{
public:
	void run(void *arg1, void *arg2, void *arg3, void *arg4);
};

class TerrainLogic
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual Real getGroundHeight(Real x, Real y, Coord3D *normal);
};

class GameLogic
{
public:
	Object *findObjectByID(ObjectID id);
};

class StateMachine
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03(); virtual void slot04(); virtual void slot05();
	virtual void slot06(); virtual void slot07(); virtual void slot08();
	virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13();
	virtual void setGoalObject(const Object *object);

	Object *getGoalObject();
	void setGoalPosition(const Coord3D *pos);

	char m_before10[0x0c];
	Object *m_owner;
	char m_before24[0x24 - 0x14];
	Coord3D m_goalPosition;
};

extern GameLogic *TheGameLogic;
extern TerrainLogic *TheTerrainLogic;
extern int g_Rva012F02D4;
extern int g_Rva012F02DC;
extern int g_Rva012F02E4;

Int GetGameLogicRandomValue(Int lo, Int hi, char *file, Int line);

class AIGiantBirdSwoopState
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02();
	virtual void slot03();
	virtual StateReturnType onEnter();

	Object *getMachineOwner() { return m_machine->m_owner; }

	char m_before1c[0x18];
	StateMachine *m_machine;
	char m_before24[4];
	ObjectID m_targetID;
	Coord3D m_goal;
	Bool m_enabled;
	char m_before38[3];
	Int m_counter;
	Real m_scale;
};

// ?onEnter@AIGiantBirdSwoopState@@UAE?AW4StateReturnType@@XZ
StateReturnType AIGiantBirdSwoopState::onEnter()
{
	Object *owner = getMachineOwner();
	AIUpdateInterface *ai = owner->m_ai204;
	Object *victim = 0;
	if (ai == 0 || (owner->m_privateStatus & 1) != 0)
		return STATE_FAILURE;

	ai->m_flags3f0 &= ~0x38;
	ai->m_targetID3f8 = 0;
	m_scale = 0.4f;

	if (m_targetID == 0)
	{
		owner->chooseBestWeaponForTarget(0, PREFER_MOST_DAMAGE, CMD_FROM_AI);
		m_goal = m_machine->m_goalPosition;
		ai->m_targetID3f8 = 0;
		{
			GeometryInfo geometry(owner->m_geometryInfo);
			m_goal.z += ((const BfmeBoundaryGeometry3D *)&geometry)->bfmeZDeltaToCenter();
		}
	}
	else
	{
		if (m_machine->getGoalObject() != 0 &&
			(victim = m_machine->getGoalObject()) != 0 &&
			((Rva000D3F10 *)victim)->test(0x47))
		{
			victim = 0;
			m_machine->setGoalObject(victim);
		}
		if (victim == 0)
		{
			if (ai->m_targetID48c != 0)
			{
				victim = TheGameLogic->findObjectByID(ai->m_targetID48c);
				m_scale = 1.0f;
			}
			if (victim == 0)
				return STATE_FAILURE;
		}
		if ((victim->m_privateStatus & 1) != 0)
			return STATE_FAILURE;

		if (victim->isKindOf((KindOfType)0x6c))
		{
			ai->m_targetID48c = victim->m_id;
			victim = victim->bfmePostClosest(owner, true);
		}
		else
		{
			Object *container = victim->m_container214;
			if (container != 0)
			{
				Rva002C3020Contain *contain = container->m_contain1fc;
				if (contain != 0 && contain->slot68())
					ai->m_targetID48c = container->m_id;
			}
			else
				ai->m_targetID48c = 0;
		}

		if (victim == 0 || (victim->m_privateStatus & 1) != 0)
			return STATE_FAILURE;

		ai->m_targetID3f8 = victim->m_id;
		owner->chooseBestWeaponForTarget(victim, (WeaponChoiceCriteria)2, CMD_FROM_AI);
		Weapon *weapon = owner->getCurrentWeapon(0);
		if (weapon == 0)
			return STATE_FAILURE;

		ai->m_flags3f0 &= ~0x10;
		if (((BfmeThingMG *)weapon)->bfmeTellMG((BfmeOtherMG *)owner, victim) &&
			(victim->isKindOf((KindOfType)0x8d) || (victim->m_status[2] & 4) != 0))
			ai->m_flags3f0 |= 0x110;
		else if (victim->isKindOf((KindOfType)0x0b))
			ai->m_flags3f0 = (ai->m_flags3f0 & ~0x100) | 0x20;
		else if (weapon->m_template->m_field4ac > 1 && (victim->m_status[0] & 0x40) == 0)
			ai->m_flags3f0 |= 8;

		ai->m_mode494 = 2;
		AIUpdateInterface *victimAI = victim->m_ai204;
		if (victimAI != 0)
		{
			AIUpdateInterface *other = victimAI->slot150();
			if (other != 0)
			{
				ai->setCurrentVictim(victim);
				if (other->getCurrentVictim() == owner)
				{
#line 551 "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Update\\AIUpdate\\GiantBirdAIUpdate.cpp"
					if (GetGameLogicRandomValue(11, 23, __FILE__, __LINE__) <= 17)
					{
						ai->m_mode494 = 0;
						other->m_mode494 = 1;
					}
					else
					{
						ai->m_mode494 = 1;
						other->m_mode494 = 0;
					}
				}
			}
		}

		const Coord3D *ownerPos = &owner->m_position38;
		if (!ai->findNearestLabeledContactPointOnTarget(victim, &m_goal, ownerPos, false))
		{
#line 567 "F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Update\\AIUpdate\\GiantBirdAIUpdate.cpp"
			victim->getWorldspaceBestContactPoint(&m_goal, ownerPos, 0, 1,
				GetGameLogicRandomValue(0, 12345678, __FILE__, __LINE__), false);
		}

		if (ai->m_mode494 != 2)
		{
			Rva002C3020Terrain *terrain = ai->m_field1cc;
			if (terrain != 0)
			{
				m_goal.z = TheTerrainLogic->getGroundHeight(m_goal.x, m_goal.y, 0) +
					terrain->m_height44;
				m_machine->setGoalPosition(&m_goal);
			}
		}
	}

	if (m_enabled)
		ai->setLocomotorSet(4);
	else if (ai->m_mode494 == 0)
		ai->setLocomotorSet(3);
	else
		ai->setLocomotorSet(6);

	if (ai->testFlag3f0(2) || ai->testFlag3f0(3))
		((Rva002BC260Owner *)ai)->run(&m_goal, &g_Rva012F02DC, 0, 0);
	else if (m_enabled)
		((Rva002BC260Owner *)ai)->run(&m_goal, &g_Rva012F02E4, 0, 0);
	else
		((Rva002BC260Owner *)ai)->run(&m_goal, &g_Rva012F02D4, 0, 0);

	return ai->m_continue424 ? STATE_CONTINUE : STATE_FAILURE;
}
