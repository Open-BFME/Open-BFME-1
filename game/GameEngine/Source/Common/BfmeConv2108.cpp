class BfmeEntryZG
{
public:
	void bfmeStepZG();
	void bfmeFinishZG(void *slot, bool flag);

	unsigned char m_bfmeHeadZG[0x20];
	int m_bfme20ZG;
	unsigned char m_bfmeGapZG[0x18];
	int m_bfme3CZG;
};

void BfmeEntryZG::bfmeStepZG()
{
	if (m_bfme20ZG != 3)
		return;

	m_bfme20ZG = 4;
	bfmeFinishZG(&m_bfme3CZG, false);
}
