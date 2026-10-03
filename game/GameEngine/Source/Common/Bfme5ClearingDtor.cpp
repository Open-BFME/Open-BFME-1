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
	BfmeClearNodeB *m_bfmeNext;				// +0x00
	BfmeClearNodeB *m_bfmePrev;				// +0x04
	void *m_bfmeValue;					// +0x08
};

class BfmeClearListB;

// The list nodes come from the STLport node pool: 0x0082E5F0 is the private
// static _STL::__node_alloc<true, 0>::_M_deallocate, so the list reaches it
// under that real name instead of an invented free function.
namespace _STL
{
template <bool __threads, int __inst>
class __node_alloc
{
	friend class ::BfmeClearListB;
	static void __cdecl _M_deallocate(void *__p, unsigned int __n);
};
}

class BfmeClearListB
{
public:
	void bfmeClear(void)
	{
		BfmeClearNodeB *node = m_bfmeNode->m_bfmeNext;

		while (node != m_bfmeNode)
		{
			BfmeClearNodeB *current = node;

			node = node->m_bfmeNext;

			_STL::__node_alloc<true, 0>::_M_deallocate(current, sizeof(BfmeClearNodeB));
		}

		m_bfmeNode->m_bfmeNext = m_bfmeNode;
		m_bfmeNode->m_bfmePrev = m_bfmeNode;
	}

	BfmeClearNodeB *m_bfmeNode;				// +0x00
};

class BfmeDBaseA
{
public:
	virtual ~BfmeDBaseA(void);				// retail 0x00033F6E

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
