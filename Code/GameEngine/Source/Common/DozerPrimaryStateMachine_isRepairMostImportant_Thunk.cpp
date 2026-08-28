// cl: /DNDEBUG /MD /EHsc
// readable body of ?isRepairMostImportant@DozerPrimaryStateMachine@@SA_NPAVState@@PAX@Z: Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/DozerAIUpdate.cpp
// Lift the ?isRepairMostImportant@DozerPrimaryStateMachine@@SA_NPAVState@@PAX@Z __emit thunk to clean C++.
//
// Zero Hour's DozerAIUpdate.cpp carries this predicate, and retail keeps its
// logic while inlining the two lookups at the top: ZH's
// thisState->getMachineOwner() then dozer->getAIUpdateInterface() collapse into
// the State +0x1C -> +0x10 -> +0x204 walk below. Retail's `dec eax` pins DOZER_TASK_REPAIR to 1.
//
// The filler virtuals only place the three real calls on their retail vtable
// offsets (+0x13C and +0x180 on AIUpdateInterface, +0x14 on DozerAIInterface);
// none of them is ever defined. MSVC 7.1 compiles the final equality to
// sub/neg/sbb/inc, which is why the dump ends that way.

class State;

enum DozerTask
{
	DOZER_TASK_BUILD = 0,
	DOZER_TASK_REPAIR,
	DOZER_TASK_FORTIFY
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DozerAIUpdate.h
class DozerAIInterface
{
public:
	virtual void unused00();
	virtual void unused01();
	virtual void unused02();
	virtual void unused03();
	virtual void unused04();
	virtual DozerTask getMostRecentCommand(void);		///< vtable +0x14
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/AIUpdate.h
class AIUpdateInterface
{
public:
	virtual void unused00();
	virtual void unused01();
	virtual void unused02();
	virtual void unused03();
	virtual void unused04();
	virtual void unused05();
	virtual void unused06();
	virtual void unused07();
	virtual void unused08();
	virtual void unused09();
	virtual void unused10();
	virtual void unused11();
	virtual void unused12();
	virtual void unused13();
	virtual void unused14();
	virtual void unused15();
	virtual void unused16();
	virtual void unused17();
	virtual void unused18();
	virtual void unused19();
	virtual void unused20();
	virtual void unused21();
	virtual void unused22();
	virtual void unused23();
	virtual void unused24();
	virtual void unused25();
	virtual void unused26();
	virtual void unused27();
	virtual void unused28();
	virtual void unused29();
	virtual void unused30();
	virtual void unused31();
	virtual void unused32();
	virtual void unused33();
	virtual void unused34();
	virtual void unused35();
	virtual void unused36();
	virtual void unused37();
	virtual void unused38();
	virtual void unused39();
	virtual void unused40();
	virtual void unused41();
	virtual void unused42();
	virtual void unused43();
	virtual void unused44();
	virtual void unused45();
	virtual void unused46();
	virtual void unused47();
	virtual void unused48();
	virtual void unused49();
	virtual void unused50();
	virtual void unused51();
	virtual void unused52();
	virtual void unused53();
	virtual void unused54();
	virtual void unused55();
	virtual void unused56();
	virtual void unused57();
	virtual void unused58();
	virtual void unused59();
	virtual void unused60();
	virtual void unused61();
	virtual void unused62();
	virtual void unused63();
	virtual void unused64();
	virtual void unused65();
	virtual void unused66();
	virtual void unused67();
	virtual void unused68();
	virtual void unused69();
	virtual void unused70();
	virtual void unused71();
	virtual void unused72();
	virtual void unused73();
	virtual void unused74();
	virtual void unused75();
	virtual void unused76();
	virtual void unused77();
	virtual void unused78();
	virtual DozerAIInterface *getDozerAIInterface(void);	///< vtable +0x13C
	virtual void unused80();
	virtual void unused81();
	virtual void unused82();
	virtual void unused83();
	virtual void unused84();
	virtual void unused85();
	virtual void unused86();
	virtual void unused87();
	virtual void unused88();
	virtual void unused89();
	virtual void unused90();
	virtual void unused91();
	virtual void unused92();
	virtual void unused93();
	virtual void unused94();
	virtual void unused95();
	virtual bool isIdle(void) const;					///< vtable +0x180
};

struct DozerStateOwnerAI
{
	unsigned char m_unreconstructed_00[0x204];
	AIUpdateInterface *m_ai;							///< retail this+0x204
};

struct DozerStateOwner
{
	unsigned char m_unreconstructed_00[0x10];
	DozerStateOwnerAI *m_owner;						///< retail this+0x10
};

struct DozerStateMachineOwner
{
	unsigned char m_unreconstructed_00[0x1C];
	DozerStateOwner *m_machine;						///< retail this+0x1C
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/DozerAIUpdate.h
class DozerPrimaryStateMachine
{
public:
	static bool __cdecl isRepairMostImportant(State *, void *);
};

// ?isRepairMostImportant@DozerPrimaryStateMachine@@SA_NPAVState@@PAX@Z
bool __cdecl DozerPrimaryStateMachine::isRepairMostImportant(State *thisState, void *)
{
	AIUpdateInterface *ai =
		((DozerStateMachineOwner *)thisState)->m_machine->m_owner->m_ai;
	if (ai == 0)
		return false;

	DozerAIInterface *dozerAI = ai->getDozerAIInterface();
	if (dozerAI == 0)
		return false;

	if (!ai->isIdle())
		return false;

	return dozerAI->getMostRecentCommand() == DOZER_TASK_REPAIR;
}
