// cl: /Od
// This record's own run and a text of the caller's passed on as four ends, the
// text measured by the worker below. Built without optimisation; both callees
// are pinned by address.

int bfmeMakeOX(void *one);

void bfmeDoPW(char *first, char *last, char *otherFirst, char *otherLast);

struct BfmeThingPW
{
	void bfmeGoPW(char *at);

	char *m_bfmeAt;				// 0x0
	char *m_bfmeEnd;			// 0x4
};

void BfmeThingPW::bfmeGoPW(char *at)
{
	unsigned char spare[0x10];

	bfmeDoPW(m_bfmeAt, m_bfmeEnd, at, at + bfmeMakeOX(at));
}
