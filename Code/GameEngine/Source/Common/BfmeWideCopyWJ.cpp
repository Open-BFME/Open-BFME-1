// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the three-wide-string copy constructor at retail 0x006869C0,
// 122 bytes, followed by four plain words.

class UnicodeStringWJ
{
public:
	UnicodeStringWJ(const UnicodeStringWJ &other);
	~UnicodeStringWJ(void);

private:
	unsigned short *m_bfmeData;
};

class BfmeWideWJ : private UnicodeStringWJ
{
public:
	BfmeWideWJ(const UnicodeStringWJ &other) : UnicodeStringWJ(other) {}
	~BfmeWideWJ(void) {}
};

class Gen_006869C0
{
public:
	Gen_006869C0(const Gen_006869C0 &other);

	BfmeWideWJ m_bfmeFirst;					// +0x00
	BfmeWideWJ m_bfmeSecond;				// +0x04
	BfmeWideWJ m_bfmeThird;					// +0x08
	int m_bfmeA;						// +0x0C
	int m_bfmeB;						// +0x10
	int m_bfmeC;						// +0x14
	int m_bfmeD;						// +0x18
};

// ??0Gen_006869C0@@QAE@ABV0@@Z
Gen_006869C0::Gen_006869C0(const Gen_006869C0 &other)
	: m_bfmeFirst(other.m_bfmeFirst),
	  m_bfmeSecond(other.m_bfmeSecond),
	  m_bfmeThird(other.m_bfmeThird),
	  m_bfmeA(other.m_bfmeA),
	  m_bfmeB(other.m_bfmeB),
	  m_bfmeC(other.m_bfmeC),
	  m_bfmeD(other.m_bfmeD)
{
}
