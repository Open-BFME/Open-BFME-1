// ?invoke@Rva007E55F0Vp6Stream@@QAEDPBXHH@Z
// partial score=0.36 date=2026-09-21
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Open-BFME: anonymous carved body at 0x007E55F0 (439 bytes). The derived
// VP6 stream vtable at 0x01128DA8 proves this owns slot 19 of the same
// class as the landed Rva007E5420Vp6Stream::setAudio (setAudio.cpp) and
// Rva007E5820ImportCall.cpp neighbours; method name is not otherwise
// proven. Retail: resolve a string key through the (still dump-only)
// Rva007E3930StringState::_bfme_initialize_007E35E0, ask BfmeB996 whether
// this stream is one of "AVP6"/"MVhd" (FourCC constants, confirmed by
// reading the image), read a 0x18-byte video-format descriptor through
// Rva007E32A0State::dispatchWhenReady, copy its fields into this+0x30..
// +0x58, allocate a scratch block sized from that descriptor
// (bfmeMakeBlock), free the descriptor (operator delete[]), and build two
// codec states through bfmeInitCodecJX (BfmeConv2080.cpp) followed each by
// the still-unresolved d_009a4e50 reset call, finishing with two virtual
// calls (slot 8, slot 0x50) and a timestamp (+0x50) derived from
// g_bfmeNowVNH.

class Rva007E3930StringState
{
public:
	char _bfme_initialize_007E35E0(const char *name, int a, int b);
};

class BfmeDev996
{
public:
	virtual void bfmeVX0996();
	virtual void bfmeVX1996();
	virtual void bfmeVX2996();
	virtual void bfmeVX3996();
	virtual void bfmeVX4996();
	virtual void bfmeSet996(int a, int b);
};

class BfmeB996
{
public:
	char bfmeGo996B(int a, int b, char *c);
	void bfmeAdvance996();

private:
	char m_bfmePad[4];
	BfmeDev996 *m_bfmeDev;
	int m_bfmeKind;
};

class Rva007E32A0State
{
public:
	bool dispatchWhenReady(int first, int second, int third);
};

struct CodecState;

extern "C" int bfmeInitCodecJX(CodecState **p, int a, int b);
extern "C" void d_009a4e50(void *state, int a, int b);
extern "C" void *__cdecl bfmeMakeBlock(int tag, unsigned int size);
extern "C" void __cdecl operator delete[](void *p);
extern "C" int (__cdecl *g_bfmeNowVNH)();

struct Rva007E55F0FormatDesc
{
	unsigned char m_pad00[0xc];
	short m_width;
	short m_height;
	unsigned char m_pad10[4];
	int m_stride;
	unsigned char m_pad18[4];
	short m_bpp;
	unsigned char m_pad1e[2];
};

class Rva007E55F0Vp6Stream
{
public:
	char invoke(const void *nameHolder, int unused1, int unused2);

private:
	unsigned char m_pad00[0x14];
	CodecState *m_decodeState;
	CodecState *m_renderState;
	BfmeB996 m_b996;
	unsigned char m_pad28[0x30 - 0x28];
	int m_width;
	int m_height;
	unsigned char m_pad38[0x3c - 0x38];
	int m_stride;
	unsigned char m_pad40[0x44 - 0x40];
	int m_bpp;
	unsigned char m_pad48[0x54 - 0x48];
	void *m_scratch;
	int m_scratchSize;
};

// address-derived identity: vtable slot 19 of the VP6 stream class
char Rva007E55F0Vp6Stream::invoke(const void *nameHolder, int, int)
{
	const char *data = *(const char *const *)nameHolder;
	const char *name = data ? data + 8 : (const char *)0x0107388B;

	Rva007E3930StringState *state = (Rva007E3930StringState *)&m_b996;
	if (!state->_bfme_initialize_007E35E0(name, 1, 0))
		return 0;

	bool isSpecial = false;
	int first, second;
	char stop = 0;

	if (m_b996.bfmeGo996B((int)&first, (int)&second, &stop))
	{
		if (second == 0x36505641)
			isSpecial = true;
		else if (second != 0x6468564d)
		{
			m_b996.bfmeAdvance996();
			if (!m_b996.bfmeGo996B((int)&first, (int)&second, &stop))
				return 0;
		}
	}
	else
	{
		return 0;
	}

	int descAddr = 0;
	if (!((Rva007E32A0State *)&m_b996)->dispatchWhenReady((int)&descAddr,
		(int)&first, (int)&second))
		return 0;

	Rva007E55F0FormatDesc *desc = (Rva007E55F0FormatDesc *)descAddr;
	if (!desc)
		return 0;
	if (*(int *)((char *)desc + 4) - 8 != 0x18)
		return 0;

	m_width = desc->m_width;
	m_height = desc->m_height;
	m_stride = desc->m_stride;
	m_bpp = *(int *)((char *)desc + 0x18);
	int align = (*(int *)((char *)desc + 0x14) + 3) & ~3;
	m_scratchSize = align + 8;

	operator delete[](desc);

	m_scratch = bfmeMakeBlock(0, m_scratchSize);

	bfmeInitCodecJX(&m_decodeState, m_width, m_height);
	d_009a4e50(*(void **)&m_decodeState, 0, 0);

	if (isSpecial)
	{
		bfmeInitCodecJX(&m_renderState, m_height, m_width);
		d_009a4e50(*(void **)&m_renderState, 0, 0);
	}

	return 1;
}
