// Two tree removes.
//
// Each hands the node and the addresses of three fields of the root to an
// unlinker, destroys the value the node it gets back carries, frees that node
// and drops the count.
//
// The three arguments are lea of members at +0x04, +0x08 and +0x0C of the same
// object, pushed back to front, which is the header trio a splay tree keeps.
// The free is guarded even though the unlinker always returns a node -- the
// guard is what delete on the result compiles to -- and the size is the whole
// node with the value at +0x10.

void __cdecl bfmeDeallocate(void *block, unsigned int bytes);	// retail 0x0082E5F0

class BfmeSplitValue
{
public:
	~BfmeSplitValue(void);					// retail 0x000402BE

private:
	char m_bfmeBytes[0x40];
};

struct BfmeSplitNode
{
	BfmeSplitNode *m_bfmeRoot;				// +0x00
	BfmeSplitNode *m_bfmeLeft;				// +0x04
	BfmeSplitNode *m_bfmeParent;				// +0x08
	BfmeSplitNode *m_bfmeRight;				// +0x0C
	BfmeSplitValue m_bfmeValue;				// +0x10
};

BfmeSplitNode * __cdecl bfmeUnlink(BfmeSplitNode *node, BfmeSplitNode **left,
	BfmeSplitNode **parent, BfmeSplitNode **right);		// retail 0x0082CB60

class Gen_00587670
{
public:
	void bfmeRemove(BfmeSplitNode *node);

private:
	BfmeSplitNode *m_bfmeRoot;				// +0x00
	int m_bfmeCount;					// +0x04
};

// ?bfmeRemove@Gen_00587670@@QAEXPAUBfmeSplitNode@@@Z
void Gen_00587670::bfmeRemove(BfmeSplitNode *node)
{
	BfmeSplitNode *removed = bfmeUnlink(node, &m_bfmeRoot->m_bfmeLeft,
		&m_bfmeRoot->m_bfmeParent, &m_bfmeRoot->m_bfmeRight);

	removed->m_bfmeValue.~BfmeSplitValue();

	if (removed)
		bfmeDeallocate(removed, sizeof(BfmeSplitNode));

	--m_bfmeCount;
}

class Gen_00587750
{
public:
	void bfmeRemove(BfmeSplitNode *node);

private:
	BfmeSplitNode *m_bfmeRoot;				// +0x00
	int m_bfmeCount;					// +0x04
};

// ?bfmeRemove@Gen_00587750@@QAEXPAUBfmeSplitNode@@@Z
void Gen_00587750::bfmeRemove(BfmeSplitNode *node)
{
	BfmeSplitNode *removed = bfmeUnlink(node, &m_bfmeRoot->m_bfmeLeft,
		&m_bfmeRoot->m_bfmeParent, &m_bfmeRoot->m_bfmeRight);

	removed->m_bfmeValue.~BfmeSplitValue();

	if (removed)
		bfmeDeallocate(removed, sizeof(BfmeSplitNode));

	--m_bfmeCount;
}
