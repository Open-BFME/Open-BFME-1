extern "C" unsigned char bfmeVftSH[];

class BfmeSubSH
{
public:
	void bfmeTailSH();
};

class BfmeThingSH
{
public:
	void bfmeResetSH();
	void *m_bfmeVft;
	BfmeSubSH *m_bfmeSub;
};

void BfmeThingSH::bfmeResetSH()
{
	m_bfmeVft = bfmeVftSH;
	BfmeSubSH *sub = m_bfmeSub;
	if (sub != 0)
		sub->bfmeTailSH();
}
