// ?onEnter@GiantBirdFollowPathState@@UAE?AW4StateReturnType@@XZ
// partial score=0.84 date=2026-09-02
// cl: /DNDEBUG /MD
// GiantBirdFollowPathState::onEnter.  Ctor at 0x002BDB30 names this class.

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

class Object
{
public:
	unsigned char m_beforeAI[0x204];
	class GiantBirdAIUpdate *m_aiUpdate;
	unsigned char m_beforeFlags[0x344 - 0x208];
	unsigned char m_flags344;
};

class StateMachine
{
public:
	unsigned char m_beforeOwner[0x10];
	Object *m_owner;
};

class GiantBirdAIUpdate
{
public:
	unsigned char m_beforeFlags[0x3f0];
	unsigned int m_flags3f0;
	unsigned char m_beforeByte[0x424 - 0x3f4];
	unsigned char m_byte424;
};

class GiantBirdFollowPathState
{
public:
	virtual StateReturnType onEnter();
	bool tryAdvance();

private:
	int m_id;
	int m_successStateID;
	int m_failureStateID;
	void *m_transitions[3];
	StateMachine *m_machine;
	unsigned char m_gap20[0x5c - 0x20];
	int m_counter;
};

StateReturnType GiantBirdFollowPathState::onEnter()
{
	m_counter = 0;
	Object *obj = m_machine->m_owner;
	GiantBirdAIUpdate *ai = obj->m_aiUpdate;
	if (!ai || (obj->m_flags344 & 1))
		return STATE_FAILURE;
	if (!tryAdvance())
		return STATE_SUCCESS;
	if (!ai->m_byte424)
		return STATE_FAILURE;
	ai->m_flags3f0 |= 0x80;
	return STATE_CONTINUE;
}
