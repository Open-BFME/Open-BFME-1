extern "C" unsigned int g_bfmeDirtyZR;

struct BfmeItemZR
{
	int m_bfmeAZR;
	int m_bfmeBZR;
	int m_bfmeCZR;
};

class BfmeVecZR
{
public:
	void bfmeEraseZR(int index);

	unsigned char m_bfmeHeadZR[0x10];
	BfmeItemZR *m_bfmeItemsZR;
	int m_bfmeCountZR;
	unsigned char m_bfmeMidZR[0x18];
	char m_bfmeDirtyFlagZR;
};

void BfmeVecZR::bfmeEraseZR(int index)
{
	if (index < 0 || index >= m_bfmeCountZR)
		return;

	g_bfmeDirtyZR |= 1;

	for (int i = index; i < m_bfmeCountZR - 1; i++)
		m_bfmeItemsZR[i] = m_bfmeItemsZR[i + 1];

	m_bfmeCountZR--;
	m_bfmeDirtyFlagZR = 1;
}
