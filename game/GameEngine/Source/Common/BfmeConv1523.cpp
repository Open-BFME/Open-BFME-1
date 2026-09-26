// Open-BFME5 conversions.

void bfmeFreeVNY(void *p, unsigned n);

struct BfmeNodeVNY
{
	BfmeNodeVNY *m_bfme00;
	BfmeNodeVNY *m_bfme04;
};

class BfmeOwnerVNY
{
public:
	void bfmeResetVNY();
	char m_bfmePad0000[0x1304];
	BfmeNodeVNY *m_bfme1304;
	int m_bfme1308;
	int m_bfme130c;
	int m_bfme1310;
	int m_bfme1314;
};

void BfmeOwnerVNY::bfmeResetVNY()
{
	BfmeNodeVNY *p = m_bfme1304->m_bfme00;

	while (p != m_bfme1304)
	{
		BfmeNodeVNY *n = p;

		p = p->m_bfme00;
		bfmeFreeVNY(n, 0x10);
	}
	m_bfme1304->m_bfme00 = m_bfme1304;
	m_bfme1304->m_bfme04 = m_bfme1304;
	m_bfme1308 = -2;
	m_bfme130c = -2;
	m_bfme1310 = -2;
	m_bfme1314 = -2;
}
