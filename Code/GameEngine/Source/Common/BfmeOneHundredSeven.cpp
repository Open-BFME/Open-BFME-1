// Two siblings: the same reset clearing three rows a column at a time.

class Gen_00490990
{
public:
	void bfmeReset(void);
private:
	int m_bfmeGap[2];							// +0x00
	int m_bfmeCount;							// +0x08
	int m_bfmeGap2;								// +0x0c
	int m_bfmeFirst[8];							// +0x10
	int m_bfmeSecond[8];						// +0x30
	int m_bfmeThird[8];							// +0x50
};

void Gen_00490990::bfmeReset(void)
{
	m_bfmeCount = 0;

	for (int index = 0; index < 8; ++index)
	{
		m_bfmeFirst[index] = 0;
		m_bfmeSecond[index] = 0;
		m_bfmeThird[index] = 0;
	}
}

class Gen_00490C50
{
public:
	void bfmeReset(void);
private:
	int m_bfmeGap[2];							// +0x00
	int m_bfmeCount;							// +0x08
	int m_bfmeGap2;								// +0x0c
	int m_bfmeFirst[8];							// +0x10
	int m_bfmeSecond[8];						// +0x30
	int m_bfmeThird[8];							// +0x50
};

void Gen_00490C50::bfmeReset(void)
{
	m_bfmeCount = 0;

	for (int index = 0; index < 8; ++index)
	{
		m_bfmeFirst[index] = 0;
		m_bfmeSecond[index] = 0;
		m_bfmeThird[index] = 0;
	}
}
