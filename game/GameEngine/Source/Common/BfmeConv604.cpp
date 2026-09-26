class BfmeOneCHF
{
public:
	void bfmeOneCHF();
};

class BfmeTwoCHF
{
public:
	void bfmeTwoCHF();
	unsigned char m_bfmeHead[0x44];
	bool m_bfmeFlag;
};

extern BfmeOneCHF *bfmeTheOneCHF;
extern BfmeTwoCHF *bfmeTheTwoCHF;

void bfmeGoCHF()
{
	BfmeTwoCHF *two = bfmeTheTwoCHF;
	if (two->m_bfmeFlag)
	{
		bfmeTheOneCHF->bfmeOneCHF();
		two->bfmeTwoCHF();
		bfmeTheTwoCHF->m_bfmeFlag = false;
	}
}
