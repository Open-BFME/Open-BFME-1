// cl: /Od
// A run given as a pair of ends passed on as a start and a length, built
// without optimisation. The callee is pinned by address; nothing here names it.

struct BfmeRangePI
{
	char *m_bfmeAt;				// 0x0
	char *m_bfmeEnd;			// 0x4
};

// The helper the run below calls is retail's BfmeS1155::bfmeFind1155 (its
// three arguments are pushed and its this comes from the caller's this).
class BfmeS1155
{
public:
	unsigned int bfmeFind1155(const char *s, unsigned int pos, unsigned int n);
};

class BfmeThingPI
{
public:
	void bfmeGoPI(const BfmeRangePI *span, void *what);
};

void BfmeThingPI::bfmeGoPI(const BfmeRangePI *span, void *what)
{
	reinterpret_cast<BfmeS1155 *>(this)->bfmeFind1155(
		span->m_bfmeAt, reinterpret_cast<unsigned int>(what),
		(unsigned int)(span->m_bfmeEnd - span->m_bfmeAt));
}
