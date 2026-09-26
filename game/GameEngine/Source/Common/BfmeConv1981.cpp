class BfmeArgETB;
class BfmeHostETB;

class BfmeItemETB
{
public:
	int bfmeBusyETB();
	char bfmeRunETB(BfmeHostETB *host, BfmeArgETB *arg, int mode);
};

class BfmeSinkETB
{
public:
	void bfmeNotifyETB(BfmeItemETB *item, int first, BfmeArgETB *arg, int second);
};

class BfmeHostETB
{
public:
	void bfmeApplyETB(BfmeArgETB *arg);
	void bfmeFinishETB(int mode);

	unsigned char m_bfmeHeadETB[0x94];
	char m_bfme94ETB;
	unsigned char m_bfmeMid1ETB[0x157];
	BfmeSinkETB *m_bfme1ecETB;
	unsigned char m_bfmeMid2ETB[0x7c];
	BfmeItemETB *m_bfme26cETB[4];
	int m_bfme27cETB;
	unsigned char m_bfmeMid3ETB[0xc4];
	char m_bfme344ETB;
};

void BfmeHostETB::bfmeApplyETB(BfmeArgETB *arg)
{
	if (arg == 0)
		return;

	if ((m_bfme94ETB & 0x10) != 0)
		return;

	BfmeItemETB *item = m_bfme26cETB[m_bfme27cETB];

	if (item == 0)
		return;

	if (item->bfmeBusyETB() != 0)
		return;

	char ok = item->bfmeRunETB(this, arg, 0);

	if (m_bfme1ecETB != 0)
		m_bfme1ecETB->bfmeNotifyETB(item, 0, arg, 0);

	if (ok != 0)
		bfmeFinishETB(1);

	m_bfme344ETB &= 0xfd;
}
