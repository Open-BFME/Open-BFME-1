// cl: /O2
//
// Open-BFME7: TimedOperationNode's constructor at 0x0007BA00 installs
// vftable 0x010766E8.  Slot zero reaches 0x0007BA60 through ILT 0x00001FFA,
// and this wrapper calls the identified complete destructor at 0x0007B8B0
// through ILT 0x00018593 before conditionally invoking operator delete.

class TimedOperation
{
public:
	virtual void release(int deletingFlag);
	int m_refCount;
};

class TimedOperationHolder
{
public:
	~TimedOperationHolder()
	{
		TimedOperation *current = m_value;
		if (current != 0 && --current->m_refCount <= 0)
			current->release(1);
	}

	TimedOperation *m_value;
};

class TimedOperationNode
{
public:
	virtual ~TimedOperationNode();

private:
	void *m_next;
	TimedOperationHolder m_hold;
};

TimedOperationNode::~TimedOperationNode() {}
