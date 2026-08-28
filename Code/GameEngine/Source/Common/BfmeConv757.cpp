class BfmeSubDQB
{
public:
	void bfmeCallDQB(void *arg);
};

struct BfmeOutDQB
{
	int m_bfmeA;
	BfmeSubDQB m_bfmeSub;
};

BfmeOutDQB *bfmeGoDQB(BfmeOutDQB *out, int *src, void *arg)
{
	volatile int tmp = 0;
	out->m_bfmeA = *src;
	out->m_bfmeSub.bfmeCallDQB(arg);
	return out;
}
