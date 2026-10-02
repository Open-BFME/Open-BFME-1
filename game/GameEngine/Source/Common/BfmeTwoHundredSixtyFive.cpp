// cl: /Od
// A run given as a pair of ends passed on as a start and a length, built
// without optimisation. It forwards to BfmeThingPE::bfmeDoPE.

struct BfmeRangePE
{
	char *m_bfmeAt;				// 0x0
	char *m_bfmeEnd;			// 0x4
};

class BfmeThingPE
{
public:
	void bfmeGoPE(const BfmeRangePE *span, void *what);

	unsigned int bfmeDoPE(const char *at, unsigned int what, unsigned int many);
};

void BfmeThingPE::bfmeGoPE(const BfmeRangePE *span, void *what)
{
	bfmeDoPE(span->m_bfmeAt, (unsigned int)what, span->m_bfmeEnd - span->m_bfmeAt);
}
