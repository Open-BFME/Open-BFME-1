// stlport
#include "../GameClient/FXListRetail.h"

// A clearing destructor over two bases.
//
// The body is one statement: clear the list the first base keeps. Everything
// around it is bookkeeping -- the two most-derived vptrs at entry, then the
// second base's own vptr as it is destroyed inline, then the first base's
// destructor out of line.
//
// The clear is the list's, not the list's destructor: it walks and frees the
// nodes and re-points the sentinel at itself, but never frees the sentinel.
// The unwind frame is there for the two bases, which is why the state word
// starts at one rather than zero.

struct BfmeClearNodeB
{
	BfmeClearNodeB *m_next;				// +0x00
	BfmeClearNodeB *m_prev;				// +0x04
	void *m_bfmeValue;					// +0x08
};

class BfmeClearListB;

// The list nodes come from the STLport node pool: 0x0082E5F0 is the private
// static _STL::__node_alloc<true, 0>::_M_deallocate. The public deallocate
// wrapper folds its size check for these 12-byte nodes and reaches that body.
class BfmeClearListB
{
public:
	void bfmeClear(void)
	{
		BfmeClearNodeB *node = m_bfmeNode->m_next;

		while (node != m_bfmeNode)
		{
			BfmeClearNodeB *current = node;

			node = node->m_next;

			_STL::__node_alloc<true, 0>::deallocate(current, sizeof(BfmeClearNodeB));
		}

		m_bfmeNode->m_next = m_bfmeNode;
		m_bfmeNode->m_prev = m_bfmeNode;
	}

	BfmeClearNodeB *m_bfmeNode;				// +0x00
};

class __declspec(novtable) BfmeDBaseA
{
public:
	// Preserve the derived vtable spelling while forwarding this lifetime view
	// to the shared FXList destructor (ILT 0x00033F6E -> 0x0042B5D0).
	__forceinline virtual ~BfmeDBaseA(void) { ((FXList *)this)->FXList::~FXList(); }

	BfmeClearListB m_bfmeList;				// +0x04
	char m_bfmePad[0x1C];					// +0x08
};

// The retail unwind action proves this base destructor at 0x003828E0.
// Keep the inherited local view name qualified by its actual body address.
namespace Rva003828E0
{
class BfmeDBaseB
{
public:
	virtual ~BfmeDBaseB(void) {}
};

}
using Rva003828E0::BfmeDBaseB;

class Gen_0042B9F0 : public BfmeDBaseA, public BfmeDBaseB
{
public:
	virtual ~Gen_0042B9F0(void);
};

// ??1Gen_0042B9F0@@UAE@XZ
Gen_0042B9F0::~Gen_0042B9F0(void)
{
	m_bfmeList.bfmeClear();
}
