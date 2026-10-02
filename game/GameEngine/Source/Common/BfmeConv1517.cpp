// Open-BFME5 conversions.

class BfmeThingNH
{
public:
	int bfmeSizeNH(void);

private:
	unsigned char m_bfmeHead[8];
	void *m_bfmeWide;
	unsigned char m_bfmeGap[0x14];
	void *m_bfmeOne;
	void *m_bfmeTwo;
	void *m_bfmeThree;
	void *m_bfmeFour;
	void *m_bfmeFive;
	void *m_bfmeSix;
	void *m_bfmeSeven;
	void *m_bfmeEight;
};

class BfmeThingVNQ
{
public:
	int bfmeTotalVNQ();
	char m_bfmePad00[0xc];
	BfmeThingNH **m_bfme0c;
	char m_bfmePad10[8];
	int m_bfme18;
	char m_bfmePad1c[0x14];
	int m_bfme30;
};

int BfmeThingVNQ::bfmeTotalVNQ()
{
	int n = m_bfme18;
	int total = (m_bfme30 + n) * 4 + 0x38;
	int i = 0;

	if (n > 0)
	{
		do
		{
			BfmeThingNH *p = m_bfme0c[i];

			if (p != 0)
				total += p->bfmeSizeNH();
			++i;
		} while (i < m_bfme18);
	}
	return total;
}
