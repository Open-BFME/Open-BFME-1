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

class BfmeObserverYV
{
public:
	char m_bfmePadYV[0x10c];
	int m_bfmeModeYV;
};

class BfmeRegistryYV
{
public:
	void *bfmeFindYV(const AsciiStringYV &name);

	void bfmeUseYV(int mode, void *entry);
};

extern BfmeObserverYV *g_bfmeObserverYV;			// retail 0x012F0898
extern BfmeRegistryYV *g_bfmeRegistryYV;			// retail 0x012F33F8

// ?bfmeOptionsYV@@YGXH@Z
void __stdcall bfmeOptionsYV(int unused)
{
	AsciiStringYV *name;

	if (g_bfmeObserverYV != 0
			&& (g_bfmeObserverYV->m_bfmeModeYV == 1 || g_bfmeObserverYV->m_bfmeModeYV == 5))
	{
		static AsciiStringYV s_bfmeMultiplayerYV("NonCommand_MultiplayerOptions");

		name = &s_bfmeMultiplayerYV;
	}
	else
	{
		static AsciiStringYV s_bfmeOptionsYV("NonCommand_Options");

		name = &s_bfmeOptionsYV;
	}

	void *entry = g_bfmeRegistryYV->bfmeFindYV(*name);

	if (entry != 0)
		g_bfmeRegistryYV->bfmeUseYV(0, entry);
}
