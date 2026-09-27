// ?updateInternal@AIAttackMeleeEngageState@@AAE?AW4StateReturnType@@XZ
// partial score=0.3 date=2026-09-27
// ?updateInternal@AIAttackMeleeEngageState@@AAE?AW4StateReturnType@@XZ
// Retail RVA 0x00178470, 1314 bytes. Identity comes from the ComputePath28
// string and the 0x00004629 thunk called by Rva00178AE0State::onEnter.

// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWMath

typedef bool Bool;
typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;

#include "coord.h"

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

enum CrushSquishTestType
{
	TEST_CRUSH_OR_SQUISH = 2
};

class Object;
class Weapon;
class Player;
class Pathfinder;
class CRCParameterCheck;
class Rva178470Receiver {};

template<int N> class UnresolvedVtablePrefix : public UnresolvedVtablePrefix<N-1>
{
public:
	virtual void slot(char (*)[N]) = 0;
};

template<> class UnresolvedVtablePrefix<0> {};

class StateMachine : public UnresolvedVtablePrefix<14>
{
public:
	virtual void call38(Object *) = 0;
	Object *getGoalObject();
	unsigned char m_pad00[0x0c];
	Object *m_owner;
};

class State : public UnresolvedVtablePrefix<4>
{
public:
	StateMachine *getMachine() { return m_machine; }
	Object *getMachineOwner() { return m_machine->m_owner; }

private:
	unsigned char m_pad04[0x18];
	StateMachine *m_machine;
};

class AIInternalMoveToState : public State
{
public:
	virtual StateReturnType onEnter();
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2C() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38() = 0;
	virtual void slot3C() = 0;
	virtual void slot40() = 0;
	virtual Bool computePath() = 0;
	virtual StateReturnType update();

protected:
	unsigned char m_pad20[0x2c];
	Bool m_adjustDestinations;
};

struct BfmeShapeE15
{
	unsigned char m[0x24];
};

class BfmeObjE15
{
public:
	BfmeShapeE15 *bfmeAtE15(Int);
	unsigned char m_pad00[0x2c];
	BfmeShapeE15 *m_start;
	BfmeShapeE15 *m_finish;
};

class AIUpdateInterface
{
public:
	void setCurrentVictim(const Object *);
	void destroyPath();
	void setDesiredSpeed(Real);
};

class Rva0016FFA0
{
public:
	Bool field() const;
};

class Rva001B7E90Receiver
{
public:
	Real query(Object *);
};

class Object
{
public:
	Player *getControllingPlayer() const;
	Bool isStealthedAndUndetected(const Object *) const;
	Bool crushPolicy(Object *, CrushSquishTestType) const;
	Bool rva001C7530();

	unsigned char m_pad00[0x38];
	Coord3D m_cachedPos;
	unsigned char m_pad44[0x94 - 0x44];
	UnsignedInt m_status94;
	unsigned char m_pad98[0xac - 0x98];
	BfmeObjE15 m_e15;
	unsigned char m_padD8[0x140 - 0xe0];
	void *m_field140;
	unsigned char m_pad144[0x1fc - 0x144];
	void *m_field1FC;
	unsigned char m_pad200[4];
	AIUpdateInterface *m_ai;
	void *m_field208;
	unsigned char m_pad20c[0x344 - 0x20c];
	unsigned char m_status344;
};

class Rva178470Substate : public UnresolvedVtablePrefix<4>
{
public:
	virtual void *slot10();
	virtual void slot14(Int);
	virtual void *slot18();
};

class Rva178470Contain : public UnresolvedVtablePrefix<26>
{
public:
	virtual void *slot68();
};

class Rva178470Target : public UnresolvedVtablePrefix<18>
{
public:
	virtual Object *slot48(Int, Coord3D *, Int);
};

class AI
{
public:
	unsigned char m_pad00[0x0c];
	Pathfinder *m_pathfinder;
	Pathfinder *pathfinder() const { return m_pathfinder; }
};

class GameLogic
{
public:
	unsigned char m_pad00[0x3c];
	UnsignedInt m_frame;
	unsigned char m_pad40[0x1a0 - 0x40];
	Int m_field1A0;
};

class AIAttackMeleeEngageState : public AIInternalMoveToState
{
private:
	StateReturnType updateInternal();

	unsigned char m_pad4d[3];
	Rva178470Substate *m_field50;
	Int m_field54;
	Int m_field58;
	Coord3D m_field5C;
	unsigned char m_pad68[8];
	UnsignedInt m_field70;
	Bool m_field74;
	Bool m_field75;
	unsigned char m_pad76[2];
};

extern void j_000016a4();
extern void j_00003b1b();
extern void j_000047c8();
extern void j_000065e1();
extern void j_0000e570();
extern void j_0000faa6();
extern void j_00010910();
extern void j_000125e9();
extern void j_00016199();
extern void j_00019c54();
extern void j_0001b919();
extern void j_0002056d();
extern void j_00020824();
extern void j_00021017();
extern void j_0002253e();
extern void j_000230ab();
extern void j_000294e2();
extern void j_0002e85c();
extern void j_00031a7f();
extern void j_00032dee();
extern void j_00036089();
extern void j_000375e2();
extern void j_0003a391();
extern void j_000420aa();
extern void j_00048ca7();
extern void j_0004ab4c();
extern "C" void __cdecl bfmeRetailCritterDesyncLog(void *, const char *, ...);
extern void j_0003a17a();

extern AI *TheAI;
extern GameLogic *TheBfmeGameLogic;
extern bool Glo012F0239;
extern CRCParameterCheck *TheCRCParameterCheck;
extern const Real g_bfmeDirectionWeight1285;
extern const Real BfmeZeroRange;

typedef Object *(Rva178470Receiver::*GoalCall)();
typedef Player *(Rva178470Receiver::*PlayerCall)();
typedef void (Rva178470Receiver::*VictimCall)(const Object *);
typedef Bool (Rva178470Receiver::*FieldCall)();
typedef Bool (Rva178470Receiver::*BoolNoArgCall)();
typedef Bool (__cdecl *InvalidCall)(Object *, Object *);
typedef Real (Rva178470Receiver::*DistanceCall)(Object *);
typedef BfmeShapeE15 *(Rva178470Receiver::*ShapeCall)(Int);
typedef void *(Rva178470Receiver::*NoArgPointerCall)();
typedef void *(Rva178470Receiver::*OneArgPointerCall)(Object *);
typedef void *(Rva178470Receiver::*PointerIntCall)(Int);
typedef Real (Rva178470Receiver::*HeightCall)();
typedef Real (Rva178470Receiver::*SpeedCall)(Object *);
typedef void (Rva178470Receiver::*SpeedSetterCall)(Real);
typedef void (Rva178470Receiver::*DestroyCall)();
typedef void (Rva178470Receiver::*StatusCall)(Int, Bool);
typedef Object *(Rva178470Receiver::*ResolveCall)(Int);
typedef Bool (Rva178470Receiver::*BoolCall)(Int);
typedef Bool (Rva178470Receiver::*ThreeArgBoolCall)(Object *, Object *, Int);
typedef void (Rva178470Receiver::*SetGoalCall)(Object *);
typedef Bool (Rva178470Receiver::*PathBoolCall)(Object *, Coord3D *);
typedef Bool (Rva178470Receiver::*PathOneBoolCall)(Object *);
typedef Int (Rva178470Receiver::*LayerCall)();
typedef void (Rva178470Receiver::*UpdateGoalCall)(Object *, const Coord3D *, Int, const char *, Int);
typedef void (Rva178470Receiver::*SetCoordCall)(const Coord3D *);
typedef void (__cdecl *CritterDesyncLog)(void *, const char *, ...);

template<class T> T Rva178470Member(void (*raw)())
{
	union { void (*raw)(); T member; } fn;
	fn.raw = raw;
	return fn.member;
}
#define CALL(T, obj, fn) (((Rva178470Receiver *)(obj))->*Rva178470Member<T>(fn))

static Object *getGoal(StateMachine *machine)
{
	return CALL(GoalCall, machine, j_0000e570)();
}

static Player *getPlayer(Object *object)
{
	return CALL(PlayerCall, object, j_00020824)();
}

static Bool invalidTarget(Object *attacker, Object *target)
{
	return ((InvalidCall)j_0002056d)(attacker, target);
}

StateReturnType AIAttackMeleeEngageState::updateInternal()
{
	AIAttackMeleeEngageState *const self = this;
	Object *source = self->getMachine()->m_owner;
	AIUpdateInterface *ai = source->m_ai;
	Object *victim = getGoal(self->getMachine());
	if (victim == 0 || (victim->m_status94 & 0x40000) != 0)
		return STATE_FAILURE;

	if (victim->isStealthedAndUndetected((const Object *)getPlayer(source)))
		return STATE_FAILURE;
	if ((victim->m_status344 & 1) != 0)
		return STATE_FAILURE;

	{
	CALL(VictimCall, ai, j_0004ab4c)(victim);
	if (source->crushPolicy(victim, TEST_CRUSH_OR_SQUISH))
	{
		if (CALL(FieldCall, source, j_000375e2)() &&
			CALL(BoolNoArgCall, source, j_00016199)())
			return STATE_SUCCESS;
	}
	if (self->m_field74)
	{
		if (self->m_field70 >= TheBfmeGameLogic->m_frame)
			return STATE_FAILURE;
		self->m_field74 = false;
	}

compute_path:
	Bool positionFound = false;
	if (!invalidTarget(source, victim))
		goto speed_fallback;
	positionFound = true;
	{
		Real sourceDistance = CALL(DistanceCall, source, j_0002253e)(victim);
		BfmeShapeE15 *sourceShape = source->m_e15.bfmeAtE15(0);
		BfmeShapeE15 *victimShape = victim->m_e15.bfmeAtE15(0);
		Real victimHeight = *(Real *)((char *)victimShape + 8);
		Real sourceHeight = *(Real *)((char *)sourceShape + 8);
		Real heightDelta = sourceHeight - victimHeight;
		heightDelta += CALL(HeightCall, source, j_000047c8)();
		if (heightDelta < BfmeZeroRange)
		{
			sourceDistance = 0.0f;
			Real speed = 999999.0f;
			void *state = CALL(NoArgPointerCall, source, j_00021017)();
			if (state != 0)
			{
				void *state2 = CALL(OneArgPointerCall, source, j_00021017)(source);
				speed = CALL(SpeedCall, state2, j_000230ab)(source);
			}
				Bool ready = sourceDistance < speed;
				CALL(SpeedSetterCall, ai, j_00048ca7)(sourceDistance);
				CALL(StatusCall, source, j_00032dee)(0x4a, ready);
			CALL(StatusCall, source, j_00019c54)(0x4a, ready);
			positionFound = ready;
		}
	}

	if (positionFound && self->m_field54 != 0)
	{
		Rva178470Substate *state = self->m_field50;
		self->m_field54 = (Int)state->slot10();
	}

	Object *resolved = CALL(ResolveCall, victim, j_0000faa6)(0);
	if (self->m_field54 == 0)
	{
		Rva178470Substate *state = self->m_field50;
		self->m_field54 = (Int)state->slot18();
	}
	if (self->m_field54 != 0)
		self->m_field50->slot14(0);

	if ((victim->m_status344 & 1) != 0 && resolved != 0)
	{
		Rva178470Contain *contain = (Rva178470Contain *)resolved->m_field1FC;
		if (contain != 0)
		{
			Rva178470Target *target = (Rva178470Target *)contain->slot68();
			if (target != 0)
				victim = target->slot48(0, &source->m_cachedPos, 0);
		}
	}
	if (victim == 0)
		return STATE_FAILURE;

	CALL(SetGoalCall, ai, j_000125e9)(victim);
	self->getMachine()->call38(victim);

after_goal:
	if (CALL(BoolCall, source, j_000016a4)(0x1c) && !positionFound)
		CALL(DestroyCall, ai, j_000065e1)();

	Weapon *weapon = (Weapon *)CALL(PointerIntCall, source, j_00031a7f)(0);
	if (weapon != 0 && TheBfmeGameLogic->m_field1A0 > 0 &&
		CALL(BoolCall, source, j_000016a4)(0x24) &&
		!CALL(BoolCall, victim, j_000016a4)(0x24))
	{
		if (source->m_field140 == 0)
		{
			if (Glo012F0239 && TheCRCParameterCheck != 0)
				((CritterDesyncLog)j_0003a17a)(TheCRCParameterCheck,
					"masiwar called by AIAttackMeleeEngageState::updateInternal [1]");
			if (CALL(BoolCall, source, j_000016a4)(0x24) &&
				!CALL(BoolCall, victim, j_000016a4)(0x24) &&
				CALL(ThreeArgBoolCall, weapon, j_0002e85c)(source, victim, 0))
			{
				Pathfinder *pathfinder = TheAI->pathfinder();
				if (CALL(PathOneBoolCall, pathfinder, j_00036089)(source))
				{
					Coord3D position;
					position.x = source->m_cachedPos.x;
					position.y = source->m_cachedPos.y;
					position.z = source->m_cachedPos.z;
					Int layer = CALL(LayerCall, source, j_0003a391)();
					CALL(UpdateGoalCall, pathfinder, j_000294e2)(source, &position, layer,
						"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Ai\\AIStates.cpp", 0x1d41);
					if (CALL(PathBoolCall, pathfinder, j_0001b919)(source, &position))
					{
						CALL(SetCoordCall, ai, j_00010910)(&position);
						CALL(StatusCall, source, j_00032dee)(0x1c, true);
						return STATE_SUCCESS;
					}
				}
			}
		}
	}

	speed_fallback:
	CALL(SpeedSetterCall, ai, j_00048ca7)(999999.0f);
	if (self->m_field54 == 0)
	{
		Rva178470Substate *state = self->m_field50;
		state->slot14(0);
		self->m_field54 = -1;
	}

	if (CALL(BoolCall, source, j_000016a4)(0x4a))
	{
		CALL(StatusCall, source, j_00019c54)(0x4a, false);
		CALL(StatusCall, source, j_00032dee)(0x4a, false);
		goto after_goal;
	}

	if (Glo012F0239 && TheCRCParameterCheck != 0)
		((CritterDesyncLog)j_0003a17a)(TheCRCParameterCheck,
			"CritterDesync: ComputePath28");
	if (!computePath())
		return STATE_FAILURE;
	if (self->m_field74)
		return STATE_CONTINUE;

compute_path_tail:
	StateReturnType result = AIInternalMoveToState::update();
	if (positionFound)
	{
		if (result != STATE_CONTINUE)
			goto retry_path;
		return result;
	}
	if (result != STATE_CONTINUE)
		goto retry_path;
	if (source->m_field140 != 0 || self->m_field75)
		return STATE_CONTINUE;

retry_path:
	{
		Pathfinder *pathfinder = TheAI->pathfinder();
		Bool pathReady = CALL(PathOneBoolCall, pathfinder, j_00036089)(source);
		Bool sourceHasField = source->m_field140 != 0;
		if (!sourceHasField || pathReady)
		{
			weapon = (Weapon *)CALL(PointerIntCall, source, j_00031a7f)(0);
			if (weapon != 0 && CALL(ThreeArgBoolCall, weapon, j_0002e85c)(source, victim, 0))
			{
				Coord3D position;
				position.x = source->m_cachedPos.x;
				position.y = source->m_cachedPos.y;
				position.z = source->m_cachedPos.z;
				Int layer = CALL(LayerCall, source, j_0003a391)();
				CALL(UpdateGoalCall, pathfinder, j_000294e2)(source, &position, layer,
					"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Ai\\AIStates.cpp", 0x1d63);
				if (CALL(PathBoolCall, pathfinder, j_0001b919)(source, &position))
				{
					CALL(SetCoordCall, ai, j_00010910)(&position);
					return STATE_SUCCESS;
				}
			}
		}
	}
	self->m_field74 = true;
	self->m_field70 = TheBfmeGameLogic->m_frame +
		(self->m_field75 ? 0x19 : 0x0a);
	return STATE_CONTINUE;
	}
}
