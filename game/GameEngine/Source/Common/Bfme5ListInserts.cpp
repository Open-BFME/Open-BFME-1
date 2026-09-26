// Five list inserts that copy a two-word value into a fresh node.
//
// The node is sixteen bytes: two links and the value at +0x08. The address of
// that value is computed first and then tested for null before the copy runs
// -- that null test on a member address is placement new, whose operator
// returns the pointer it was handed and which MSVC guards before constructing.
// A plain assignment through the member instead emits a conditional select and
// is seven bytes longer.
//
// The predecessor is read into a local before the four splice stores; reading
// it through the position again forces a reload after the first store, since
// the compiler cannot prove the node and the position are disjoint.
//
// The result is returned through a hidden pointer because the iterator has a
// constructor, and the first argument slot is that pointer, which is why the
// function returns it and cleans twelve bytes.

void *bfmeAllocNode(unsigned int bytes);			// retail 0x0082E540

inline void * __cdecl operator new(unsigned int, void *where) { return where; }


struct BfmeValue_000CF2F0 { void *m_bfmeA; void *m_bfmeB; };

struct BfmeNode_000CF2F0
{
	BfmeNode_000CF2F0 *m_bfmeNext;			// +0x00
	BfmeNode_000CF2F0 *m_bfmePrev;			// +0x04
	BfmeValue_000CF2F0 m_bfmeValue;			// +0x08
};

class BfmeIterator_000CF2F0
{
public:
	BfmeIterator_000CF2F0(BfmeNode_000CF2F0 *node) : m_bfmeNode(node) {}

private:
	BfmeNode_000CF2F0 *m_bfmeNode;
};

struct BfmeValue_0010E2D0 { void *m_bfmeA; void *m_bfmeB; };

struct BfmeNode_0010E2D0
{
	BfmeNode_0010E2D0 *m_bfmeNext;			// +0x00
	BfmeNode_0010E2D0 *m_bfmePrev;			// +0x04
	BfmeValue_0010E2D0 m_bfmeValue;			// +0x08
};

class BfmeIterator_0010E2D0
{
public:
	BfmeIterator_0010E2D0(BfmeNode_0010E2D0 *node) : m_bfmeNode(node) {}

private:
	BfmeNode_0010E2D0 *m_bfmeNode;
};

struct BfmeValue_00151AB0 { void *m_bfmeA; void *m_bfmeB; };

struct BfmeNode_00151AB0
{
	BfmeNode_00151AB0 *m_bfmeNext;			// +0x00
	BfmeNode_00151AB0 *m_bfmePrev;			// +0x04
	BfmeValue_00151AB0 m_bfmeValue;			// +0x08
};

class BfmeIterator_00151AB0
{
public:
	BfmeIterator_00151AB0(BfmeNode_00151AB0 *node) : m_bfmeNode(node) {}

private:
	BfmeNode_00151AB0 *m_bfmeNode;
};

struct BfmeValue_00251010 { void *m_bfmeA; void *m_bfmeB; };

struct BfmeNode_00251010
{
	BfmeNode_00251010 *m_bfmeNext;			// +0x00
	BfmeNode_00251010 *m_bfmePrev;			// +0x04
	BfmeValue_00251010 m_bfmeValue;			// +0x08
};

class BfmeIterator_00251010
{
public:
	BfmeIterator_00251010(BfmeNode_00251010 *node) : m_bfmeNode(node) {}

private:
	BfmeNode_00251010 *m_bfmeNode;
};

struct BfmeValue_00440480 { void *m_bfmeA; void *m_bfmeB; };

struct BfmeNode_00440480
{
	BfmeNode_00440480 *m_bfmeNext;			// +0x00
	BfmeNode_00440480 *m_bfmePrev;			// +0x04
	BfmeValue_00440480 m_bfmeValue;			// +0x08
};

class BfmeIterator_00440480
{
public:
	BfmeIterator_00440480(BfmeNode_00440480 *node) : m_bfmeNode(node) {}

private:
	BfmeNode_00440480 *m_bfmeNode;
};

// ?bfmeInsert_000CF2F0@@YG?AVBfmeIterator_000CF2F0@@PAUBfmeNode_000CF2F0@@ABUBfmeValue_000CF2F0@@@Z
BfmeIterator_000CF2F0 __stdcall bfmeInsert_000CF2F0(BfmeNode_000CF2F0 *position, const BfmeValue_000CF2F0 &value)
{
	BfmeNode_000CF2F0 *node = (BfmeNode_000CF2F0 *)bfmeAllocNode(sizeof(BfmeNode_000CF2F0));

	new (&node->m_bfmeValue) BfmeValue_000CF2F0(value);

	BfmeNode_000CF2F0 *previous = position->m_bfmePrev;
	node->m_bfmeNext = position;
	node->m_bfmePrev = previous;
	previous->m_bfmeNext = node;
	position->m_bfmePrev = node;

	return BfmeIterator_000CF2F0(node);
}

// ?bfmeInsert_0010E2D0@@YG?AVBfmeIterator_0010E2D0@@PAUBfmeNode_0010E2D0@@ABUBfmeValue_0010E2D0@@@Z
BfmeIterator_0010E2D0 __stdcall bfmeInsert_0010E2D0(BfmeNode_0010E2D0 *position, const BfmeValue_0010E2D0 &value)
{
	BfmeNode_0010E2D0 *node = (BfmeNode_0010E2D0 *)bfmeAllocNode(sizeof(BfmeNode_0010E2D0));

	new (&node->m_bfmeValue) BfmeValue_0010E2D0(value);

	BfmeNode_0010E2D0 *previous = position->m_bfmePrev;
	node->m_bfmeNext = position;
	node->m_bfmePrev = previous;
	previous->m_bfmeNext = node;
	position->m_bfmePrev = node;

	return BfmeIterator_0010E2D0(node);
}

// ?bfmeInsert_00151AB0@@YG?AVBfmeIterator_00151AB0@@PAUBfmeNode_00151AB0@@ABUBfmeValue_00151AB0@@@Z
BfmeIterator_00151AB0 __stdcall bfmeInsert_00151AB0(BfmeNode_00151AB0 *position, const BfmeValue_00151AB0 &value)
{
	BfmeNode_00151AB0 *node = (BfmeNode_00151AB0 *)bfmeAllocNode(sizeof(BfmeNode_00151AB0));

	new (&node->m_bfmeValue) BfmeValue_00151AB0(value);

	BfmeNode_00151AB0 *previous = position->m_bfmePrev;
	node->m_bfmeNext = position;
	node->m_bfmePrev = previous;
	previous->m_bfmeNext = node;
	position->m_bfmePrev = node;

	return BfmeIterator_00151AB0(node);
}

// ?bfmeInsert_00251010@@YG?AVBfmeIterator_00251010@@PAUBfmeNode_00251010@@ABUBfmeValue_00251010@@@Z
BfmeIterator_00251010 __stdcall bfmeInsert_00251010(BfmeNode_00251010 *position, const BfmeValue_00251010 &value)
{
	BfmeNode_00251010 *node = (BfmeNode_00251010 *)bfmeAllocNode(sizeof(BfmeNode_00251010));

	new (&node->m_bfmeValue) BfmeValue_00251010(value);

	BfmeNode_00251010 *previous = position->m_bfmePrev;
	node->m_bfmeNext = position;
	node->m_bfmePrev = previous;
	previous->m_bfmeNext = node;
	position->m_bfmePrev = node;

	return BfmeIterator_00251010(node);
}

// ?bfmeInsert_00440480@@YG?AVBfmeIterator_00440480@@PAUBfmeNode_00440480@@ABUBfmeValue_00440480@@@Z
BfmeIterator_00440480 __stdcall bfmeInsert_00440480(BfmeNode_00440480 *position, const BfmeValue_00440480 &value)
{
	BfmeNode_00440480 *node = (BfmeNode_00440480 *)bfmeAllocNode(sizeof(BfmeNode_00440480));

	new (&node->m_bfmeValue) BfmeValue_00440480(value);

	BfmeNode_00440480 *previous = position->m_bfmePrev;
	node->m_bfmeNext = position;
	node->m_bfmePrev = previous;
	previous->m_bfmeNext = node;
	position->m_bfmePrev = node;

	return BfmeIterator_00440480(node);
}
