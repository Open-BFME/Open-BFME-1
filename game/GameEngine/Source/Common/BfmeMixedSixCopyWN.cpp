// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the mixed six-member copy constructor at retail 0x004E9FD0,
// 148 bytes: a word, three narrow strings, a word and two wide strings.

class AsciiStringWN
{
public:
	AsciiStringWN(const AsciiStringWN &other);
	~AsciiStringWN(void);

private:
	char *m_bfmeData;
};

class UnicodeStringWN
{
public:
	UnicodeStringWN(const UnicodeStringWN &other);
	~UnicodeStringWN(void);

private:
	unsigned short *m_bfmeData;
};

class BfmeStrWN : private AsciiStringWN
{
public:
	BfmeStrWN(const AsciiStringWN &other) : AsciiStringWN(other) {}
	~BfmeStrWN(void) {}
};

class BfmeWideWN : private UnicodeStringWN
{
public:
	BfmeWideWN(const UnicodeStringWN &other) : UnicodeStringWN(other) {}
	~BfmeWideWN(void) {}
};

class Gen_004E9FD0
{
public:
	Gen_004E9FD0(const Gen_004E9FD0 &other);

	int m_bfmeKind;						// +0x00
	BfmeStrWN m_bfmeFirst;					// +0x04
	BfmeStrWN m_bfmeSecond;					// +0x08
	BfmeStrWN m_bfmeThird;					// +0x0C
	int m_bfmeCount;					// +0x10
	BfmeWideWN m_bfmeText;					// +0x14
	BfmeWideWN m_bfmeHint;					// +0x18
};

// ??0Gen_004E9FD0@@QAE@ABV0@@Z
Gen_004E9FD0::Gen_004E9FD0(const Gen_004E9FD0 &other)
	: m_bfmeKind(other.m_bfmeKind),
	  m_bfmeFirst(other.m_bfmeFirst),
	  m_bfmeSecond(other.m_bfmeSecond),
	  m_bfmeThird(other.m_bfmeThird),
	  m_bfmeCount(other.m_bfmeCount),
	  m_bfmeText(other.m_bfmeText),
	  m_bfmeHint(other.m_bfmeHint)
{
}
