struct BfmeVec4CMB
{
	void *m_bfmeA;
	void *m_bfmeB;
	void *m_bfmeC;
	void *m_bfmeD;
};

class BfmeThingCMB
{
public:
	void bfmeUpdateCMB();
	void bfmeGoCMB(BfmeVec4CMB *out);
	unsigned char m_bfmeHead[0x1c];
	BfmeVec4CMB m_bfmeCache;
	unsigned char m_bfmeGap[4];
	bool m_bfmeFlag;
};

void BfmeThingCMB::bfmeGoCMB(BfmeVec4CMB *out)
{
	if (out != 0)
	{
		if (m_bfmeFlag)
			bfmeUpdateCMB();
		*out = m_bfmeCache;
	}
}
