// ?j_0000df76@Glo012F1024Item@@QAEXXZ
// partial score=0.8 date=2026-09-01
// cl: /DNDEBUG /MD /EHsc

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

class AsciiString
{
public:
	~AsciiString(void);
	operator int(void) const { return (int)this; }

	char *m_bfmeData;
};

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

class BfmeElem32Pair
{
public:
	int m_bfmeX;
	int m_bfmeY;
};

struct ICoord2D
{
	int x;
	int y;
};

class BfmeElem32
{
public:
	AsciiString *getAt04(AsciiString *result);
	AsciiString *getAt14(AsciiString *result);
	AsciiString *getAt18(AsciiString *result);
	struct ICoord2D *getAt08(struct ICoord2D *result);

	char m_bfmeHead[0x04];
	AsciiString m_bfmeAt04;
	BfmeElem32Pair m_bfmeAt08;
	unsigned char m_bfmeAt10;
	char m_bfmePad11[0x03];
	AsciiString m_bfmeAt14;
	AsciiString m_bfmeAt18;
	int m_bfmeAt1C;
};

class BfmeElem32Vector
{
public:
	Int bfmeSize(void) const { return (Int)(m_bfmeEnd - m_bfmeBegin); }

	BfmeElem32 *m_bfmeBegin;
	BfmeElem32 *m_bfmeEnd;
};

class Glo012F1024Scratch
{
public:
	AsciiString m_bfmeAt04;
	AsciiString m_bfmeAt14;
	AsciiString m_bfmeAt18;
	ICoord2D m_bfmeAt08;
};

class Glo012F1024LoopState
{
public:
	Int m_bfmeOffset;
	Int m_bfmeIndex;
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

	char m_bfmeHead[0x2C];
	BfmeElem32Vector m_bfmeEntries;
	char m_bfmeHeadAfterEntries[0x38 - 0x34];
	BfmeIntVector m_bfmeItems;
	char m_bfmeMiddleA[0x44 - 0x40];
	BfmeElem4Vector m_bfmeNames;
	char m_bfmeMiddle[0x6C - 0x4C];
	BfmeElem20Vector m_bfmeTable;
	char m_bfmeMiddleB[0xB4 - 0x74];
	BfmeElem16Vector m_bfmeQueue;
	char m_bfmeMiddleC[0xC0 - 0xBC];
	BfmeElem12Vector m_bfmeOuter;
	char m_bfmeTail[0xDC - 0xC8];
};

class Gen_003C02B0
{
public:
	void bfmeRemove(int value);
};

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
};

class Glo012F1028Type
{
public:
	char m_bfmeHead[0x28];
	Glo012F1028Sub *m_bfmeSub;				// +0x28
	void j_00008c0b(void);
	bool apply(void *key, void *position, bool flag, void *second, void *first, int value);
};

extern Glo012F1028Type *Glo012F1028;				// 0x012F1028

extern Gen_003C02B0 *Glo012F1028Remove;				// 0x012F1028

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

// ?j_0000df76@Glo012F1024Item@@QAEXXZ present-unmatched
void Glo012F1024Item::j_0000df76(void)
{
	for (Int index = 0, offset = 0;
		 index < m_bfmeEntries.bfmeSize() / sizeof(BfmeElem32);
		 ++index, offset += sizeof(BfmeElem32))
	{
		BfmeElem32 *element = (BfmeElem32 *)((char *)m_bfmeEntries.m_bfmeBegin + offset);
		Glo012F1024Scratch scratch;

		AsciiString *first = element->getAt18(&scratch.m_bfmeAt18);
		AsciiString *second = element->getAt14(&scratch.m_bfmeAt14);
		AsciiString *third = element->getAt04(&scratch.m_bfmeAt04);

		Glo012F1028->apply(third, element->getAt08(&scratch.m_bfmeAt08), element->m_bfmeAt10,
			second, first, element->m_bfmeAt1C);
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
