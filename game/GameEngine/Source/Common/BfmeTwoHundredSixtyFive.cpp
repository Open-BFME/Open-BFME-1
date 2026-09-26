// cl: /Od
// A run given as a pair of ends passed on as a start and a length, built
// without optimisation. The callee is pinned by address; nothing here names it.

struct BfmeRangePE
{
	char *m_bfmeAt;				// 0x0
	char *m_bfmeEnd;			// 0x4
};

class BfmeThingPE
{
public:
	void bfmeGoPE(const BfmeRangePE *span, void *what);

	void bfmeDoPE(char *at, void *what, int many);
};

void BfmeThingPE::bfmeGoPE(const BfmeRangePE *span, void *what)
{
	bfmeDoPE(span->m_bfmeAt, what, span->m_bfmeEnd - span->m_bfmeAt);
}
