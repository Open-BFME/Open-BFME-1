// Open-BFME5: TimedOperationNode constructor at 0x0007BA00 (68B).
// thiscall (Holder, key) ret 8. Stores vftable 0x010766E8, next=0, the
// by-value holder's pointer at +8 with AddRef, started/startTime=0, key at
// +0x14, then the inlined holder dtor Releases.

class TimedOperation
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
		TimedOperation *current = m_value;
		if (current != 0)
		{
			if (--current->m_refCount <= 0)
				current->release(1);
		}
	}

	TimedOperation *m_value;
};

class TimedOperationNode
{
public:
	TimedOperationNode(LoadGameFadeHolder holder, void *key);
	virtual ~TimedOperationNode();

	TimedOperationNode *m_next;
	TimedOperation *m_operation;
	bool m_started;
	char m_pad[3];
	unsigned int m_startTime;
	void *m_key;
};

// ??0TimedOperationNode@@QAE@VLoadGameFadeHolder@@PAX@Z
TimedOperationNode::TimedOperationNode(LoadGameFadeHolder holder, void *key)
{
	m_next = 0;
	m_operation = holder.m_value;
	if (m_operation != 0)
		++m_operation->m_refCount;
	m_started = 0;
	m_startTime = 0;
	m_key = key;
}
