class BfmeSubDOF
{
public:
	void bfmeCallDOF(void *arg);
};

struct BfmeOutDOF
{
	int m_bfmeA;
	BfmeSubDOF m_bfmeSub;
};

BfmeOutDOF *bfmeGoDOF(BfmeOutDOF *out, int *src, void *arg)
{
	volatile int tmp = 0;
	out->m_bfmeA = *src;
	out->m_bfmeSub.bfmeCallDOF(arg);
	return out;
}
