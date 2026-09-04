// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /ICode/GameEngine/Source/Common/System /ICode/GameEngine/Include /ICode/GameEngine/Include/Precompiled /ICode/Libraries/Source/WWVegas/WWLib
// stlport

#include "ascii_string.h"

extern "C" unsigned char bfmeVftASAa[];
extern "C" unsigned char bfmeVftASAb[];
extern "C" unsigned char bfmeVftASAc[];

void *bfmeAllocNode(unsigned int bytes);
void __cdecl bfmeDeallocate(void *block, unsigned int bytes);

struct BfmeCtorNodeD
{
	BfmeCtorNodeD *m_bfmeNext;
	BfmeCtorNodeD *m_bfmePrev;
	int m_bfmeValue;
};

class BfmeCtorListD
{
public:
	BfmeCtorListD(void)
	{
		m_bfmeNode = 0;
		BfmeCtorNodeD *node = (BfmeCtorNodeD *)bfmeAllocNode(sizeof(BfmeCtorNodeD));
		node->m_bfmeNext = node;
		node->m_bfmePrev = node;
		m_bfmeNode = node;
	}

	~BfmeCtorListD(void);

	void bfmeClear(void)
	{
		BfmeCtorNodeD *node = m_bfmeNode->m_bfmeNext;
		while (node != m_bfmeNode)
		{
			BfmeCtorNodeD *current = node;
			node = node->m_bfmeNext;
			bfmeDeallocate(current, sizeof(BfmeCtorNodeD));
		}
		m_bfmeNode->m_bfmeNext = m_bfmeNode;
		m_bfmeNode->m_bfmePrev = m_bfmeNode;
	}

	BfmeCtorNodeD *m_bfmeNode;
};

class BfmeThingASABase
{
public:
	BfmeThingASABase(void)
	{
		m_bfmeVftA = (void *)0x010F3550;
	}

	void *volatile m_bfmeVftA;
};

class BfmeThingASA : public BfmeThingASABase
{
public:
	BfmeThingASA(void *one);
	void bfmeBaseASA(void *one);
	BfmeThingASA *bfmeInitASA(void *one);
	BfmeCtorListD m_bfmeListA;
	unsigned char m_bfmeFlag8;
	AsciiString m_bfmeName;
	unsigned char m_bfmeFlag10;
	volatile int m_bfmeZero14;
	BfmeCtorListD m_bfmeListB;
	int m_bfmeLimit;
	int m_bfmePeriod;
	void *volatile m_bfmeVftB;
	volatile int m_bfmeZero;
};

BfmeThingASA::BfmeThingASA(void *one)
	: m_bfmeName(*(const AsciiString *)one),
	  m_bfmeFlag10(0)
{
	m_bfmeFlag8 = 0;
	m_bfmeZero14 = 0;
	m_bfmeLimit = 0x1e;
	m_bfmePeriod = 0x3c;
	m_bfmeListB.bfmeClear();
}

BfmeThingASA *BfmeThingASA::bfmeInitASA(void *one)
{
	bfmeBaseASA(one);
	m_bfmeVftB = bfmeVftASAa;
	m_bfmeZero = 0;
	m_bfmeVftA = bfmeVftASAb;
	m_bfmeVftB = bfmeVftASAc;
	return this;
}
