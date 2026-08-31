// cl: /O2

// BFME's State/StateMachine owner links are four bytes earlier than ZH's, and
// its AI-update and supply-interface views are at Object+0x204 and update+0x344.
// Keeping those layout facts local avoids changing every consumer of the ZH
// headers. Retail's predicate accepts state 47 as well as AI_DOCK; that second
// comparison is absent from the upstream ZH implementation but explicit in
// the BFME body.

typedef bool Bool;

enum AIStateType
{
	BFME_AI_DOCK = 14,
	BFME_AI_SECOND_SUPPLY_STATE = 47
};

class AIUpdateInterface
{
public:
	AIStateType getAIStateType() const;
};

class WorkerAIUpdate
{
};

class SupplyTruckAIInterface
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual Bool isForcedIntoWantingState() const;
};

struct Object
{
	char m_beforeAIUpdate[0x204];
	WorkerAIUpdate *m_aiUpdate;
};

struct StateMachine
{
	char m_beforeOwner[0x10];
	Object *m_owner;
};

class State
{
public:
	char m_beforeMachine[0x1C];
	StateMachine *m_machine;
};

class WorkerStateMachine
{
public:
	static Bool supplyTruckSubMachineWantsToEnter(State *thisState,
			void *userData);
};

Bool WorkerStateMachine::supplyTruckSubMachineWantsToEnter(
		State *thisState, void *)
{
	WorkerAIUpdate *update = thisState->m_machine->m_owner->m_aiUpdate;
	if (update == 0)
		return false;

	AIStateType masterState =
		reinterpret_cast<AIUpdateInterface *>(update)->getAIStateType();
	SupplyTruckAIInterface *supplyInterface =
		reinterpret_cast<SupplyTruckAIInterface *>(
			reinterpret_cast<char *>(update) + 0x344);

	return supplyInterface->isForcedIntoWantingState()
		|| masterState == BFME_AI_DOCK
		|| masterState == BFME_AI_SECOND_SUPPLY_STATE;
}
