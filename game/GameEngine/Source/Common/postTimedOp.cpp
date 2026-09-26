// cl: /EHsc
//
// Open-BFME5: postTimedOp at 0x0007BA90 (245B). Allocates a 0x18-byte
// TimedOperationNode, stamps the serial at 0x012A737C through the key out-param,
// inlines the node ctor, and appends onto 0x012ED584.

class TimedOperation
{
public:
	virtual void release(int deletingFlag);
	int m_refCount;
};

class LoadGameFadeHolder
{
public:
	LoadGameFadeHolder(const LoadGameFadeHolder &other)
		: m_value(other.m_value)
	{
		if (m_value != 0)
			++m_value->m_refCount;
	}

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

class TimedOperationList
{
public:
	void append(void *value);
};

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

extern TimedOperationNode *g_timedOperationHead;
extern unsigned int g_timedOperationSerial;

// ?postTimedOp@@YA_NVLoadGameFadeHolder@@PAX@Z
bool postTimedOp(LoadGameFadeHolder holder, void *key)
{
	unsigned int *id = (unsigned int *)key;
	*id = g_timedOperationSerial;
	++g_timedOperationSerial;

	TimedOperationNode *node = new TimedOperationNode(holder, (void *)*id);
	if (node != 0)
	{
		if (g_timedOperationHead != 0)
			((TimedOperationList *)g_timedOperationHead)->append(node);
		else
			g_timedOperationHead = node;
	}
	return node != 0;
}
