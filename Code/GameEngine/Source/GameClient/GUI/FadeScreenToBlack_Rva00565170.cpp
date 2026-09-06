// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline
#include "StringInline.h"

// Open-BFME: transition-step function at retail 0x00565170 (96B). Same
// shape family as PreParchmentMapFade_LoadGame.cpp / SoloMordorFade_LoadGame.cpp:
// int f(int, bool start) -- on start, kick a transition group and poke two
// other singletons; on !start, poll isFinished(). Literal at 0x1109E30 is
// "FadeScreenToBlack". Callee 0x00042E6F pins isFinished@GameWindowTransitionsHandler,
// 0x00045C28 pins setGroup@BfmeRankTransitionHandler (name is a placeholder --
// same TheTransitionHandler object, cast to a different declared type per
// pinned mangled name), 0x0003D578 pins bfmeEnd1100@BfmeZ1100 (called on
// TheMouse), and the second TheTransitionHandler call (0x0000F1FF) resolves
// through its ILT thunk to the already-matched Rva004893C0ByteSetter::set()
// (sets a flag byte at +0x55).

class GameWindowTransitionsHandler
{
public:
	bool isFinished();
};
extern GameWindowTransitionsHandler *TheTransitionHandler;

class BfmeRankTransitionHandler
{
public:
	void setGroup(AsciiString name, int immediate);
};

struct Rva004893C0ByteSetter
{
	char m_padding[0x55];
	unsigned char m_flag;

	void set();
};

class BfmeZ1100
{
public:
	void bfmeEnd1100(int h);
};
extern BfmeZ1100 *TheMouse;

// ?rva00565170@@YAHH_N@Z
int rva00565170(int, bool start)
{
	int result = 1;

	if (start)
	{
		((BfmeRankTransitionHandler *)TheTransitionHandler)->setGroup(AsciiString("FadeScreenToBlack"), 0);
		((Rva004893C0ByteSetter *)TheTransitionHandler)->set();
		TheMouse->bfmeEnd1100(0);
	}
	else if (TheTransitionHandler->isFinished())
	{
		result = 3;
	}

	return result;
}
