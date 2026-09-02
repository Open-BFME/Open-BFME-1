// ?link@Gen0060BB60@@QAEXPAUGen0060BB60Node@@@Z
// partial score=0.86 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc

class Gen0060BB60Owner;

struct Gen0060BB60Node
{
	Gen0060BB60Owner *m_owner;
	Gen0060BB60Node *m_prev;
	Gen0060BB60Node *m_next;
};

class Gen0060BB60Owner
{
private:
	char m_pad00[0x98];
	Gen0060BB60Node *m_head;
	Gen0060BB60Node *m_tail;

	friend class Gen0060BB60;
};

class Gen0060BB60
{
public:
	void link(Gen0060BB60Node *node);

private:
	char m_pad00[0x160];
	Gen0060BB60Owner *m_owner;
};

// ?link@Gen0060BB60@@QAEXPAUGen0060BB60Node@@@Z
void Gen0060BB60::link(Gen0060BB60Node *node)
{
	Gen0060BB60Owner *owner = m_owner;
	{
		Gen0060BB60Node * volatile unused = 0;
	}
	node->m_owner = owner;
	if (owner != 0)
	{
		node->m_prev = owner->m_tail;
		node->m_next = 0;
		owner->m_tail = node;
		if (node->m_prev != 0)
			node->m_prev->m_next = node;
		else
			owner->m_head = node;
	}
	else
	{
		node->m_next = 0;
		node->m_prev = 0;
	}
}
