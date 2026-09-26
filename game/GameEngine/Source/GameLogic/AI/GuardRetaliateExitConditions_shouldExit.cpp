// cl: /DNDEBUG /MD /EHsc

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;

struct Coord3D
{
	Real x;
	Real y;
	Real z;

	Real lengthSqr() const { return x * x + y * y + z * z; }
};

struct Coord2D
{
	Real x;
	Real y;

	Coord2D() {}
	Coord2D(const Coord2D &other) : x(other.x), y(other.y) {}
	Coord2D(const Coord3D &other) : x(other.x), y(other.y) {}
	Real lengthSqr() const { return x * x + y * y; }
};

struct Coord2DLocal
{
	Real m_pad;
	Real x;
	Real y;
	Real z;

	Coord2DLocal(const Coord3D &other) : x(other.x), y(other.y) {}
};

class Object;

class StateMachine
{
public:
	const Object *getGoalObject() const;
	Object *getOwner() const { return m_owner; }

private:
	unsigned char m_pad00[0x10];
	Object *m_owner;
};

class Object
{
public:
	unsigned char m_pad00[0x38];
	Coord3D m_position;
	const Coord3D *getPosition() const { return &m_position; }
};

class GameLogic
{
public:
	unsigned char m_pad00[0x3c];
	UnsignedInt m_frame;
};

extern GameLogic *TheGameLogic;

class AIGuardRetaliateMachine
{
public:
	static Real getStdGuardRange(const Object *object);
};

#pragma comment(linker, "/alternatename:?getStdGuardRange@AIGuardRetaliateMachine@@SAMPBVObject@@@Z=?j_00008da5@@YAXXZ")

enum
{
	ATTACK_ExitIfOutsideRadius = 0x01,
	ATTACK_ExitIfExpiredDuration = 0x02
};

class AttackExitConditionsInterface
{
public:
	virtual Bool shouldExit(const StateMachine *machine) const = 0;
};

class GuardRetaliateExitConditions : public AttackExitConditionsInterface
{
public:
	Int m_conditionsToConsider;
	Coord3D m_center;
	Real m_radiusSqr;
	UnsignedInt m_attackGiveUpFrame;

	virtual Bool shouldExit(const StateMachine *machine) const;
};

Bool GuardRetaliateExitConditions::shouldExit(const StateMachine *machine) const
{
	if (m_conditionsToConsider & ATTACK_ExitIfExpiredDuration)
	{
		if (TheGameLogic->m_frame >= m_attackGiveUpFrame)
			return true;
	}

	if (m_conditionsToConsider & ATTACK_ExitIfOutsideRadius)
	{
		Coord2D objPos = *machine->getGoalObject()->getPosition();
		Coord2DLocal myPos = *machine->getOwner()->getPosition();
		Coord2D deltaAggressor;
		Coord2D myRange;

		deltaAggressor.x = objPos.x - m_center.x;
		deltaAggressor.y = objPos.y - m_center.y;

		Real guardRangeSqr = AIGuardRetaliateMachine::getStdGuardRange(machine->getOwner());
		guardRangeSqr *= guardRangeSqr;

		myRange.x = myPos.x - m_center.x;
		myRange.y = myPos.y - m_center.y;

		if (deltaAggressor.lengthSqr() > m_radiusSqr)
			return true;
		if (myRange.lengthSqr() > guardRangeSqr)
			return true;
	}

	return false;
}
