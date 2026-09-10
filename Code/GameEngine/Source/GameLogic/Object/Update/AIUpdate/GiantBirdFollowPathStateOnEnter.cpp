// cl: /DNDEBUG /MD
//
// GiantBirdFollowPathState::onEnter, retail RVA 0x002BDB80, 78 bytes.
// The constructor at 0x002BDB30 passes the literal state name and installs
// vtable 0x010C7778; the matched onExit at 0x002BDF10 and update at
// 0x002BDDC0 establish the same state layout.  The call below is the state
// helper's retail ILT at 0x00024884, which jumps to 0x002BDBF0.

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
	bool m_byte424;
	__forceinline bool isContinueEnabled() const
	{
		return m_byte424 != 0;
	}
};

class GiantBirdFollowPathState
{
public:
	virtual StateReturnType onEnter();
	bool rva002BDBF0();

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
	Object *object = m_machine->m_owner;
	GiantBirdAIUpdate *ai = object->m_aiUpdate;
	if (ai == 0)
		goto failure;
	if ((object->m_flags344 & 1) != 0)
		goto failure;
	if (!rva002BDBF0())
		return STATE_SUCCESS;
	// Keep the shared failure block before the final flag-setting tail; this
	// is the retail branch layout emitted by MSVC 7.1 for this state.
	goto checkByte;
failure:
	return STATE_FAILURE;

checkByte:
	if (ai->isContinueEnabled() == 0)
		goto failure;
	ai->m_flags3f0 |= 0x80;
	return STATE_CONTINUE;
}
