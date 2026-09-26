// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/stringinline
// Retail 0x00386910, 216 bytes. The carved boundary ends at ret 8.
// The add-ecx tail thunk at 0x00388730 proves the receiver offset, and the
// retail body proves two stack arguments. No semantic owner is proven, so the
// class and method keep the body address in their names.

#include "StringInline.h"

typedef bool Bool;
typedef int Int;

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

struct Rva00367E30Logic
{
	unsigned char m_pad_000[0x3c];
	unsigned int m_state_03c;
	unsigned char m_pad_040[0x10c - 0x40];
	Int m_mode_10c;
};
extern Rva00367E30Logic * volatile TheBfmeGameLogic;

class Glo00EF3330
{
public:
	void h004893E0();
	void h00489410();
};

class Rva004893D0ByteClear
{
public:
	void clear();
};

class GameWindowTransitionsHandler
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void update() = 0;
	void reverse(AsciiString groupName);
};
extern GameWindowTransitionsHandler *TheTransitionHandler;

class Rva00386910TransitionLock
{
public:
	Rva00386910TransitionLock()
	{
		if (TheTransitionHandler != 0)
			((Glo00EF3330 *)TheTransitionHandler)->h004893E0();
	}

	~Rva00386910TransitionLock()
	{
		if (TheTransitionHandler != 0)
			((Glo00EF3330 *)TheTransitionHandler)->h00489410();
	}
};

class Mouse
{
public:
	void _bfme_setEngineVisibility(Bool visible);
};
extern Mouse *TheMouse;

class Rva00386910
{
public:
	Int invoke(Int unused, Bool unusedFlag);

private:
	AsciiString m_groupName;
};

Int Rva00386910::invoke(Int unused, Bool unusedFlag)
{
	_ReadWriteBarrier();
	Int result = 1;
	register unsigned int state = TheBfmeGameLogic->m_state_03c;
	if (state > 6)
	{
		{
			Rva00386910TransitionLock lock;
			((Rva004893D0ByteClear *)TheTransitionHandler)->clear();
			TheTransitionHandler->update();
			TheTransitionHandler->reverse(AsciiString(m_groupName));
			TheTransitionHandler->update();
		}

		Int mode = TheBfmeGameLogic->m_mode_10c;
		if (mode >= 2 && (mode <= 3 || mode == 6))
		{
			TheMouse->_bfme_setEngineVisibility(true);
		}
		result = 3;
	}
	return result;
}
