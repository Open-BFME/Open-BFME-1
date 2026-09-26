// ?update@AIMoveToState@@UAE?AW4StateReturnType@@XZ
// partial score=0.48 date=2026-09-10
// cl: /DNDEBUG /MD /EHsc
// readable body of ?update@AIMoveToState@@UAE?AW4StateReturnType@@XZ: Code/GameEngine/Source/GameLogic/AI/AIStates.cpp
// BFME layout view: the vendored ZH headers put the state and Object fields at
// different offsets.  These are declarations/layouts only; every called body
// is the retail symbol already recorded in the narrow ledger.

typedef bool Bool;
typedef float Real;
typedef int Int;
typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;

extern "C" double __cdecl sqrt(double);

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

enum StateExitType
{
	STATE_EXIT_UNKNOWN = 0
};

enum CommandSourceType
{
	CMD_FROM_AI = 2
};

enum MoodMatrixAction
{
	MM_Action_Move = 1
};

enum KindOfType
{
	KINDOF_IMMOBILE = 2
};

enum
{
	MAA_Action_To_AttackMove = 4,
	NO_MAX_SHOTS_LIMIT = 0x7fffffff,
	BFME_KINDOF_PROJECTILE = 25
};

struct Coord3D
{
	Real x;
	Real y;
	Real z;

	Real length(void) const
	{
		return (Real)sqrt(x * x + y * y + z * z);
	}
};

class Object;

class AICommandInterface
{
public:
	void aiAttackMoveToPosition(const Coord3D *, Int, CommandSourceType);
};

class AIUpdateInterfacePrefix
{
private:
	UnsignedByte m_unreconstructed_000[0x20];
};

class AIUpdateInterface : public AIUpdateInterfacePrefix, public AICommandInterface
{
public:
	UnsignedInt getMoodMatrixActionAdjustment(MoodMatrixAction) const;
};

class BfmeOverridable
{
public:
	BfmeOverridable *friend_getFinalOverride();

	UnsignedByte m_unreconstructed_000[4];
	BfmeOverridable *m_nextOverride;
};

class Thing
{
protected:
	void *m_vtable;
	BfmeOverridable *m_template;
	UnsignedByte m_unreconstructed_008[0x38 - 0x08];
	Coord3D m_position;

public:
	Bool isKindOf(KindOfType) const;
	void getUnitDirectionVector3D(Coord3D &) const;

	const Coord3D *getPosition(void) const
	{
		return &m_position;
	}
};

class GeometryInfo
{
public:
	Real getMaxHeightAbovePosition() const;
};

class Rva000047C8ObjectHeight
{
public:
	Real getHeight() const;
};

class Rva00001DB6Thing
{
public:
	void getUnitDirectionVector3D(Coord3D &) const;
};

class Object : public Thing
{
private:
	UnsignedByte m_unreconstructed_044[0x204 - 0x44];
	AIUpdateInterface *m_ai;

public:
	using Thing::isKindOf;

	AIUpdateInterface *getAI(void) const
	{
		return m_ai;
	}

	const GeometryInfo &getGeometryInfo(void) const
	{
		return *(const GeometryInfo *)((const UnsignedByte *)this + 0xac);
	}

	Bool isKindOf(Int kind) const
	{
		BfmeOverridable *tmpl = m_template;
		if (tmpl && tmpl->m_nextOverride)
			tmpl = tmpl->m_nextOverride->friend_getFinalOverride();
		return (Bool)((((const UnsignedInt *)((const UnsignedByte *)tmpl + 0xc8))[kind >> 5]) >> (kind & 0x1f) & 1);
	}
};

class StateMachine
{
public:
	Object *getGoalObject();

	const Coord3D *getGoalPosition(void) const
	{
		return &m_goalPosition;
	}

	private:
	UnsignedByte m_unreconstructed_000[0x10];

public:
	Object *m_owner;
	UnsignedByte m_unreconstructed_014[0x0c];
	Int m_goalObjectId;
	Coord3D m_goalPosition;
};

class AIInternalMoveToState
{
public:
	virtual StateReturnType onEnter();
	virtual void onExit(StateExitType);
	virtual StateReturnType update();

protected:
	Object *getMachineOwner(void) const
	{
		return m_machine->m_owner;
	}

	const Coord3D *getMachineGoalPosition(void) const
	{
		return m_machine->getGoalPosition();
	}

	Object *getMachineGoalObject(void) const
	{
		return m_machine->getGoalObject();
	}

	UnsignedByte m_unreconstructed_004[0x18];
	StateMachine *m_machine;
	UnsignedByte m_unreconstructed_020[4];
	Coord3D m_goalPosition;
	UnsignedByte m_unreconstructed_030[0x20];
};

class AIMoveToState : public AIInternalMoveToState
{
public:
	StateReturnType update();

private:
	Bool m_isMoveTo;
};

// ?update@AIMoveToState@@UAE?AW4StateReturnType@@XZ
StateReturnType AIMoveToState::update()
{
	AIUpdateInterface *ai = getMachineOwner()->getAI();

	UnsignedInt adjustment = ai->getMoodMatrixActionAdjustment(MM_Action_Move);
	if (m_isMoveTo && (adjustment & MAA_Action_To_AttackMove))
		ai->aiAttackMoveToPosition(&m_goalPosition, NO_MAX_SHOTS_LIMIT, CMD_FROM_AI);

	// If there is a goal object, move to its current position.  BFME's retail
	// body uses its Object height helper for the lead-speed terms; the existing
	// Zero Hour body names those calls as PhysicsBehavior velocity queries.
	Object *goalObj = getMachineGoalObject();
	Object *obj = getMachineOwner();
	if (goalObj)
	{
		m_goalPosition = *goalObj->getPosition();
		Bool isMissile = obj->isKindOf(BFME_KINDOF_PROJECTILE);
		if (isMissile) {
			Real halfHeight = getMachineGoalObject()->getGeometryInfo().getMaxHeightAbovePosition() / 2.0f;
			m_goalPosition.z += halfHeight;
			Real zDelta = m_goalPosition.z - obj->getPosition()->z;
			if (zDelta > 0) {
				m_goalPosition.z += zDelta;
			}
		}
		if (isMissile && !goalObj->isKindOf(KINDOF_IMMOBILE)) {
			Coord3D ourPos = *obj->getPosition();
			Coord3D delta;
			delta.x = m_goalPosition.x - ourPos.x;
			delta.y = m_goalPosition.y - ourPos.y;
			delta.z = m_goalPosition.z - ourPos.z;
			Real mySpeed = ((const Rva000047C8ObjectHeight *)obj)->getHeight();
			Real goalSpeed = ((const Rva000047C8ObjectHeight *)goalObj)->getHeight();
			if (mySpeed < 5.0f) mySpeed = 5.0f;
			Real leadDistance = (0.5 * delta.length()) * goalSpeed / mySpeed;
			Coord3D dir;
			((const Rva00001DB6Thing *)goalObj)->getUnitDirectionVector3D(dir);
			m_goalPosition.x += dir.x * leadDistance;
			m_goalPosition.y += dir.y * leadDistance;
			m_goalPosition.z += dir.z * leadDistance;
		}
	} else {
		Bool isMissile = obj->isKindOf(BFME_KINDOF_PROJECTILE);
		if (isMissile) {
			m_goalPosition = *getMachineGoalPosition();
			Real zDelta = m_goalPosition.z - obj->getPosition()->z;
			if (zDelta > 0) {
				m_goalPosition.z += zDelta;
			}
		}
	}

	return AIInternalMoveToState::update();
}
