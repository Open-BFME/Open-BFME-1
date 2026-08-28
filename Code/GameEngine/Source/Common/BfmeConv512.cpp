void bfmeFreeBQC(void *what, unsigned int bytes);

struct BfmeSubBQC
{
	void bfmeStepBQC();
	void *m_bfmeWhat;
};

class BfmeThingBQC
{
public:
	void bfmeGoBQC();
	unsigned char m_bfmeHead[0x30];
	BfmeSubBQC m_bfmeSub;
};

void BfmeThingBQC::bfmeGoBQC()
{
	m_bfmeSub.bfmeStepBQC();
	void *what = m_bfmeSub.m_bfmeWhat;
	if (what != 0)
		bfmeFreeBQC(what, 0x10);
}
