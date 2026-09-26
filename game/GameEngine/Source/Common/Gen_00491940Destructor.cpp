// cl: /DNDEBUG /MD /EHsc /O2 /Ob2
//
// The destructor paired with Gen_00491880's matched three-string constructor
// at 0x00491880.  The deleting wrapper at 0x004923A0 calls this body through
// its 0x00021526 thunk, and both the constructor and destructor install the
// 0x010F9BBC table.  The list-linking base is the already recovered
// Rva00490350 family.  This object's inherited cleanup is the existing
// Rva00490470 window-owner dtor. Its +0x08 payload may later hold a
// GameWindow, so inherited cleanup must run even though construction sets it null.

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

class Rva00490470
{
public:
	virtual ~Rva00490470();

protected:
	Rva00490470 *m_link;
	void *m_payload;
	bool m_flag;
	char m_flagPadding[3];
};

class ClientSubsystem
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
	virtual void slot48(); virtual void slot4C(int value);
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

extern ClientSubsystem *TheAudioClientUpdate;
extern GameLogic *TheBfmeGameLogic;
extern Display *TheDisplay;

class Gen_00491880 : public Rva00490470
{
public:
	virtual ~Gen_00491880(void);

private:
	BfmeStrVX m_bfmeFirst;
	BfmeStrVX m_bfmeSecond;
	BfmeStrVX m_bfmeThird;
	int m_bfmeCount;
	int m_bfmeLimit;
};

// ??1Gen_00491880@@UAE@XZ
Gen_00491880::~Gen_00491880(void)
{
	if (m_bfmeCount != 1)
	{
		TheAudioClientUpdate->slot4C(m_bfmeCount);
		m_bfmeCount = 1;
	}
	if (m_bfmeLimit != 1)
	{
		TheAudioClientUpdate->slot4C(m_bfmeLimit);
		m_bfmeLimit = 1;
	}
	TheBfmeGameLogic->m_bfmeResetFlag = 0;
	TheDisplay->slotEC();
	TheDisplay->bfmeStopMovie();
}
