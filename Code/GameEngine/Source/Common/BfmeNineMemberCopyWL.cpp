// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the nine-member copy constructor at retail 0x0010DB80,
// 189 bytes: five narrow strings, one wide one, two words and a sixteen-byte
// sub-object whose copy goes through materialised pointers.

class AsciiStringWL
{
public:
	AsciiStringWL(const AsciiStringWL &other);
	~AsciiStringWL(void);

private:
	char *m_bfmeData;
};

class UnicodeStringWL
{
public:
	UnicodeStringWL(const UnicodeStringWL &other);
	~UnicodeStringWL(void);

private:
	unsigned short *m_bfmeData;
};

class BfmeStrWL : private AsciiStringWL
{
public:
	BfmeStrWL(const AsciiStringWL &other) : AsciiStringWL(other) {}
	~BfmeStrWL(void) {}
};

class BfmeWideWL : private UnicodeStringWL
{
public:
	BfmeWideWL(const UnicodeStringWL &other) : UnicodeStringWL(other) {}
	~BfmeWideWL(void) {}
};

struct BfmeQuadWL
{
	int m_bfmeA;						// +0x00
	int m_bfmeB;						// +0x04
	int m_bfmeC;						// +0x08
	int m_bfmeD;						// +0x0C
};

class Gen_0010DB80
{
public:
	Gen_0010DB80(const Gen_0010DB80 &other);

	BfmeStrWL m_bfmeFirst;					// +0x00
	BfmeStrWL m_bfmeSecond;					// +0x04
	BfmeStrWL m_bfmeThird;					// +0x08
	BfmeQuadWL m_bfmeQuad;					// +0x0C
	BfmeStrWL m_bfmeFourth;					// +0x1C
	int m_bfmeKind;						// +0x20
	BfmeWideWL m_bfmeText;					// +0x24
	int m_bfmeCount;					// +0x28
	BfmeStrWL m_bfmeFifth;					// +0x2C
};

// ??0Gen_0010DB80@@QAE@ABV0@@Z
Gen_0010DB80::Gen_0010DB80(const Gen_0010DB80 &other)
	: m_bfmeFirst(other.m_bfmeFirst),
	  m_bfmeSecond(other.m_bfmeSecond),
	  m_bfmeThird(other.m_bfmeThird),
	  m_bfmeQuad(other.m_bfmeQuad),
	  m_bfmeFourth(other.m_bfmeFourth),
	  m_bfmeKind(other.m_bfmeKind),
	  m_bfmeText(other.m_bfmeText),
	  m_bfmeCount(other.m_bfmeCount),
	  m_bfmeFifth(other.m_bfmeFifth)
{
}
