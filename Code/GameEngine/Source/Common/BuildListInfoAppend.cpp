// cl: /DNDEBUG /MD /GX- /O2 /Ob2
// Tail-link helper reached from BuildListInfo::parseStructure.

class BfmeBuildListNode
{
public:
	char m_bfmePad[0x2c];
	BfmeBuildListNode *m_bfmeNext;
};

class BfmeBuildList
{
public:
	void bfmeAppend(BfmeBuildListNode *node);

private:
	char m_bfmePad[8];
	BfmeBuildListNode *m_bfmeHead;
};

void BfmeBuildList::bfmeAppend(BfmeBuildListNode *node)
{
	BfmeBuildListNode *walk = m_bfmeHead;
	if (walk == 0)
	{
		m_bfmeHead = node;
		node->m_bfmeNext = 0;
		return;
	}

	while (walk != 0)
	{
		if (walk->m_bfmeNext == 0)
			break;
		walk = walk->m_bfmeNext;
	}

	walk->m_bfmeNext = node;
	node->m_bfmeNext = 0;
}
