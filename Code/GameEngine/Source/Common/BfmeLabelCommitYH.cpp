// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the label commit at retail 0x004D1080, 117 bytes.  The label
// arrives by value and is released at the end; the receiver for set is an
// embedded member of the global base, which is why its address is materialised
// with an add rather than folded into a displacement.

class AsciiStringYH
{
public:
	~AsciiStringYH(void);

	void set(const AsciiStringYH &other);
};

class BfmeBaseYH
{
public:
	char m_bfmePad000[0xB84];				// +0x000
	AsciiStringYH m_bfmeLabel;				// +0xB84
};

class BfmeThingYH
{
public:
	void bfmeNotifyYH(void);
};

class BfmeOtherYH
{
public:
	void bfmeRefreshYH(int mode);
};

extern BfmeBaseYH *g_bfmeBaseYH;				// retail 0x012ED5C8
extern BfmeThingYH *g_bfmeThingYH;				// retail 0x012F4B58
extern BfmeOtherYH *g_bfmeOtherYH;				// retail 0x012F19E8
extern bool g_bfmeDirtyYH;					// retail 0x012F3E6D

// ?bfmeCommitYH@@YAXVAsciiStringYH@@@Z
void __cdecl bfmeCommitYH(AsciiStringYH label)
{
	g_bfmeDirtyYH = true;

	AsciiStringYH *slot = &g_bfmeBaseYH->m_bfmeLabel;

	slot->set(label);

	g_bfmeThingYH->bfmeNotifyYH();

	if (g_bfmeOtherYH != 0)
		g_bfmeOtherYH->bfmeRefreshYH(0);
}
