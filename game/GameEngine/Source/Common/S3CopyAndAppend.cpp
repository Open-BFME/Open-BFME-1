// Eight more bodies in two shapes.
//
// 0x003505E0, 0x00350630, 0x00351F30 and 0x00351FB0 are memberwise copy
// constructors. The widths give the layout away: two dwords, then a
// sub-object at +0x08 that has a copy constructor of its own so it is CALLED
// rather than moved, then a byte at +0x0C, a word at +0x0E -- with the byte of
// padding between them untouched, which is what natural alignment leaves --
// and a final dword at +0x10.
//
// 0x0014C700, 0x0034E260, 0x00439E00 and 0x004492A0 append to a list. The
// position is read from the head BEFORE the node is allocated, and the node's
// neighbour is read into a local before any of the four link stores, or the
// compiler cannot common it across them. Both calls are __cdecl and their
// twelve bytes of arguments are cleaned by one merged add esp,0xc.

void *bfmeAllocNode(unsigned int bytes);			// retail 0x0082E540

class BfmeSubA
{
public:
	BfmeSubA(const BfmeSubA &other);			// retail 0x00887C90

private:
	void *m_bfmeItem;
};

class BfmeSubB
{
public:
	BfmeSubB(const BfmeSubB &other);			// retail 0x00887B60

private:
	void *m_bfmeItem;
};

struct BfmeAppendValue
{
	char m_bfmeValue[8];
};

struct BfmeAppendNode
{
	BfmeAppendNode *m_bfmePrev;				// +0x00
	BfmeAppendNode *m_bfmeNext;				// +0x04
	BfmeAppendValue m_bfmeValue;				// +0x08
};

void bfmeConstructA(BfmeAppendValue *slot, void *source);	// ILT 0x0004031D
void bfmeConstructB(BfmeAppendValue *slot, void *source);	// ILT 0x00033FF5
void bfmeConstructC(BfmeAppendValue *slot, void *source);	// ILT 0x0000637A
void bfmeConstructD(BfmeAppendValue *slot, void *source);	// ILT 0x00033E15


class Gen_003505E0
{
public:
	Gen_003505E0(const Gen_003505E0 &other);

private:
	int m_bfmeFirst;					// +0x00
	int m_bfmeSecond;					// +0x04
	BfmeSubA m_bfmeSub;					// +0x08
	char m_bfmeFlag;					// +0x0C
	short m_bfmeCount;					// +0x0E
	int m_bfmeExtra;					// +0x10
};

class Gen_00350630
{
public:
	Gen_00350630(const Gen_00350630 &other);

private:
	int m_bfmeFirst;					// +0x00
	int m_bfmeSecond;					// +0x04
	BfmeSubA m_bfmeSub;					// +0x08
	char m_bfmeFlag;					// +0x0C
	short m_bfmeCount;					// +0x0E
	int m_bfmeExtra;					// +0x10
};

class Gen_00351F30
{
public:
	Gen_00351F30(const Gen_00351F30 &other);

private:
	int m_bfmeFirst;					// +0x00
	int m_bfmeSecond;					// +0x04
	BfmeSubB m_bfmeSub;					// +0x08
	char m_bfmeFlag;					// +0x0C
	short m_bfmeCount;					// +0x0E
	int m_bfmeExtra;					// +0x10
};

class Gen_00351FB0
{
public:
	Gen_00351FB0(const Gen_00351FB0 &other);

private:
	int m_bfmeFirst;					// +0x00
	int m_bfmeSecond;					// +0x04
	BfmeSubB m_bfmeSub;					// +0x08
	char m_bfmeFlag;					// +0x0C
	short m_bfmeCount;					// +0x0E
	int m_bfmeExtra;					// +0x10
};

class Gen_0014C700
{
public:
	void bfmeAppend(void *source);

private:
	BfmeAppendNode *m_bfmeHead;
};

class Gen_0034E260
{
public:
	void bfmeAppend(void *source);

private:
	BfmeAppendNode *m_bfmeHead;
};

class Gen_00439E00
{
public:
	void bfmeAppend(void *source);

private:
	BfmeAppendNode *m_bfmeHead;
};

class Gen_004492A0
{
public:
	void bfmeAppend(void *source);

private:
	BfmeAppendNode *m_bfmeHead;
};

// ??0Gen_003505E0@@QAE@ABV0@@Z
Gen_003505E0::Gen_003505E0(const Gen_003505E0 &other)
	: m_bfmeFirst(other.m_bfmeFirst)
	, m_bfmeSecond(other.m_bfmeSecond)
	, m_bfmeSub(other.m_bfmeSub)
	, m_bfmeFlag(other.m_bfmeFlag)
	, m_bfmeCount(other.m_bfmeCount)
	, m_bfmeExtra(other.m_bfmeExtra)
{
}

// ??0Gen_00350630@@QAE@ABV0@@Z
Gen_00350630::Gen_00350630(const Gen_00350630 &other)
	: m_bfmeFirst(other.m_bfmeFirst)
	, m_bfmeSecond(other.m_bfmeSecond)
	, m_bfmeSub(other.m_bfmeSub)
	, m_bfmeFlag(other.m_bfmeFlag)
	, m_bfmeCount(other.m_bfmeCount)
	, m_bfmeExtra(other.m_bfmeExtra)
{
}

// ??0Gen_00351F30@@QAE@ABV0@@Z
Gen_00351F30::Gen_00351F30(const Gen_00351F30 &other)
	: m_bfmeFirst(other.m_bfmeFirst)
	, m_bfmeSecond(other.m_bfmeSecond)
	, m_bfmeSub(other.m_bfmeSub)
	, m_bfmeFlag(other.m_bfmeFlag)
	, m_bfmeCount(other.m_bfmeCount)
	, m_bfmeExtra(other.m_bfmeExtra)
{
}

// ??0Gen_00351FB0@@QAE@ABV0@@Z
Gen_00351FB0::Gen_00351FB0(const Gen_00351FB0 &other)
	: m_bfmeFirst(other.m_bfmeFirst)
	, m_bfmeSecond(other.m_bfmeSecond)
	, m_bfmeSub(other.m_bfmeSub)
	, m_bfmeFlag(other.m_bfmeFlag)
	, m_bfmeCount(other.m_bfmeCount)
	, m_bfmeExtra(other.m_bfmeExtra)
{
}

// ?bfmeAppend@Gen_0014C700@@QAEXPAX@Z
void Gen_0014C700::bfmeAppend(void *source)
{
	BfmeAppendNode *position = m_bfmeHead->m_bfmePrev;
	BfmeAppendNode *node = (BfmeAppendNode *)bfmeAllocNode(sizeof(BfmeAppendNode));

	bfmeConstructA(&node->m_bfmeValue, source);

	BfmeAppendNode *following = position->m_bfmeNext;

	node->m_bfmePrev = position;
	node->m_bfmeNext = following;
	following->m_bfmePrev = node;
	position->m_bfmeNext = node;
}

// ?bfmeAppend@Gen_0034E260@@QAEXPAX@Z
void Gen_0034E260::bfmeAppend(void *source)
{
	BfmeAppendNode *position = m_bfmeHead->m_bfmePrev;
	BfmeAppendNode *node = (BfmeAppendNode *)bfmeAllocNode(sizeof(BfmeAppendNode));

	bfmeConstructB(&node->m_bfmeValue, source);

	BfmeAppendNode *following = position->m_bfmeNext;

	node->m_bfmePrev = position;
	node->m_bfmeNext = following;
	following->m_bfmePrev = node;
	position->m_bfmeNext = node;
}

// ?bfmeAppend@Gen_00439E00@@QAEXPAX@Z
void Gen_00439E00::bfmeAppend(void *source)
{
	BfmeAppendNode *position = m_bfmeHead->m_bfmePrev;
	BfmeAppendNode *node = (BfmeAppendNode *)bfmeAllocNode(sizeof(BfmeAppendNode));

	bfmeConstructC(&node->m_bfmeValue, source);

	BfmeAppendNode *following = position->m_bfmeNext;

	node->m_bfmePrev = position;
	node->m_bfmeNext = following;
	following->m_bfmePrev = node;
	position->m_bfmeNext = node;
}

// ?bfmeAppend@Gen_004492A0@@QAEXPAX@Z
void Gen_004492A0::bfmeAppend(void *source)
{
	BfmeAppendNode *position = m_bfmeHead->m_bfmePrev;
	BfmeAppendNode *node = (BfmeAppendNode *)bfmeAllocNode(sizeof(BfmeAppendNode));

	bfmeConstructD(&node->m_bfmeValue, source);

	BfmeAppendNode *following = position->m_bfmeNext;

	node->m_bfmePrev = position;
	node->m_bfmeNext = following;
	following->m_bfmePrev = node;
	position->m_bfmeNext = node;
}
