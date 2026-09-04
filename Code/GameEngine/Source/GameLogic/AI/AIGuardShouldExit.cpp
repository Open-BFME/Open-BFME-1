// cl: /DNDEBUG /MD /EHsc
// Clean C++ reconstruction of the ZH ExitConditions::shouldExit twin.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;

struct Coord3D
{
	Real x, y, z;
	Coord3D() {}
	Coord3D(const Coord3D &other) : x(other.x), y(other.y), z(other.z) {}
	Real lengthSqr() const { return x * x + y * y + z * z; }
};

class Object
{
public:
	char m_bfmeHead[0x38];
	Coord3D m_pos;
	const Coord3D *getPosition(void) const { return &m_pos; }
};

class StateMachine
{
public:
	const Object *getGoalObject(void) const;
};

class GameLogic
{
public:
	char m_bfmeHead[0x3C];
	UnsignedInt m_frame;
};

extern GameLogic *TheGameLogic;

enum
{
	ATTACK_ExitIfOutsideRadius = 0x01,
	ATTACK_ExitIfExpiredDuration = 0x02,
	ATTACK_ExitIfNoUnitFound = 0x04
};

class AttackExitConditionsInterface
{
public:
	virtual Bool shouldExit(const StateMachine *machine) const = 0;
};

class ExitConditions : public AttackExitConditionsInterface
{
public:
	Int m_conditionsToConsider;
	Coord3D m_center;
	Real m_radiusSqr;
	UnsignedInt m_attackGiveUpFrame;

	virtual Bool shouldExit(const StateMachine *machine) const;
};

Bool ExitConditions::shouldExit(const StateMachine *machine) const
{
	if (!machine->getGoalObject())
	{
		if (m_conditionsToConsider & ATTACK_ExitIfNoUnitFound)
			return true;
		else
			return false;
	}

	if (m_conditionsToConsider & ATTACK_ExitIfExpiredDuration)
	{
		if (TheGameLogic->m_frame >= m_attackGiveUpFrame)
			return true;
	}

	if (m_conditionsToConsider & ATTACK_ExitIfOutsideRadius)
	{
		Coord3D deltaAggressor;
		Coord3D objPos = *machine->getGoalObject()->getPosition();
		deltaAggressor.x = objPos.x - m_center.x;
		deltaAggressor.y = objPos.y - m_center.y;
		deltaAggressor.z = 0;

		if (deltaAggressor.lengthSqr() > m_radiusSqr)
			return true;
	}

	return false;
}
