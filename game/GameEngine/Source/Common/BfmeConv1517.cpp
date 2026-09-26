// Open-BFME5 conversions.

class BfmeItemVNQ
{
public:
	int bfmeSizeVNQ();
};

class BfmeThingVNQ
{
public:
	int bfmeTotalVNQ();
	char m_bfmePad00[0xc];
	BfmeItemVNQ **m_bfme0c;
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
			BfmeItemVNQ *p = m_bfme0c[i];

			if (p != 0)
				total += p->bfmeSizeVNQ();
			++i;
		} while (i < m_bfme18);
	}
	return total;
}
