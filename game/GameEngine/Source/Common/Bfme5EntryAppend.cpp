// An entry make-and-append body.
//
// It news a twenty-byte entry, initialises a sub-object inside it, stores the
// second argument, and hangs the entry off the end of the list its owner keeps
// far into the object.
//
// The entry's constructor is inlined behind the null test new does: one store
// of the owner pointer offset by 0x70, then the three zeroes of the
// sub-object's own default constructor. The two statements that follow -- the
// sub-object's init and the extra store -- are outside the test, because a
// member call and a member store do not null-check.
//
// The append is the usual twelve-byte node splice with placement new at +0x08
// and the predecessor cached before the four stores.

void *bfmeAllocNode(unsigned int bytes);			// retail 0x0082E540

inline void * __cdecl operator new(unsigned int, void *where) { return where; }

class BfmeSub
{
public:
	BfmeSub(void) : m_bfmeA(0), m_bfmeB(0), m_bfmeC(0) {}

	void bfmeInit(void *value);				// retail 0x0000DF49

private:
	int m_bfmeA;						// +0x00
	int m_bfmeB;						// +0x04
	int m_bfmeC;						// +0x08
};

class BfmeEntry
{
public:
	BfmeEntry(void *owner) : m_bfmeOwner((char *)owner + 0x70) {}

	void *m_bfmeOwner;					// +0x00
	BfmeSub m_bfmeSub;					// +0x04
	void *m_bfmeExtra;					// +0x10
};

struct BfmeEntryHead
{
	BfmeEntryHead *m_bfmeNext;				// +0x00
	BfmeEntryHead *m_bfmePrev;				// +0x04
};

struct BfmeEntryNode
{
	BfmeEntryNode *m_bfmeNext;				// +0x00
	BfmeEntryNode *m_bfmePrev;				// +0x04
	BfmeEntry *m_bfmeValue;					// +0x08
};

class Gen_000D5E90
{
public:
	void bfmeAdd(void *owner, void *extra);

private:
	char m_bfmePad[0x640];					// +0x00
	BfmeEntryHead *m_bfmeList;				// +0x640
};

// ?bfmeAdd@Gen_000D5E90@@QAEXPAX0@Z
void Gen_000D5E90::bfmeAdd(void *owner, void *extra)
{
	BfmeEntry *entry = new BfmeEntry(owner);

	entry->m_bfmeSub.bfmeInit((char *)owner + 0x74);
	entry->m_bfmeExtra = extra;

	BfmeEntryHead *head = m_bfmeList;
	BfmeEntryNode *node = (BfmeEntryNode *)bfmeAllocNode(sizeof(BfmeEntryNode));

	new (&node->m_bfmeValue) BfmeEntry *(entry);

	BfmeEntryHead *previous = head->m_bfmePrev;
	node->m_bfmeNext = (BfmeEntryNode *)head;
	node->m_bfmePrev = (BfmeEntryNode *)previous;
	previous->m_bfmeNext = (BfmeEntryHead *)node;
	head->m_bfmePrev = (BfmeEntryHead *)node;
}
