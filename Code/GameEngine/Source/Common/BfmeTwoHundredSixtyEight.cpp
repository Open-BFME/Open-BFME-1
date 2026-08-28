// cl: /Od
// A run given as a pair of ends passed on as a start and a length, built
// without optimisation. The callee is pinned by address; nothing here names it.

struct BfmeRangePH
{
	char *m_bfmeAt;				// 0x0
	char *m_bfmeEnd;			// 0x4
};

class BfmeThingPH
{
public:
	void bfmeGoPH(const BfmeRangePH *span, void *what);

	void bfmeDoPH(char *at, void *what, int many);
};

void BfmeThingPH::bfmeGoPH(const BfmeRangePH *span, void *what)
{
	bfmeDoPH(span->m_bfmeAt, what, span->m_bfmeEnd - span->m_bfmeAt);
}
