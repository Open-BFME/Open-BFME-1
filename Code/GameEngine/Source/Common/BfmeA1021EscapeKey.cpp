// Open-BFME5: the BfmeA1021 escape-key handler at retail 0x0052CDA0, 99 bytes.
//
// The owning class is proven twice over. The body calls
// BfmeA1021::bfmeGo1021A (retail 0x0052CD70, already matched in
// BfmeConv1021.cpp) with ecx holding its own this pointer, so the two methods
// share a class at offset zero. It also reads the state word at this + 0xA8,
// the same field bfmeGo1021A writes 4 into, and it gives up when that field
// already reads 4.
//
// The two literals the sink call pushes read "CallChild" at VA 0x011053D4 and
// "EscapeKeyPressed" at VA 0x011063E4, so this handler tells the Apt movie
// that the player pressed escape and then closes the screen. The method's own
// retail name is not recovered, so the symbol keeps its address.
//
// Write the key-kind test as a switch, not as a term in the && chain. Both
// spellings emit the same movzx and dec, but the switch is what puts the owner
// pointer in eax and the sink pointer in ecx, which lets MSVC reload ecx with
// the manager after the last push. The && chain keeps the owner in ecx and the
// sink in edx and loads the manager before the pushes, 15 bytes out.

class BfmeMgr19E
{
public:
	void bfmeAddAI(void *owner, char *fmt, int argc, char *first, char *second,
		char *third, char *fourth, char *fifth);
};

extern BfmeMgr19E *g_mgr12F19E8;
extern char g_bfmeFmt1057[];
extern char g_bfmeEscAI[];

// The Apt sink pointer this owner hands to the manager; same +0x250 slot the
// matched BfmeStateXC and Rva00511260Owner views use.
class BfmeOwner1021
{
public:
	unsigned char m_bfmePad[0x250];
	void *m_bfmeSink;
};

class BfmeA1021
{
public:
	int bfmeKey0052CDA0(int unused, int code, unsigned char kind, unsigned char flags);
	void bfmeGo1021A(int unused);

	unsigned char m_bfmePad[0x34];
	BfmeOwner1021 *m_bfmeOwner;
	unsigned char m_bfmePad2[0xA8 - 0x38];
	int m_bfmeState;
};

int BfmeA1021::bfmeKey0052CDA0(int unused, int code, unsigned char kind, unsigned char flags)
{
	if (code == 0x15)
	{
		switch (kind)
		{
		case 1:
			if ((flags & 1) != 0 && m_bfmeState != 4)
			{
				g_mgr12F19E8->bfmeAddAI(m_bfmeOwner->m_bfmeSink, g_bfmeFmt1057, 1,
					g_bfmeEscAI, 0, 0, 0, 0);

				bfmeGo1021A(0);

				return 1;
			}
			break;
		}
	}

	return 0;
}
