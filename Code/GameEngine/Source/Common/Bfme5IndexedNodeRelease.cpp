// cl: /O2 /EHsc
// stlport
// Releases one indexed 16-byte node, repairs its two reciprocal short links,
// and moves the retired index onto the owner's free-list head.

#include <map>

// Reuse the verified 0x00196D30 tree-erase instantiation. Its payload's
// original identity remains unknown; retail updates its second dword at
// tree-node+0x18 to the new chain head. No new payload identity is claimed.
struct Gen_t_00196d30_p8cd {
	int a[2];
	Gen_t_00196d30_p8cd();
	Gen_t_00196d30_p8cd(const Gen_t_00196d30_p8cd &);
	~Gen_t_00196d30_p8cd();
	Gen_t_00196d30_p8cd &operator=(const Gen_t_00196d30_p8cd &);
};
typedef _STL::pair<const int, Gen_t_00196d30_p8cd> BfmeIndexedTreePair;
typedef _STL::_Rb_tree<int, BfmeIndexedTreePair,
	_STL::_Select1st<BfmeIndexedTreePair>, _STL::less<int>,
	_STL::allocator<BfmeIndexedTreePair> > BfmeIndexedTree;
template<> void BfmeIndexedTree::erase(BfmeIndexedTree::iterator);
typedef char CheckIndexedTreeSize[(sizeof(BfmeIndexedTree) == 12) ? 1 : -1];

class BfmeMapObjectExtra
{
public:
	void bfmeReset(void);

private:
	int m_state;
};

struct BfmeIndexedNodeFM
{
	short m_previous;
	short m_next;
	short m_chainNext;
	short m_chainPrevious;
	_STL::_Rb_tree_node<BfmeIndexedTreePair> *m_entry;
	BfmeMapObjectExtra m_extra;
};

class BfmeIndexedNodesFM
{
public:
	__declspec(noinline) void bfmePrepareRelease(int index);
	void bfmeRelease(int index);
	void clearChainedNodesAt00197860();

private:
	BfmeIndexedTree m_tree;
	BfmeIndexedNodeFM *m_nodes;
	char m_gap[8];
	short m_count;
	short m_freeHead;
};

// ?bfmeRelease@BfmeIndexedNodesFM@@QAEXH@Z
void BfmeIndexedNodesFM::bfmeRelease(int index)
{
	bfmePrepareRelease(index);

	BfmeIndexedNodeFM *node = &m_nodes[index];
	node->m_extra.bfmeReset();
	m_nodes[node->m_previous].m_next = node->m_next;
	m_nodes[node->m_next].m_previous = node->m_previous;
	short oldFreeHead = m_freeHead;
	--m_count;
	node->m_previous = oldFreeHead;
	m_freeHead = static_cast<short>(index);
}

// Retail 0x00197860, 130 bytes: traverse the live-index list, preserving
// the next index before releasing entries with a nonzero +6 chain link.
// The owner/layout and release sequence are shared with bfmeRelease above;
// the original method name is unknown. The +4/+6 reciprocal chain links
// are independently visible in bfmePrepareRelease at 0x00197750.
void BfmeIndexedNodesFM::clearChainedNodesAt00197860()
{
	int index = m_nodes[0].m_previous;
	while (index)
	{
		int next = m_nodes[index].m_previous;
		if (m_nodes[index].m_chainPrevious)
		{
			bfmePrepareRelease(index);
			BfmeIndexedNodeFM *node = &m_nodes[index];
			node->m_extra.bfmeReset();
			m_nodes[node->m_previous].m_next = node->m_next;
			m_nodes[node->m_next].m_previous = node->m_previous;
			short oldFreeHead = m_freeHead;
			--m_count;
			node->m_previous = oldFreeHead;
			m_freeHead = static_cast<short>(index);
		}
		index = next;
	}
}

// Retail 0x00197750, 125 bytes. Unlink from the per-key chain; if removing
// its head, update the tree payload or erase the now-empty tree entry.
void BfmeIndexedNodesFM::bfmePrepareRelease(int index)
{
	BfmeIndexedNodeFM *node = &m_nodes[index];
	short previous = node->m_chainPrevious;
	if (!previous)
	{
		if (node->m_chainNext)
		{
			node->m_entry->_M_value_field.second.a[1] = node->m_chainNext;
			m_nodes[node->m_chainNext].m_chainPrevious = 0;
		}
		else
		{
			m_tree.erase(BfmeIndexedTree::iterator(node->m_entry));
		}
	}
	else
	{
		m_nodes[previous].m_chainNext = node->m_chainNext;
		if (node->m_chainNext)
			m_nodes[node->m_chainNext].m_chainPrevious = node->m_chainPrevious;
	}
}
