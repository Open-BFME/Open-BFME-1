// Releases one indexed 16-byte node, repairs its two reciprocal short links,
// and moves the retired index onto the owner's free-list head.

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
	void *m_entry;
	BfmeMapObjectExtra m_extra;
};

class BfmeIndexedNodesFM
{
public:
	void bfmePrepareRelease(int index);
	void bfmeRelease(int index);
	void clearChainedNodesAt00197860();

private:
	char m_head[0x0c];
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
