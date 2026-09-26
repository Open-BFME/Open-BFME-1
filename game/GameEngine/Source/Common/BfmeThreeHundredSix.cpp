// cl: /Od
// A stretch of one byte put into the run at a given place, after the place has
// been checked against the length and the new length against the limit. The
// record is handed back. Built without optimisation; all three callees are
// pinned by address.

struct BfmeThingQX
{
	BfmeThingQX *bfmeInsertQX(unsigned int where, unsigned int many, unsigned char what);

	void bfmeRangeErrorQX(void);

	void bfmeLengthErrorQX(void);

	void bfmeDoInsertQX(char *at, unsigned int many, unsigned char what);

	char *m_bfmeAt;				// 0x0
	char *m_bfmeEnd;			// 0x4
};

BfmeThingQX *BfmeThingQX::bfmeInsertQX(unsigned int where, unsigned int many, unsigned char what)
{
	if (where > (unsigned int)(m_bfmeEnd - m_bfmeAt))
		bfmeRangeErrorQX();

	if ((unsigned int)(m_bfmeEnd - m_bfmeAt) > 0xfffffffe - many)
		bfmeLengthErrorQX();

	char *at = m_bfmeAt;

	bfmeDoInsertQX(at + where, many, what);

	return this;
}
