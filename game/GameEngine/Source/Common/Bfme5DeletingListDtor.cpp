// A deleting list destructor.
//
// It walks the list, clears a flag on what each node holds and deletes it,
// then unlinks and frees the node, and finally chains to the base.
//
// The flag store belongs to the loop body, not to the held object's
// destructor: retail emits it before the unwind slot that registers the object
// for deletion, and a destructor body would land after that registration. The
// held object's own destructor is empty -- what runs is its two members, in
// reverse order, before the free.
//
// The state word is byte-wide for the inner transitions and dword-wide for the
// outer ones, which is the usual "only the low byte changes" saving.

void __cdecl bfmeFreeScalar(void *block);			// retail 0x00881EB0
void __cdecl bfmeDeallocate(void *block, unsigned int bytes);	// retail 0x0082E5F0

inline void __cdecl operator delete(void *block) { bfmeFreeScalar(block); }

class BfmeSubF
{
public:
	~BfmeSubF(void);					// retail 0x00887940

private:
	int m_bfmeValue;
};

class BfmeHeldF
{
public:
	~BfmeHeldF(void) {}

	int m_bfmeFlag;						// +0x00
	BfmeSubF m_bfmeA;					// +0x04
	BfmeSubF m_bfmeB;					// +0x08
};

struct BfmeNodeF
{
	BfmeNodeF *m_bfmeNext;					// +0x00
	BfmeNodeF *m_bfmePrev;					// +0x04
	BfmeHeldF *m_bfmeValue;					// +0x08
};

class BfmeBaseF
{
public:
	~BfmeBaseF(void);					// retail 0x00029537

	BfmeNodeF *m_bfmeList;					// +0x00
};

class Gen_0048C5B0 : public BfmeBaseF
{
public:
	~Gen_0048C5B0(void);
};

// ??1Gen_0048C5B0@@QAE@XZ
Gen_0048C5B0::~Gen_0048C5B0(void)
{
	BfmeNodeF *node = m_bfmeList->m_bfmeNext;

	while (node != m_bfmeList)
	{
		BfmeHeldF *held = node->m_bfmeValue;

		if (held)
		{
			held->m_bfmeFlag = 0;

			delete held;
		}

		BfmeNodeF *next = node->m_bfmeNext;
		BfmeNodeF *previous = node->m_bfmePrev;

		previous->m_bfmeNext = next;
		next->m_bfmePrev = previous;

		bfmeDeallocate(node, sizeof(BfmeNodeF));

		node = next;
	}
}
