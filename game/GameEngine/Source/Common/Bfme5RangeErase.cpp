// A range erase.
//
// It walks from first to last, unlinking each node, destroying the value it
// carries and freeing it, and hands back an iterator on the node it stopped at
// through a hidden pointer.
//
// Three things about the shape. The unlink lives in its own inline helper, so
// the node's successor is read twice -- once to advance the walk and once to
// splice -- where doing it all at the call site coalesces the two reads and
// loses two bytes. Inside that helper the successor is declared before the
// predecessor, which is what puts the predecessor in ecx and the successor in
// eax rather than the other way round. And the end parameter is copied into a
// local so it is the one loaded first.

void __cdecl bfmeDeallocate(void *block, unsigned int bytes);	// retail 0x0082E5F0

class BfmeRangeValue
{
public:
	~BfmeRangeValue(void);					// retail 0x000205A9

private:
	char m_bfmeBytes[0x24];
};

struct BfmeRangeNode
{
	BfmeRangeNode *m_bfmeNext;				// +0x00
	BfmeRangeNode *m_bfmePrev;				// +0x04
	BfmeRangeValue m_bfmeValue;				// +0x08
};

inline void bfmeEraseNode(BfmeRangeNode *node)
{
	BfmeRangeNode *next = node->m_bfmeNext;
	BfmeRangeNode *previous = node->m_bfmePrev;

	previous->m_bfmeNext = next;
	next->m_bfmePrev = previous;

	node->m_bfmeValue.~BfmeRangeValue();

	bfmeDeallocate(node, sizeof(BfmeRangeNode));
}

class BfmeRangeIterator
{
public:
	BfmeRangeIterator(BfmeRangeNode *node) : m_bfmeNode(node) {}

private:
	BfmeRangeNode *m_bfmeNode;
};

// ?bfmeEraseRange_0076D720@@YG?AVBfmeRangeIterator@@PAUBfmeRangeNode@@0@Z
BfmeRangeIterator __stdcall bfmeEraseRange_0076D720(BfmeRangeNode *first, BfmeRangeNode *last)
{
	BfmeRangeNode *end = last;

	while (first != end)
	{
		BfmeRangeNode *node = first;

		first = first->m_bfmeNext;

		bfmeEraseNode(node);
	}

	return BfmeRangeIterator(end);
}
