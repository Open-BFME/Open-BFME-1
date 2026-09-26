// Six more bodies in two shapes.
//
// 0x00528F10, 0x0054ED90 and 0x0056E1E0 return a whole object: the first stack
// argument is a hidden return pointer -- which is why the source object is
// read from [esp+8] and the answer is stored through [esp+0xc] -- so the class
// has to be wider than eight bytes or the compiler would hand it back in
// edx:eax instead. Only the dword at +0x04 is written; the rest of the result
// is left alone, which is what a named return value with a single assignment
// gives.
//
// 0x0046A070, 0x0046B1C0 and 0x00927760 allocate sixteen bytes, clear the
// first dword, and initialise the sub-object at +0x04. Both calls are __cdecl
// and their arguments are cleaned by ONE add esp,0xc afterwards, which the
// compiler merges because nothing between them needs the stack settled.

void *bfmeAllocNode(unsigned int bytes);			// retail 0x0082E540

unsigned int bfmeHashCombineA(unsigned int left, unsigned int right);	// ILT 0x00042FA0
unsigned int bfmeHashCombineB(unsigned int left, unsigned int right);	// ILT 0x00023254
unsigned int bfmeHashCombineC(unsigned int left, unsigned int right);	// ILT 0x0003F7CE

struct BfmeNodeBody
{
	char m_bfmeBody[0x0C];
};

void bfmeInitBodyA(BfmeNodeBody *body, void *source);		// ILT 0x000012D5
void bfmeInitBodyB(BfmeNodeBody *body, void *source);		// ILT 0x0000C568
void bfmeInitBodyC(BfmeNodeBody *body, void *source);		// retail 0x00926750

struct BfmeNode
{
	void *m_bfmeNext;					// +0x00
	BfmeNodeBody m_bfmeBody;				// +0x04
};


class Gen_00528F10
{
public:
	Gen_00528F10 bfmeCombine(const Gen_00528F10 &other) const;

	Gen_00528F10(unsigned int value) { m_bfmeValue = value; }

private:
	char m_bfmeHead[4];
	unsigned int m_bfmeValue;				// +0x04
	char m_bfmeTail[4];
};

class Gen_0054ED90
{
public:
	Gen_0054ED90 bfmeCombine(const Gen_0054ED90 &other) const;

	Gen_0054ED90(unsigned int value) { m_bfmeValue = value; }

private:
	char m_bfmeHead[4];
	unsigned int m_bfmeValue;				// +0x04
	char m_bfmeTail[4];
};

class Gen_0056E1E0
{
public:
	Gen_0056E1E0 bfmeCombine(const Gen_0056E1E0 &other) const;

	Gen_0056E1E0(unsigned int value) { m_bfmeValue = value; }

private:
	char m_bfmeHead[4];
	unsigned int m_bfmeValue;				// +0x04
	char m_bfmeTail[4];
};

// ?bfmeCombine@Gen_00528F10@@QBE?AV1@ABV1@@Z
Gen_00528F10 Gen_00528F10::bfmeCombine(const Gen_00528F10 &other) const
{
	unsigned int theirs = other.m_bfmeValue;
	unsigned int mine = m_bfmeValue;

	return Gen_00528F10(bfmeHashCombineA(mine, theirs));
}

// ?bfmeCombine@Gen_0054ED90@@QBE?AV1@ABV1@@Z
Gen_0054ED90 Gen_0054ED90::bfmeCombine(const Gen_0054ED90 &other) const
{
	unsigned int theirs = other.m_bfmeValue;
	unsigned int mine = m_bfmeValue;

	return Gen_0054ED90(bfmeHashCombineB(mine, theirs));
}

// ?bfmeCombine@Gen_0056E1E0@@QBE?AV1@ABV1@@Z
Gen_0056E1E0 Gen_0056E1E0::bfmeCombine(const Gen_0056E1E0 &other) const
{
	unsigned int theirs = other.m_bfmeValue;
	unsigned int mine = m_bfmeValue;

	return Gen_0056E1E0(bfmeHashCombineC(mine, theirs));
}

// ?bfmeMakeNode_0046A070@@YGPAUBfmeNode@@PAX@Z
BfmeNode *__stdcall bfmeMakeNode_0046A070(void *source)
{
	BfmeNode *node = (BfmeNode *)bfmeAllocNode(sizeof(BfmeNode));

	node->m_bfmeNext = 0;
	bfmeInitBodyA(&node->m_bfmeBody, source);

	return node;
}

// ?bfmeMakeNode_0046B1C0@@YGPAUBfmeNode@@PAX@Z
BfmeNode *__stdcall bfmeMakeNode_0046B1C0(void *source)
{
	BfmeNode *node = (BfmeNode *)bfmeAllocNode(sizeof(BfmeNode));

	node->m_bfmeNext = 0;
	bfmeInitBodyB(&node->m_bfmeBody, source);

	return node;
}

// ?bfmeMakeNode_00927760@@YGPAUBfmeNode@@PAX@Z
BfmeNode *__stdcall bfmeMakeNode_00927760(void *source)
{
	BfmeNode *node = (BfmeNode *)bfmeAllocNode(sizeof(BfmeNode));

	node->m_bfmeNext = 0;
	bfmeInitBodyC(&node->m_bfmeBody, source);

	return node;
}
