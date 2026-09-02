extern int g_bfmeRingReset;

struct BfmeResetBlock
{
	bool m_bfmeFlag;
	int m_bfmeWord;
	BfmeResetBlock *m_bfmeNext;
	BfmeResetBlock *m_bfmePrev;
};

class BfmeRingOwnerA
{
public:
	void bfmeRelease(int value);
	void bfmeClear(void)
	{
		if (m_bfmeCount != 0)
		{
			bfmeRelease(m_bfmeBlock->m_bfmeWord);
			m_bfmeBlock->m_bfmeNext = m_bfmeBlock;
			m_bfmeBlock->m_bfmeWord = 0;
			m_bfmeBlock->m_bfmePrev = m_bfmeBlock;
			m_bfmeCount = 0;
		}
	}

private:
	BfmeResetBlock *m_bfmeBlock;
	int m_bfmeCount;
};

class BfmeRingOwnerB
{
public:
	void bfmeRelease(int value);
	void bfmeClear(void)
	{
		if (m_bfmeCount != 0)
		{
			bfmeRelease(m_bfmeBlock->m_bfmeWord);
			m_bfmeBlock->m_bfmeNext = m_bfmeBlock;
			m_bfmeBlock->m_bfmeWord = 0;
			m_bfmeBlock->m_bfmePrev = m_bfmeBlock;
			m_bfmeCount = 0;
		}
	}

private:
	BfmeResetBlock *m_bfmeBlock;
	int m_bfmeCount;
};

class Gen_00587C50
{
public:
	void bfmeReset(void);

private:
	char m_bfme00[0x18];
	BfmeRingOwnerA m_bfmeFirst;
	int m_bfme20;
	BfmeRingOwnerB m_bfmeSecond;
};

// ?bfmeReset@Gen_00587C50@@QAEXXZ
void Gen_00587C50::bfmeReset(void)
{
	g_bfmeRingReset = 0;
	m_bfmeFirst.bfmeClear();
	m_bfmeSecond.bfmeClear();
}
