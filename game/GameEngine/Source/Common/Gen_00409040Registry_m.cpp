// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: Gen_00409040Registry::m, retail 0x00409040, 103 bytes. The body
// carried only a machine byte-dump row; the symbols.csv pin names it from its
// caller and asserts no identity.
//
// A move-to-front over an intrusive list. The registry keeps four pointers --
// two ends at +0x08 and +0x0C and two cursors at +0x10 and +0x14 -- and the
// nodes are threaded through +0x14 and +0x18. Nothing happens at all if the
// node is already at either end.
//
// Otherwise each cursor that was sitting on the node is stepped off it, the
// node is unlinked from both sides, and it goes on the front. The front is read
// twice, once to repair the old first node and once to become the new node's
// next, because the store in between could have changed it as far as the
// compiler knows.

class BfmeRegistryNode
{
public:
	char m_bfmeHead[0x14];
	BfmeRegistryNode *m_bfmeNext;				// +0x14
	BfmeRegistryNode *m_bfmePrev;				// +0x18
};

class Gen_00409040Registry
{
public:
	void m(void *node);

private:
	char m_bfmeHead[0x08];
	BfmeRegistryNode *m_bfmeFront;				// +0x08
	BfmeRegistryNode *m_bfmeBack;				// +0x0C
	BfmeRegistryNode *m_bfmeCursorA;			// +0x10
	BfmeRegistryNode *m_bfmeCursorB;			// +0x14
};

// ?m@Gen_00409040Registry@@QAEXPAX@Z
void Gen_00409040Registry::m(void *nodePointer)
{
	BfmeRegistryNode *node = (BfmeRegistryNode *)nodePointer;

	if (m_bfmeFront == node)
		return;

	if (m_bfmeBack == node)
		return;

	if (m_bfmeCursorA == node)
		m_bfmeCursorA = node->m_bfmeNext;

	if (m_bfmeCursorB == node)
		m_bfmeCursorB = node->m_bfmePrev;

	if (node->m_bfmeNext)
		node->m_bfmeNext->m_bfmePrev = node->m_bfmePrev;

	if (node->m_bfmePrev)
		node->m_bfmePrev->m_bfmeNext = node->m_bfmeNext;

	if (m_bfmeFront)
		m_bfmeFront->m_bfmePrev = node;

	node->m_bfmeNext = m_bfmeFront;
	m_bfmeFront = node;
	node->m_bfmePrev = 0;

	if (!m_bfmeBack)
		m_bfmeBack = node;
}
