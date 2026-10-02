// ?onContaining@Rva0021D5D0Secondary@@QAEXPAVObject@@_N@Z
// cl: /O2 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/sweep /Igame/GameEngine/Source /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include "GameLogic/Module/UpdateModule.h"
typedef bool Bool;

class Object
{
public:
	void setStatusBit(int status, Bool enable);
	unsigned char m_beforeStatus[0x94];
	unsigned char m_status;
};

struct Rva0021D5D0Node
{
	Rva0021D5D0Node *m_next;
	Rva0021D5D0Node *m_prev;
	Object *m_object;
};

class GarrisonContain
{
public:
	virtual void onContaining(Object *object, Bool selected);
};

class Gen0021CE60
{
public:
	void handle(int objectBits);
};

class Rva0021D180
{
public:
	void body();
};

// ILT 0x000157DA reaches the matched UpdateModule::setWakeFrame at 0x002B2040.
// Keep the header's protected signature and enum value through a local view.
class Rva0021D5D0WakeAccess : public UpdateModule
{
public:
	__forceinline void wake(Object *object)
	{
		setWakeFrame(object, UPDATE_SLEEP_NONE);
	}
};

class GameLogic
{
public:
	unsigned char m_beforeFrame[0x3c];
	unsigned int m_frame;
};
extern GameLogic *TheGameLogic;

// This receiver is ContestableContain's secondary interface at primary+0x20.
// The ctor at 0x0021BEE0 installs its 0x010AB140 vtable here; slot 17
// (ILT 0x000494A4) routes to this 0x0021D5D0 body.
class Rva0021D5D0Secondary
{
public:
	void onContaining(Object *object, Bool selected);

private:
	void *primary() const { return (char *)this - 0x20; }
	Object *owner() const
	{
		return *(Object *const *)((const char *)this - 0x18);
	}
	Rva0021D5D0Node *contestHead() const
	{
		return *(Rva0021D5D0Node *const *)((const char *)this + 0x99c);
	}
	Rva0021D5D0Node *containHead() const
	{
		return *(Rva0021D5D0Node *const *)((const char *)this + 0x18);
	}
	Bool disabled() const { return *((const char *)this + 0x9b8) != 0; }
	void setNextFrame(unsigned int frame)
	{
		*(unsigned int *)((char *)this + 0x9b4) = frame;
	}
};

void Rva0021D5D0Secondary::onContaining(Object *object, Bool selected)
{
	((GarrisonContain *)this)->GarrisonContain::onContaining(object, selected);
	Object *host = owner();
	if (disabled())
		return;
	if (contestHead()->m_next == contestHead())
		return;

	if (host->m_status & 8) {
		((Gen0021CE60 *)primary())->handle((int)object);
	} else {
		if (containHead()->m_next == containHead()) {
			((Rva0021D180 *)primary())->body();
			return;
		}

		host->setStatusBit(0x23, true);
		for (Rva0021D5D0Node *node = containHead()->m_next;
			node != containHead(); node = node->m_next)
			((Gen0021CE60 *)primary())->handle((int)node->m_object);

		for (Rva0021D5D0Node *node = contestHead()->m_next;
			node != contestHead(); node = node->m_next)
			((Gen0021CE60 *)primary())->handle((int)node->m_object);
	}

	((Rva0021D5D0WakeAccess *)primary())->wake(host);
	setNextFrame(TheGameLogic->m_frame);
}
