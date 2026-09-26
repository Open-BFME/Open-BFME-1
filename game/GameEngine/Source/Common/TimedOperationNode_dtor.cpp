// Open-BFME5: TimedOperationNode destructor at 0x0007B8B0 (33B).
// Empty user dtor so MSVC stores vftable 0x010766E8 first, then the member
// holder at +8 Releases (dec +4; slot 0 with 1 on last ref). Same release
// shape as ReferencePointerReleaseThunk::release at 0x0007B890.

class TimedOperation
{
public:
	virtual void release(int deletingFlag);

	int decrementReferenceCount()
	{
		return --m_refCount;
	}

	int m_refCount;
};

class TimedOperationHolder
{
public:
	~TimedOperationHolder()
	{
		TimedOperation *current = m_value;
		if (current != 0)
		{
			if (current->decrementReferenceCount() <= 0)
				current->release(1);
		}
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

// ??1TimedOperationNode@@UAE@XZ
TimedOperationNode::~TimedOperationNode()
{
}
