// cl: /DNDEBUG /MD /EHsc
// readable body of ?isBuildMostImportant@DozerPrimaryStateMachine@@: Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/DozerAIUpdate.cpp
// Open-BFME: DozerPrimaryStateMachine::isBuildMostImportant, retail 0x002B6480.
//
// Same five layout points as its landed siblings isRepairMostImportant
// (0x002B64E0) and isFortifyMostImportant (0x002B6540) in DozerAIUpdate.cpp:
// the state's machine is at State+0x1C (vendored +0x20), its owner at
// StateMachine+0x10 (vendored +0x14), the AI at Object+0x204 (vendored
// +0x19C), getDozerAIInterface at AIUpdateInterface vtable +0x13C (vendored
// +0xFC), isIdle at vtable +0x180 (vendored +0x13C), and getMostRecentCommand
// at DozerAIInterface vtable +0x14 (vendored +0x180). Reproduced here as an
// independent twin TU (not editing the landed DozerAIUpdate.cpp) using the
// same BfmeDozer* shape classes as the two sibling functions.

typedef bool Bool;
typedef int Int;

class Object;
class State;
class AIUpdateInterface;
class DozerAIInterface;

class DozerPrimaryStateMachine
{
public:
	static Bool isBuildMostImportant( State *thisState, void *userData );
};

enum DozerTask
{
	DOZER_TASK_BUILD = 0
};

template <Int N>
class BfmeDozerSlots : public BfmeDozerSlots<N - 1>
{
public:
	virtual void unused(char (*)[N]) = 0;
};

template <>
class BfmeDozerSlots<0>
{
};

class BfmeDozerAiVTable : public BfmeDozerSlots<79>
{
public:
	virtual void *getDozerAIInterface() = 0;		///< vtable +0x13C
	virtual void unusedSlot80() = 0;
	virtual void unusedSlot81() = 0;
	virtual void unusedSlot82() = 0;
	virtual void unusedSlot83() = 0;
	virtual void unusedSlot84() = 0;
	virtual void unusedSlot85() = 0;
	virtual void unusedSlot86() = 0;
	virtual void unusedSlot87() = 0;
	virtual void unusedSlot88() = 0;
	virtual void unusedSlot89() = 0;
	virtual void unusedSlot90() = 0;
	virtual void unusedSlot91() = 0;
	virtual void unusedSlot92() = 0;
	virtual void unusedSlot93() = 0;
	virtual void unusedSlot94() = 0;
	virtual void unusedSlot95() = 0;
	virtual Bool isIdle() = 0;				///< vtable +0x180
};

class BfmeDozerTaskVTable : public BfmeDozerSlots<5>
{
public:
	virtual Int getMostRecentCommand() = 0;			///< vtable +0x14
};

struct BfmeDozerMachineFields
{
	unsigned char m_unreconstructed_000[ 0x10 ];
	Object *m_owner;					///< retail this+0x10
};

struct BfmeDozerStateFields
{
	unsigned char m_unreconstructed_000[ 0x1c ];
	BfmeDozerMachineFields *m_machine;			///< retail this+0x1C
};

struct BfmeDozerObjectFields
{
	unsigned char m_unreconstructed_000[ 0x204 ];
	AIUpdateInterface *m_ai;				///< retail this+0x204
};

// ?isBuildMostImportant@DozerPrimaryStateMachine@@SA_NPAVState@@PAX@Z
Bool DozerPrimaryStateMachine::isBuildMostImportant( State *thisState, void* userData )
{
	Object *dozer = ((BfmeDozerStateFields *)thisState)->m_machine->m_owner;
	AIUpdateInterface *ai = ((BfmeDozerObjectFields *)dozer)->m_ai;
	if( !ai )
	{
		return false;
	}
	DozerAIInterface *dozerAI = (DozerAIInterface *)((BfmeDozerAiVTable *)ai)->getDozerAIInterface();
	if( !dozerAI )
	{
		return false;
	}

	if( !((BfmeDozerAiVTable *)ai)->isIdle() )
		return false;  // busy doing something else

	// if the most important task is us then return true
	DozerTask task = (DozerTask)((BfmeDozerTaskVTable *)dozerAI)->getMostRecentCommand();
	return task == DOZER_TASK_BUILD;

}  // end isBuildMostImportant
