// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: BfmeQuickMatchScreenBase's constructor, retail 0x00470620, 86
// bytes. The body carried only a machine byte-dump row; reverse/reloc_names.csv
// holds the name with identity=real, and the member it ends with is pinned with
// this row.
//
// The vtable goes in, five fields from +0x04 out to the byte at +0x14 are
// cleared, and the argument is handed straight on. Only one of those five is
// written before the unwind state: that is the member whose destructor the
// frame exists for, and its constructor is nothing but the null. The rest are
// body assignments.

typedef int Int;

class BfmeQuickMatchSlot
{
public:
	BfmeQuickMatchSlot() { m_bfmePointer = 0; }
	~BfmeQuickMatchSlot();
	void set(const BfmeQuickMatchSlot &other);

private:
	void *m_bfmePointer;
};

struct BfmeQuickMatchNode
{
	BfmeQuickMatchNode *m_next;
	BfmeQuickMatchNode *m_previous;
	void *m_payload;
};

struct BfmeQuickMatchList
{
	BfmeQuickMatchNode *m_sentinel;
};

class BfmeQuickMatchScreen
{
public:
	char m_bfmeHead[0x04];
	Int m_bfme04;
	Int m_bfme08;
	Int m_bfme0C;
	char m_bfmePad[0x24 - 0x10];
	BfmeQuickMatchSlot m_bfmeString;
	BfmeQuickMatchList m_bfmeItems;
};

class BfmeQuickMatchScreenBase
{
public:
	BfmeQuickMatchScreenBase(void *screen);

	virtual void bfmeSlot0(void);
	virtual void bfmeSlot1(void);
	virtual void bfmeSlot2(void);
	virtual void bfmeSlot3(void);
	virtual void bfmeSlot4(void);
	virtual void bfmeSlot5(void);
	virtual void bfmeAdd(void *payload);

private:
	void bfmeAttach(void *screen);				// ILT 0x0000C0A4

	BfmeQuickMatchSlot m_bfmeSlot;				// +0x04
	Int m_bfme08;						// +0x08
	Int m_bfme0C;						// +0x0C
	Int m_bfme10;						// +0x10
	char m_bfme14;						// +0x14
	char m_bfmePad[0x18 - 0x15];
	Int m_bfme18;
	Int m_bfme1C;
	Int m_bfme20;
};

// ?bfmeAttach@BfmeQuickMatchScreenBase@@AAEXPAX@Z
void BfmeQuickMatchScreenBase::bfmeAttach(void *screen)
{
	m_bfme18 = ((BfmeQuickMatchScreen *)screen)->m_bfme04;
	m_bfme1C = ((BfmeQuickMatchScreen *)screen)->m_bfme08;
	m_bfme20 = ((BfmeQuickMatchScreen *)screen)->m_bfme0C;

	BfmeQuickMatchNode *node = ((BfmeQuickMatchScreen *)screen)->m_bfmeItems.m_sentinel->m_next;
	while (node != ((BfmeQuickMatchScreen *)screen)->m_bfmeItems.m_sentinel)
	{
		bfmeAdd(node->m_payload);
		node = node->m_next;
	}

	m_bfmeSlot.set(*(BfmeQuickMatchSlot *)((char *)screen + 0x24));
}

// ??0BfmeQuickMatchScreenBase@@QAE@PAX@Z
BfmeQuickMatchScreenBase::BfmeQuickMatchScreenBase(void *screen)
{
	m_bfme08 = 0;
	m_bfme0C = 0;
	m_bfme10 = 0;
	m_bfme14 = 0;

	bfmeAttach(screen);
}
