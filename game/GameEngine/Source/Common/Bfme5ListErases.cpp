// Four list erases.
//
// Each unlinks a node, destroys the value it holds, frees the node, and hands
// back an iterator on the node that followed. The node's successor is read
// before anything is unlinked, because the two link stores would otherwise
// force it to be read again.
//
// The size handed to the deallocator is the whole node -- two links plus the
// value -- so it names the value width: 0x14, 0x18, 0x1C and 0x24 across the
// four. The result comes back through a hidden pointer, which is the first
// argument slot and is why the function cleans eight bytes for what looks like
// one parameter.

void __cdecl bfmeDeallocate(void *block, unsigned int bytes);	// retail 0x0082E5F0

class BfmeErasedValue_004EBC10
{
public:
	~BfmeErasedValue_004EBC10(void);			// retail 0x00021445

private:
	char m_bfmeBytes[0x18];
};

struct BfmeEraseNode_004EBC10
{
	BfmeEraseNode_004EBC10 *m_bfmeNext;			// +0x00
	BfmeEraseNode_004EBC10 *m_bfmePrev;			// +0x04
	BfmeErasedValue_004EBC10 m_bfmeValue;		// +0x08
};

class BfmeEraseIterator_004EBC10
{
public:
	BfmeEraseIterator_004EBC10(BfmeEraseNode_004EBC10 *node) : m_bfmeNode(node) {}

private:
	BfmeEraseNode_004EBC10 *m_bfmeNode;
};

class BfmeErasedValue_00627200
{
public:
	~BfmeErasedValue_00627200(void);			// retail 0x0003F95E

private:
	char m_bfmeBytes[0x1C];
};

struct BfmeEraseNode_00627200
{
	BfmeEraseNode_00627200 *m_bfmeNext;			// +0x00
	BfmeEraseNode_00627200 *m_bfmePrev;			// +0x04
	BfmeErasedValue_00627200 m_bfmeValue;		// +0x08
};

class BfmeEraseIterator_00627200
{
public:
	BfmeEraseIterator_00627200(BfmeEraseNode_00627200 *node) : m_bfmeNode(node) {}

private:
	BfmeEraseNode_00627200 *m_bfmeNode;
};

class BfmeErasedValue_0076A810
{
public:
	~BfmeErasedValue_0076A810(void);			// retail 0x0001C954

private:
	char m_bfmeBytes[0x14];
};

struct BfmeEraseNode_0076A810
{
	BfmeEraseNode_0076A810 *m_bfmeNext;			// +0x00
	BfmeEraseNode_0076A810 *m_bfmePrev;			// +0x04
	BfmeErasedValue_0076A810 m_bfmeValue;		// +0x08
};

class BfmeEraseIterator_0076A810
{
public:
	BfmeEraseIterator_0076A810(BfmeEraseNode_0076A810 *node) : m_bfmeNode(node) {}

private:
	BfmeEraseNode_0076A810 *m_bfmeNode;
};

class BfmeErasedValue_0076B2F0
{
public:
	~BfmeErasedValue_0076B2F0(void);			// retail 0x000205A9

private:
	char m_bfmeBytes[0x24];
};

struct BfmeEraseNode_0076B2F0
{
	BfmeEraseNode_0076B2F0 *m_bfmeNext;			// +0x00
	BfmeEraseNode_0076B2F0 *m_bfmePrev;			// +0x04
	BfmeErasedValue_0076B2F0 m_bfmeValue;		// +0x08
};

class BfmeEraseIterator_0076B2F0
{
public:
	BfmeEraseIterator_0076B2F0(BfmeEraseNode_0076B2F0 *node) : m_bfmeNode(node) {}

private:
	BfmeEraseNode_0076B2F0 *m_bfmeNode;
};

// ?bfmeErase_004EBC10@@YG?AVBfmeEraseIterator_004EBC10@@PAUBfmeEraseNode_004EBC10@@@Z
BfmeEraseIterator_004EBC10 __stdcall bfmeErase_004EBC10(BfmeEraseNode_004EBC10 *node)
{
	BfmeEraseNode_004EBC10 *next = node->m_bfmeNext;
	BfmeEraseNode_004EBC10 *previous = node->m_bfmePrev;

	previous->m_bfmeNext = next;
	next->m_bfmePrev = previous;

	node->m_bfmeValue.~BfmeErasedValue_004EBC10();

	bfmeDeallocate(node, sizeof(BfmeEraseNode_004EBC10));

	return BfmeEraseIterator_004EBC10(next);
}

// ?bfmeErase_00627200@@YG?AVBfmeEraseIterator_00627200@@PAUBfmeEraseNode_00627200@@@Z
BfmeEraseIterator_00627200 __stdcall bfmeErase_00627200(BfmeEraseNode_00627200 *node)
{
	BfmeEraseNode_00627200 *next = node->m_bfmeNext;
	BfmeEraseNode_00627200 *previous = node->m_bfmePrev;

	previous->m_bfmeNext = next;
	next->m_bfmePrev = previous;

	node->m_bfmeValue.~BfmeErasedValue_00627200();

	bfmeDeallocate(node, sizeof(BfmeEraseNode_00627200));

	return BfmeEraseIterator_00627200(next);
}

// ?bfmeErase_0076A810@@YG?AVBfmeEraseIterator_0076A810@@PAUBfmeEraseNode_0076A810@@@Z
BfmeEraseIterator_0076A810 __stdcall bfmeErase_0076A810(BfmeEraseNode_0076A810 *node)
{
	BfmeEraseNode_0076A810 *next = node->m_bfmeNext;
	BfmeEraseNode_0076A810 *previous = node->m_bfmePrev;

	previous->m_bfmeNext = next;
	next->m_bfmePrev = previous;

	node->m_bfmeValue.~BfmeErasedValue_0076A810();

	bfmeDeallocate(node, sizeof(BfmeEraseNode_0076A810));

	return BfmeEraseIterator_0076A810(next);
}

// ?bfmeErase_0076B2F0@@YG?AVBfmeEraseIterator_0076B2F0@@PAUBfmeEraseNode_0076B2F0@@@Z
BfmeEraseIterator_0076B2F0 __stdcall bfmeErase_0076B2F0(BfmeEraseNode_0076B2F0 *node)
{
	BfmeEraseNode_0076B2F0 *next = node->m_bfmeNext;
	BfmeEraseNode_0076B2F0 *previous = node->m_bfmePrev;

	previous->m_bfmeNext = next;
	next->m_bfmePrev = previous;

	node->m_bfmeValue.~BfmeErasedValue_0076B2F0();

	bfmeDeallocate(node, sizeof(BfmeEraseNode_0076B2F0));

	return BfmeEraseIterator_0076B2F0(next);
}
