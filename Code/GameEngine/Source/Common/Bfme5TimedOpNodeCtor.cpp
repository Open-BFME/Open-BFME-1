// Open-BFME5: BfmeTimedOpNode constructor at 0x0007BA00 (68B).
// thiscall (Holder, key) ret 8. Stores vftable 0x010766E8, next=0, the
// by-value holder's pointer at +8 with AddRef, started/startTime=0, key at
// +0x14, then the inlined holder dtor Releases.

class BfmeTimedOperation
{
public:
	virtual void release(int deletingFlag);
	int m_refCount;
};

class LoadGameFadeHolder
{
public:
	~LoadGameFadeHolder()
	{
		BfmeTimedOperation *current = m_value;
		if (current != 0)
		{
			if (--current->m_refCount <= 0)
				current->release(1);
		}
	}

	BfmeTimedOperation *m_value;
};

class BfmeTimedOpNode
{
public:
	BfmeTimedOpNode(LoadGameFadeHolder holder, void *key);
	virtual ~BfmeTimedOpNode();

	BfmeTimedOpNode *m_next;
	BfmeTimedOperation *m_operation;
	bool m_started;
	char m_pad[3];
	unsigned int m_startTime;
	void *m_key;
};

// ??0BfmeTimedOpNode@@QAE@VLoadGameFadeHolder@@PAX@Z
BfmeTimedOpNode::BfmeTimedOpNode(LoadGameFadeHolder holder, void *key)
{
	m_next = 0;
	m_operation = holder.m_value;
	if (m_operation != 0)
		++m_operation->m_refCount;
	m_started = 0;
	m_startTime = 0;
	m_key = key;
}
