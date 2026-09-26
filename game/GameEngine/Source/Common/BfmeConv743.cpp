class BfmeSubDOD
{
public:
	void bfmeCallDOD(void *arg);
};

struct BfmeOutDOD
{
	int m_bfmeA;
	BfmeSubDOD m_bfmeSub;
};

BfmeOutDOD *bfmeGoDOD(BfmeOutDOD *out, int *src, void *arg)
{
	volatile int tmp = 0;
	out->m_bfmeA = *src;
	out->m_bfmeSub.bfmeCallDOD(arg);
	return out;
}
