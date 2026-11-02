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

// The call goes through ILT 0x00036548 (body 0x0042D170), which the ledger defines
// as ?j_00036548@@YAXXZ; it is named through a member pointer.
extern void j_00036548(void);

BfmeOutDOG *bfmeGoDOG(BfmeOutDOG *out, int *src, void *arg)
{
	volatile int tmp = 0;
	out->m_bfmeA = *src;
	union { void (*raw)(void); void (BfmeSubDOG::*member)(void *); } call;
	call.raw = j_00036548;
	(out->m_bfmeSub.*call.member)(arg);
	return out;
}
