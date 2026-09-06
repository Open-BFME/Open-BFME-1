// cl: /DNDEBUG /MD /EHsc
// Address-derived turret-state update; the specific state name and meaning
// of terminal result -2 are unproven. Positive results are sleep frames.
// Retail 0x0018D4F0.  The BFME state base places the machine at +0x1c;
// TurretStateMachine places its TurretAI back-pointer at +0x44.

typedef unsigned int UnsignedInt;

typedef int StateReturnType;
static const StateReturnType STATE_CONTINUE = 0;
static const StateReturnType STATE_RETURN_NEGATIVE_TWO = -2;

class AIUpdateInterface
{
private:
	unsigned char m_pad[0x1fc];

public:
	UnsignedInt m_nextMoodCheckTime;
};

class Object
{
private:
	unsigned char m_pad[0x204];

public:
	AIUpdateInterface *m_ai;
};

class GameLogic
{
private:
	unsigned char m_pad[0x3c];

public:
	UnsignedInt m_frame;

	UnsignedInt getFrame() const
	{
		return m_frame;
	}
};

extern GameLogic *TheGameLogic;

class TurretAI
{
public:
	void friend_checkForIdleMoodTarget();

	Object *getOwner() const
	{
		return *(Object **)((const unsigned char *)this + 0x10);
	}

	UnsignedInt friend_getNextIdleMoodTargetFrame() const
	{
		const Object *obj = getOwner();
		const AIUpdateInterface *ai = obj->m_ai;
		return ai ? ai->m_nextMoodCheckTime : TheGameLogic->getFrame();
	}
};

class TurretStateMachine
{
private:
	unsigned char m_pad[0x44];

public:
	TurretAI *m_turretAI;
};

static StateReturnType frameToSleepTime(UnsignedInt frame1, UnsignedInt frame2)
{
	if (frame1 > frame2)
		frame1 = frame2;
	if (frame1 > 0x3fffffff)
		frame1 = 0x3fffffff;

	UnsignedInt now = TheGameLogic->getFrame();
	if (frame1 > now)
		return (StateReturnType)(frame1 - now);

	return STATE_CONTINUE;
}

class Rva0018D4F0State
{
public:
	virtual StateReturnType update();

private:
	unsigned char m_pad[0x18];
	TurretStateMachine *m_machine;
	unsigned char m_pad20[4];
	UnsignedInt m_timestamp;

	TurretAI *getTurretAI() const
	{
		return m_machine->m_turretAI;
	}
};

// ?update@Rva0018D4F0State@@UAEHXZ
StateReturnType Rva0018D4F0State::update()
{
	if (TheGameLogic->getFrame() >= m_timestamp)
		return STATE_RETURN_NEGATIVE_TWO;

	TurretAI *turret = getTurretAI();
	turret->friend_checkForIdleMoodTarget();

	return frameToSleepTime(
		turret->friend_getNextIdleMoodTargetFrame(), m_timestamp);
}
