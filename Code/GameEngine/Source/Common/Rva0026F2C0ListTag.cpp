// Open-BFME6: convert 0x0026F2C0 list-tag probe, sibling of BfmeThingEGF.

class BfmeTimerF2C
{
public:
	int m_pad00[2];
	BfmeTimerF2C *m_alt;
	int m_pad0C[5];
	int m_deadline;
};

class BfmeSubF2C
{
public:
	bool bfmeActive();

	bool fastActive() const
	{
		if (!m_owner)
			return false;
		if (!m_timer)
			return false;
		BfmeTimerF2C *node = m_timer->m_alt;
		if (!node)
			node = m_timer;
		return node->m_deadline != 0x7FFFFFFF;
	}

	int m_head;
	int *m_owner;
	int m_gap[2];
	BfmeTimerF2C *m_timer;
};

class BfmeThingEGF
{
public:
	bool bfmeGoEGFc();

private:
	unsigned char m_headA[0x140];
	BfmeSubF2C *m_p;
	unsigned char m_headB[0x88];
	void *m_guard1cc;
	unsigned char m_headC[8];
	int m_state;
};

// ?bfmeGoEGFc@BfmeThingEGF@@QAE_NXZ
bool BfmeThingEGF::bfmeGoEGFc()
{
	if (!m_guard1cc)
		return false;

	switch (m_state)
	{
	case 1:
	case 4:
		{
			BfmeSubF2C *p = m_p;
			if (p && (p->fastActive() || p->bfmeActive()))
				return true;
		}
		break;
	}

	return false;
}
