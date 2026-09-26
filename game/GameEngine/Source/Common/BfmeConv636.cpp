class BfmeACRC
{
public:
	void bfmeOneCRC(void *b, void *c);
};

class BfmeBCRC
{
public:
	void bfmeTwoCRC(void *b, void *c);
};

struct BfmeThingCRC
{
	unsigned char m_bfmeHead[0x230];
	BfmeACRC *m_bfmeA;
	BfmeBCRC *m_bfmeB;
};

void bfmeGoCRC(BfmeThingCRC *thing, void *b, void *c)
{
	BfmeACRC *a = thing->m_bfmeA;
	if (a != 0)
		a->bfmeOneCRC(b, c);
	BfmeBCRC *bb = thing->m_bfmeB;
	if (bb != 0)
		bb->bfmeTwoCRC(b, c);
}
