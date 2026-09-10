// ?bfmeThreeDVB@BfmeSubDVB@@QAE?AVBfmeStrAVTV@@H@Z
// partial score=0.98 date=2026-09-10
class BfmeStrAVTV
{
public:
	BfmeStrAVTV(const BfmeStrAVTV &other);
	~BfmeStrAVTV();

	char *m_bfme00;
};

extern BfmeStrAVTV Rva01336E50Str;

class BfmeElementDVB
{
public:
	BfmeStrAVTV getName() const;

	unsigned char m_bfmeBody[0x58];
};

class BfmeSubDVB
{
public:
	void bfmeOneDVB(void *a, void *b);
	void bfmeTwoDVB(void *a, void *b);
	void bfmeThreeDVB(void *a, void *b);
	BfmeStrAVTV bfmeThreeDVB(int index);

	unsigned char m_bfmeHead[0x18];
	BfmeElementDVB *m_bfmeBegin;
	BfmeElementDVB *m_bfmeEnd;
};

BfmeStrAVTV BfmeSubDVB::bfmeThreeDVB(int index)
{
	if (index >= 0 && (unsigned int)index <
		(unsigned int)(m_bfmeEnd - m_bfmeBegin))
	{
		return (*(BfmeElementDVB *volatile *)&m_bfmeBegin)[index].getName();
	}

	return Rva01336E50Str;
}

struct BfmeThingDVB
{
	void *bfmeGoDVBa(void *a, void *b);
	void *bfmeGoDVBb(void *a, void *b);
	void *bfmeGoDVBc(void *a, void *b);
	unsigned char m_bfmeHead[0x170];
	BfmeSubDVB m_bfmeSub;
};

void *BfmeThingDVB::bfmeGoDVBa(void *a, void *b)
{
	volatile int tmp = 0;
	m_bfmeSub.bfmeOneDVB(a, b);
	return a;
}

void *BfmeThingDVB::bfmeGoDVBb(void *a, void *b)
{
	volatile int tmp = 0;
	m_bfmeSub.bfmeTwoDVB(a, b);
	return a;
}

void *BfmeThingDVB::bfmeGoDVBc(void *a, void *b)
{
	volatile int tmp = 0;
	m_bfmeSub.bfmeThreeDVB(a, b);
	return a;
}
