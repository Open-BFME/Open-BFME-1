extern "C" unsigned char bfmeVftCNIa[];
extern "C" unsigned char bfmeVftCNIb[];

struct BfmeBaseCNI
{
	void bfmeCopyBaseCNI(BfmeBaseCNI *other);
	unsigned char m_bfmeHead[0x48];
};

struct BfmeThingCNI
{
	void *m_bfmeVft;
	BfmeBaseCNI m_bfmeBase;
	void *volatile m_bfmeVft2;
	volatile int m_bfmeA;
	volatile int m_bfmeB;
	volatile bool m_bfmeFlag;
};

void bfmeCopyCNI(BfmeThingCNI *self, BfmeThingCNI *other)
{
	if (self == 0)
		return;
	self->m_bfmeVft = bfmeVftCNIa;
	self->m_bfmeBase.bfmeCopyBaseCNI(&other->m_bfmeBase);
	self->m_bfmeVft2 = bfmeVftCNIb;
	self->m_bfmeA = other->m_bfmeA;
	self->m_bfmeB = other->m_bfmeB;
	self->m_bfmeFlag = other->m_bfmeFlag;
}
