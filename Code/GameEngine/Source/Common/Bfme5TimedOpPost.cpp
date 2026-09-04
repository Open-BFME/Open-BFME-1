// cl: /EHsc
//
// Open-BFME5: postTimedOp at 0x0007BA90 (245B). Allocates a 0x18-byte
// BfmeTimedOpNode, stamps the serial at 0x012A737C through the key out-param,
// inlines the node ctor, and appends onto 0x012ED584 via bfmeAppend.

class BfmeTimedOperation
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

class Gen_0007b5a0
{
public:
	void bfmeAppend(void *value);
};

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

extern BfmeTimedOpNode *g_bfmeTimedOpHead;
extern unsigned int g_bfmeTimedOpSerial;

// ?postTimedOp@@YA_NVLoadGameFadeHolder@@PAX@Z
bool postTimedOp(LoadGameFadeHolder holder, void *key)
{
	unsigned int *id = (unsigned int *)key;
	*id = g_bfmeTimedOpSerial;
	++g_bfmeTimedOpSerial;

	BfmeTimedOpNode *node = new BfmeTimedOpNode(holder, (void *)*id);
	if (node != 0)
	{
		if (g_bfmeTimedOpHead != 0)
			((Gen_0007b5a0 *)g_bfmeTimedOpHead)->bfmeAppend(node);
		else
			g_bfmeTimedOpHead = node;
	}
	return node != 0;
}
