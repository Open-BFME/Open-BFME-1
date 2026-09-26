// cl: /DNDEBUG /MD /EHsc

class BfmeCondition
{
public:
	bool isActive();
};

struct BfmeConditionOwnerPart
{
	unsigned char m_pad00[0x140];
	BfmeCondition *m_condition;
};

struct BfmeConditionOwner
{
	unsigned char m_pad00[0x204];
	BfmeConditionOwnerPart *m_part;
};

struct BfmeConditionNode
{
	BfmeConditionNode *m_next;
	BfmeConditionNode *m_previous;
	BfmeConditionOwner *m_value;
};

class BfmeConditionListView
{
public:
	bool bfmeAnyLinkedConditionActive();
};

bool BfmeConditionListView::bfmeAnyLinkedConditionActive()
{
	BfmeConditionListView *self = this;
	BfmeConditionNode *node = (*reinterpret_cast<BfmeConditionNode **>(
		reinterpret_cast<unsigned char *>(self) - 0xac))->m_next;
	while (node != *reinterpret_cast<BfmeConditionNode **>(
		reinterpret_cast<unsigned char *>(self) - 0xac))
	{
		BfmeConditionOwner *owner = node->m_value;
		if (owner != 0)
		{
			BfmeCondition *condition = owner->m_part->m_condition;
			if (condition != 0 && condition->isActive())
				return true;
		}
		node = node->m_next;
	}
	return false;
}
