// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the polymorphic mixed copy constructor at retail
// 0x003A8910, 134 bytes.

class AsciiStringWO
{
public:
	AsciiStringWO(const AsciiStringWO &other);
	~AsciiStringWO(void);

private:
	char *m_bfmeData;
};

class BfmeStrWO : private AsciiStringWO
{
public:
	BfmeStrWO(const AsciiStringWO &other) : AsciiStringWO(other) {}
	~BfmeStrWO(void) {}
};

class Gen_003A8910
{
public:
	Gen_003A8910(const Gen_003A8910 &other);

	virtual ~Gen_003A8910(void);

	BfmeStrWO m_bfmeFirst;					// +0x04
	int m_bfmeA;						// +0x08
	int m_bfmeB;						// +0x0C
	bool m_bfmeFlag;					// +0x10
	BfmeStrWO m_bfmeSecond;					// +0x14
	BfmeStrWO m_bfmeThird;					// +0x18
	int m_bfmeC;						// +0x1C
};

// ??0Gen_003A8910@@QAE@ABV0@@Z
Gen_003A8910::Gen_003A8910(const Gen_003A8910 &other)
	: m_bfmeFirst(other.m_bfmeFirst),
	  m_bfmeA(other.m_bfmeA),
	  m_bfmeB(other.m_bfmeB),
	  m_bfmeFlag(other.m_bfmeFlag),
	  m_bfmeSecond(other.m_bfmeSecond),
	  m_bfmeThird(other.m_bfmeThird),
	  m_bfmeC(other.m_bfmeC)
{
}
