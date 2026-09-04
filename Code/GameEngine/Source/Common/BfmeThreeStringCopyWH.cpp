// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the three-string copy constructor at retail 0x003A8BE0,
// 98 bytes.  Members are inline forwarding wrappers over the retail string,
// the shape the landed constructor at 0x0014ADC0 uses.

class AsciiStringWH
{
public:
	AsciiStringWH(const AsciiStringWH &other);
	~AsciiStringWH(void);

private:
	char *m_bfmeData;
};

class BfmeStrWH : private AsciiStringWH
{
public:
	BfmeStrWH(const BfmeStrWH &other) : AsciiStringWH(other) {}
	~BfmeStrWH(void) {}
};

class Gen_003A8BE0
{
public:
	Gen_003A8BE0(const Gen_003A8BE0 &other);

	BfmeStrWH m_bfmeFirst;					// +0x00
	BfmeStrWH m_bfmeSecond;					// +0x04
	BfmeStrWH m_bfmeThird;					// +0x08
};

// ??0Gen_003A8BE0@@QAE@ABV0@@Z
Gen_003A8BE0::Gen_003A8BE0(const Gen_003A8BE0 &other)
	: m_bfmeFirst(other.m_bfmeFirst),
	  m_bfmeSecond(other.m_bfmeSecond),
	  m_bfmeThird(other.m_bfmeThird)
{
}
