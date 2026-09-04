// ?shouldExit@ExitConditions@@UBE_NPBVStateMachine@@@Z
// partial score=0.99 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc

// Open-BFME: ExitConditions::shouldExit, retail 0x0015BF80, 135 bytes.
// ZH twin with BFME 2D (x,y) radius test. Position is Object+0x38.

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
	Coord3D m_pos;					// +0x38
	const Coord3D *getPosition(void) const { return &m_pos; }
};

class StateMachine
{
public:
	Object *getGoalObject(void) const;
};

class GameLogic
{
public:
	char m_bfmeHead[0x3C];
	UnsignedInt m_frame;				// +0x3C
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

// ?shouldExit@ExitConditions@@UBE_NPBVStateMachine@@@Z
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
