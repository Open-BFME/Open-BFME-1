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

extern BfmeObserverYU *g_bfmeObserverYU;			// retail 0x012F0898
extern BfmeRegistryYU *g_bfmeRegistryYU;			// retail 0x012F33F8

// ?bfmeApplyYU@@YGXH@Z
void __stdcall bfmeApplyYU(int unused)
{
	AsciiStringYU *name;

	if (g_bfmeObserverYU != 0 && g_bfmeObserverYU->bfmeActiveYU())
	{
		static AsciiStringYU s_bfmeObjectivesYU("NonCommand_Objectives");

		name = &s_bfmeObjectivesYU;
	}
	else
	{
		static AsciiStringYU s_bfmeOtherYU("NonCommand_PlayerStatus");

		name = &s_bfmeOtherYU;
	}

	void *entry = g_bfmeRegistryYU->bfmeFindYU(*name);

	if (entry != 0)
		g_bfmeRegistryYU->bfmeUseYU(0, entry);
}
