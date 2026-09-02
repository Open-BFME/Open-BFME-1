// Open-BFME5 conversions.

class BfmeMgrVNR;

class BfmeCellVNR
{
public:
	void bfmeCellUpdateVNR(BfmeMgrVNR *m, int idx);
	char m_bfmePad00[0x68];
};

class BfmeMgrVNR
{
public:
	void bfmeUpdateVNR(int idx);
	char m_bfmePad00[0x24];
	int m_bfme24;
	int m_bfme28;
	BfmeCellVNR *m_bfme2c;
};

void BfmeMgrVNR::bfmeUpdateVNR(int idx)
{
	if (idx >= 0 && idx < 0x10)
	{
		int n = m_bfme28 * m_bfme24;
		BfmeCellVNR *e = m_bfme2c + n;
		BfmeCellVNR *p = m_bfme2c;

		while (p != e)
		{
			p->bfmeCellUpdateVNR(this, idx);
			++p;
		}
	}
}
