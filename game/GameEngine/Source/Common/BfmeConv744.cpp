class BfmeSubDOE
{
public:
	void bfmeCallDOE(void *arg);
};

struct BfmeOutDOE
{
	int m_bfmeA;
	BfmeSubDOE m_bfmeSub;
};

BfmeOutDOE *bfmeGoDOE(BfmeOutDOE *out, int *src, void *arg)
{
	volatile int tmp = 0;
	out->m_bfmeA = *src;
	out->m_bfmeSub.bfmeCallDOE(arg);
	return out;
}
