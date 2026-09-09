// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline
#include "StringInline.h"

typedef int Int;

// Existing matched body at 0x006092D0.  This call is made with the same
// receiver and the two incoming integers; the target's thunk is an ILT for
// this already-owned method.
class Rva006092D0State
{
public:
	void setMode(Int mode, Int value);
};

class GameWindowTransitionsHandler
{
};
extern GameWindowTransitionsHandler *TheTransitionHandler;

class BfmeRankTransitionHandler
{
public:
	void setGroup(AsciiString name, Int immediate);
};

// The retail call is the existing alternate ILT for the matched byte setter
// at 0x004893C0.  The target receiver is the transition handler object.
class Rva004893C0ByteSetter
{
public:
	void set();
};

class Mouse
{
};
extern Mouse *TheMouse;

class BfmeZ1100
{
public:
	void bfmeEnd1100(Int height);
};

// The owner name is not recovered.  The retail object has a vtable and the
// fields touched here are proven by the target body: the mode state begins at
// +0x04, two reset fields are at +0xE4/+0xE8, and the fade value is +0x144.
// Five slots are declared because the mode-3 call is the fifth vtable entry
// (+0x10); no adjacent table entries are inferred or consumed.
class Rva006FEA60Owner
{
public:
	virtual void rva006fea60Slot00() = 0;
	virtual void rva006fea60Slot04() = 0;
	virtual void rva006fea60Slot08() = 0;
	virtual void rva006fea60Slot0C() = 0;
	virtual void rva006fea60Slot10(Int value) = 0;

	void rva006fea60(Int mode, Int value);

private:
	Int m_mode;
	char m_padding08[0xDC];
	Int m_resetE4;
	Int m_resetE8;
	char m_paddingEC[0x58];
	float m_fadeValue;
};

// ?rva006fea60@Rva006FEA60Owner@@QAEXHH@Z
void Rva006FEA60Owner::rva006fea60(Int mode, Int value)
{
	reinterpret_cast<Rva006092D0State *>(this)->setMode(mode, value);

	if (mode == 2)
	{
		m_fadeValue = 0.0f;
		((BfmeRankTransitionHandler *)TheTransitionHandler)->setGroup(
			AsciiString("FadeInGameMovie"), 0);
		((Rva004893C0ByteSetter *)TheTransitionHandler)->set();
		((BfmeZ1100 *)TheMouse)->bfmeEnd1100(0);
		return;
	}

	if (mode == 3)
	{
		m_fadeValue = 1.0f;
		m_resetE4 = 0;
		m_resetE8 = 0;
		rva006fea60Slot10(1);
	}
}
