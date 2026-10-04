// Open-BFME5 conversions.

// The bump this body calls is at 0x009EB940, matched and defined as
// Rva009EB940Receiver::bump; the placeholder name here went back to it.
class Rva009EB940Receiver
{
public:
	void bump();
};

class BfmeThingURB
{
public:
	int bfmeGoURB();
	char m_bfmePad[4];
	int m_bfmeFlags;
};

int BfmeThingURB::bfmeGoURB()
{
	((Rva009EB940Receiver *)this)->bump();
	return (m_bfmeFlags & 0xff0000) == 0x30000;
}

extern char g_bfmeNameURC[];

// The formatter this constructor calls is at 0x007E8A80, matched and defined
// as BfmeThingUPB::bfmeGoUPB in BfmeConv1339.cpp; the placeholder name here
// went back to it, spelled exactly as that TU declares it.
class BfmeThingUPB
{
public:
	char bfmeGoUPB(void *a, char *out, void *c);
};

class BfmeSrcURC
{
public:
	char bfmeFillURC(void *a, char *out, void *n);
};

class BfmeThingURC
{
public:
	BfmeThingURC(BfmeSrcURC *p);
	BfmeSrcURC *m_bfmeOwner;
	char m_bfmeText[4];
};

BfmeThingURC::BfmeThingURC(BfmeSrcURC *p)
{
	m_bfmeOwner = p;
	((BfmeThingUPB *)p)->bfmeGoUPB(g_bfmeNameURC, m_bfmeText, (void *)0x40);
}

// The 0x0090C400 call is WW3D2's Get_Bits_Per_Pixel, whose argument is BFME's
// WW3DFormat -- which is D3DFORMAT, not Zero Hour's numbering; see the header
// comment of game/Libraries/Source/WWVegas/WW3D2/ww3dformat_bits.cpp, the one
// place that enumeration is spelled out.  Only its name is needed here to
// reference the definition the ledger owns, so it is forward declared.
enum WW3DFormat;
unsigned __fastcall Get_Bits_Per_Pixel(WW3DFormat format);

class BfmeThingURD
{
public:
	unsigned bfmeGoURD();
	char m_bfmePad[0x24];
	unsigned m_bfmeWidth;
	unsigned m_bfmeHeight;
	char m_bfmePad2[8];
	int m_bfmeMode;
	char m_bfmePad3[4];
	int m_bfmeFormat;
};

unsigned BfmeThingURD::bfmeGoURD()
{
	unsigned n = Get_Bits_Per_Pixel((WW3DFormat)m_bfmeFormat) * m_bfmeHeight * m_bfmeWidth >> 3;
	if (m_bfmeMode != 1)
		return n * 2 + 0x48;
	return n + 0x48;
}
