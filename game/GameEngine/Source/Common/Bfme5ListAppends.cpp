// Six circular-list appends.
//
// Each reads the sentinel node out of the list its member points at, allocates
// a node, constructs the payload in place through a helper, and splices the
// node in ahead of the sentinel: next to the sentinel, prev to the sentinel's
// old prev, and the two neighbours pointed back at the node.
//
// The allocation size names the payload width -- eight bytes of links plus the
// value -- and the helper differs per element type. The predecessor is read
// before any of the four stores because none of them can alias it; writing it
// into a local first is what puts that load ahead of the splice.
//
// One body reaches its list through a member far into a large object rather
// than at offset zero, which costs the four extra bytes of displacement.

void *bfmeAllocNode(unsigned int bytes);			// retail 0x0082E540

void __cdecl bfmeConstructA(void *destination, void *source);	// retail 0x0003FDA5
void __cdecl bfmeConstructB(void *destination, void *source);	// retail 0x00030DAA
void __cdecl bfmeConstructC(void *destination, void *source);	// retail 0x00007554
void __cdecl bfmeConstructD(void *destination, void *source);	// retail 0x00030EF4
void __cdecl bfmeConstructE(void *destination, void *source);	// retail 0x00040AE3

struct BfmePayload3 { int m_bfmeWords[3]; };

struct BfmeLinkNode3
{
	BfmeLinkNode3 *m_bfmeNext;				// +0x00
	BfmeLinkNode3 *m_bfmePrev;				// +0x04
	BfmePayload3 m_bfmeValue;				// +0x08
};

struct BfmeLinkHead3 { BfmeLinkNode3 *m_bfmeHead; };

struct BfmePayload1 { int m_bfmeWords[1]; };

struct BfmeLinkNode1
{
	BfmeLinkNode1 *m_bfmeNext;				// +0x00
	BfmeLinkNode1 *m_bfmePrev;				// +0x04
	BfmePayload1 m_bfmeValue;				// +0x08
};

struct BfmeLinkHead1 { BfmeLinkNode1 *m_bfmeHead; };

struct BfmePayload4 { int m_bfmeWords[4]; };

struct BfmeLinkNode4
{
	BfmeLinkNode4 *m_bfmeNext;				// +0x00
	BfmeLinkNode4 *m_bfmePrev;				// +0x04
	BfmePayload4 m_bfmeValue;				// +0x08
};

struct BfmeLinkHead4 { BfmeLinkNode4 *m_bfmeHead; };

struct BfmePayload5 { int m_bfmeWords[5]; };

struct BfmeLinkNode5
{
	BfmeLinkNode5 *m_bfmeNext;				// +0x00
	BfmeLinkNode5 *m_bfmePrev;				// +0x04
	BfmePayload5 m_bfmeValue;				// +0x08
};

struct BfmeLinkHead5 { BfmeLinkNode5 *m_bfmeHead; };

class Gen_000BF340
{
public:
	void bfmeAppend(void *item);

private:
	BfmeLinkHead3 *m_bfmeList;				// +0x00
};

class Gen_001ADB10
{
public:
	void bfmeAppend(void *item);

private:
	BfmeLinkHead1 *m_bfmeList;				// +0x00
};

class Gen_0034DD50
{
public:
	void bfmeAppend(void *item);

private:
	BfmeLinkHead1 *m_bfmeList;				// +0x00
};

class Gen_0034E210
{
public:
	void bfmeAppend(void *item);

private:
	char m_bfmePad[0x17270];				// +0x00
	BfmeLinkHead1 *m_bfmeList;				// +0x17270
};

class Gen_0034E2A0
{
public:
	void bfmeAppend(void *item);

private:
	BfmeLinkHead4 *m_bfmeList;				// +0x00
};

class Gen_0076D1D0
{
public:
	void bfmeAppend(void *item);

private:
	BfmeLinkHead5 *m_bfmeList;				// +0x00
};

// ?bfmeAppend@Gen_000BF340@@QAEXPAX@Z
void Gen_000BF340::bfmeAppend(void *item)
{
	BfmeLinkNode3 *head = m_bfmeList->m_bfmeHead;
	BfmeLinkNode3 *node = (BfmeLinkNode3 *)bfmeAllocNode(sizeof(BfmeLinkNode3));

	bfmeConstructA(&node->m_bfmeValue, item);

	BfmeLinkNode3 *previous = head->m_bfmePrev;
	node->m_bfmeNext = head;
	node->m_bfmePrev = previous;
	previous->m_bfmeNext = node;
	head->m_bfmePrev = node;
}

// ?bfmeAppend@Gen_001ADB10@@QAEXPAX@Z
void Gen_001ADB10::bfmeAppend(void *item)
{
	BfmeLinkNode1 *head = m_bfmeList->m_bfmeHead;
	BfmeLinkNode1 *node = (BfmeLinkNode1 *)bfmeAllocNode(sizeof(BfmeLinkNode1));

	bfmeConstructB(&node->m_bfmeValue, item);

	BfmeLinkNode1 *previous = head->m_bfmePrev;
	node->m_bfmeNext = head;
	node->m_bfmePrev = previous;
	previous->m_bfmeNext = node;
	head->m_bfmePrev = node;
}

// ?bfmeAppend@Gen_0034DD50@@QAEXPAX@Z
void Gen_0034DD50::bfmeAppend(void *item)
{
	BfmeLinkNode1 *head = m_bfmeList->m_bfmeHead;
	BfmeLinkNode1 *node = (BfmeLinkNode1 *)bfmeAllocNode(sizeof(BfmeLinkNode1));

	bfmeConstructC(&node->m_bfmeValue, item);

	BfmeLinkNode1 *previous = head->m_bfmePrev;
	node->m_bfmeNext = head;
	node->m_bfmePrev = previous;
	previous->m_bfmeNext = node;
	head->m_bfmePrev = node;
}

// ?bfmeAppend@Gen_0034E210@@QAEXPAX@Z
void Gen_0034E210::bfmeAppend(void *item)
{
	BfmeLinkNode1 *head = m_bfmeList->m_bfmeHead;
	BfmeLinkNode1 *node = (BfmeLinkNode1 *)bfmeAllocNode(sizeof(BfmeLinkNode1));

	bfmeConstructC(&node->m_bfmeValue, item);

	BfmeLinkNode1 *previous = head->m_bfmePrev;
	node->m_bfmeNext = head;
	node->m_bfmePrev = previous;
	previous->m_bfmeNext = node;
	head->m_bfmePrev = node;
}

// ?bfmeAppend@Gen_0034E2A0@@QAEXPAX@Z
void Gen_0034E2A0::bfmeAppend(void *item)
{
	BfmeLinkNode4 *head = m_bfmeList->m_bfmeHead;
	BfmeLinkNode4 *node = (BfmeLinkNode4 *)bfmeAllocNode(sizeof(BfmeLinkNode4));

	bfmeConstructD(&node->m_bfmeValue, item);

	BfmeLinkNode4 *previous = head->m_bfmePrev;
	node->m_bfmeNext = head;
	node->m_bfmePrev = previous;
	previous->m_bfmeNext = node;
	head->m_bfmePrev = node;
}

// ?bfmeAppend@Gen_0076D1D0@@QAEXPAX@Z
void Gen_0076D1D0::bfmeAppend(void *item)
{
	BfmeLinkNode5 *head = m_bfmeList->m_bfmeHead;
	BfmeLinkNode5 *node = (BfmeLinkNode5 *)bfmeAllocNode(sizeof(BfmeLinkNode5));

	bfmeConstructE(&node->m_bfmeValue, item);

	BfmeLinkNode5 *previous = head->m_bfmePrev;
	node->m_bfmeNext = head;
	node->m_bfmePrev = previous;
	previous->m_bfmeNext = node;
	head->m_bfmePrev = node;
}
