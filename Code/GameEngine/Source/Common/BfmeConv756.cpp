class BfmeSubDQA
{
public:
	void bfmeCallDQA(void *arg);
};

struct BfmeOutDQA
{
	int m_bfmeA;
	BfmeSubDQA m_bfmeSub;
};

BfmeOutDQA *bfmeGoDQA(BfmeOutDQA *out, int *src, void *arg)
{
	volatile int tmp = 0;
	out->m_bfmeA = *src;
	out->m_bfmeSub.bfmeCallDQA(arg);
	return out;
}
