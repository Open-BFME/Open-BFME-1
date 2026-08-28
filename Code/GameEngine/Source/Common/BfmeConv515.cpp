extern "C" unsigned char bfmeTextBQF[];

class BfmeThingBQF
{
public:
	void bfmeBaseBQF(void *text, int flag);
	BfmeThingBQF *bfmeInitBQF();
	unsigned char m_bfmeHead[0x70];
	int m_bfmeZero;
	bool m_bfmeFlag;
};

BfmeThingBQF *BfmeThingBQF::bfmeInitBQF()
{
	bfmeBaseBQF(bfmeTextBQF, 0);
	m_bfmeZero = 0;
	m_bfmeFlag = false;
	return this;
}
