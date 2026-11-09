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

class Gen_00250F50;

namespace _STL
{
	template <bool __threads, int __inst>
	class __node_alloc
	{
		friend class ::Gen_00250F50;
		static void __cdecl _M_deallocate(void *block, unsigned int bytes);
	};
}

struct BfmeSumNode
{
	BfmeSumNode *m_next;				// +0x00
	BfmeSumNode *m_prev;				// +0x04
	float m_bfmeValue;					// +0x08
	int m_bfmeStamp;					// +0x0C
};

struct BfmeSumClock
{
	char m_bfmePad[0x3C];					// +0x00
	int m_frame;						// +0x3C
};

struct BfmeSumOwner
{
	char m_bfmePad[0x14];					// +0x00
	int m_bfmeOffset;					// +0x14
};

// Retail's GameLogic singleton at 0x012F0898; the one canonical spelling.
class GameLogic;
extern GameLogic *TheGameLogic;

// TU-local view of the singleton's clock dword at +0x3C.
static __forceinline BfmeSumClock *bfmeSumClockHF(void)
{
	return (BfmeSumClock *)TheGameLogic;
}

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
	int threshold = bfmeSumClockHF()->m_frame - m_bfmeOwner->m_bfmeOffset;

	BfmeSumNode *node = m_bfmeList->m_next;
	float total = 0.0f;

	while (node != m_bfmeList)
	{
		if (node->m_bfmeStamp <= threshold)
		{
			BfmeSumNode *next = node->m_next;
			BfmeSumNode *previous = node->m_prev;

			previous->m_next = next;
			next->m_prev = previous;

			_STL::__node_alloc<true, 0>::_M_deallocate(
				node, sizeof(BfmeSumNode));

			node = next;
		}
		else
		{
			total += node->m_bfmeValue;

			node = node->m_next;
		}
	}

	return total;
}
