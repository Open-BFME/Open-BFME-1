// cl: /Od
// A run given as a pair of ends passed on as a start and a length, built
// without optimisation. The callee is pinned by address; nothing here names it.

struct BfmeRangePF
{
	char *m_bfmeAt;				// 0x0
	char *m_bfmeEnd;			// 0x4
};

class BfmeThingPF
{
public:
	void bfmeGoPF(const BfmeRangePF *span, void *what);

	void bfmeDoPF(char *at, void *what, int many);
};

void BfmeThingPF::bfmeGoPF(const BfmeRangePF *span, void *what)
{
	bfmeDoPF(span->m_bfmeAt, what, span->m_bfmeEnd - span->m_bfmeAt);
}
