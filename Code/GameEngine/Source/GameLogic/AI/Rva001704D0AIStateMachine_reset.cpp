// cl: /DNDEBUG /MD
// Retail 0x001704D0: reset wrapper for the BFME AI state machine.

enum StateReturnType
{
	STATE_CONTINUE = 0,
	STATE_SUCCESS = -1,
	STATE_FAILURE = -2
};

struct Rva001704D0AIUpdate
{
	void **m_vtable;
	char m_unknown[0x204 - 4];

	void notifyStateMachineChanged()
	{
		typedef void (__fastcall *Notify)(Rva001704D0AIUpdate *);
		((Notify)m_vtable[0x224 / 4])(this);
	}
};

struct Rva001704D0Object
{
	char m_unknown[0x204];
	Rva001704D0AIUpdate *m_ai;
};

class Rva001704D0AIStateMachine
{
	char m_unknown[0x0c];
	Rva001704D0Object *m_owner;
	char m_gap14[0x44];
	void *m_temporaryState;
	int m_temporaryStateFrameEnd;

public:
	virtual StateReturnType resetToDefaultState();
};

void j_00027566();
void j_0000705e();

typedef void (__fastcall *Rva001704D0Clear)(Rva001704D0AIStateMachine *);
typedef StateReturnType (__fastcall *Rva001704D0Reset)(Rva001704D0AIStateMachine *);

StateReturnType Rva001704D0AIStateMachine::resetToDefaultState()
{
	if (m_temporaryState)
	{
		if (m_temporaryStateFrameEnd == -1)
			return STATE_CONTINUE;

		((Rva001704D0Clear)j_00027566)(this);
	}
	{
		StateReturnType result = ((Rva001704D0Reset)j_0000705e)(this);
		Rva001704D0Object *owner = m_owner;
		Rva001704D0AIUpdate *ai = owner->m_ai;
		if (ai)
			ai->notifyStateMachineChanged();
		return result;
	}
}
