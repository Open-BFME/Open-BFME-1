// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the observer-dependent command dispatch at retail 0x0058EDB0,
// 228 bytes.  Same two-static shape as 0x0058ECA0, but the selector is a live
// observer plus a predicate call rather than a flag bit.

class AsciiStringYU
{
public:
	AsciiStringYU(const char *text);

	~AsciiStringYU(void);
};

class BfmeObserverYU
{
public:
	bool bfmeActiveYU(void);
};

class BfmeRegistryYU
{
public:
	void *bfmeFindYU(const AsciiStringYU &name);

	void bfmeUseYU(int mode, void *entry);
};

// The global at 0x012F33F8 is the ControlBar singleton; only the accessor
// spellings the method pins carry are needed here, so it stays incomplete.
class ControlBar;
class GameLogic;
extern GameLogic *TheGameLogic;				// retail 0x012F0898
extern ControlBar *TheControlBar;			// retail 0x012F33F8

// ?bfmeApplyYU@@YGXH@Z
void __stdcall bfmeApplyYU(int unused)
{
	AsciiStringYU *name;

	if (TheGameLogic != 0 && ((BfmeObserverYU *)TheGameLogic)->bfmeActiveYU())
	{
		static AsciiStringYU s_bfmeObjectivesYU("NonCommand_Objectives");

		name = &s_bfmeObjectivesYU;
	}
	else
	{
		static AsciiStringYU s_bfmeOtherYU("NonCommand_PlayerStatus");

		name = &s_bfmeOtherYU;
	}

	void *entry = reinterpret_cast<BfmeRegistryYU *>(TheControlBar)->bfmeFindYU(*name);

	if (entry != 0)
		reinterpret_cast<BfmeRegistryYU *>(TheControlBar)->bfmeUseYU(0, entry);
}
