// Six more: two tests reached through a back-step to the holder -- one over a
// vector's size, one counting a circular list -- and four guarded reads.

class BfmeVecCQ
{
public:
	int *bfmeEnd(void) const
	{
		return m_bfmeFinish;
	}

	int *bfmeBegin(void) const
	{
		return m_bfmeStart;
	}

	unsigned int bfmeSize(void) const
	{
		return bfmeEnd() - bfmeBegin();
	}

	unsigned char bfmeAny(void) const
	{
		return bfmeSize() > 0;
	}

	int *m_bfmeStart;					// +0x00
	int *m_bfmeFinish;					// +0x04
};

class BfmeHolderCQ
{
public:
	char m_bfmeHead[0x23C];					// +0x000
	BfmeVecCQ m_bfmeVector;					// +0x23C
};

class Gen_00234180
{
public:
	unsigned char bfmeHasAny(void) const;
};

// ?bfmeHasAny@Gen_00234180@@QBEEXZ
unsigned char Gen_00234180::bfmeHasAny(void) const
{
	BfmeHolderCQ *holder = *(BfmeHolderCQ **)((char *)this - 0xE0);

	return holder->m_bfmeVector.bfmeAny();
}

class BfmeNodeCQ
{
public:
	BfmeNodeCQ *m_bfmeNext;					// +0x00
};

class Gen_00235E00
{
public:
	bool bfmeEmpty(void) const;
};

// ?bfmeEmpty@Gen_00235E00@@QBE_NXZ
bool Gen_00235E00::bfmeEmpty(void) const
{
	BfmeNodeCQ *head = *(BfmeNodeCQ **)((char *)this - 0xAC);
	BfmeNodeCQ *node = head->m_bfmeNext;

	int count = 0;

	while (node != head)
	{
		node = node->m_bfmeNext;

		++count;
	}

	return count == 0;
}

class BfmeTimerCQ
{
public:
	int m_bfmeHead[8];					// +0x00
	int m_bfmeDeadline;					// +0x20
};

class Gen_0026E570
{
public:
	bool bfmeActive(void) const;

private:
	int m_bfmeHead;						// +0x00
	int *m_bfmeOwner;					// +0x04
	int m_bfmeGap[2];					// +0x08
	BfmeTimerCQ *m_bfmeTimer;				// +0x10
};

// ?bfmeActive@Gen_0026E570@@QBE_NXZ
bool Gen_0026E570::bfmeActive(void) const
{
	if (!m_bfmeOwner)
		return false;

	if (!m_bfmeTimer)
		return false;

	return m_bfmeTimer->m_bfmeDeadline != 0x7FFFFFFF;
}

class BfmeSlotCQ
{
public:
	char m_bfmeHead[0xA8];					// +0x00
	bool m_bfmeOpen;					// +0xA8
};

class Gen_0026EA30
{
public:
	bool bfmeIsOpen(int index) const;

private:
	int m_bfmeHead[122];					// +0x000
	BfmeSlotCQ *m_bfmeSlots[8];				// +0x1E8
};

// ?bfmeIsOpen@Gen_0026EA30@@QBE_NH@Z
bool Gen_0026EA30::bfmeIsOpen(int index) const
{
	BfmeSlotCQ *slot = m_bfmeSlots[index];

	if (slot)
		return slot->m_bfmeOpen;

	return false;
}

class BfmeTaskCQ
{
public:
	int m_bfmeHead[22];					// +0x00
	int *m_bfmeHandle;					// +0x58
	int m_bfmeIndex;					// +0x5C
};

class Gen_0026FD20
{
public:
	int bfmeReady(void) const;

private:
	int m_bfmeHead[12];					// +0x00
	BfmeTaskCQ *m_bfmeTask;					// +0x30
};

// ?bfmeReady@Gen_0026FD20@@QBEHXZ
int Gen_0026FD20::bfmeReady(void) const
{
	if (m_bfmeTask != 0 && m_bfmeTask->m_bfmeHandle != 0 && m_bfmeTask->m_bfmeIndex == -1)
		return 1;

	return 0;
}

class BfmeSourceCQ
{
public:
	int m_bfmeHead[15];					// +0x00
	int m_bfmeValue;					// +0x3C
	bool m_bfmeForced;					// +0x40
};

class BfmeStateCQ
{
public:
	int m_bfmeHead[36];					// +0x00
	unsigned int m_bfmeFlags;				// +0x90
};

class Gen_00279750
{
public:
	int bfmeValue(void) const;

private:
	int m_bfmeHead;						// +0x00
	BfmeSourceCQ *m_bfmeSource;				// +0x04
	BfmeStateCQ *m_bfmeState;				// +0x08
};

// ?bfmeValue@Gen_00279750@@QBEHXZ
int Gen_00279750::bfmeValue(void) const
{
	if (m_bfmeSource->m_bfmeForced && !(m_bfmeState->m_bfmeFlags & 0x400))
		return 0;

	return m_bfmeSource->m_bfmeValue;
}
