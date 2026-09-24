// cl: /DNDEBUG /MD
// Retail 0x0016D330.  The owning state and method names remain unresolved.

typedef int Bool;

class Object;

class StateMachine
{
public:
	Object *getGoalObject();

	virtual void slot00();
	char m_pad04[0x0c];
	Object *m_owner;
};

#define BFME_VOID_SLOT(N) virtual void slot##N();

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
	BFME_VOID_SLOT(30) BFME_VOID_SLOT(31) BFME_VOID_SLOT(32)
	BFME_VOID_SLOT(33) BFME_VOID_SLOT(34) BFME_VOID_SLOT(35)
	BFME_VOID_SLOT(36) BFME_VOID_SLOT(37) BFME_VOID_SLOT(38)
	BFME_VOID_SLOT(39) BFME_VOID_SLOT(40) BFME_VOID_SLOT(41)
	BFME_VOID_SLOT(42) BFME_VOID_SLOT(43) BFME_VOID_SLOT(44)
	BFME_VOID_SLOT(45) BFME_VOID_SLOT(46) BFME_VOID_SLOT(47)
	BFME_VOID_SLOT(48) BFME_VOID_SLOT(49) BFME_VOID_SLOT(50)
	BFME_VOID_SLOT(51) BFME_VOID_SLOT(52) BFME_VOID_SLOT(53)
	BFME_VOID_SLOT(54) BFME_VOID_SLOT(55)
	virtual unsigned char slot56();
	BFME_VOID_SLOT(57)
	virtual void slot58(Object *object);
};

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
	virtual HordeContainInterface *getHordeContainInterface();
};

#undef BFME_VOID_SLOT

#include "../Object/object.h"

class Rva0016D330State
{
public:
	virtual void slot00();
	int rva0016D330();

	char m_pad[0x18];
	StateMachine *m_machine;
};

#pragma comment(linker, "/alternatename:?getGoalObject@StateMachine@@QAEPAVObject@@XZ=?j_0000e570@@YAXXZ")
extern "C" void j_0000e570();

int Rva0016D330State::rva0016D330()
{
	StateMachine *machine = m_machine;
	Object *owner = machine->m_owner;
	Object *goal = machine->getGoalObject();
	if (owner != 0 && goal != 0)
	{
		ContainModuleInterface *contain = owner->m_contain;
		if (contain != 0)
		{
			HordeContainInterface *horde =
				contain->getHordeContainInterface();
			if (horde != 0)
			{
				if (horde->slot56())
					return -1;
				horde->slot58(goal);
				return 0;
			}
		}
	}
	return -2;
}
