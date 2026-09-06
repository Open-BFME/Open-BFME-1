// cl: /DNDEBUG /MD /EHsc

typedef int Int;

class InGameUI;

class Player
{
private:
	char m_padding00[0x24];
	Int m_playerIndex;

	friend class PlayerList;
	friend class InGameUI;
};

class PlayerList
{
private:
	char m_padding00[0x0c];
	Player *m_localPlayer;

	friend class InGameUI;
};

extern PlayerList *ThePlayerList;

struct BfmeIdleWorkerNode
{
	BfmeIdleWorkerNode *m_next;
	BfmeIdleWorkerNode *m_prev;
	void *m_object;
};

struct BfmeIdleWorkerList
{
	BfmeIdleWorkerNode *m_head;

	Int size() const
	{
		BfmeIdleWorkerNode *node = m_head->m_next;
		Int count = 0;
		while (node != m_head)
		{
			node = node->m_next;
			++count;
		}
		return count;
	}
};

class InGameUI
{
private:
	virtual Int getIdleWorkerCount();

	char m_padding04[0x1318];
	BfmeIdleWorkerList m_idleWorkers[32];
};

// ?getIdleWorkerCount@InGameUI@@EAEHXZ
Int InGameUI::getIdleWorkerCount()
{
	Int index = ThePlayerList->m_localPlayer->m_playerIndex;
	return m_idleWorkers[index].size();
}
