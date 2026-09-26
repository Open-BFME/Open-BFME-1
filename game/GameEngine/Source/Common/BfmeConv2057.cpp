class BfmeSlotGD
{
public:
	void *m_bfmePtrGD;
	unsigned char m_bfmeRestGD[12];
};

class BfmeRingGD
{
public:
	char bfmePushGD(void *p, int unused);
	void bfmeProcessGD(int i, void *p);

	unsigned char m_bfmeHeadGD2[0x4e14];
	BfmeSlotGD m_bfmeSlotsGD[256];
	unsigned char m_bfmeGapGD[4];
	int m_bfmeHeadGD;
};

char BfmeRingGD::bfmePushGD(void *p, int unused)
{
	int i = m_bfmeHeadGD;

	if (m_bfmeSlotsGD[i].m_bfmePtrGD == 0)
		return 0;

	bfmeProcessGD(i, p);

	m_bfmeSlotsGD[m_bfmeHeadGD].m_bfmePtrGD = 0;

	++m_bfmeHeadGD;

	if ((unsigned int)m_bfmeHeadGD >= 0x100)
		m_bfmeHeadGD = 0;

	return 1;
}
