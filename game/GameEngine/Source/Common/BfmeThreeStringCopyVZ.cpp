// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the three-string copy constructor at retail 0x0033A640,
// 104 bytes.  Members are inline forwarding wrappers over the retail string,
// the shape the landed constructor at 0x0014ADC0 uses.

class AsciiStringVZ
{
public:
	AsciiStringVZ(const AsciiStringVZ &other);
	~AsciiStringVZ(void);

private:
	char *m_bfmeData;
};

class BfmeStrVZ : private AsciiStringVZ
{
public:
	BfmeStrVZ(const BfmeStrVZ &other) : AsciiStringVZ(other) {}
	~BfmeStrVZ(void) {}
};

class Gen_0033A640
{
public:
	Gen_0033A640(const Gen_0033A640 &other);

	BfmeStrVZ m_bfmeFirst;					// +0x00
	BfmeStrVZ m_bfmeSecond;					// +0x04
	int m_bfmeCount;					// +0x08
	BfmeStrVZ m_bfmeThird;					// +0x0C
};

// ??0Gen_0033A640@@QAE@ABV0@@Z
Gen_0033A640::Gen_0033A640(const Gen_0033A640 &other)
	: m_bfmeFirst(other.m_bfmeFirst),
	  m_bfmeSecond(other.m_bfmeSecond),
	  m_bfmeCount(other.m_bfmeCount),
	  m_bfmeThird(other.m_bfmeThird)
{
}
