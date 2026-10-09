class BfmeOwnCH
{
public:
	BfmeOwnCH *bfmeMakeCH(void *other);
};

class TeamsInfoRec
{
public:
	void clear();
};

class BfmeThingBVB
{
public:
	void bfmeGoBVB(BfmeThingBVB *other);
	unsigned char m_bfmeHead[0x630];
	TeamsInfoRec m_bfmeSub;
};

void BfmeThingBVB::bfmeGoBVB(BfmeThingBVB *other)
{
	TeamsInfoRec *sub = &m_bfmeSub;
	sub->clear();
	reinterpret_cast<BfmeOwnCH *>(sub)->bfmeMakeCH(&other->m_bfmeSub);
}
