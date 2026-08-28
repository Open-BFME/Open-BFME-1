class BfmeSubDOG
{
public:
	void bfmeCallDOG(void *arg);
};

struct BfmeOutDOG
{
	int m_bfmeA;
	BfmeSubDOG m_bfmeSub;
};

BfmeOutDOG *bfmeGoDOG(BfmeOutDOG *out, int *src, void *arg)
{
	volatile int tmp = 0;
	out->m_bfmeA = *src;
	out->m_bfmeSub.bfmeCallDOG(arg);
	return out;
}
