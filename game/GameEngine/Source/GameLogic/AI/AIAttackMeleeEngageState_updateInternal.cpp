// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/GameEngine/Include/Precompiled /Igame/Libraries/Source/WWVegas/WWMath

typedef bool Bool;
typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;

#include "coord.h"

enum StateReturnType { STATE_CONTINUE = 0, STATE_SUCCESS = -1, STATE_FAILURE = -2 };
enum CrushSquishTestType { TEST_CRUSH_ONLY, TEST_SQUISH_ONLY, TEST_CRUSH_OR_SQUISH };
enum WeaponSlotType;

class Object;
class Player;
class CRCParameterCheck;

template<int N> class UnresolvedVtablePrefix : public UnresolvedVtablePrefix<N-1> { public: virtual void slot(char (*)[N])=0; };
template<> class UnresolvedVtablePrefix<0> {};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class StateMachine : public UnresolvedVtablePrefix<14>
{
public:
	virtual void slot38(Object *obj) = 0;
	Object *getOwner() { return m_owner; }
	Object *getGoalObject();

private:
	unsigned char m_pad004[0x0c];
	Object *m_owner;
};

// The fire-weapon substate: vtable slots 4/5/6 are the State
// onEnter/onExit/update trio.
class AIAttackFireWeaponState : public UnresolvedVtablePrefix<4>
{
public:
	virtual StateReturnType onEnter() = 0;
	virtual void onExit(Int status) = 0;
	virtual StateReturnType update() = 0;
};

class Weapon
{
public:
	Bool isWithinAttackRange(const Object *source, const Object *target, Int extra) const;
};

// Retail call 0x00010910 -> 0x0016A6D0 takes the AI receiver and the
// goal-position address; ledger identity is still address-derived.
struct Rva0016A6D0Vec;
class Rva0016A6D0
{
public:
	void set(const Rva0016A6D0Vec *v);
};

class AIUpdateInterface
{
public:
	void setCurrentVictim(const Object *victim);
	void friend_setGoalObject(Object *obj);
	void destroyPath();
	void setDesiredSpeed(Real speed);
	void *getPath() { return m_path; }

private:
	unsigned char m_pad000[0x140];
	void *m_path;
};

// Retail 0x001B7E90, called on the pointer 0x001BE010 returns for the
// source object; ledger identity is still address-derived.
class BfmeSub1CC_EC3
{
public:
	Real effectiveMaxSpeed(void *obj);
};

// Object+0x1FC contain module and the object its slot-26 query returns.
class Rva178470Rider : public UnresolvedVtablePrefix<18>
{
public:
	virtual Object *slot48(Int, const Coord3D *, Int) = 0;
};

class Rva178470Contain : public UnresolvedVtablePrefix<26>
{
public:
	virtual Rva178470Rider *slot68() = 0;
};

struct BfmeShapeE15
{
	unsigned char m_pad00[8];
	Real m_08;
};

class BfmeObjE15
{
public:
	BfmeShapeE15 *bfmeAtE15(Int index);
};

class Rva0016FFA0 { public: Bool field() const; };
class Rva001BE010 { public: Int get(); };
class BfmeSpotCN;
class Gen_0016E370 { public: Real bfmeDistanceSquared(const BfmeSpotCN *other) const; };

class Object
{
public:
	Player *getControllingPlayer() const;
	Bool isStealthedAndUndetected(const Player *player) const;
	Bool crushPolicy(Object *other, CrushSquishTestType test) const;
	Bool rva001c7530();
	Real bfmeGetNonnegativePreferredLocomotorHeight() const;
	Object *bfmeResolveMeleeTarget(Int index);
	Weapon *getCurrentWeapon(WeaponSlotType *slot);
	Int getLayer() const;
	void setStatusBit(Int bit, Bool value);
	// 0x000F20F0 builds a one-bit status mask and forwards its second
	// argument to Object::rva001CD540(const BitFlags<86> &, Bool), the same
	// shape as setStatusBit; retail pushes the one memory bool to both.
	void unidentified_000F20F0(Int bit, Bool value);
	Bool testStatus(Int bit) const;
	AIUpdateInterface *getAI() { return m_ai; }
	Rva178470Contain *getContain() const { return m_contain; }
	const Coord3D *getPosition() const { return &m_cachedPos; }

	unsigned char m_pad000[0x38];
	Coord3D m_cachedPos;
	unsigned char m_pad044[0x94 - 0x44];
	UnsignedInt m_status94;
	unsigned char m_pad098[0xac - 0x98];
	BfmeObjE15 m_e15;
	unsigned char m_pad0ad[0x1fc - 0xad];
	Rva178470Contain *m_contain;
	unsigned char m_pad200[4];
	AIUpdateInterface *m_ai;
	unsigned char m_pad208[0x344 - 0x208];
	unsigned char m_privateStatus;
};

class Pathfinder
{
public:
	Bool rva003E5E40(Object *obj);
	void updateGoal(Object *obj, const Coord3D *pos, Int layer, const char *file, Int line);
	Bool goalPosition(Object *obj, Coord3D *pos);
};

class AI
{
public:
	Pathfinder *pathfinder() { return m_pathfinder; }

private:
	unsigned char m_pad000[0xc];
	Pathfinder *m_pathfinder;
};

class GameLogic
{
public:
	UnsignedInt getFrame() { return m_frame; }

	unsigned char m_pad000[0x3c];
	UnsignedInt m_frame;
	unsigned char m_pad040[0x1a0 - 0x40];
	Int m_field1A0;
};

extern AI *TheAI;
extern GameLogic *TheGameLogic;
extern bool Glo012F0239;
extern CRCParameterCheck *TheCRCParameterCheck;
extern const Real g_rva01075350;
extern "C" void __cdecl bfmeRetailCritterDesyncLog(void *check, const char *format, ...);
Bool bfmeMeleeHordeTargetInvalid(Object *source, Object *victim);

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class State : public UnresolvedVtablePrefix<4>
{
public:
	StateMachine *getMachine() { return m_machine; }
	Object *getMachineOwner() { return m_machine->getOwner(); }
	Object *getMachineGoalObject() { return m_machine->getGoalObject(); }

private:
	unsigned char m_unmodelled004[0x18];
	StateMachine *m_machine;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIStateMachine.h
class AIInternalMoveToState : public State
{
public:
	virtual StateReturnType onEnter();
	virtual void slot14()=0;
	virtual StateReturnType update();
	virtual void slot1C()=0;
	virtual void slot20()=0;
	virtual void slot24()=0;
	virtual void slot28()=0;
	virtual void slot2C()=0;
	virtual void slot30()=0;
	virtual void slot34()=0;
	virtual void slot38()=0;
	virtual void slot3C()=0;
	virtual void slot40()=0;
	virtual Bool computePath()=0;

protected:
	unsigned char m_unmodelled020[0x4c - 0x20];
	Bool m_adjustDestinations;
	Bool m_field4D;
};

class AIAttackMeleeEngageState : public AIInternalMoveToState
{
private:
	StateReturnType updateInternal();

	AIAttackFireWeaponState *m_field50;
	Int m_field54;
	UnsignedInt m_field58;
	Coord3D m_field5C;
	unsigned char m_field68[8];
	UnsignedInt m_field70;
	Bool m_field74;
	Bool m_field75;
};

// Retail 0x00178470, 1314 bytes.  The body's own CRC literal names it
// ("masiwar called by AIAttackMeleeEngageState::updateInternal [1]", VA
// 0x01099978), and Rva00178AE0State::onEnter calls it through ILT
// 0x00004629.  Layout and callee declarations follow the landed
// AIAttackMeleeEngageState_onEnter.cpp.  The 10.0f is a literal: retail's
// operand at VA 0x01075C74 is the shared float constant, and only the literal
// keeps VC7.1 from reassociating the sum of the two radii.
// ?updateInternal@AIAttackMeleeEngageState@@AAE?AW4StateReturnType@@XZ
StateReturnType AIAttackMeleeEngageState::updateInternal()
{
	Object *source = getMachineOwner();
	AIUpdateInterface *ai = source->getAI();
	Object *victim = getMachineGoalObject();
	if (!victim || (victim->m_status94 & 0x40000))
		return STATE_FAILURE;
	if (victim->isStealthedAndUndetected(source->getControllingPlayer()))
		return STATE_FAILURE;
	if (victim->m_privateStatus & 1)
		return STATE_FAILURE;

	ai->setCurrentVictim(victim);
	if (source->crushPolicy(victim, TEST_CRUSH_OR_SQUISH)
		&& ((const Rva0016FFA0 *)source)->field() && source->rva001c7530())
		return STATE_SUCCESS;

	if (m_field74)
	{
		if (m_field70 >= TheGameLogic->getFrame())
			return STATE_CONTINUE;
		m_field74 = false;
		return STATE_FAILURE;
	}

	Bool inRange = false;
	if (bfmeMeleeHordeTargetInvalid(source, victim))
	{
		inRange = true;
		Real distSqr = ((const Gen_0016E370 *)source)->bfmeDistanceSquared((const BfmeSpotCN *)victim);
		Real sourceRadius = source->m_e15.bfmeAtE15(0)->m_08;
		BfmeShapeE15 *victimShape = victim->m_e15.bfmeAtE15(0);
		Real surfaceGap = sqrtf(distSqr) - (victimShape->m_08 + (sourceRadius + 10.0f));
		Real gap = surfaceGap + victim->bfmeGetNonnegativePreferredLocomotorHeight();
		if (gap < g_rva01075350)
			gap = 0.0f;

		Real maxSpeed = 999999.0f;
		if (((Rva001BE010 *)source)->get())
			maxSpeed = ((BfmeSub1CC_EC3 *)((Rva001BE010 *)source)->get())->effectiveMaxSpeed(source);
		ai->setDesiredSpeed(gap);
		Bool closing = gap < maxSpeed;
		source->setStatusBit(0x4a, closing);
		source->unidentified_000F20F0(0x4a, closing);

		if (closing && m_field54)
			m_field54 = m_field50->onEnter();

		Object *resolved = victim->bfmeResolveMeleeTarget(0);
		if (!m_field54)
		{
			m_field54 = m_field50->update();
			if (m_field54)
				m_field50->onExit(0);

			if ((victim->m_privateStatus & 1) && resolved)
			{
				Rva178470Contain *contain = resolved->getContain();
				if (contain)
				{
					Rva178470Rider *rider = contain->slot68();
					if (rider)
					{
						victim = rider->slot48(0, source->getPosition(), 0);
						if (!victim)
							return STATE_CONTINUE;
						ai->friend_setGoalObject(victim);
						getMachine()->slot38(victim);
					}
				}
			}
		}
	}
	else
	{
		ai->setDesiredSpeed(999999.0f);
		if (!m_field54)
		{
			m_field50->onExit(0);
			m_field54 = -1;
		}
		if (source->testStatus(0x4a))
		{
			source->unidentified_000F20F0(0x4a, false);
			source->setStatusBit(0x4a, false);
		}
	}

	if (source->testStatus(0x1c) && !inRange)
		ai->destroyPath();

	Weapon *weapon = source->getCurrentWeapon(0);
	if ((TheGameLogic->m_field1A0 > 0 && source->testStatus(0x24) && victim->testStatus(0x24))
		|| (!ai->getPath() && weapon))
	{
		if (TheCRCParameterCheck)
			bfmeRetailCritterDesyncLog(TheCRCParameterCheck,
				"masiwar called by AIAttackMeleeEngageState::updateInternal [1]");
	}
	if ((source->testStatus(0x24) && victim->testStatus(0x24))
		|| (!ai->getPath() && weapon && weapon->isWithinAttackRange(source, victim, 0)
			&& TheAI->pathfinder()->rva003E5E40(source)))
	{
		Coord3D pos;
		pos.set(source->getPosition());
		TheAI->pathfinder()->updateGoal(source, &pos, source->getLayer(),
			"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Ai\\AIStates.cpp", 0x1d41);
		if (TheAI->pathfinder()->goalPosition(source, &pos))
			((Rva0016A6D0 *)ai)->set((const Rva0016A6D0Vec *)&pos);
		source->setStatusBit(0x1c, true);
		return STATE_SUCCESS;
	}

	if (Glo012F0239 && TheCRCParameterCheck)
		bfmeRetailCritterDesyncLog(TheCRCParameterCheck, "CritterDesync: ComputePath28");
	if (!computePath())
		return STATE_FAILURE;
	if (m_field74)
		return STATE_CONTINUE;

	StateReturnType code = AIInternalMoveToState::update();
	if (inRange)
	{
		if (code == STATE_CONTINUE)
			return code;
	}
	else if (code == STATE_CONTINUE)
	{
		if (ai->getPath() || m_field4D)
			return STATE_CONTINUE;
	}

	Bool canRepath = TheAI->pathfinder()->rva003E5E40(source);
	if (!ai->getPath())
		canRepath = true;
	if (weapon && weapon->isWithinAttackRange(source, victim, 0) && canRepath)
	{
		Coord3D pos;
		pos.set(source->getPosition());
		TheAI->pathfinder()->updateGoal(source, &pos, source->getLayer(),
			"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Ai\\AIStates.cpp", 0x1d63);
		if (TheAI->pathfinder()->goalPosition(source, &pos))
			((Rva0016A6D0 *)ai)->set((const Rva0016A6D0Vec *)&pos);
		return STATE_SUCCESS;
	}

	m_field74 = true;
	if (m_field75)
		m_field70 = TheGameLogic->getFrame() + 25;
	else
		m_field70 = TheGameLogic->getFrame() + 10;
	return STATE_CONTINUE;
}
