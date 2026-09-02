// cl: /DNDEBUG /MD /EHsc

class BfmeDeleteNode
{
public:
	virtual ~BfmeDeleteNode();
	BfmeDeleteNode *m_next;
};

class BfmeDeletingChainOwner
{
public:
	virtual ~BfmeDeletingChainOwner();

private:
	BfmeDeleteNode *m_chain;
	BfmeDeleteNode *m_owned;
};

BfmeDeletingChainOwner::~BfmeDeletingChainOwner()
{
	if (m_owned != 0) {
		delete m_owned;
		m_owned = 0;
	}

	BfmeDeleteNode *node = m_chain;
	while (node != 0) {
		BfmeDeleteNode *next = node->m_next;
		node->m_next = 0;
		delete node;
		node = next;
	}
}
