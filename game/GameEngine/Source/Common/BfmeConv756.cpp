class BfmeSubDQA
{
};

void j_0003da3c();

// The generic thunk name has no arguments; retain the target's thiscall ABI here.
union BfmeCallDQA
{
	void (*function)(void);
	void (BfmeSubDQA::*member)(void *);
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
	BfmeCallDQA call;
	call.function = &j_0003da3c;
	(out->m_bfmeSub.*call.member)(arg);
	return out;
}
