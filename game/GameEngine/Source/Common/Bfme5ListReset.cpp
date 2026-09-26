// A list reset.
//
// It frees every node of a circular list, points the head back at itself, and
// then puts three unrelated fields back to their starting values -- a flag, a
// cursor taken from another object, and a count.
//
// The loop advances before it frees, which is what keeps the node in the
// callee-saved register; the head member is re-read for every comparison and
// for both of the self-link stores, because the deallocator can change memory.

typedef bool Bool;

void __cdecl bfmeDeallocate(void *block, unsigned int bytes);	// retail 0x0082E5F0

struct BfmeResetNode
{
	BfmeResetNode *m_bfmeNext;				// +0x00
	BfmeResetNode *m_bfmePrev;				// +0x04
	void *m_bfmeValue;					// +0x08
};

struct BfmeResetOther
{
	void *m_bfmeFirst;					// +0x00
};

class Gen_0040C600
{
public:
	void bfmeReset(void);

private:
	int m_bfmeHead[2];					// +0x00
	BfmeResetOther *m_bfmeOther;				// +0x08
	void *m_bfmeCursor;					// +0x0C
	BfmeResetNode *m_bfmeList;				// +0x10
	int m_bfmeGap[7];					// +0x14
	Bool m_bfmeFlag;					// +0x30
	char m_bfmePad[3];					// +0x31
	int m_bfmeCount;					// +0x34
};

// ?bfmeReset@Gen_0040C600@@QAEXXZ
void Gen_0040C600::bfmeReset(void)
{
	BfmeResetNode *node = m_bfmeList->m_bfmeNext;

	while (node != m_bfmeList)
	{
		BfmeResetNode *current = node;

		node = node->m_bfmeNext;

		bfmeDeallocate(current, sizeof(BfmeResetNode));
	}

	m_bfmeList->m_bfmeNext = m_bfmeList;
	m_bfmeList->m_bfmePrev = m_bfmeList;

	m_bfmeFlag = false;
	m_bfmeCursor = m_bfmeOther->m_bfmeFirst;
	m_bfmeCount = 0;
}
