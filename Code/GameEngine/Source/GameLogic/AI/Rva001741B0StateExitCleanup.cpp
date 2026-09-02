// cl: /DNDEBUG /MD
// Retail 0x001741B0: state-exit cleanup after the related 0x00172D80 base
// routine.  It clears the high model-condition bit and an AI-update byte.
// No surviving caller identifies the concrete state, so its name is
// address-derived.

class Rva001741B0AIUpdate
{
public:
	char m_unknown[ 0x332 ];
	bool m_exitFlag;
};

class Object
{
public:
	void notifyModelConditionChanged();

	char m_unknown0[ 0x114 ];
	unsigned int m_modelConditionFlags;
	char m_unknown118[ 0xEC ];
	Rva001741B0AIUpdate *m_ai;
};

struct StateMachine
{
	char m_unknown[ 0x10 ];
	Object *m_owner;
};

class Rva00172D80StateBase
{
public:
	virtual void onExit( int status );

protected:
	char m_state[ 0x18 ];
	StateMachine *m_machine;
};

class Rva001741B0State : public Rva00172D80StateBase
{
public:
	virtual void onExit( int status );
};

void Rva001741B0State::onExit( int status )
{
	Rva00172D80StateBase::onExit( status );

	Object *owner = m_machine->m_owner;
	if( owner )
	{
		if( owner->m_modelConditionFlags & 0x80000000 )
		{
			owner->m_modelConditionFlags &= 0x7FFFFFFF;
			owner->notifyModelConditionChanged();
		}
	}

	Rva001741B0AIUpdate *ai = owner->m_ai;
	if( ai )
		ai->m_exitFlag = false;
}
