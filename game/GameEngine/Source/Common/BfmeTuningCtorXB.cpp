// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the tuning-record constructor at retail 0x00762100, 89 bytes.
// A string, a kind word and a run of float defaults; -1.0f and 1.0f each
// repeat, so MSVC holds them in registers as retail does.

class AsciiStringXB
{
public:
	AsciiStringXB(const AsciiStringXB &other);
	~AsciiStringXB(void);

private:
	char *m_bfmeData;
};

class BfmeStrXB : private AsciiStringXB
{
public:
	BfmeStrXB(const AsciiStringXB &other) : AsciiStringXB(other) {}
	~BfmeStrXB(void) {}
};

// The two zeroed words stay ahead of the kind word instead of sinking, so they
// are built by an inlined sub-object rather than by this constructor.
class BfmePairXB
{
public:
	__forceinline BfmePairXB(void)
	{
		m_bfmeA = 0;
		m_bfmeB = 0;
	}

	int m_bfmeA;						// +0x00
	int m_bfmeB;						// +0x04
};

class Gen_00762100
{
public:
	Gen_00762100(const AsciiStringXB &name, int kind);

	BfmeStrXB m_bfmeName;					// +0x00
	BfmePairXB m_bfme04;					// +0x04
	int m_bfmeKind;						// +0x0C
	float m_bfme10;						// +0x10
	int m_bfme14;						// +0x14
	float m_bfme18;						// +0x18
	float m_bfme1C;						// +0x1C
	float m_bfme20;						// +0x20
	bool m_bfme24;						// +0x24
	bool m_bfme25;						// +0x25
	int m_bfme28;						// +0x28
	float m_bfme2C;						// +0x2C
	float m_bfme30;						// +0x30
	bool m_bfme34;						// +0x34
};

// ??0Gen_00762100@@QAE@ABVAsciiStringXB@@H@Z
Gen_00762100::Gen_00762100(const AsciiStringXB &name, int kind)
	: m_bfmeName(name),
	  m_bfmeKind(kind),
	  m_bfme10(-1.0f),
	  m_bfme14(1),
	  m_bfme18(5.0f),
	  m_bfme1C(1.0f),
	  m_bfme20(1.0f),
	  m_bfme24(false),
	  m_bfme25(false),
	  m_bfme28(1),
	  m_bfme2C(-1.0f),
	  m_bfme30(-1.0f),
	  m_bfme34(false)
{
}
