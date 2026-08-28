struct BfmeSlotWA
{
	void *m_bfmeWhat;
	unsigned char m_bfmeRest[0x2c];
};

class BfmeThingWA
{
public:
	void bfmeEnsureWA();
	void *bfmeGetWA();
	unsigned char m_bfmeHead[0x1c];
	BfmeSlotWA m_bfmeSlots[120];
	unsigned char m_bfmeGapOne[0x28];
	int m_bfmeIndex;
	unsigned char m_bfmeGapTwo[0x26];
	bool m_bfmeMany;
	unsigned char m_bfmeGapThree[0x19];
	int m_bfmeState;
};

void *BfmeThingWA::bfmeGetWA()
{
	if (m_bfmeState == -1)
		bfmeEnsureWA();
	if (!m_bfmeMany)
		return m_bfmeSlots[0].m_bfmeWhat;
	return m_bfmeSlots[m_bfmeIndex].m_bfmeWhat;
}
