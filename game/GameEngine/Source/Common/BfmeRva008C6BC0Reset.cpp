// Reset four fixed slots and a counted array, each released then pointed at
// the fallback database.

class BfmeSlotEL
{
public:
	virtual void destroy(void);
	virtual void release(void);
};

extern int g_bfmeFallbackDB;					// retail 0x013379BC

class Gen_008C6BC0
{
public:
	void bfmeReset(void);

private:
	int m_bfmeHead[20];					// +0x00
	int m_bfmeCount;					// +0x50
	int m_bfmeGap54;					// +0x54
	int *m_bfmeArr;						// +0x58
	int m_bfmeGap5C[3];					// +0x5C
	BfmeSlotEL *m_bfmeFour[4];				// +0x68
};

// ?bfmeReset@Gen_008C6BC0@@QAEXXZ
void Gen_008C6BC0::bfmeReset(void)
{
	BfmeSlotEL **slot = m_bfmeFour;
	int remain = 4;

	do
	{
		BfmeSlotEL *cur = *slot;

		if (cur)
			cur->release();

		*slot = (BfmeSlotEL *)g_bfmeFallbackDB;
		++slot;
	} while (--remain);

	int count = m_bfmeCount;
	int index = 0;

	if (count > 0)
	{
		do
		{
			if (*(volatile int *)((unsigned)m_bfmeArr + index * 4) != 0)
				((BfmeSlotEL *)m_bfmeArr[index])->release();

			m_bfmeArr[index] = g_bfmeFallbackDB;
			++index;
		} while (index < count);
	}
}
