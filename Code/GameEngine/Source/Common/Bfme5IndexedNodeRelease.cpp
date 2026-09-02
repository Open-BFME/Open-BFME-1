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
	char m_gap[8];
	BfmeMapObjectExtra m_extra;
};

class BfmeIndexedNodesFM
{
public:
	void bfmePrepareRelease(int index);
	void bfmeRelease(int index);

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
