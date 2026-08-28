// Construct the transition-group state and its 12-byte circular-list
// sentinel.  The retail allocator call returns the sentinel address.

struct BFMETransitionGroupNode
{
	BFMETransitionGroupNode *m_next;
	BFMETransitionGroupNode *m_previous;
	void *m_value;
};

class BFMETransitionList
{
public:
	BFMETransitionList(void)
	{
		m_head = 0;
		BFMETransitionGroupNode *node = new BFMETransitionGroupNode;
		node->m_next = node;
		node->m_previous = node;
		m_head = node;
	}

private:
	void *m_head;
};

class BFMETransitionZero
{
public:
	BFMETransitionZero(void) : m_value(0) {}

	int m_value;
};

class BFMETransitionGroup
{
public:
	BFMETransitionGroup(void);

private:
	unsigned char m_bfmeFlag;				// +0x00
	char m_bfmePadding[3];
	BFMETransitionList m_bfmeList;			// +0x04
	int m_bfmeState;					// +0x08
	int m_bfmeCount;					// +0x0C
	BFMETransitionZero m_bfmeReserved;			// +0x10
};

// ??0BFMETransitionGroup@@QAE@XZ
BFMETransitionGroup::BFMETransitionGroup(void)
{
	m_bfmeState = 1;
	m_bfmeCount = 0;
	m_bfmeFlag = 0;
}
