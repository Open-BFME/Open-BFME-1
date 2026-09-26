// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// AIGuardOuterState::onEnter, vtable 0x01096248 slot 4.
#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef float Real;

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class Object
{
public:
	unsigned char m_pad00[0x38];
	Coord3D m_position;
};

class StateMachine
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1c();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2c();
	virtual void slot30();
	virtual void slot34();
	virtual void setGoalObject(const Object *object);
};

class Rva0015C7A0GuardMachine : public StateMachine
{
public:
	unsigned char m_body[0x0c];
	Object *m_owner;
	unsigned char m_pad14[0x30];
	Int m_targetID;
	UnsignedInt m_teamID;
	class PolygonTrigger *m_area;
	Coord3D m_position;
	unsigned char m_pad5c[0x0c];
	Bool m_field68;
	unsigned char m_pad69[3];
	Int m_nemesisID;
	Int m_field70;
	Int getNemesisID() const { return m_nemesisID; }
};

typedef _STL::hash_map<Int, Object *, _STL::hash<Int>, _STL::equal_to<Int> > ObjectPtrHash;
class GameLogic
{
public:
	__declspec(noinline) Object *findObjectByID(Int id)
	{
		if (id == 0) return 0;
		ObjectPtrHash::iterator it = m_objHash.find(id);
		if (it == m_objHash.end()) return 0;
		return (*it).second;
	}
	UnsignedInt getFrame() { return m_frame; }
	unsigned char m_pad00[0x3c];
	UnsignedInt m_frame;
	unsigned char m_slice_pad[0x70];
	ObjectPtrHash m_objHash;
};

class Team
{
public:
	Coord3D *getEstimateTeamPosition(Coord3D *position) const;
};

class TeamFactory
{
public:
	Team *findTeamByID(UnsignedInt id);
};

class PolygonTrigger
{
public:
	void getCenterPoint(Coord3D *position) const;
};

class FactorsR0015C7A0
{
public:
	unsigned char m_pad00[0x3c];
	UnsignedInt m_field3c;
};

class AIRootR0015C7A0
{
public:
	unsigned char m_pad00[0x14];
	FactorsR0015C7A0 *m_factors;
	const FactorsR0015C7A0 *getAiData() const { return m_factors; }
};

class AttackExitConditionsInterface
{
public:
	virtual Bool shouldExit(const StateMachine *machine) const = 0;
};

class QR0015C7A0 : public AttackExitConditionsInterface
{
public:
	virtual Bool shouldExit(const StateMachine *machine) const
	{
		return false;
	}
	Int m_conditionsToConsider;
	Coord3D m_center;
	Real m_radiusSqr;
	UnsignedInt m_field18;
};

// Retail calls AIAttackState through ILT 0x0000BF3C.
class CtorTargetR0015C7A0
{
public:
	CtorTargetR0015C7A0(StateMachine *machine, Bool follow,
		Bool attackingObject, Bool forceAttacking,
		AttackExitConditionsInterface *conditions);
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual StateReturnType onEnter();
	unsigned char m_body[0x18];
	StateMachine *m_machine;
	unsigned char m_tail[0x34];
};

class State
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0c();
	virtual StateReturnType onEnter();
	StateMachine *getMachine() const { return m_machine; }
	unsigned char m_body[0x18];
	StateMachine *m_machine;
};

class AIGuardOuterState : public State
{
public:
	virtual StateReturnType onEnter();
	Rva0015C7A0GuardMachine *getGuardMachine() const { return (Rva0015C7A0GuardMachine *)getMachine(); }
	unsigned char m_pad20[4];
	QR0015C7A0 m_exitConditions;
	CtorTargetR0015C7A0 *m_attackState;
};

extern void j_0000bf3c();
extern void j_00004c37();
extern void j_00007ad6();
extern void j_0001f253();
extern void j_000241fe();
extern void j_0003a391();
extern void j_00044c2e();

typedef Object *(GameLogic::*FindObjectByIDCall)(Int);
typedef Team *(TeamFactory::*FindTeamByIDCall)(UnsignedInt);
typedef Coord3D *(Team::*EstimateTeamPositionCall)(Coord3D *) const;
typedef Int (Object::*GetLayerCall)() const;
typedef void (PolygonTrigger::*GetCenterPointCall)(Coord3D *) const;
typedef Bool (__cdecl *OutOfWeaponRangeCall)(Object *, Object *);

class Rva002BD020AI
{
public:
	static Real getAdjustedVisionRangeForObject(const Object *object, Int flags);
};

#pragma comment(linker, "/alternatename:??0CtorTargetR0015C7A0@@QAE@PAVStateMachine@@_N11PAVAttackExitConditionsInterface@@@Z=?j_0000bf3c@@YAXXZ")

StateReturnType AIGuardOuterState::onEnter()
{
	unsigned char *self = (unsigned char *)this;
	unsigned char *container = *reinterpret_cast<unsigned char **>(self + 0x1c);
	Int guardMode = *reinterpret_cast<Int *>(container + 0x70);
	if (guardMode == 1)
		return STATE_SUCCESS;

	Coord3D position;
	{
		GameLogic *logic = *(GameLogic **)0x012F0898;
		Object *target = logic->findObjectByID(*reinterpret_cast<Int *>(container + 0x44));

		Team *team = (*(TeamFactory **)0x012ED810)->findTeamByID(
			*reinterpret_cast<UnsignedInt *>(container + 0x48));

		if (target)
		{
			position = target->m_position;
		}
		else if (team)
		{
			union
			{
				void *asVoid;
				EstimateTeamPositionCall asMember;
			} positionCast;
			positionCast.asVoid = (void *)j_000241fe;
			(team->*positionCast.asMember)(&position);
		}
		else
		{
			unsigned char *container2 =
				*reinterpret_cast<unsigned char **>(self + 0x1c);
			position = *reinterpret_cast<Coord3D *>(container2 + 0x50);
		}
	}

	container = *reinterpret_cast<unsigned char **>(self + 0x1c);
	GameLogic *logic = *(GameLogic **)0x012F0898;
	Object *nemesis = logic->findObjectByID(
		((Rva0015C7A0GuardMachine *)container)->getNemesisID());
	if (!nemesis)
		return STATE_SUCCESS;

	Object *owner = *reinterpret_cast<Object **>(container + 0x10);
	union
	{
		void *asVoid;
		GetLayerCall asMember;
	} layerCast;
	layerCast.asVoid = (void *)j_0003a391;
	if ((owner->*layerCast.asMember)() != 1)
	{
		OutOfWeaponRangeCall call =
			(OutOfWeaponRangeCall)j_00004c37;
		if (!call(owner, nemesis))
			return STATE_SUCCESS;
	}

	Real range = Rva002BD020AI::getAdjustedVisionRangeForObject(owner, 3);
	unsigned char *container2 = *reinterpret_cast<unsigned char **>(self + 0x1c);
	PolygonTrigger *area = *reinterpret_cast<PolygonTrigger **>(container2 + 0x4c);
	if (area)
	{
		if (*(unsigned char *)(container2 + 0x68))
			position = *reinterpret_cast<Coord3D *>(container2 + 0x5c);
		else
		{
			union
			{
				void *asVoid;
				GetCenterPointCall asMember;
			} centerCast;
			centerCast.asVoid = (void *)j_00007ad6;
			(area->*centerCast.asMember)(&position);
		}
	}

	m_exitConditions.m_center = position;
	m_exitConditions.m_radiusSqr = range * range;
	m_exitConditions.m_field18 =
		(*(GameLogic **)0x012F0898)->getFrame() +
		(*(AIRootR0015C7A0 **)0x012EF214)->getAiData()->m_field3c;
	m_exitConditions.m_conditionsToConsider = 7;

	m_attackState = new CtorTargetR0015C7A0(
		getMachine(), false, true, false, &m_exitConditions);
	m_attackState->m_machine->setGoalObject(nemesis);
	StateReturnType result = m_attackState->onEnter();
	return result == STATE_CONTINUE ? STATE_CONTINUE : STATE_SUCCESS;
}
