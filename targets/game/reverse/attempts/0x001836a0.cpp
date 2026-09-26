// ?update@AIAttackMeleeHordeApproachTargetState@@UAE?AW4StateReturnType@@XZ
// partial score=0.2 date=2026-09-22
// Retail 0x001836A0: AIAttackMeleeHordeApproachTargetState::update.
// Identity is the slot-six body of vtable 0x0109A540.

// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /FAsc /Fabuild/approach_update.cod

#include <math.h>

typedef bool Bool;
typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;

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

class Object;
class Player;

template <Int N>
class BFMEVirtualSlots : public BFMEVirtualSlots<N - 1>
{
public:
	virtual void slot(char (*)[N]) = 0;
};

template <>
class BFMEVirtualSlots<0>
{
};

template <Int N>
class HordeVirtualSlots : public HordeVirtualSlots<N - 1>
{
public:
	virtual void slot(char (*)[N]) = 0;
};

template <>
class HordeVirtualSlots<0>
{
};

class BfmeShapeE15
{
public:
	unsigned char m_pad000[8];
	Real m_height;
	unsigned char m_pad00c[0x24 - 0x0c];
};

class BfmeObjE15
{
public:
	BfmeShapeE15 *bfmeAtE15(Int index);
	unsigned char m_pad000[0x2c];
	BfmeShapeE15 *m_start;
	BfmeShapeE15 *m_finish;
};

class StateMachine
{
public:
	Bool isGoalObjectDestroyed() const;
	Object *getGoalObject();

	unsigned char m_pad000[0x10];
	Object *m_owner;
};

class AIUpdateInterface : public BFMEVirtualSlots<122>
{
public:
	virtual void setLocomotorGoalNone() = 0;
	virtual void slot123() = 0;
	virtual void slot124() = 0;
	virtual void slot125() = 0;
	virtual void slot126() = 0;
	virtual void slot127() = 0;
	virtual void slot128() = 0;
	virtual void notifyVictimIsDead() = 0;

	void setCurrentVictim(const Object *victim);
	void setDesiredSpeed(Real speed);
};

class ContainModuleInterface : public BFMEVirtualSlots<26>
{
public:
	virtual class HordeContainInterface *getHordeContainInterface() = 0;
};

class HordeContainInterface : public HordeVirtualSlots<72>
{
public:
	virtual Bool isMeleeTargetReady(Object *target) = 0;
	virtual void slot74(Object *target) = 0;
	virtual Bool slot75() = 0;
	virtual void slot76() = 0;
	virtual void slot77() = 0;
	virtual void setMeleeFormation(UnsignedInt formation) = 0;
};

class LocomotorSpeedQuery
{
public:
	Real query(void *object);
};

class Rva001BE010
{
public:
	Int get();
};

class BFMEObjectStealthQuery
{
public:
	Bool isStealthedAndUndetected(const Object *viewer) const;
};

class Object
{
public:
	Player *getControllingPlayer() const;
	Object *bfmeResolveMeleeTarget(Int index);
	Real bfmeGetNonnegativePreferredLocomotorHeight() const;
	void unidentified_000F20F0(Int index, Int value);

	unsigned char m_pad000[0x38];
	Coord3D m_position;
	unsigned char m_pad044[0x30];
	UnsignedInt m_meleeFormation;
	unsigned char m_pad078[0x1c];
	UnsignedInt m_flags94;
	UnsignedInt m_status98;
	unsigned char m_pad09c[0x10];
	BfmeObjE15 m_shapeE15;
	unsigned char m_pad0e0[0x1fc - 0xe0];
	ContainModuleInterface *m_contain;
	unsigned char m_pad200[4];
	AIUpdateInterface *m_ai;
};

class AIInternalMoveToState : public BFMEVirtualSlots<17>
{
public:
	virtual Bool computePath() = 0;
	virtual StateReturnType update();

	unsigned char m_pad004[0x18];
	StateMachine *m_machine;
};

class AIAttackMeleeHordeApproachTargetState : public AIInternalMoveToState
{
public:
	virtual StateReturnType update();

	unsigned char m_pad020[0x41 - 0x20];
	Bool m_isInitialApproach;
};

extern const Real BfmeZeroRange;

Bool bfmeMeleeHordeTargetInvalid(Object *source, Object *target);

StateReturnType AIAttackMeleeHordeApproachTargetState::update()
{
	AIUpdateInterface *ai;
	Object *source;
	source = m_machine->m_owner;
	ai = source->m_ai;

	if (m_machine->isGoalObjectDestroyed())
	{
		ai->notifyVictimIsDead();
		ai->setCurrentVictim(0);
		return STATE_FAILURE;
	}

	for (;;)
	{
		Object *target = m_machine->getGoalObject();
		if (target == 0)
			return STATE_FAILURE;

		Bool specialTarget = false;
		if (bfmeMeleeHordeTargetInvalid(source, target))
		{
			Real dx = source->m_position.x - target->m_position.x;
			Real dy = source->m_position.y - target->m_position.y;
			specialTarget = true;
			BfmeShapeE15 *sourceShape = source->m_shapeE15.bfmeAtE15(0);
			BfmeShapeE15 *targetShape = target->m_shapeE15.bfmeAtE15(0);
			Real sourceHeight = sourceShape->m_height;
			Real range = sqrt(dx * dx + dy * dy);
			range -= sourceHeight;
			range -= targetShape->m_height;
			range += target->bfmeGetNonnegativePreferredLocomotorHeight();
			if (range < BfmeZeroRange)
				range = BfmeZeroRange;

			Real speed = 1000000.0f;
			Rva001BE010 *getter = reinterpret_cast<Rva001BE010 *>(source);
			if (getter->get())
			{
				LocomotorSpeedQuery *locomotor =
					reinterpret_cast<LocomotorSpeedQuery *>(getter->get());
				speed = locomotor->query(source);
			}
			ai->setDesiredSpeed(range);
			Bool closeEnough = true;
			if (!(range < speed))
				closeEnough = false;
			source->unidentified_000F20F0(0x4a, closeEnough);
		}
		else if ((source->m_status98 & 0x40000) == 0)
			source->unidentified_000F20F0(0x4a, 0);

		ContainModuleInterface *contain = source->m_contain;
		if (contain != 0)
		{
			HordeContainInterface *horde = contain->getHordeContainInterface();
			if (horde != 0)
			{
				UnsignedInt formation = target->m_meleeFormation;
				if ((target->m_flags94 & 0x20) != 0)
				{
					Object *resolved = target->bfmeResolveMeleeTarget(0);
					if (resolved != 0)
						formation = resolved->m_meleeFormation;
				}
				horde->setMeleeFormation(formation);
				if (specialTarget)
				{
					horde->slot74(target);
				}
				else if (horde->isMeleeTargetReady(target))
				{
					if (m_isInitialApproach && !horde->slot75())
						goto afterHorde;
					ai->setLocomotorGoalNone();
					return STATE_SUCCESS;
				}
			}
		}

	afterHorde:
		if ((target->m_flags94 & 0x40000) != 0)
			continue;
		if (((BFMEObjectStealthQuery *)target)->isStealthedAndUndetected(
				 (const Object *)source->getControllingPlayer()))
			continue;

		ai->setCurrentVictim(target);
		if (!computePath())
			return STATE_SUCCESS;
		StateReturnType code = AIInternalMoveToState::update();
		return code == STATE_CONTINUE ? STATE_CONTINUE : STATE_SUCCESS;
	}
}
