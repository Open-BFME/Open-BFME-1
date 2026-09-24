// cl: /DNDEBUG /MD
// Retail 0x0016D270, 153 bytes. bounds=high (carved). Two prior blocked
// passes established the callee (StateMachine::getGoalObject, pinned
// j_0000e570) and the +0x68/+0x84/+0x88 virtual slots but found no owning
// class, caller, or independent method identity, so this stays
// address-derived per docs/naming_evidence.md.
//
// Twin: Code/GameEngine/Source/GameLogic/AI/Rva0016D330State.cpp (retail
// 0x0016D330, right after this body) proves the StateMachine/Object/
// ContainModuleInterface/HordeContainInterface layout -- same m_owner@+0x10,
// m_contain@+0x1fc, and the ContainModuleInterface::getHordeContainInterface
// slot at +0x68. This body walks BOTH the state's owner and its goal object,
// and only merges them into one horde (owner's horde slot +0x78, goal's
// contain slot +0x88) when the goal does not already have a horde interface
// and the goal's contain accepts it (slot +0x84).

typedef bool Bool;

class Object;

class StateMachine
{
public:
	Object *getGoalObject();

	virtual void slot00();
	char m_pad04[0x0c];
	Object *m_owner;
};

class HordeContainInterface;

#define BFME_VOID_SLOT(N) virtual void slot##N();

class ContainModuleInterface
{
public:
	BFME_VOID_SLOT(00) BFME_VOID_SLOT(01) BFME_VOID_SLOT(02)
	BFME_VOID_SLOT(03) BFME_VOID_SLOT(04) BFME_VOID_SLOT(05)
	BFME_VOID_SLOT(06) BFME_VOID_SLOT(07) BFME_VOID_SLOT(08)
	BFME_VOID_SLOT(09) BFME_VOID_SLOT(10) BFME_VOID_SLOT(11)
	BFME_VOID_SLOT(12) BFME_VOID_SLOT(13) BFME_VOID_SLOT(14)
	BFME_VOID_SLOT(15) BFME_VOID_SLOT(16) BFME_VOID_SLOT(17)
	BFME_VOID_SLOT(18) BFME_VOID_SLOT(19) BFME_VOID_SLOT(20)
	BFME_VOID_SLOT(21) BFME_VOID_SLOT(22) BFME_VOID_SLOT(23)
	BFME_VOID_SLOT(24) BFME_VOID_SLOT(25)
	virtual HordeContainInterface *getHordeContainInterface();	// slot 26 (+0x68)
	BFME_VOID_SLOT(27) BFME_VOID_SLOT(28) BFME_VOID_SLOT(29)
	BFME_VOID_SLOT(30) BFME_VOID_SLOT(31) BFME_VOID_SLOT(32)
	virtual Bool slot33(Object *owner, Bool flag);					// slot 33 (+0x84)
	virtual void slot34(Object *owner);							// slot 34 (+0x88)
};

class HordeContainInterface
{
public:
	BFME_VOID_SLOT(00) BFME_VOID_SLOT(01) BFME_VOID_SLOT(02)
	BFME_VOID_SLOT(03) BFME_VOID_SLOT(04) BFME_VOID_SLOT(05)
	BFME_VOID_SLOT(06) BFME_VOID_SLOT(07) BFME_VOID_SLOT(08)
	BFME_VOID_SLOT(09) BFME_VOID_SLOT(10) BFME_VOID_SLOT(11)
	BFME_VOID_SLOT(12) BFME_VOID_SLOT(13) BFME_VOID_SLOT(14)
	BFME_VOID_SLOT(15) BFME_VOID_SLOT(16) BFME_VOID_SLOT(17)
	BFME_VOID_SLOT(18) BFME_VOID_SLOT(19) BFME_VOID_SLOT(20)
	BFME_VOID_SLOT(21) BFME_VOID_SLOT(22) BFME_VOID_SLOT(23)
	BFME_VOID_SLOT(24) BFME_VOID_SLOT(25) BFME_VOID_SLOT(26)
	BFME_VOID_SLOT(27) BFME_VOID_SLOT(28) BFME_VOID_SLOT(29)
	virtual void slot30(void *interiorObject, int what, Object *object);	// slot 30 (+0x78)
};

#undef BFME_VOID_SLOT

#include "../Object/object.h"

class Rva0016D270Owner
{
public:
	int invoke();

private:
	char m_pad[0x1c];
	StateMachine *m_machine;						// +0x1c
};

int Rva0016D270Owner::invoke()
{
	StateMachine *machine = m_machine;
	Object *owner = machine->m_owner;
	Object *goal = machine->getGoalObject();
	ContainModuleInterface *ownerContain;

	if (owner == 0 || goal == 0 || (goal->m_privateStatus & 1) != 0 ||
		(ownerContain = owner->m_contain) == 0)
		return -2;

	HordeContainInterface *ownerHorde = ownerContain->getHordeContainInterface();
	if (ownerHorde == 0)
		return -2;

	ContainModuleInterface *goalContain = goal->m_contain;
	if (goalContain == 0)
		return -2;

	if (goalContain->getHordeContainInterface() != 0)
		return -2;
	if (!goalContain->slot33(owner, 1))
		return -2;

	ownerHorde->slot30((char *)goal + 0x38, 2, goal);
	goalContain->slot34(owner);
	return 0;
}
