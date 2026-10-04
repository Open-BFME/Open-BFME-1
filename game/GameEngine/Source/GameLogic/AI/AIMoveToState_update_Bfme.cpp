// cl: /DNDEBUG /MD /EHsc
// BFME layout for the retail ?update@AIMoveToState@@UAE?AW4StateReturnType@@XZ
// body at 0x00188290, 522 bytes, last ret at 0x00188499.
//
// IDENTITY.  AIMoveToState's dedicated vftable 0x01098F08 (installed by the
// matched exact constructor ??0AIMoveToState@@QAE@PAVStateMachine@@@Z at
// 0x00173430) routes slot +0x18 through the ILT thunk 0x00008238, which is a
// plain `jmp 0x00188290`; slot 6 is `update` in this vtable, the sibling
// AIMoveToStateSA table 0x01098FA8 has its matched clean C++ update at the
// same slot.  Two matched callers name the symbol outright:
// ??update@AIAttackMoveToState@@UAE?AW4StateReturnType@@XZ (0x001885B0) and
// ??update@AIMoveToPositionAndEnterState@@UAE?AW4StateReturnType@@XZ
// (0x00189760).
//
// READABLE BODY.  The Zero Hour AIMoveToState::update in
// game/GameEngine/Source/GameLogic/AI/AIStates.cpp, which this tree already
// carries.  BFME made two edits to it, both visible in the retail bytes:
//   * the Zero Hour `gotPhysics` conjunct is gone, so the lead-speed block is
//     guarded only by isKindOf(KINDOF_IMMOBILE) on the goal object;
//   * the two getPhysics()->getVelocityMagnitude() reads became
//     Object::bfmeGetNonnegativePreferredLocomotorHeight() on the object
//     itself (retail ILT 0x000047C8, twice, and the 5.0f floor stays).
//
// LAYOUT.  Every offset below is one the retail body itself reads:
// machine +0x1C, StateMachine::m_owner +0x10, StateMachine::m_goalPosition
// +0x24, this->m_goalPosition +0x24, m_isMoveTo +0x50, Thing::m_template
// +0x04, ThingTemplate kind-of bits +0xC8, Object::m_position +0x38,
// Object geometry +0xAC, Object::m_ai +0x204.  The two shapes that are load
// bearing for the byte match and are easy to lose:
//   * `machine` is a LOCAL copy of m_machine taken after getGoalObject().  The
//     member is re-read from memory after every call; a local keeps it in ebp
//     for the whole body, which is what produces the goal/owner materialisation
//     at +0x0044 and the `add ebp,0x24` goal-position copy in the else arm.
//   * `ourPos` is filled field by field rather than copied as a whole Coord3D.
//     Only the field-wise form lets MSVC scalarise the aggregate, which is what
//     puts owner.x/owner.y on the x87 stack (the `fsub st(2)` / `fsub st(1)`
//     pair) and spills only owner.z.

typedef bool Bool;
typedef float Real;
typedef int Int;
typedef unsigned char UnsignedByte;
typedef unsigned int UnsignedInt;

extern "C" double __cdecl sqrt(double);

// upstream layout: game/Libraries/Source/WWVegas/WWLib/basetype.h
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

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
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
	KINDOF_IMMOBILE = 2,
	KINDOF_PROJECTILE = 25
};

enum
{
	MAA_Action_To_AttackMove = 4,
	NO_MAX_SHOTS_LIMIT = 0x7fffffff
};

class Object;
class StateMachine;

// upstream layout: .../GameLogic/AICommandInterface.h
class AICommandInterface
{
public:
	void aiAttackMoveToPosition(const Coord3D *pos, Int maxShots, CommandSourceType source);
};

// The command interface is a second base at AIUpdateInterface+0x20, which is
// why retail reaches the attack-move call through `lea ecx, [edi+0x20]`.
class AIUpdateInterfacePrefix
{
	UnsignedByte m_unreconstructed_000[0x20];
};

// upstream layout: .../GameLogic/Module/AIUpdate.h
class AIUpdateInterface : public AIUpdateInterfacePrefix, public AICommandInterface
{
public:
	UnsignedInt getMoodMatrixActionAdjustment(MoodMatrixAction action) const;
};

// Retail reaches getFinalOverride through the incremental-link thunk
// ?j_000022bb@@YAXXZ, which the call below names directly.
extern void j_000022bb();

// upstream layout: .../Common/Overridable.h
class Overridable
{
public:
	virtual ~Overridable();

	Overridable *m_nextOverride;
};

// upstream layout: .../Common/ThingTemplate.h
class ThingTemplate : public Overridable
{
public:
	Bool isKindOf(KindOfType kind) const
	{
		return (m_kindof[(UnsignedInt)kind >> 5] & (1 << ((UnsignedInt)kind & 31))) != 0;
	}

private:
	UnsignedByte m_unreconstructed_008[0xc8 - 0x08];
	UnsignedInt m_kindof[3];
};

// upstream layout: .../Common/Thing.h
class Thing
{
public:
	const ThingTemplate *getTemplate() const
	{
		const ThingTemplate *tmpl = m_template;
		if (tmpl == 0)
			return 0;
		if (tmpl->m_nextOverride)
		{
			typedef const Overridable *(Overridable::*Fn)() const;
			union { void (*fn)(); Fn call; } u = { j_000022bb };
			tmpl = (const ThingTemplate *)(tmpl->m_nextOverride->*u.call)();
		}
		return tmpl;
	}

	// Out of line in retail: the goal object's KINDOF_IMMOBILE test is the
	// call through ILT 0x0003251F, while the owner's own test is the inlined
	// getTemplate()->isKindOf() above.
	Bool isKindOf(KindOfType kind) const;

	void getUnitDirectionVector3D(Coord3D &directionVector) const;

protected:
	virtual ~Thing();

	const ThingTemplate *m_template;
};

class GeometryInfo
{
public:
	Real getMaxHeightAbovePosition() const;
};

// upstream layout: .../GameLogic/Object.h
class Object : public Thing
{
public:
	// Retail reads the Zero Hour physics velocity magnitude through this
	// Object method (ILT 0x000047C8) when it leads the goal.
	Real bfmeGetNonnegativePreferredLocomotorHeight() const;

	AIUpdateInterface *getAI() const
	{
		return m_ai;
	}

	const Coord3D *getPosition(void) const
	{
		return &m_position;
	}

	const GeometryInfo &getGeometryInfo(void) const
	{
		return *(const GeometryInfo *)((const UnsignedByte *)this + 0xac);
	}

	UnsignedByte m_unreconstructed_008[0x38 - 0x08];
	Coord3D m_position;
	UnsignedByte m_unreconstructed_044[0x204 - 0x44];
	AIUpdateInterface *m_ai;
};

// upstream layout: .../GameLogic/StateMachine.h
class StateMachine
{
public:
	Object *getGoalObject();

	UnsignedByte m_unreconstructed_000[0x10];
	Object *m_owner;
	UnsignedByte m_unreconstructed_014[0x24 - 0x14];
	Coord3D m_goalPosition;
};

// upstream layout: .../GameLogic/AIStateMachine.h
class AIInternalMoveToState
{
public:
	virtual StateReturnType update();

	UnsignedByte m_unreconstructed_004[0x1c - 0x04];
	StateMachine *m_machine;
	UnsignedByte m_unreconstructed_020[0x24 - 0x20];
	Coord3D m_goalPosition;
};

class __declspec(novtable) AIMoveToState : public AIInternalMoveToState
{
public:
	virtual StateReturnType update();

private:
	UnsignedByte m_unreconstructed_030[0x50 - 0x30];
	Bool m_isMoveTo;
};

// ?update@AIMoveToState@@UAE?AW4StateReturnType@@XZ
StateReturnType AIMoveToState::update()
{
	AIUpdateInterface *ai = m_machine->m_owner->getAI();

	UnsignedInt adjustment = ai->getMoodMatrixActionAdjustment(MM_Action_Move);
	if (m_isMoveTo && (adjustment & MAA_Action_To_AttackMove))
		ai->aiAttackMoveToPosition(&m_goalPosition, NO_MAX_SHOTS_LIMIT, CMD_FROM_AI);

	// if we have a goal object, move to it, as it may have moved
	Object *goalObj = m_machine->getGoalObject();
	StateMachine *machine = m_machine;
	Object *obj = machine->m_owner;
	if (goalObj)
	{
		m_goalPosition = *goalObj->getPosition();
		Bool isMissile = obj->getTemplate()->isKindOf(KINDOF_PROJECTILE);
		if (isMissile) {
			Real halfHeight = m_machine->getGoalObject()->getGeometryInfo().getMaxHeightAbovePosition()/2.0f;
			m_goalPosition.z += halfHeight;
			Real zDelta = m_goalPosition.z - obj->getPosition()->z;
			if (zDelta>0) {
				m_goalPosition.z += zDelta;
			}
		}
		if (isMissile && !goalObj->isKindOf(KINDOF_IMMOBILE)) {
			Coord3D ourPos;
			ourPos.x = obj->getPosition()->x;
			ourPos.y = obj->getPosition()->y;
			ourPos.z = obj->getPosition()->z;
			Coord3D delta;
			delta.x = m_goalPosition.x - ourPos.x;
			delta.y = m_goalPosition.y - ourPos.y;
			delta.z = m_goalPosition.z - ourPos.z;
			Real mySpeed = obj->bfmeGetNonnegativePreferredLocomotorHeight();
			Real goalSpeed = goalObj->bfmeGetNonnegativePreferredLocomotorHeight();
			if (mySpeed<5.0f) mySpeed = 5.0f; // avoid divide by 0.
			Real leadDistance = (0.5*delta.length()) * goalSpeed / mySpeed;
			Coord3D dir;
			goalObj->getUnitDirectionVector3D(dir);
			m_goalPosition.x += dir.x*leadDistance;
			m_goalPosition.y += dir.y*leadDistance;
			m_goalPosition.z += dir.z*leadDistance;
		}
	} else {
		Bool isMissile = obj->getTemplate()->isKindOf(KINDOF_PROJECTILE);
		if (isMissile) {
			// When missiles are moving uphill, they need to start up quickly to clear hills.  jba.
			m_goalPosition = machine->m_goalPosition;
			Real zDelta = m_goalPosition.z - obj->getPosition()->z;
			if (zDelta>0) {
				m_goalPosition.z += zDelta;
			}
		}
	}

	return AIInternalMoveToState::update();
}
