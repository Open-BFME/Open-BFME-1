// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the polymorphic seven-string copy constructor at retail
// 0x003A87D0, 208 bytes.

class AsciiStringWP
{
public:
	AsciiStringWP(const AsciiStringWP &other);
	~AsciiStringWP(void);

private:
	char *m_bfmeData;
};

class BfmeStrWP : private AsciiStringWP
{
public:
	BfmeStrWP(const AsciiStringWP &other) : AsciiStringWP(other) {}
	~BfmeStrWP(void) {}
};

class Gen_003A87D0
{
public:
	Gen_003A87D0(const Gen_003A87D0 &other);

	virtual ~Gen_003A87D0(void);

	BfmeStrWP m_bfmeFirst;					// +0x04
	BfmeStrWP m_bfmeSecond;					// +0x08
	BfmeStrWP m_bfmeThird;					// +0x0C
	int m_bfmeA;						// +0x10
	int m_bfmeB;						// +0x14
	bool m_bfmeFlagA;					// +0x18
	bool m_bfmeFlagB;					// +0x19
	BfmeStrWP m_bfmeFourth;					// +0x1C
	BfmeStrWP m_bfmeFifth;					// +0x20
	BfmeStrWP m_bfmeSixth;					// +0x24
	BfmeStrWP m_bfmeSeventh;				// +0x28
	bool m_bfmeFlagC;					// +0x2C
};

// ??0Gen_003A87D0@@QAE@ABV0@@Z
Gen_003A87D0::Gen_003A87D0(const Gen_003A87D0 &other)
	: m_bfmeFirst(other.m_bfmeFirst),
	  m_bfmeSecond(other.m_bfmeSecond),
	  m_bfmeThird(other.m_bfmeThird),
	  m_bfmeA(other.m_bfmeA),
	  m_bfmeB(other.m_bfmeB),
	  m_bfmeFlagA(other.m_bfmeFlagA),
	  m_bfmeFlagB(other.m_bfmeFlagB),
	  m_bfmeFourth(other.m_bfmeFourth),
	  m_bfmeFifth(other.m_bfmeFifth),
	  m_bfmeSixth(other.m_bfmeSixth),
	  m_bfmeSeventh(other.m_bfmeSeventh),
	  m_bfmeFlagC(other.m_bfmeFlagC)
{
}
