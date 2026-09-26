// cl: /Od
// A run given as a pair of ends passed on as a start and a length, built
// without optimisation. The callee is pinned by address; nothing here names it.

struct BfmeRangePI
{
	char *m_bfmeAt;				// 0x0
	char *m_bfmeEnd;			// 0x4
};

class BfmeThingPI
{
public:
	void bfmeGoPI(const BfmeRangePI *span, void *what);

	void bfmeDoPI(char *at, void *what, int many);
};

void BfmeThingPI::bfmeGoPI(const BfmeRangePI *span, void *what)
{
	bfmeDoPI(span->m_bfmeAt, what, span->m_bfmeEnd - span->m_bfmeAt);
}
