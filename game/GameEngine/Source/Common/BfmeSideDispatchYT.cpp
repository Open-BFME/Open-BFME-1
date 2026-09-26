// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the side-dependent command dispatch at retail 0x0058ECA0,
// 209 bytes.  Two function-local statics in one function share a single guard
// word, taking bit 0 and bit 1 in declaration order.

class AsciiStringYT
{
public:
	AsciiStringYT(const char *text);

	~AsciiStringYT(void);
};

class BfmeRegistryYT
{
public:
	void *bfmeFindYT(const AsciiStringYT &name);

	void bfmeUseYT(int mode, void *entry);
};

extern BfmeRegistryYT *g_bfmeRegistryYT;			// retail 0x012F33F8

class Gen_0058ECA0
{
public:
	void bfmeApplyYT(int unused);

	char m_bfmePad00[0x58];					// +0x00
	unsigned char m_bfmeFlags;				// +0x58
};

// ?bfmeApplyYT@Gen_0058ECA0@@QAEXH@Z
void Gen_0058ECA0::bfmeApplyYT(int unused)
{
	AsciiStringYT *name;

	if ((m_bfmeFlags & 4) != 0)
	{
		static AsciiStringYT s_bfmeEvilYT("NonCommand_EvilPlayerExperience");

		name = &s_bfmeEvilYT;
	}
	else
	{
		static AsciiStringYT s_bfmeGoodYT("NonCommand_GoodPlayerExperience");

		name = &s_bfmeGoodYT;
	}

	void *entry = g_bfmeRegistryYT->bfmeFindYT(*name);

	if (entry != 0)
		g_bfmeRegistryYT->bfmeUseYT(0, entry);
}
