// A pruning sum.
//
// It walks a circular list adding up a float from every entry that is still
// within a window, and drops the entries that are not. The window is a global
// clock minus an offset the owner keeps, computed once before the walk.
//
// The dropping branch is the fall-through and the adding branch is the one the
// jump goes to, so the test in source is the expired case: entries at or below
// the threshold are unlinked and freed, everything else contributes. The total
// is a float local initialised with an integer zero store and returned on the
// stack.

void __cdecl bfmeDeallocate(void *block, unsigned int bytes);	// retail 0x0082E5F0

struct BfmeSumNode
{
	BfmeSumNode *m_bfmeNext;				// +0x00
	BfmeSumNode *m_bfmePrev;				// +0x04
	float m_bfmeValue;					// +0x08
	int m_bfmeStamp;					// +0x0C
};

struct BfmeSumClock
{
	char m_bfmePad[0x3C];					// +0x00
	int m_bfmeTime;						// +0x3C
};

struct BfmeSumOwner
{
	char m_bfmePad[0x14];					// +0x00
	int m_bfmeOffset;					// +0x14
};

extern BfmeSumClock *TheBfmeSumClock;

class Gen_00250F50
{
public:
	float bfmeSum(void);

private:
	int m_bfmeHead;						// +0x00
	BfmeSumOwner *m_bfmeOwner;				// +0x04
	int m_bfmeGap[3];					// +0x08
	BfmeSumNode *m_bfmeList;				// +0x14
};

// ?bfmeSum@Gen_00250F50@@QAEMXZ
float Gen_00250F50::bfmeSum(void)
{
	int threshold = TheBfmeSumClock->m_bfmeTime - m_bfmeOwner->m_bfmeOffset;

	BfmeSumNode *node = m_bfmeList->m_bfmeNext;
	float total = 0.0f;

	while (node != m_bfmeList)
	{
		if (node->m_bfmeStamp <= threshold)
		{
			BfmeSumNode *next = node->m_bfmeNext;
			BfmeSumNode *previous = node->m_bfmePrev;

			previous->m_bfmeNext = next;
			next->m_bfmePrev = previous;

			bfmeDeallocate(node, sizeof(BfmeSumNode));

			node = next;
		}
		else
		{
			total += node->m_bfmeValue;

			node = node->m_bfmeNext;
		}
	}

	return total;
}
