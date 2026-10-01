// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: two-pass owned-pointer list destroy at this+0xE0, 0x004302B0 (97B).
// Same shape as Bfme5TwoPassListClear: delete each node's value, then free
// the 0xC nodes, then point the sentinel at itself. Value delete is the
// virtual at +0x1C with the MSVC deleting flag (push 1). Deallocator is
// the STLport small-node helper already pinned at 0x0082E5F0.

class Gen_00430440;

// STLport's private node-pool entry point at retail 0x0082E5F0.
namespace _STL
{
template <bool __threads, int __inst>
class __node_alloc
{
	friend class ::Gen_00430440;
	static void __cdecl _M_deallocate(void *block, unsigned int bytes);
};
}

class BfmeOwnedItem
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual ~BfmeOwnedItem();
};

struct BfmeOwnNode
{
	BfmeOwnNode *m_bfmeNext;
	BfmeOwnNode *m_bfmePrev;
	BfmeOwnedItem *m_bfmeValue;
};

class Gen_00430440
{
public:
	void bfmeClear(void);

private:
	unsigned char m_pad[0xE0];
	BfmeOwnNode *m_bfmeList;
};

// ?bfmeClear@Gen_00430440@@QAEXXZ
void Gen_00430440::bfmeClear(void)
{
	BfmeOwnNode *node = m_bfmeList->m_bfmeNext;

	while (node != m_bfmeList)
	{
		delete node->m_bfmeValue;
		node = node->m_bfmeNext;
	}

	BfmeOwnNode *walk = m_bfmeList->m_bfmeNext;

	while (walk != m_bfmeList)
	{
		BfmeOwnNode *current = walk;
		walk = walk->m_bfmeNext;
		_STL::__node_alloc<true, 0>::_M_deallocate(current, sizeof(BfmeOwnNode));
	}

	m_bfmeList->m_bfmeNext = m_bfmeList;
	m_bfmeList->m_bfmePrev = m_bfmeList;
}
