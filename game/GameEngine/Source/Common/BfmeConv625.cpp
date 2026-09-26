extern "C" unsigned char bfmeVftCNDa[];
extern "C" unsigned char bfmeVftCNDb[];

struct BfmeBaseCND
{
	void bfmeCopyBaseCND(BfmeBaseCND *other);
	unsigned char m_bfmeHead[0x48];
};

struct BfmeThingCND
{
	BfmeThingCND *bfmeCopyCND(BfmeThingCND *other);
	void *m_bfmeVft;
	BfmeBaseCND m_bfmeBase;
	void *volatile m_bfmeVft2;
	volatile int m_bfmeA;
	volatile int m_bfmeB;
	volatile bool m_bfmeFlag;
};

BfmeThingCND *BfmeThingCND::bfmeCopyCND(BfmeThingCND *other)
{
	m_bfmeVft = bfmeVftCNDa;
	m_bfmeBase.bfmeCopyBaseCND(&other->m_bfmeBase);
	m_bfmeVft2 = bfmeVftCNDb;
	m_bfmeA = other->m_bfmeA;
	m_bfmeB = other->m_bfmeB;
	m_bfmeFlag = other->m_bfmeFlag;
	return this;
}
