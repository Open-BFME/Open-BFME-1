// cl: /Od
// A stretch of one byte put into the run at a given place, after the place has
// been checked against the length and the new length against the limit. The
// record is handed back. Built without optimisation; all three callees are
// pinned by address.

// retail callee at 0x006434C0, reached through the ILT thunk at 0x000132CD;
// declaration only, the body is game/gen_small/fun_004.cpp
struct Gen_006434c0 { void m(); };

struct BfmeThingQX
{
	BfmeThingQX *bfmeInsertQX(unsigned int where, unsigned int many, unsigned char what);

	void bfmeLengthErrorQX(void);

	void bfmeDoInsertQX(char *at, unsigned int many, unsigned char what);

	char *m_bfmeAt;				// 0x0
	char *m_bfmeEnd;			// 0x4
};

BfmeThingQX *BfmeThingQX::bfmeInsertQX(unsigned int where, unsigned int many, unsigned char what)
{
	if (where > (unsigned int)(m_bfmeEnd - m_bfmeAt))
		((Gen_006434c0 *)this)->m();

	if ((unsigned int)(m_bfmeEnd - m_bfmeAt) > 0xfffffffe - many)
		bfmeLengthErrorQX();

	char *at = m_bfmeAt;

	bfmeDoInsertQX(at + where, many, what);

	return this;
}
