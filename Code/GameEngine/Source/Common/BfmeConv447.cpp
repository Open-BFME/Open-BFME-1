class BfmeThingBDG
{
public:
	void bfmeDoBDG();
	void bfmeGoBDG(void *what);
	unsigned char m_bfmeHead[0x264];
	int m_bfmeState;
};

void BfmeThingBDG::bfmeGoBDG(void *what)
{
	if (m_bfmeState == 1)
		bfmeDoBDG();
}
