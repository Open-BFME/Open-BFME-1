// ?bfmeTwoDVB@BfmeSubDVB@@QAE?AVBfmeStringDVB@@H@Z
// partial score=0.98 date=2026-09-10
// The three wrappers below call the same small vector-backed helper family.
// The first member's caller exposed the ABI: its first stack argument is the
// returned four-byte string storage and its second is the signed element index.
// Keep the helper's actual by-value return type here rather than treating the
// caller's opaque forwarder arguments as its semantic signature.
class BfmeStringDVB
{
public:
	BfmeStringDVB(const BfmeStringDVB &other);
	~BfmeStringDVB();

	void *m_data;
};

class Rva002E5FF0Str
{
public:
	void *m_data;
};

extern Rva002E5FF0Str Rva01336E50Str;

class Rva00361960
{
public:
	BfmeStringDVB copyString();

	unsigned char m_bfmeBody[0x58];
};

class BfmeSubDVB
{
public:
	BfmeStringDVB bfmeTwoDVB(int index);
	void bfmeOneDVB(void *a, void *b);
	void bfmeTwoDVB(void *a, void *b);
	void bfmeThreeDVB(void *a, void *b);

	unsigned char m_bfmeHead[0x18];
	Rva00361960 *m_bfmeBegin;
	Rva00361960 *m_bfmeEnd;
};

BfmeStringDVB BfmeSubDVB::bfmeTwoDVB(int index)
{
	if (index >= 0 && (unsigned int)index < (unsigned int)(m_bfmeEnd - m_bfmeBegin))
	{
		return (*(Rva00361960 *volatile *)&m_bfmeBegin)[index].copyString();
	}

	return *(const BfmeStringDVB *)&Rva01336E50Str;
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
