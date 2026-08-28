// cl: /Od
// Two runs, this record's own and the one the caller brought, passed on as four
// ends. Built without optimisation; the frame holds more than this body names.
// The callee is pinned by address.

void bfmeDoPQ(char *first, char *last, char *otherFirst, char *otherLast);

struct BfmeThingPQ
{
	void bfmeGoPQ(const BfmeThingPQ *other);

	char *m_bfmeAt;				// 0x0
	char *m_bfmeEnd;			// 0x4
};

void BfmeThingPQ::bfmeGoPQ(const BfmeThingPQ *other)
{
	unsigned char spare[0x10];

	bfmeDoPQ(m_bfmeAt, m_bfmeEnd, other->m_bfmeAt, other->m_bfmeEnd);
}
