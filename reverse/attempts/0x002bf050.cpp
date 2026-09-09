// ?onEnter@GiantBirdFollowWaypointPathState@@UAE?AW4StateReturnType@@XZ
// partial score=0.84 date=2026-09-07

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

class AIUpdateInterface
{
public:
	char m_pad000[0x3f0];
	unsigned int m_flags3f0;
	char m_pad3f4[0x30];
	unsigned char m_flags424;
};

class Object
{
public:
	char m_pad000[0x204];
	AIUpdateInterface *m_ai;
	char m_pad208[0x13c];
	unsigned char m_flags344;
};

class StateMachine
{
public:
	char m_pad000[0x10];
	Object *m_owner;
};

class GiantBirdFollowWaypointPathState
{
public:
	virtual StateReturnType onEnter();
	bool updateWaypointGoal();

	char m_pad004[0x18];
	StateMachine *m_machine;
	char m_pad020[4];
	int m_counter;
};

#pragma comment(linker, "/alternatename:?updateWaypointGoal@GiantBirdFollowWaypointPathState@@QAE_NXZ=?j_00031b47@@YAXXZ")

StateReturnType GiantBirdFollowWaypointPathState::onEnter()
{
	m_counter = 0;
	Object *object = m_machine->m_owner;
	AIUpdateInterface *ai = object->m_ai;
	if (!ai || (object->m_flags344 & 1) != 0)
		return STATE_FAILURE;
	if (!updateWaypointGoal())
		return STATE_SUCCESS;
	switch (ai->m_flags424)
	{
	case 0:
		goto failure;
	default:
		goto continue_path;
	}

failure:
	return STATE_FAILURE;

continue_path:
	ai->m_flags3f0 |= 0x80;
	return STATE_CONTINUE;
}
