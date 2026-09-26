// Two holding-list clears.
//
// Each walks a circular list, disposes of what every node holds, unlinks the
// node and frees it, and stops when it comes back to the head -- which is
// re-read every pass, because the frees can change memory.
//
// What a node holds is disposed of in two steps: the inner pointer is deleted
// through its slot zero with a one, and then the holder itself goes straight
// to the scalar free with no destructor call, which is what delete on a class
// without one compiles to. The second null test folds away because the holder
// sits in a register the calls cannot touch.

void __cdecl bfmeFreeScalar(void *block);			// retail 0x00881EB0
void __cdecl bfmeDeallocate(void *block, unsigned int bytes);	// retail 0x0082E5F0

inline void __cdecl operator delete(void *block) { bfmeFreeScalar(block); }

class BfmeInner
{
public:
	virtual ~BfmeInner(void);
};

class BfmeHeld
{
public:
	BfmeInner *m_bfmeInner;					// +0x00
};

struct BfmeHoldNode
{
	BfmeHoldNode *m_bfmeNext;				// +0x00
	BfmeHoldNode *m_bfmePrev;				// +0x04
	BfmeHeld *m_bfmeValue;					// +0x08
};

class Gen_0043F5D0
{
public:
	void bfmeClear(void);

private:
	char m_bfmePad[0x12C0];					// +0x0000
	BfmeHoldNode *m_bfmeList;				// +0x12C0
};

// ?bfmeClear@Gen_0043F5D0@@QAEXXZ
void Gen_0043F5D0::bfmeClear(void)
{
	BfmeHoldNode *node = m_bfmeList->m_bfmeNext;

	while (node != m_bfmeList)
	{
		BfmeHeld *held = node->m_bfmeValue;

		if (held)
		{
			delete held->m_bfmeInner;
			delete held;
		}

		BfmeHoldNode *next = node->m_bfmeNext;
		BfmeHoldNode *previous = node->m_bfmePrev;

		previous->m_bfmeNext = next;
		next->m_bfmePrev = previous;

		bfmeDeallocate(node, sizeof(BfmeHoldNode));

		node = next;
	}
}

class Gen_0043FBB0
{
public:
	void bfmeClear(void);

private:
	char m_bfmePad[0x12C4];					// +0x0000
	BfmeHoldNode *m_bfmeList;				// +0x12C4
};

// ?bfmeClear@Gen_0043FBB0@@QAEXXZ
void Gen_0043FBB0::bfmeClear(void)
{
	BfmeHoldNode *node = m_bfmeList->m_bfmeNext;

	while (node != m_bfmeList)
	{
		BfmeHeld *held = node->m_bfmeValue;

		if (held)
		{
			delete held->m_bfmeInner;
			delete held;
		}

		BfmeHoldNode *next = node->m_bfmeNext;
		BfmeHoldNode *previous = node->m_bfmePrev;

		previous->m_bfmeNext = next;
		next->m_bfmePrev = previous;

		bfmeDeallocate(node, sizeof(BfmeHoldNode));

		node = next;
	}
}
