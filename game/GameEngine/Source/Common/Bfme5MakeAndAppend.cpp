// A make-and-append body.
//
// It builds a forty-byte object with new, sets one of its fields, and hangs it
// off the end of the circular list its owner points at.
//
// The object's constructor is inlined, so the eleven field stores sit inside
// the null test that new does on its block -- and the field the constructor
// already set to four is set again afterwards, outside the test, because the
// assignment is a separate statement. The list append is the same inlined
// splice as elsewhere: a twelve-byte node, the value placement-constructed at
// +0x08 behind its own null test, and the predecessor cached before the four
// stores.

typedef bool Bool;

void *bfmeAllocNode(unsigned int bytes);			// retail 0x0082E540

inline void * __cdecl operator new(unsigned int, void *where) { return where; }

class BfmeMade
{
public:
	BfmeMade(void)
		: m_bfmeKind(4), m_bfmeA(0), m_bfmeB(0), m_bfmeC(false), m_bfmeD(false),
		  m_bfmeE(0), m_bfmeF(0), m_bfmeG(0), m_bfmeH(0), m_bfmeI(0), m_bfmeJ(0)
	{
	}

	int m_bfmeKind;						// +0x00
	int m_bfmeA;						// +0x04
	int m_bfmeB;						// +0x08
	Bool m_bfmeC;						// +0x0C
	Bool m_bfmeD;						// +0x0D
	int m_bfmeE;						// +0x10
	int m_bfmeF;						// +0x14
	int m_bfmeG;						// +0x18
	int m_bfmeH;						// +0x1C
	int m_bfmeI;						// +0x20
	int m_bfmeJ;						// +0x24
};

struct BfmeListHead
{
	BfmeListHead *m_bfmeNext;				// +0x00
	BfmeListHead *m_bfmePrev;				// +0x04
};

struct BfmeListNode
{
	BfmeListNode *m_bfmeNext;				// +0x00
	BfmeListNode *m_bfmePrev;				// +0x04
	BfmeMade *m_bfmeValue;					// +0x08
};

class Gen_0040D4A0
{
public:
	void bfmeAdd(void);

private:
	int m_bfmePad[2];					// +0x00
	BfmeListHead *m_bfmeList;				// +0x08
};

// ?bfmeAdd@Gen_0040D4A0@@QAEXXZ
void Gen_0040D4A0::bfmeAdd(void)
{
	BfmeMade *thing = new BfmeMade();

	thing->m_bfmeKind = 4;

	BfmeListHead *head = m_bfmeList;
	BfmeListNode *node = (BfmeListNode *)bfmeAllocNode(sizeof(BfmeListNode));

	new (&node->m_bfmeValue) BfmeMade *(thing);

	BfmeListHead *previous = head->m_bfmePrev;
	node->m_bfmeNext = (BfmeListNode *)head;
	node->m_bfmePrev = (BfmeListNode *)previous;
	previous->m_bfmeNext = (BfmeListHead *)node;
	head->m_bfmePrev = (BfmeListHead *)node;
}
