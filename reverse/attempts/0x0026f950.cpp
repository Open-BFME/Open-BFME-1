// ?getEnterTarget@AIUpdateInterface@@UAEPAVObject@@XZ
// partial score=0.86 date=2026-08-28
struct BFMEEnterTargetStateFields
{
	char m_unreconstructed_000[0x04];
	Int m_stateID;
};

struct BFMEEnterTargetStateMachineFields
{
	Int getCurrentStateID() const
	{
		return m_currentState ? m_currentState->m_stateID : INVALID_STATE_ID;
	}

	char m_unreconstructed_000[0x58];
	BFMEEnterTargetStateFields *m_currentState;
};

struct BFMEEnterTargetAIUpdateFields
{
	AIStateType getAIStateType() const;

	char m_unreconstructed_000[0x30];
	BFMEEnterTargetStateMachineFields *m_stateMachine;
};

AIStateType BFMEEnterTargetAIUpdateFields::getAIStateType() const
{
	return static_cast<AIStateType>( m_stateMachine->getCurrentStateID() );
}

Object* AIUpdateInterface::getEnterTarget()
{
	BFMEEnterTargetAIUpdateFields *retail = reinterpret_cast<BFMEEnterTargetAIUpdateFields *>( this );
	BFMEEnterTargetStateMachineFields *stateMachine = retail->m_stateMachine;
	AIStateType stateType = retail->getAIStateType();

	// BFME added entry-state variants after Zero Hour, so its saved enum values differ.
	if( stateType != static_cast<AIStateType>( 0x0F ) &&
			stateType != static_cast<AIStateType>( 0x31 ) &&
			stateType != static_cast<AIStateType>( 0x18 ) &&
			stateType != static_cast<AIStateType>( 0x2B ) &&
			stateType != static_cast<AIStateType>( 0x19 ) &&
			stateType != static_cast<AIStateType>( 0x34 ) )
		return NULL;

	return reinterpret_cast<AIStateMachine *>( stateMachine )->getGoalObject();
}
