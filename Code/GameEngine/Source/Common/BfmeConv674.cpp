class BfmeThingDDE
{
public:
	int bfmeGoDDE();
	unsigned char m_bfmeHead[8];
	void *m_bfmeSub;
	unsigned char m_bfmeGap[0x3a];
	bool m_bfmeFlag;
	unsigned char m_bfmeGap2[0x11];
	int m_bfmeVal;
};

void bfmeNotifyDDE();

int BfmeThingDDE::bfmeGoDDE()
{
	if (m_bfmeFlag && m_bfmeSub != 0)
		bfmeNotifyDDE();
	return m_bfmeVal;
}
