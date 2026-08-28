class BfmeGlobalBZF
{
public:
	void bfmeTwoBZF();
	void bfmeThreeBZF(int value);
};

class BfmeSubBZF
{
public:
	void bfmeOneBZF();
};

class BfmeThingBZF
{
public:
	void bfmeGoBZF();
	unsigned char m_bfmeHead[0x170];
	BfmeSubBZF m_bfmeSub;
};

extern BfmeGlobalBZF *bfmeTheBZF;

void BfmeThingBZF::bfmeGoBZF()
{
	m_bfmeSub.bfmeOneBZF();
	bfmeTheBZF->bfmeTwoBZF();
	bfmeTheBZF->bfmeThreeBZF(0);
}
