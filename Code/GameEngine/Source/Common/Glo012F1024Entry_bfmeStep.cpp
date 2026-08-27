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

	char m_bfmeBody[0xDC];
};

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
};

extern Glo012F1028Type *Glo012F1028;				// 0x012F1028

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
