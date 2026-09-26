// cl: /Od
// Where a byte first stands at or after a given place, counted from the start,
// or nothing when it does not stand there at all. Built without optimisation;
// the searcher is pinned by address.

char *bfmeSearchQW(char *first, char *last, unsigned char one);

struct BfmeThingQW
{
	int bfmeFindQW(unsigned char what, unsigned int from);

	char *m_bfmeAt;				// 0x0
	char *m_bfmeEnd;			// 0x4
};

int BfmeThingQW::bfmeFindQW(unsigned char what, unsigned int from)
{
	if (from > (unsigned int)(m_bfmeEnd - m_bfmeAt))
		return -1;

	unsigned char one = what;

	char *found = bfmeSearchQW(m_bfmeAt + from, m_bfmeEnd, one);

	return (found != m_bfmeEnd) ? (int)(found - m_bfmeAt) : -1;
}
