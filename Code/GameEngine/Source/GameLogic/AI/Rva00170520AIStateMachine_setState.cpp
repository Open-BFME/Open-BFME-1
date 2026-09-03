// cl: /DNDEBUG /MD
// Retail 0x00170520: AI state-machine state transition wrapper.

enum StateReturnType
{
    STATE_CONTINUE = 0,
    STATE_SUCCESS = -1,
    STATE_FAILURE = -2
};

struct Rva00170520State
{
    void *m_vtable;
    int m_id;
};

struct Rva00170520AIUpdate
{
    void **m_vtable;
    char m_unknown[0x224 - 4];

    void notifyStateMachineChanged()
    {
        typedef void (__fastcall *Notify)(Rva00170520AIUpdate *);
        ((Notify)m_vtable[0x224 / 4])(this);
    }
};

struct Rva00170520Object
{
    char m_unknown[0x204];
    Rva00170520AIUpdate *m_ai;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/StateMachine.h
class StateMachine
{
protected:
    char m_unknown[0x0c];
    Rva00170520Object *m_owner;
    char m_gap14[8];

public:
    virtual StateReturnType setState(unsigned int newStateID);
};

class Rva00170520AIStateMachine : public StateMachine
{
    Rva00170520State *m_currentState;
    char m_gap20[0x38];
    void *m_temporaryState;
    int m_temporaryStateFrameEnd;

public:
    virtual StateReturnType setState(unsigned int newStateID);
};

void j_00027566();
typedef void (__fastcall *Rva00170520Clear)(Rva00170520AIStateMachine *);

StateReturnType Rva00170520AIStateMachine::setState(unsigned int newStateID)
{
	if (m_temporaryState)
	{
		if (m_temporaryStateFrameEnd == -1)
			return STATE_CONTINUE;

		((Rva00170520Clear)j_00027566)(this);
	}

	int oldStateID;
	if (m_currentState)
		oldStateID = m_currentState->m_id;
	else
		oldStateID = 0xF423F;

	StateReturnType result = StateMachine::setState(newStateID);
    Rva00170520AIUpdate *ai = m_owner->m_ai;
    if (ai && oldStateID != newStateID)
        ai->notifyStateMachineChanged();
    return result;
}
