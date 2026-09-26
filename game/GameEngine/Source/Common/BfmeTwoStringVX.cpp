// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// Open-BFME5: the two-string constructor at retail 0x00491580, 119 bytes.
//
// Both table stores are the compiler's own vfptr initialisation -- the base's
// and then this class's -- which is what puts each member receiver ahead of
// its pushed argument.

class Rva00490470;

extern Rva00490470 *g_bfmeListVX;				// retail 0x012F3350

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

class GameLogic
{
private:
	char m_bfmePrefix[0x74];

public:
	unsigned char m_bfmeResetFlag;
};

class Display
{
public:
	virtual void slot00(); virtual void slot04();
	virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14();
	virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24();
	virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34();
	virtual void slot38(); virtual void slot3C();
	virtual void slot40(); virtual void slot44();
	virtual void slot48(); virtual void slot4C();
	virtual void slot50(); virtual void slot54();
	virtual void slot58(); virtual void slot5C();
	virtual void slot60(); virtual void slot64();
	virtual void slot68(); virtual void slot6C();
	virtual void slot70(); virtual void slot74();
	virtual void slot78(); virtual void slot7C();
	virtual void slot80(); virtual void slot84();
	virtual void slot88(); virtual void slot8C();
	virtual void slot90(); virtual void slot94();
	virtual void slot98(); virtual void slot9C();
	virtual void slotA0(); virtual void slotA4();
	virtual void slotA8(); virtual void slotAC();
	virtual void slotB0(); virtual void slotB4();
	virtual void slotB8(); virtual void slotBC();
	virtual void slotC0(); virtual void slotC4();
	virtual void slotC8(); virtual void slotCC();
	virtual void slotD0(); virtual void slotD4();
	virtual void slotD8(); virtual void slotDC();
	virtual void slotE0(); virtual void slotE4();
	virtual void slotE8(); virtual void slotEC();

	void bfmeStopMovie(void);
};

extern GameLogic *TheBfmeGameLogic;
extern Display *TheDisplay;

class Rva00490470
{
public:
	__forceinline Rva00490470(void)
	{
		m_bfmeNext = g_bfmeListVX;

		g_bfmeListVX = this;

		m_bfmeCount = 0;
		m_bfmeArmed = true;
	}

	virtual ~Rva00490470(void);

	Rva00490470 *m_bfmeNext;					// +0x04
	int m_bfmeCount;					// +0x08
	bool m_bfmeArmed;					// +0x0C
};

class Gen_00491580 : public Rva00490470
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

// ??1Gen_00491580@@UAE@XZ
Gen_00491580::~Gen_00491580(void)
{
	TheBfmeGameLogic->m_bfmeResetFlag = 0;

	TheDisplay->slotEC();
	TheDisplay->bfmeStopMovie();
}

class Gen_00491880 : public Rva00490470
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
