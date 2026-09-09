// ?j_0001eb9b@Glo012F1024Item@@QAEXXZ
// partial score=0.29 date=2026-09-09
// cl: /DNDEBUG /MD /EHsc /Ireference/shims/stringinline

#define AsciiString Glo012F1024ItemString
#include "StringInline.h"
#undef AsciiString

// Keep the pre-existing TU model used by the already-matched helpers.  The
// inline-header model below is deliberately a separate ABI-only type for the
// new address-derived calls, so those helpers retain their established
// AsciiString conversion and relocation spelling.
class AsciiString
{
public:
	~AsciiString(void);
	operator int(void) const { return (int)this; }

	char *m_bfmeData;
};

// Open-BFME5: Glo012F1024Entry::bfmeStep, retail 0x003A7320, 62 bytes. The body
// carried only a machine byte-dump row; the pin naming it went in with
// Glo012F1024Type::step at 0x003B3900, which tail-jumps into it on the entry
// its index selects.
//
// The counter at +0x08 moves on by one and is written back before anything
// else looks at it. Past the limit at +0x18 it is pulled back to the limit and
// that is all; otherwise the item the new counter names is entered -- items of
// 0xDC bytes from the array at +0x0C.
//
// Both arms then notify the sub-object at +0x28 of the global at 0x012F1028,
// and the notification is written out twice rather than shared: it is a tail
// jump in each arm, so there is no frame here at all.

typedef int Int;

class User;

class BfmeIntVector
{
public:
	unsigned int bfmeSize(void) const { return m_bfmeEnd - m_bfmeBegin; }

	int *m_bfmeBegin;
	int *m_bfmeEnd;
};

class BfmeElem4Vector
{
public:
	unsigned int bfmeSize(void) const { return m_bfmeEnd - m_bfmeBegin; }
	User **bfmeAt(unsigned int index) const { return m_bfmeBegin + index; }
	User **bfmeBegin(void) const { return m_bfmeBegin; }

	User **m_bfmeBegin;
	User **m_bfmeEnd;
};

class BfmeElem16
{
public:
	char m_bfmeBody[0x10];
};

class BfmeElem16Vector
{
public:
	unsigned int bfmeSize(void) const { return m_bfmeEnd - m_bfmeBegin; }

	BfmeElem16 *m_bfmeBegin;
	BfmeElem16 *m_bfmeEnd;
};

class BfmeElem20
{
public:
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

class BfmeFlag16
{
public:
	char m_bfmeHead[0x0C];
	unsigned char m_bfmeFlag;
	char m_bfmeTail[0x03];
};

class BfmeFlag16Vector
{
public:
	unsigned int bfmeSize(void) const { return m_bfmeEnd - m_bfmeBegin; }

	BfmeFlag16 *m_bfmeBegin;
	BfmeFlag16 *m_bfmeEnd;
};

class BfmeFlag24
{
public:
	char m_bfmeHead[0x08];
	unsigned char m_bfmeFlag;
	char m_bfmeTail[0x0F];
};

class BfmeFlag24Vector
{
public:
	unsigned int bfmeSize(void) const { return m_bfmeEnd - m_bfmeBegin; }

	BfmeFlag24 *m_bfmeBegin;
	BfmeFlag24 *m_bfmeEnd;
};

class BfmeFlag32
{
public:
	char m_bfmeHead[0x1C];
	unsigned char m_bfmeFlag;
	char m_bfmeTail[0x03];
};

class BfmeFlag32Vector
{
public:
	unsigned int bfmeSize(void) const { return m_bfmeEnd - m_bfmeBegin; }

	BfmeFlag32 *m_bfmeBegin;
	BfmeFlag32 *m_bfmeEnd;
};

class BfmeElem8
{
public:
	char m_bfmeBody[0x08];
};

class BfmeElem8Vector
{
public:
	unsigned int bfmeSize(void) const { return m_bfmeEnd - m_bfmeBegin; }

	BfmeElem8 *m_bfmeBegin;
	BfmeElem8 *m_bfmeEnd;
};

class BfmeElem12Rec
{
public:
	char m_bfmeBody[0x0C];
};

class BfmeElem12RecVector
{
public:
	unsigned int bfmeSize(void) const { return m_bfmeEnd - m_bfmeBegin; }

	BfmeElem12Rec *m_bfmeBegin;
	BfmeElem12Rec *m_bfmeEnd;
};

class BfmeElem12
{
public:
	BfmeElem8Vector m_bfmeInner;
	char m_bfmeTail[0x04];
};

class BfmeElem12Vector
{
public:
	unsigned int bfmeSize(void) const { return m_bfmeEnd - m_bfmeBegin; }

	BfmeElem12 *m_bfmeBegin;
	BfmeElem12 *m_bfmeEnd;
};

class BfmeSubA
{
public:
	BfmeSubA() : m_item(0) {}
	BfmeSubA(const BfmeSubA &other);
	~BfmeSubA();

private:
	void *m_item;
};

struct BfmeElem8Str
{
	int m_first;
	BfmeSubA m_name;
};

class BfmeElem8StrVector
{
public:
	unsigned int bfmeSize(void) const { return m_bfmeEnd - m_bfmeBegin; }

	BfmeElem8Str *m_bfmeBegin;
	BfmeElem8Str *m_bfmeEnd;
};

class Glo012F1024Item
{
public:
	void bfmeEnter(void);					// ILT 0x0000BC5D

	void j_0003152a(void);
	void j_000250d6(void);
	void j_0001eb9b(void);
	void j_0000df76(void);
	void j_00008053(void);
	void j_0000d1d4(void);
	void j_00010712(void);
	void j_0002d3e4(void);
	bool j_0000ca59(void);
	void j_0002a969(void);
	void j_00021f26(void);
	void j_0002eeec(void);
	void j_00019eca(void);
	void j_00040c32(void);
	void j_00036124(void);
	void j_00010bcc(void);

	char m_bfmeHead[0x08];
	BfmeElem8StrVector m_bfmeEarly;				// +0x08
	char m_bfmeHeadRest[0x38 - 0x10];
	BfmeIntVector m_bfmeItems;
	char m_bfmeMiddleA[0x44 - 0x40];
	BfmeElem4Vector m_bfmeNames;
	char m_bfmeMiddle[0x6C - 0x4C];
	BfmeElem20Vector m_bfmeTable;
	char m_bfmePad74[0x04];
	BfmeFlag32Vector m_bfmeFlag32;				// +0x78
	char m_bfmePad80[0x04];
	BfmeFlag24Vector m_bfmeFlag24;				// +0x84
	char m_bfmePad8C[0x04];
	BfmeElem20Vector m_bfmeFlag20;				// +0x90
	char m_bfmePad98[0x04];
	BfmeFlag16Vector m_bfmeFlag16;				// +0x9C
	char m_bfmeMiddleB[0xB4 - 0xA4];
	BfmeElem16Vector m_bfmeQueue;
	char m_bfmeMiddleC[0xC0 - 0xBC];
	BfmeElem12Vector m_bfmeOuter;
	char m_bfmePadC8[0x04];
	BfmeElem12RecVector m_bfmeLate;				// +0xCC
	char m_bfmeTail[0xDC - 0xD4];
};

class Gen_003C02B0
{
public:
	void bfmeRemove(int value);
};

// The five-byte ILTs below are generated, address-derived entry points.  The
// retail callers use them as thiscall return-by-value accessors even though
// their generated declarations intentionally have no arguments.  Keep the
// ABI view local to this TU instead of assigning an unproven semantic owner.
extern void j_0000556f(void);
extern void j_000357c4(void);
extern void j_00022ead(void);
extern void j_0002ce67(void);
extern void j_00032029(void);
extern void j_00048027(void);
extern void j_0001c03a(void);
extern void j_0001de99(void);
extern void j_0002c971(void);
extern void j_000493a5(void);

class Glo012F1028Type;
class BfmeGlobal_012f1024;

struct Glo012F1024ItemCoord2D
{
	Int m_x;
	Int m_y;
};

// Use member declarations only as an ABI view.  The alternatename targets are
// the generated ILTs above, so these address-derived methods do not claim a
// recovered lexical owner for any of the record or manager calls.
struct Glo012F1024ItemRecordCall
{
	Glo012F1024ItemString j_0000556f(void);
	Glo012F1024ItemString j_000357c4(void);
	Glo012F1024ItemString j_00022ead(void);
	Glo012F1024ItemString j_0002ce67(void);
	Glo012F1024ItemString j_00032029(void);
	Glo012F1024ItemCoord2D j_00048027(void);
	Glo012F1024ItemString j_0001de99(void);
	Glo012F1024ItemString j_0002c971(void);
};

#pragma comment(linker, "/alternatename:?j_0000556f@Glo012F1024ItemRecordCall@@QAE?AVGlo012F1024ItemString@@XZ=?j_0000556f@@YAXXZ")
#pragma comment(linker, "/alternatename:?j_000357c4@Glo012F1024ItemRecordCall@@QAE?AVGlo012F1024ItemString@@XZ=?j_000357c4@@YAXXZ")
#pragma comment(linker, "/alternatename:?j_00022ead@Glo012F1024ItemRecordCall@@QAE?AVGlo012F1024ItemString@@XZ=?j_00022ead@@YAXXZ")
#pragma comment(linker, "/alternatename:?j_0002ce67@Glo012F1024ItemRecordCall@@QAE?AVGlo012F1024ItemString@@XZ=?j_0002ce67@@YAXXZ")
#pragma comment(linker, "/alternatename:?j_00032029@Glo012F1024ItemRecordCall@@QAE?AVGlo012F1024ItemString@@XZ=?j_00032029@@YAXXZ")
#pragma comment(linker, "/alternatename:?j_00048027@Glo012F1024ItemRecordCall@@QAE?AUGlo012F1024ItemCoord2D@@XZ=?j_00048027@@YAXXZ")
#pragma comment(linker, "/alternatename:?j_0001de99@Glo012F1024ItemRecordCall@@QAE?AVGlo012F1024ItemString@@XZ=?j_0001de99@@YAXXZ")
#pragma comment(linker, "/alternatename:?j_0002c971@Glo012F1024ItemRecordCall@@QAE?AVGlo012F1024ItemString@@XZ=?j_0002c971@@YAXXZ")

struct Glo012F1028DispatchCall
{
	void j_0001c03a(const Glo012F1024ItemString &, const Glo012F1024ItemString &,
		const Glo012F1024ItemCoord2D &, const Glo012F1024ItemString &,
		const Glo012F1024ItemString &, const Glo012F1024ItemString &, int, int, int);
};

#pragma comment(linker, "/alternatename:?j_0001c03a@Glo012F1028DispatchCall@@QAEXABVGlo012F1024ItemString@@0ABUGlo012F1024ItemCoord2D@@000HHH@Z=?j_0001c03a@@YAXXZ")

struct Glo012F1024LivingWorldDispatchCall
{
	void j_000493a5(const Glo012F1024ItemString &, const Glo012F1024ItemString &,
		const Glo012F1024ItemString &);
};

#pragma comment(linker, "/alternatename:?j_000493a5@Glo012F1024LivingWorldDispatchCall@@QAEXABVGlo012F1024ItemString@@00@Z=?j_000493a5@@YAXXZ")

class User : public Glo012F1024Item
{
public:
	AsciiString GetName(void);
};

class BfmeGlobal_012f706c
{
public:
	void bfmeGoDGE(void *a, void *b);
};

extern BfmeGlobal_012f706c *g_bfmeGlobal_012f706c;

class BfmeGlobal_012f1024
{
public:
	void bfmeCall40F39(void *a, void *b, void *c, unsigned char d);
	void bfmeCall3426b(void *a, void *b, void *c);
	User *getUser(void *key);
};

extern BfmeGlobal_012f1024 *g_bfmeGlobal_012f1024;

class Gen_003bcb40
{
public:
	void m(int value);
};

extern Gen_003bcb40 *g_Gen003bcb40;

class Rva0060D5E0
{
public:
	void go(void);
};

extern Rva0060D5E0 *g_Rva0060D5E0;

class Gen_0060D600
{
public:
	void bfmeForward(void *value);
};

extern Gen_0060D600 *g_Gen0060D600;

class Rva0060D620
{
public:
	void go(void);
};

extern Rva0060D620 *g_Rva0060D620;

class Glo012F1028Sub
{
public:
	void bfmeNotify(void);					// ILT 0x0002DE89
	void j_00019c36(BfmeSubA &name, int flag);
};

class Glo012F1028Type
{
public:
	char m_bfmeHead[0x28];
	Glo012F1028Sub *m_bfmeSub;				// +0x28
	void j_00008c0b(void);
};

extern Glo012F1028Type *Glo012F1028;				// 0x012F1028

extern Gen_003C02B0 *Glo012F1028Remove;				// 0x012F1028

// ?j_0001eb9b@Glo012F1024Item@@QAEXXZ
void Glo012F1024Item::j_0001eb9b(void)
{
	char *item = (char *)this;
	char *begin = *(char **)(item + 0x20);
	int offset = 0;
	for (Int index = 0;
		index < (Int)((*(char **)(item + 0x24) - begin) / 0x30);
		++index)
	{
		char *record = begin + offset;
		Glo012F1024ItemRecordCall *recordCall =
			reinterpret_cast<Glo012F1024ItemRecordCall *>(record);

		Glo012F1024ItemString field28 = recordCall->j_0000556f();
		Glo012F1024ItemString field24 = recordCall->j_000357c4();
		Glo012F1024ItemString field20 = recordCall->j_00022ead();
		Glo012F1024ItemString field08 = recordCall->j_0002ce67();
		Glo012F1024ItemString field04 = recordCall->j_00032029();
		int flag2c = *(unsigned char *)(record + 0x2C);
		int flag19 = *(unsigned char *)(record + 0x19);
		int flag18 = *(unsigned char *)(record + 0x18);
		Glo012F1024ItemCoord2D coord = recordCall->j_00048027();

		reinterpret_cast<Glo012F1028DispatchCall *>(Glo012F1028)->j_0001c03a(
			field04, field08, coord, field20, field24, field28, flag18, flag19, flag2c);

		Glo012F1024ItemString field0c = recordCall->j_0001de99();
		Glo012F1024ItemString field04Again = recordCall->j_00032029();
		Glo012F1024ItemString field1c = recordCall->j_0002c971();
		reinterpret_cast<Glo012F1024LivingWorldDispatchCall *>(g_bfmeGlobal_012f1024)->j_000493a5(
			field1c, field04Again, field0c);

		offset += 0x30;
	}
}

// ?j_0003152a@Glo012F1024Item@@QAEXXZ
void Glo012F1024Item::j_0003152a(void)
{
	BfmeSubA tmp;
	Glo012F1028Type *global = Glo012F1028;
	if (global->m_bfmeSub != 0)
	{
		for (unsigned int index = 0; index < m_bfmeEarly.bfmeSize(); ++index)
		{
			BfmeElem8Str *begin = m_bfmeEarly.m_bfmeBegin;
			tmp.BfmeSubA::BfmeSubA(*(BfmeSubA *)((char *)begin + index * 8 + 4));
			Glo012F1028Type *again = Glo012F1028;
			Glo012F1028Sub *sub = again->m_bfmeSub;
			sub->j_00019c36(tmp, 1);
		}
	}
}

// ?j_00008053@Glo012F1024Item@@QAEXXZ
void Glo012F1024Item::j_00008053(void)
{
	for (unsigned int index = 0; index < m_bfmeItems.bfmeSize(); ++index)
		Glo012F1028Remove->bfmeRemove((int)(m_bfmeItems.m_bfmeBegin + index));
}

// ?j_00040c32@Glo012F1024Item@@QAEXXZ
void Glo012F1024Item::j_00040c32(void)
{
	for (unsigned int index = 0; index < m_bfmeQueue.bfmeSize(); ++index)
	{
		BfmeElem16 *position = m_bfmeQueue.m_bfmeBegin + index;
		g_bfmeGlobal_012f706c->bfmeGoDGE(position, (char *)position + 4);
	}
}

// ?j_0000ca59@Glo012F1024Item@@QAE_NXZ
bool Glo012F1024Item::j_0000ca59(void)
{
	for (unsigned int index = 0; index < m_bfmeFlag16.bfmeSize(); ++index)
		if (m_bfmeFlag16.m_bfmeBegin[index].m_bfmeFlag != 0)
			return true;

	for (unsigned int index = 0; index < m_bfmeFlag20.bfmeSize(); ++index)
		if (m_bfmeFlag20.m_bfmeBegin[index].m_bfmeByte != 0)
			return true;

	for (unsigned int index = 0; index < m_bfmeFlag32.bfmeSize(); ++index)
		if (m_bfmeFlag32.m_bfmeBegin[index].m_bfmeFlag != 0)
			return true;

	for (unsigned int index = 0; index < m_bfmeFlag24.bfmeSize(); ++index)
		if (m_bfmeFlag24.m_bfmeBegin[index].m_bfmeFlag != 0)
			return true;

	return false;
}

// ?j_0002d3e4@Glo012F1024Item@@QAEXXZ
void Glo012F1024Item::j_0002d3e4(void)
{
	for (unsigned int index = 0; index < m_bfmeTable.bfmeSize(); ++index)
	{
		g_bfmeGlobal_012f1024->bfmeCall40F39(
			(char *)(m_bfmeTable.m_bfmeBegin + index) + 4,
			(char *)(m_bfmeTable.m_bfmeBegin + index) + 0x0C,
			(char *)(m_bfmeTable.m_bfmeBegin + index) + 8,
			(m_bfmeTable.m_bfmeBegin + index)->m_bfmeByte);
	}
}

// ?j_00019eca@Glo012F1024Item@@QAEXXZ
void Glo012F1024Item::j_00019eca(void)
{
	for (unsigned int index = 0; index < m_bfmeNames.bfmeSize(); ++index)
	{
		User *user = g_bfmeGlobal_012f1024->getUser(m_bfmeNames.bfmeBegin() + index);
		if (user != 0)
		{
			g_Gen003bcb40->m(user->GetName());
			user->bfmeEnter();
		}
	}
}

// ?j_00010bcc@Glo012F1024Item@@QAEXXZ
void Glo012F1024Item::j_00010bcc(void)
{
	for (unsigned int index = 0; index < m_bfmeLate.bfmeSize(); ++index)
	{
		BfmeElem12Rec *position = m_bfmeLate.m_bfmeBegin + index;
		g_bfmeGlobal_012f1024->bfmeCall3426b(position, (char *)position + 4, (char *)position + 8);
	}
}

// ?j_00036124@Glo012F1024Item@@QAEXXZ
void Glo012F1024Item::j_00036124(void)
{
	if (m_bfmeOuter.bfmeSize() != 0)
	{
		g_Rva0060D5E0->go();

		for (unsigned int outer = 0; outer < m_bfmeOuter.bfmeSize(); ++outer)
		{
			BfmeElem12 *element = m_bfmeOuter.m_bfmeBegin + outer;
			for (unsigned int inner = 0; inner < element->m_bfmeInner.bfmeSize(); ++inner)
				g_Gen0060D600->bfmeForward(element->m_bfmeInner.m_bfmeBegin + inner);
		}

		g_Rva0060D620->go();
	}
}

class Glo012F1024Entry
{
public:
	void bfmeStep(void);

private:
	char m_bfmeHeadA[0x08];
	Int m_bfmeIndex;					// +0x08
	Glo012F1024Item *m_bfmeItems;				// +0x0C
	char m_bfmeHeadB[0x18 - 0x10];
	Int m_bfmeLimit;					// +0x18
};

// ?bfmeEnter@Glo012F1024Item@@QAEXXZ
void Glo012F1024Item::bfmeEnter(void)
{
	j_0003152a();
	j_000250d6();
	j_0001eb9b();
	j_0000df76();
	j_00008053();
	j_0000d1d4();
	j_00010712();
	j_0002d3e4();

	if (j_0000ca59())
		Glo012F1028->j_00008c0b();

	j_0002a969();
	j_00021f26();
	j_0002eeec();
	j_00019eca();
	j_00040c32();
	j_00036124();
	j_00010bcc();
}

// ?bfmeStep@Glo012F1024Entry@@QAEXXZ
void Glo012F1024Entry::bfmeStep(void)
{
	Int index = m_bfmeIndex + 1;
	Int limit = m_bfmeLimit;

	m_bfmeIndex = index;

	if (index > limit)
	{
		m_bfmeIndex = limit;
		Glo012F1028->m_bfmeSub->bfmeNotify();
	}
	else
	{
		m_bfmeItems[index].bfmeEnter();
		Glo012F1028->m_bfmeSub->bfmeNotify();
	}
}
