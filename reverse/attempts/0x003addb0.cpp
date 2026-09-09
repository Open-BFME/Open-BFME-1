// ?j_0002eeec@Glo012F1024Item@@QAEXXZ
// partial score=0.35 date=2026-09-10
// Identity: ILT thunk 0x0002EEEC (functions.csv d_0002eeec gen-thunk,
// target=FUN_007addb0) is called directly by bfmeEnter's tail sequence
// (Glo012F1024Entry_bfmeStep.cpp, matched, 0x003AEE70). Retail body is
// 224B (ghidra boundary 217 was short of the trailing ret).
//
// Same wall and same shape as j_00021f26 (see reverse/attempts/0x003adcc0.cpp):
// walks the +0x90 BfmeElem20Vector (20-byte records: char head[0x10];
// unsigned char byte; char tail[3];) instead of the 16-byte one. Per
// record: heap-allocate 16 bytes (push 0x10; call ??2@YAPAXI@Z), and on
// success construct with value dword at +4, ADDRESS of the dword at
// +0xC, and the flag byte at +0x10, via a DIFFERENT callee at retail VA
// 0x41407E (RVA 0x0001407E). The (possibly-null) item is always handed
// to the SAME Glo012F1028Type::j_00003f0d (RVA 0x00003F0D) used by
// j_00021f26.
//
// New pin landed clean (pin_consistency --check OK):
//   ??0Glo012F1024FlagCtor16B@@QAE@HPAXE@Z,0x0001407E
//
// THE WALL: identical to j_00021f26 -- retail's SEH prologue is Form B
// (mov eax,fs:[0] first); every source shape tried here compiles to
// Form A instead, and 'this'/byte-offset land in the opposite pair of
// callee-saved registers versus retail (edi/ebx swapped) with a
// different push grouping around the early-exit branch. Best result:
// 214/224, 173 non-reloc bytes differing per tools/probe.py. Making
// j_0002eeec a real Glo012F1024Item member does not disturb bfmeEnter's
// own matched 129B compile (checked after every edit).
//
// t=90min model=claude-sonnet-5 (shared session with 0x003adcc0)

// cl: /DNDEBUG /MD /EHsc

struct BfmeElem20
{
	char m_bfmeHead[0x10];
	unsigned char m_bfmeByte;
	char m_bfmeTail[0x03];
};

class BfmeElem20Vector
{
public:
	unsigned int bfmeSize(void) const { return m_bfmeEnd - m_bfmeBegin; }

	BfmeElem20 *m_bfmeBegin;
	BfmeElem20 *m_bfmeEnd;
};

class Glo012F1028Type
{
public:
	char m_bfmeHead[0x28];
	void *m_bfmeSub;
	void j_00003f0d(void *item);
};

extern Glo012F1028Type *Glo012F1028;

class Glo012F1024FlagCtor16B
{
public:
	Glo012F1024FlagCtor16B(int value, void *addr, unsigned char flag);
	char m_bfmeBody[0x10];
};

class Glo012F1024Item
{
public:
	void j_0002eeec(void);

	char m_bfmePad[0x90];
	BfmeElem20Vector m_bfmeFlag20;			// +0x90
};

void Glo012F1024Item::j_0002eeec(void)
{
	unsigned int index = 0;
	if (m_bfmeFlag20.bfmeSize() != 0)
	{
		do
		{
			BfmeElem20 *elem = m_bfmeFlag20.m_bfmeBegin + index;
			Glo012F1024FlagCtor16B *obj = new Glo012F1024FlagCtor16B(*(int *)((char *)elem + 4), (void *)((char *)elem + 0xC), elem->m_bfmeByte);
			void *item = 0;
			if (obj != 0)
				item = obj;
			Glo012F1028->j_00003f0d(item);
			++index;
		} while (index < m_bfmeFlag20.bfmeSize());
	}
}
