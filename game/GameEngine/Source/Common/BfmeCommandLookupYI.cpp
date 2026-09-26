// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the named-command lookup at retail 0x0058D990, 145 bytes.  The
// name is a function-local static: retail carries its one-time guard bit, its
// constructor and the atexit registration of the compiler-generated destructor
// thunk inside the body.

class AsciiStringYI
{
public:
	AsciiStringYI(const char *text);
	~AsciiStringYI(void);
};

class BfmeRegistryYI
{
public:
	void *bfmeFindYI(const AsciiStringYI &name);
	void bfmeUseYI(int mode, void *entry);
};

extern BfmeRegistryYI *g_bfmeRegistryYI;			// retail 0x012F33F8

// ?bfmeSelectYI@@YGXH@Z
void __stdcall bfmeSelectYI(int unused)
{
	if (g_bfmeRegistryYI == 0)
		return;

	static AsciiStringYI s_bfmeNameYI("NonCommand_SelectAllHeroes");

	void *entry = g_bfmeRegistryYI->bfmeFindYI(s_bfmeNameYI);

	if (entry != 0)
		g_bfmeRegistryYI->bfmeUseYI(0, entry);
}
