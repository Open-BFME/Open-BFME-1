// Two list clears.
//
// Each walks a circular list freeing every node and then points the head back
// at itself, reading the head member again for each of those two stores and
// for every pass of the loop -- the deallocator can change memory, so it never
// stays in a register.
//
// The loop advances before it frees: the node is copied into a local, the
// iterator moves on, and only then is the copy handed to the deallocator.
// Saving the successor instead and freeing the current node swaps which
// pointer lives in the callee-saved register and moves the push into the loop.

void __cdecl bfmeDeallocate(void *block, unsigned int bytes);	// retail 0x0082E5F0

struct BfmeClearNode
{
	BfmeClearNode *m_bfmeNext;				// +0x00
	BfmeClearNode *m_bfmePrev;				// +0x04
	void *m_bfmeValue;					// +0x08
};

class Gen_000CE820
{
public:
	void bfmeClear(void);

private:
	char m_bfmePad[0x64C];					// +0x000
	BfmeClearNode *m_bfmeList;				// +0x64C
};

// ?bfmeClear@Gen_000CE820@@QAEXXZ
void Gen_000CE820::bfmeClear(void)
{
	BfmeClearNode *node = m_bfmeList->m_bfmeNext;

	while (node != m_bfmeList)
	{
		BfmeClearNode *current = node;

		node = node->m_bfmeNext;

		bfmeDeallocate(current, sizeof(BfmeClearNode));
	}

	m_bfmeList->m_bfmeNext = m_bfmeList;
	m_bfmeList->m_bfmePrev = m_bfmeList;
}

class Gen_001F2AA0
{
public:
	void bfmeClear(void);

private:
	char m_bfmePad[0x480];					// +0x000
	BfmeClearNode *m_bfmeList;				// +0x480
};

// ?bfmeClear@Gen_001F2AA0@@QAEXXZ
void Gen_001F2AA0::bfmeClear(void)
{
	BfmeClearNode *node = m_bfmeList->m_bfmeNext;

	while (node != m_bfmeList)
	{
		BfmeClearNode *current = node;

		node = node->m_bfmeNext;

		bfmeDeallocate(current, sizeof(BfmeClearNode));
	}

	m_bfmeList->m_bfmeNext = m_bfmeList;
	m_bfmeList->m_bfmePrev = m_bfmeList;
}
