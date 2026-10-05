// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the options command dispatch at retail 0x0058EED0, 227 bytes.
// Third body of the paired-static family after 0x0058ECA0 and 0x0058EDB0: the
// selector here is a live observer whose mode is one of two values.

class AsciiStringYV
{
public:
	AsciiStringYV(const char *text);

	~AsciiStringYV(void);
};

class GameLogic
{
public:
	char m_bfmePadYV[0x10c];
	int m_gameMode;
};

class ControlBar
{
public:
	void *bfmeFindYV(const AsciiStringYV &name);

	void bfmeUseYV(int mode, void *entry);
};

// The retail global at 0x012F0898 is EA's `GameLogic *TheGameLogic`, defined
// once in game/GameEngine/Source/GameLogic/System/GameLogic.cpp; this TU's
// GameLogic class above is its view of that layout and mangles identically.
extern GameLogic *TheGameLogic;
extern ControlBar *TheControlBar;			// retail 0x012F33F8

// ?bfmeOptionsYV@@YGXH@Z
void __stdcall bfmeOptionsYV(int unused)
{
	AsciiStringYV *name;

	if (TheGameLogic != 0
			&& (TheGameLogic->m_gameMode == 1 || TheGameLogic->m_gameMode == 5))
	{
		static AsciiStringYV s_bfmeMultiplayerYV("NonCommand_MultiplayerOptions");

		name = &s_bfmeMultiplayerYV;
	}
	else
	{
		static AsciiStringYV s_bfmeOptionsYV("NonCommand_Options");

		name = &s_bfmeOptionsYV;
	}

	void *entry = TheControlBar->bfmeFindYV(*name);

	if (entry != 0)
		TheControlBar->bfmeUseYV(0, entry);
}
