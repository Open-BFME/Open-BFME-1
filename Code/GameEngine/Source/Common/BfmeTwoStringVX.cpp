// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the two-string constructor at retail 0x00491580, 119 bytes.
//
// Both table stores are the compiler's own vfptr initialisation -- the base's
// and then this class's -- which is what puts each member receiver ahead of
// its pushed argument.

class BfmeBaseVX;

extern BfmeBaseVX *g_bfmeListVX;				// retail 0x012F3350

class AsciiStringVX
{
public:
	AsciiStringVX(const AsciiStringVX &other);
	~AsciiStringVX(void);

private:
	char *m_bfmeData;
};

class BfmeStrVX : private AsciiStringVX
{
public:
	BfmeStrVX(const AsciiStringVX &other) : AsciiStringVX(other) {}
	~BfmeStrVX(void) {}
};

class BfmeBaseVX
{
public:
	__forceinline BfmeBaseVX(void)
	{
		m_bfmeNext = g_bfmeListVX;

		g_bfmeListVX = this;

		m_bfmeCount = 0;
		m_bfmeArmed = true;
	}

	virtual ~BfmeBaseVX(void);

	BfmeBaseVX *m_bfmeNext;					// +0x04
	int m_bfmeCount;					// +0x08
	bool m_bfmeArmed;					// +0x0C
};

class Gen_00491580 : public BfmeBaseVX
{
public:
	Gen_00491580(const AsciiStringVX &first, const AsciiStringVX &second);

	virtual ~Gen_00491580(void);

	BfmeStrVX m_bfmeFirst;					// +0x10
	BfmeStrVX m_bfmeSecond;					// +0x14
};

// ??0Gen_00491580@@QAE@ABVAsciiStringVX@@0@Z
Gen_00491580::Gen_00491580(const AsciiStringVX &first,
	const AsciiStringVX &second)
	: m_bfmeFirst(first), m_bfmeSecond(second)
{
}

class Gen_00491880 : public BfmeBaseVX
{
public:
	Gen_00491880(const AsciiStringVX &first, const AsciiStringVX &second,
		const AsciiStringVX &third);

	virtual ~Gen_00491880(void);

	BfmeStrVX m_bfmeFirst;					// +0x10
	BfmeStrVX m_bfmeSecond;					// +0x14
	BfmeStrVX m_bfmeThird;					// +0x18
	int m_bfmeCount;					// +0x1C
	int m_bfmeLimit;					// +0x20
};

// ??0Gen_00491880@@QAE@ABVAsciiStringVX@@00@Z
Gen_00491880::Gen_00491880(const AsciiStringVX &first,
	const AsciiStringVX &second, const AsciiStringVX &third)
	: m_bfmeFirst(first), m_bfmeSecond(second), m_bfmeThird(third),
	  m_bfmeCount(1), m_bfmeLimit(1)
{
}
