// cl: /Od
// A run given as a pair of ends passed on as a start and a length, built
// without optimisation. The callee is pinned by address; nothing here names it.

struct BfmeRangePJ
{
	char *m_bfmeAt;				// 0x0
	char *m_bfmeEnd;			// 0x4
};

class BfmeThingPJ
{
public:
	void bfmeGoPJ(const BfmeRangePJ *span, void *what);

	void bfmeDoPJ(char *at, void *what, int many);
};

void BfmeThingPJ::bfmeGoPJ(const BfmeRangePJ *span, void *what)
{
	bfmeDoPJ(span->m_bfmeAt, what, span->m_bfmeEnd - span->m_bfmeAt);
}
