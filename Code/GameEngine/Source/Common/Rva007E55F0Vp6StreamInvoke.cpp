// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
//
// Open-BFME: anonymous carved body at 0x007E55F0 (439 bytes). Slot 19
// (+0x4c) of the VP6 stream vtable at 0x01128DA8 (pinned
// ??_7Rva007E3C20Vp6Stream@@6B@, stored by the landed destructor 0x007E3C20)
// reaches this body through ILT 0x0000F6EB; the method name is not otherwise
// proven. Retail: open the named file through the +0x1C parser object
// (0x007E35E0 via ILT 0x00005C0E; every return path of that body sets al),
// walk its chunks with BfmeB996::bfmeGo996B/bfmeAdvance996 until the
// 'MVhd' chunk (noting an 'AVP6' chunk on the way), read that chunk through
// Rva007E32A0State::dispatchWhenReady, copy its 0x18-byte payload into
// +0x30..+0x44 and +0x58, free it, allocate the +0x54 block, build one or two
// codec states through bfmeInitCodecJX each followed by the dump-only
// 0x009A4E50, then vslot 2, vslot 20 and a timeGetTime-based +0x50 stamp.

#include "ascii_string.h"

// Retail's empty-string sentinel: `mov eax, 0x107388b` at +0x16 is a DIR32
// relocation to ?Rva006A16B0Empty@@3PADA (reverse/symbols.csv, 0x0107388B).
extern char Rva006A16B0Empty[];

class Rva007E3C20Vp6Stream;

// Retail 0x007E35E0 returns al on every path (mov al,bl / mov al,1 before
// each ret 0xc), but the ledger pin still spells it void; the caller here
// tests al, so it is reached through a member-pointer cast.
class Rva007E3930StringState
{
	friend class Rva007E3C20Vp6Stream;

private:
	void _bfme_initialize_007E35E0(const char *text, int valueA, int valueB);
};

class BfmeDev996;

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

int bfmeInitCodecJX(CodecState **p, int a, int b);
void d_009a4e50();
void *bfmeMakeBlock(int tag, unsigned int size);
void operator delete[](void *p);
extern int (__cdecl *g_bfmeNowVNH)();

// The block dispatchWhenReady hands back: +0x04 must equal 0x18 + 8, and
// the fields read below end at +0x1e.
struct Rva007E55F0FormatDesc
{
	int m_dword00;
	int m_dword04;
	int m_dword08;
	short m_width;
	short m_height;
	int m_dword10;
	int m_stride;
	int m_dword18;
	short m_bpp;
	short m_word1e;
};

class Gen_0081E480
{
public:
	virtual ~Gen_0081E480(void);
	int m_count;
	int m_first;
	int m_second;
	int m_flags;
};

class Rva007E3C20Vp6Stream : public Gen_0081E480
{
public:
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual char invoke(const AsciiString &name, int value, bool flag);
	virtual int slot20(int value);

private:
	CodecState *m_decodeState;
	CodecState *m_renderState;
	BfmeB996 m_b996;
	unsigned char m_pad28[0x30 - 0x28];
	int m_width;
	int m_height;
	bool m_flag38;
	int m_stride;
	int m_dword40;
	int m_bpp;
	int m_dword48;
	int m_dword4c;
	int m_dword50;
	void *m_scratch;
	int m_scratchSize;
};

typedef char (Rva007E3930StringState::*Rva007E55F0OpenFn)(const char *, int, int);

// address-derived identity: vtable slot 19 of the VP6 stream class
char Rva007E3C20Vp6Stream::invoke(const AsciiString &name, int value, bool flag)
{
	const char *text = *reinterpret_cast<const char *const *>(&name);
	text = text ? text + 8 : Rva006A16B0Empty;

	Rva007E55F0OpenFn open = reinterpret_cast<Rva007E55F0OpenFn>(
		&Rva007E3930StringState::_bfme_initialize_007E35E0);
	if (!(((Rva007E3930StringState *)&m_b996)->*open)(text, 1, 0))
		return 0;

	int id;
	Rva007E55F0FormatDesc *desc = 0;
	int size;
	char stop;
	bool isAvp6 = false;

	while (m_b996.bfmeGo996B((int)&id, (int)&size, &stop))
	{
		if (id == 0x36505641)
			isAvp6 = true;
		else if (id == 0x6468564d)
		{
			((Rva007E32A0State *)&m_b996)->dispatchWhenReady((int)&desc,
				(int)&id, (int)&size);
			break;
		}
		m_b996.bfmeAdvance996();
	}

	if (desc && desc->m_dword04 - 8 == 0x18)
	{
		m_width = desc->m_width;
		m_height = desc->m_height;
		m_stride = desc->m_dword10;
		m_dword40 = desc->m_dword18;
		m_bpp = desc->m_bpp;
		m_scratchSize = ((desc->m_stride + 3) & ~3) + 8;
		delete[] desc;
		desc = 0;

		m_scratch = bfmeMakeBlock(0, m_scratchSize);

		bfmeInitCodecJX(&m_decodeState, m_width, m_height);
		((void (__cdecl *)(CodecState *, int, int))d_009a4e50)(m_decodeState, 0, 0);

		m_flag38 = isAvp6 && flag;
		if (m_flag38)
		{
			bfmeInitCodecJX(&m_renderState, m_width, m_height);
			((void (__cdecl *)(CodecState *, int, int))d_009a4e50)(m_renderState, 0, 0);
		}

		slot02();
		m_dword50 = -slot20(value);
		m_dword50 += g_bfmeNowVNH();
		m_dword48 = -1;
		m_dword4c = -1;
		return 1;
	}

	return 0;
}
