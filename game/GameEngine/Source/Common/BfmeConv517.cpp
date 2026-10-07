struct BfmeSrcBRC
{
	unsigned char m_bfmeHead[4];
	unsigned char m_bfmeRest[4];
};

// The call goes through ILT 0x0002F333 to the matched Script copy
// constructor at 0x0035B550 (ilt_oracle: CONFIRMED).
class Script
{
public:
	Script(const Script &that);
};

struct BfmeSubBRC
{
	void bfmeSetBRC(void *what) { ((Script *)this)->Script::Script(*(const Script *)what); }
	unsigned char m_bfmeHead[4];
};

class BfmeThingBRC
{
public:
	BfmeThingBRC *bfmeGoBRC(BfmeSrcBRC *src);
	int m_bfmeZero;
	BfmeSubBRC m_bfmeSub;
};

BfmeThingBRC *BfmeThingBRC::bfmeGoBRC(BfmeSrcBRC *src)
{
	m_bfmeZero = 0;
	m_bfmeSub.bfmeSetBRC(src->m_bfmeRest);
	return this;
}
