class BfmeThingCGD
{
public:
	void bfmeOneCGD();
	void bfmeTwoCGD();
	void bfmeGoCGD();
	void *m_bfmeFirst;
	unsigned char m_bfmeGap[0xc069];
	bool m_bfmeBusy;
};

void bfmeGlobalCGD();

void BfmeThingCGD::bfmeGoCGD()
{
	if (m_bfmeFirst != 0)
	{
		m_bfmeBusy = true;
		bfmeOneCGD();
		bfmeGlobalCGD();
		bfmeTwoCGD();
		m_bfmeBusy = false;
	}
}
