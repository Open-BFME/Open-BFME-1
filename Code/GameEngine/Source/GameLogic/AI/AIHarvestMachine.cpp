// cl: /DNDEBUG /MD /EHsc
// Retail 0x0015FE90.  The constructor's own literal, vptr store, and the
// Rva0016CF40State onEnter/xfer callers identify this as AIHarvestMachine.

#include "../../../../../reference/shims/stringinline/StringInline.h"

class Object;

struct StateConditionInfo;
class State;

class __declspec(novtable) StateMachine
{
public:
	StateMachine(Object *owner, AsciiString name, bool flag);

protected:
	virtual ~StateMachine();
	void defineState(unsigned int id, State *state, unsigned int successID,
		unsigned int failureID, const StateConditionInfo *conditions);

};

#pragma comment(linker, "/alternatename:??0StateMachine@@QAE@PAVObject@@VAsciiString@@_N@Z=?j_0000f123@@YAXXZ")
#pragma comment(linker, "/alternatename:?defineState@StateMachine@@IAEXIPAVState@@IIPBUStateConditionInfo@@@Z=?j_0003d1b3@@YAXXZ")

class AIInternalMoveToState
{
public:
	AIInternalMoveToState(void *machine, AsciiString name);

protected:
	void *m_vptr;
	unsigned char m_fields[0x4c];
};

#pragma comment(linker, "/alternatename:??0AIInternalMoveToState@@QAE@PAXVAsciiString@@@Z=?j_00032182@@YAXXZ")

class Rva000A19E0StateBase
{
public:
	Rva000A19E0StateBase(void *machine, AsciiString name);

protected:
	void *m_vptr;
	unsigned char m_fields[0x20];
};

#pragma comment(linker, "/alternatename:??0Rva000A19E0StateBase@@QAE@PAXVAsciiString@@@Z=?j_000035b2@@YAXXZ")

class Rva0015FD00State : public AIInternalMoveToState
{
public:
	Rva0015FD00State(void *machine);
};

Rva0015FD00State::Rva0015FD00State(void *machine)
	: AIInternalMoveToState(machine, AsciiString("AIHarvestApproachSiteState"))
{
	m_vptr = reinterpret_cast<void *>(0x010966f8);
}

class Rva0015FDB0State : public Rva000A19E0StateBase
{
public:
	Rva0015FDB0State(void *machine);

private:
	unsigned int m_stateField24;
};

Rva0015FDB0State::Rva0015FDB0State(void *machine)
	: Rva000A19E0StateBase(machine, AsciiString("AIHarvestPrepareSiteState"))
{
	m_vptr = reinterpret_cast<void *>(0x01096770);
	m_stateField24 = 0;
}

class Rva0015FE20State : public Rva000A19E0StateBase
{
public:
	Rva0015FE20State(void *machine);

private:
	unsigned int m_stateField24;
};

Rva0015FE20State::Rva0015FE20State(void *machine)
	: Rva000A19E0StateBase(machine, AsciiString("AIHarvestWorkSiteState"))
{
	m_vptr = reinterpret_cast<void *>(0x010967e8);
	m_stateField24 = 0;
}

class __declspec(novtable) AIHarvestMachine : public StateMachine
{
public:
	AIHarvestMachine(Object *owner);
};

// ??0AIHarvestMachine@@QAE@PAVObject@@@Z

AIHarvestMachine::AIHarvestMachine(Object *owner)
	: StateMachine(owner, AsciiString("AIHarvestMachine"), false)
{
	*reinterpret_cast<void **>(this) = reinterpret_cast<void *>(0x01096650);

	defineState(0, (State *)new Rva0015FD00State(this), 1, 9999, 0);
	defineState(1, (State *)new Rva0015FDB0State(this), 2, 0, 0);
	defineState(2, (State *)new Rva0015FE20State(this), 9998, 9999, 0);
}
