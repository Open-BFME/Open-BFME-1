// cl: /O2 /Ob0

class BfmeHold9DB
{
public:
	virtual void bfmeGo9DB(int);
	int m_04;
	int m_08;
};

class BfmeThing9DB
{
public:
	void bfmeFlag9DB(unsigned);
	char m_00[4];
	unsigned char m_04;
	char m_05[7];
	int m_0C;
	int m_10;
	unsigned m_14;
	BfmeHold9DB *m_18;
	char m_1C[0x18];
	void *m_34;
	void *m_38;
};

void BfmeThing9DB::bfmeFlag9DB(unsigned n)
{
	if (m_04)
	{
		if (!m_38 || !m_34)
		{
			if (n > m_14)
			{
				switch (m_0C)
				{
				case 1:
					if (m_18)
						m_18->m_08 = 2;
					m_04 = 0;
					break;
				}
			}
		}
	}
	if (m_18 && m_18->m_08 == 3)
	{
		m_18->bfmeGo9DB(1);
		m_18 = 0;
	}
}
