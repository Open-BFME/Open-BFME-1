// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the polymorphic three-string copy constructor at retail
// 0x003A8A70, 116 bytes.

class AsciiStringWM
{
public:
	AsciiStringWM(const AsciiStringWM &other);
	~AsciiStringWM(void);

private:
	char *m_bfmeData;
};

class BfmeStrWM : private AsciiStringWM
{
public:
	BfmeStrWM(const AsciiStringWM &other) : AsciiStringWM(other) {}
	~BfmeStrWM(void) {}
};

class Gen_003A8A70
{
public:
	Gen_003A8A70(const Gen_003A8A70 &other);

	virtual ~Gen_003A8A70(void);

	BfmeStrWM m_bfmeFirst;					// +0x04
	BfmeStrWM m_bfmeSecond;					// +0x08
	BfmeStrWM m_bfmeThird;					// +0x0C
	bool m_bfmeFlag;					// +0x10
};

// ??0Gen_003A8A70@@QAE@ABV0@@Z
Gen_003A8A70::Gen_003A8A70(const Gen_003A8A70 &other)
	: m_bfmeFirst(other.m_bfmeFirst),
	  m_bfmeSecond(other.m_bfmeSecond),
	  m_bfmeThird(other.m_bfmeThird),
	  m_bfmeFlag(other.m_bfmeFlag)
{
}
