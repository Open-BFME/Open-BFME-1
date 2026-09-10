// ?moveTowardsPositionOther@Locomotor@@IAEXPAVObject@@PBUCoord3D@@MM@Z
// partial score=0.52 date=2026-09-10
// Complete BFME-shaped reconstruction for retail 0x001B8D30.
//
// The retail thunk at 0x0001C7EC is currently labelled
// BfmeA1282::bfmeFinish1282, but its receiver is the Locomotor object used by
// the 0x001BC820 dispatcher and its three named callers.  This attempt uses
// the actual four-argument movement ABI (Object*, Coord3D*, Real, Real) and
// the BFME Object/Locomotor offsets observed in the body.  It is intentionally
// banked until the real BFME declaration can be separated from the old
// five-argument Zero Hour helper in Locomotor.cpp.

typedef float Real;
typedef bool Bool;

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

class PhysicsBehavior
{
public:
	Real getForwardSpeed2D() const;
	Real getMass() const;
	void setTurning(int turning);
	void applyMotiveForce(const Coord3D *force);
};

class AIUpdateInterface
{
public:
	Bool validMovementPosition(const Coord3D *position) const;
};

class Object
{
public:
	Coord3D *getPosition();
	const Coord3D *getPosition() const;
	PhysicsBehavior *getPhysics() const;
	AIUpdateInterface *getAI() const;
	Bool isKindOf(int kind) const;
	void setStatus(unsigned mask, Bool value);
	void setPosition(const Coord3D *position);

	char m_pad000[0x38];
	Coord3D m_position;                 // +0x38
	char m_pad044[0x78];
	unsigned m_statusBits;              // +0xBC in the local view
	char m_pad0C0[0x3C];
	unsigned m_motionBits;              // +0xFC in the local view
	char m_pad100[0x04];
	void *m_bodyModule;                 // +0x104
	void *m_physicsModule;              // +0x108
	char m_pad10C[0x10];
	unsigned m_locomotorBits;           // +0x11C
	unsigned m_locomotorState;          // +0x120
	char m_pad124[0x54];
	Coord3D m_savedGoal;                // +0x178
	char m_pad184[2];
	unsigned char m_hasSavedGoal;       // +0x186
	char m_pad187[0x7D];
	void *m_body;                       // +0x204
	void *m_blocker;                    // +0x208
};

class Overridable
{
public:
	Overridable *getFinalOverride();
	void *m_vtable;
	Overridable *m_nextOverride;
	int m_template24;
	int m_template28;
	int m_template2C;
	char m_pad30[0x14];
	Real m_template44;
	Real m_template48;
	char m_pad4C[0x10];
	int m_template5C;
	Real m_template60;
	Real m_template64;
	Real m_template68;
	Real m_template6C;
	Real m_template70;
	Real m_template74;
	Real m_template78;
	Real m_template7C;
};

class Locomotor
{
public:
	void moveTowardsPositionOther(Object *object, const Coord3D *goal,
		Real onPathDistance, Real desiredSpeed);
	Real query(Object *object);
	Real queryDivMin40(Object *object);
	Bool rotateTowardsPosition(Object *object, const Coord3D *goal);
	Bool validMovementPosition(Object *object, const Coord3D *goal) const;
	void updateObjectMotion(Object *object);

	void *m_vtable;                     // +0x00
	Overridable *m_template;            // +0x04
	char m_pad008[0x24];
	Real m_closeEnoughDistance;         // +0x2C
	Real m_maxAcceleration;             // +0x30
	char m_pad034[8];
	Real m_motionLimit;                 // +0x3C
	unsigned m_flags;                   // +0x40
	char m_pad044[0x2C];
	Real m_speedScale;                  // +0x70
	char m_pad074[0x0C];
	Real m_acceleration;                // +0x80
	char m_pad084[0x0C];
	Real m_braking;                     // +0x90
	unsigned char m_moving;             // +0x94
};

static const Real kZeroRange = 0.0001f;
static const Real kDefaultAcceleration = 0.001f;

void Locomotor::moveTowardsPositionOther(Object *object,
	const Coord3D *goal, Real onPathDistance, Real desiredSpeed)
{
	if (object == 0 || goal == 0)
		return;

	PhysicsBehavior *physics = object->getPhysics();
	if (physics == 0)
		return;

	// The retail prologue first queries the locomotor speed and clamps against
	// the resolved template value.  Keep the two values separate: the query is
	// the object-dependent cap while +0x30 is the receiver's local cap.
	Real queriedSpeed = query(object);
	if (desiredSpeed > queriedSpeed)
		desiredSpeed = queriedSpeed;

	Overridable *resolved = m_template;
	if (resolved != 0 && resolved->m_nextOverride != 0)
		resolved = resolved->m_nextOverride->getFinalOverride();
	if (resolved != 0)
	{
		Real templateSpeed = resolved->m_template60;
		if (templateSpeed > kZeroRange && desiredSpeed > templateSpeed)
			desiredSpeed = templateSpeed;
	}

	if (!validMovementPosition(object, goal))
	{
		m_flags &= ~1u;
		return;
	}

	const Coord3D *position = object->getPosition();
	Real dx = goal->x - position->x;
	Real dy = goal->y - position->y;
	Real dz = goal->z - position->z;
	Real distanceSquared = dx * dx + dy * dy;
	if (distanceSquared <= kZeroRange * kZeroRange)
	{
		m_flags &= ~1u;
		m_moving = 0;
		return;
	}

	if (!rotateTowardsPosition(object, goal))
		physics->setTurning(0);

	Real currentSpeed = physics->getForwardSpeed2D();
	Real goalSpeed = desiredSpeed;
	if (!(m_flags & (1u << 4)))
	{
		Real brakingDistance = currentSpeed * currentSpeed /
			((m_braking > kDefaultAcceleration) ? m_braking : kDefaultAcceleration);
		if (onPathDistance < brakingDistance)
			goalSpeed = (resolved != 0) ? resolved->m_template48 : 0.0f;
	}

	Real speedDelta = goalSpeed - currentSpeed;
	if (speedDelta != 0.0f)
	{
		Real acceleration = (speedDelta > 0.0f) ? m_maxAcceleration : -m_braking;
		if (acceleration == 0.0f)
			acceleration = speedDelta > 0.0f ? kDefaultAcceleration : -kDefaultAcceleration;
		Real forceMagnitude = physics->getMass() * acceleration;
		Real neededForce = physics->getMass() * speedDelta;
		if (forceMagnitude > 0.0f && neededForce < forceMagnitude)
			forceMagnitude = neededForce;
		if (forceMagnitude < 0.0f && neededForce > forceMagnitude)
			forceMagnitude = neededForce;

		Real length = distanceSquared;
		if (length > kZeroRange)
		{
			length = (Real)1.0f / (Real)__builtin_sqrt((double)length);
			Coord3D force;
			force.x = dx * length * forceMagnitude;
			force.y = dy * length * forceMagnitude;
			force.z = dz * length * forceMagnitude;
			physics->applyMotiveForce(&force);
		}
	}

	// BFME keeps a saved three-float destination and a valid bit in Object;
	// these writes are also the state transition observed on every successful
	// path through the retail body.
	object->m_savedGoal = *goal;
	object->m_hasSavedGoal = 1;
	m_moving = 1;
	updateObjectMotion(object);
}
