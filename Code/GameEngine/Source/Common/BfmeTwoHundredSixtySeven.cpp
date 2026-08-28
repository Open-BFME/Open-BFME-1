// cl: /Od
// A run given as a pair of ends passed on as a start and a length, built
// without optimisation. The callee is pinned by address; nothing here names it.

struct BfmeRangePG
{
	char *m_bfmeAt;				// 0x0
	char *m_bfmeEnd;			// 0x4
};

class BfmeThingPG
{
public:
	void bfmeGoPG(const BfmeRangePG *span, void *what);

	void bfmeDoPG(char *at, void *what, int many);
};

void BfmeThingPG::bfmeGoPG(const BfmeRangePG *span, void *what)
{
	bfmeDoPG(span->m_bfmeAt, what, span->m_bfmeEnd - span->m_bfmeAt);
}
