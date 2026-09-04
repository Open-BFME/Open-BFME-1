// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the settings copy constructor at retail 0x00193D50, 294 bytes.
// Same class as the default constructor at 0x00194210: three strings at +0x04,
// +0x08 and +0x30, a forty-byte block at +0x54 that copies as a rep movsd, and
// plain words either side.

class AsciiStringWW
{
public:
	AsciiStringWW(const AsciiStringWW &other);
	~AsciiStringWW(void);

private:
	char *m_bfmeData;
};

class BfmeStrWW : private AsciiStringWW
{
public:
	BfmeStrWW(const BfmeStrWW &other) : AsciiStringWW(other) {}
	~BfmeStrWW(void) {}
};

struct BfmeBlockWW
{
	int m_bfmeSlot[10];					// +0x00
};

// Retail moves the unwind state to 0 before the first string is built, which
// needs a destructible sub-object already in place: an empty base with a
// declared destructor supplies it without changing the layout.
class BfmeGuardWW
{
public:
	~BfmeGuardWW(void);
};

class Gen_00193D50 : public BfmeGuardWW
{
public:
	Gen_00193D50(const Gen_00193D50 &other);

	virtual ~Gen_00193D50(void);

	BfmeStrWW m_bfme04;					// +0x04
	BfmeStrWW m_bfme08;					// +0x08
	int m_bfme0C;						// +0x0C
	int m_bfme10;						// +0x10
	int m_bfme14;						// +0x14
	int m_bfme18;						// +0x18
	int m_bfme1C;						// +0x1C
	int m_bfme20;						// +0x20
	bool m_bfme24;						// +0x24
	int m_bfme28;						// +0x28
	int m_bfme2C;						// +0x2C
	BfmeStrWW m_bfme30;					// +0x30
	int m_bfme34;						// +0x34
	bool m_bfme38;						// +0x38
	bool m_bfme39;						// +0x39
	bool m_bfme3A;						// +0x3A
	bool m_bfme3B;						// +0x3B
	int m_bfme3C;						// +0x3C
	int m_bfme40;						// +0x40
	bool m_bfme44;						// +0x44
	int m_bfme48;						// +0x48
	int m_bfme4C;						// +0x4C
	bool m_bfme50;						// +0x50
	BfmeBlockWW m_bfme54;					// +0x54
	bool m_bfme7C;						// +0x7C
	int m_bfme80;						// +0x80
	int m_bfme84;						// +0x84
	bool m_bfme88;						// +0x88
};

// ??0Gen_00193D50@@QAE@ABV0@@Z
Gen_00193D50::Gen_00193D50(const Gen_00193D50 &other)
	: m_bfme04(other.m_bfme04),
	  m_bfme08(other.m_bfme08),
	  m_bfme0C(other.m_bfme0C), m_bfme10(other.m_bfme10),
	  m_bfme14(other.m_bfme14), m_bfme18(other.m_bfme18),
	  m_bfme1C(other.m_bfme1C), m_bfme20(other.m_bfme20),
	  m_bfme24(other.m_bfme24),
	  m_bfme28(other.m_bfme28), m_bfme2C(other.m_bfme2C),
	  m_bfme30(other.m_bfme30),
	  m_bfme34(other.m_bfme34),
	  m_bfme38(other.m_bfme38), m_bfme39(other.m_bfme39),
	  m_bfme3A(other.m_bfme3A), m_bfme3B(other.m_bfme3B),
	  m_bfme3C(other.m_bfme3C), m_bfme40(other.m_bfme40),
	  m_bfme44(other.m_bfme44),
	  m_bfme48(other.m_bfme48), m_bfme4C(other.m_bfme4C),
	  m_bfme50(other.m_bfme50),
	  m_bfme54(other.m_bfme54),
	  m_bfme7C(other.m_bfme7C),
	  m_bfme80(other.m_bfme80), m_bfme84(other.m_bfme84),
	  m_bfme88(other.m_bfme88)
{
}
