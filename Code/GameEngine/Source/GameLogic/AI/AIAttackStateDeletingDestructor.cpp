// cl: /DNDEBUG /MD /EHsc

// Open-BFME: AIAttackState scalar-deleting destructor at retail 0x001840E0
// (30 bytes).  The unique matched state constructor at 0x0017C910 and
// protected complete destructor at 0x0017CA40 establish the authentic class
// identity; the state-machine and weapon-layout teardown are owned there.

class AIAttackState
{
	friend void Force_AIAttackState_Deleting_Destructor(AIAttackState *value);

	protected:
	__declspec(noinline) virtual ~AIAttackState();
};

AIAttackState::~AIAttackState()
{
}

void Force_AIAttackState_Deleting_Destructor(AIAttackState *value)
{
	delete value;
}
