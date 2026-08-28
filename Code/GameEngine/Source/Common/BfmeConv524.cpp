struct BfmeSubBSD
{
	unsigned char m_bfmeHead[4];
};

void bfmeDoBSD(BfmeSubBSD *sub, void *what);

class BfmeThingBSD
{
public:
	BfmeThingBSD *bfmeGoBSD(char kind, void *what);
	char m_bfmeKind;
	unsigned char m_bfmePad[3];
	BfmeSubBSD m_bfmeSub;
};

BfmeThingBSD *BfmeThingBSD::bfmeGoBSD(char kind, void *what)
{
	m_bfmeKind = kind;
	bfmeDoBSD(&m_bfmeSub, what);
	return this;
}
