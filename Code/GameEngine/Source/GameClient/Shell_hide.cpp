// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: Shell::hide, retail 0x0057F5B0, 118 bytes. The body carried only
// a machine byte-dump row; reverse/reloc_names.csv holds the name with
// identity=real.
//
// The screen on top of the stack -- index at +0x48, entries from +0x04 -- is
// told to hide, but only when the argument says so, and the true it is given
// goes by reference: the compiler builds that temporary in the argument slot it
// no longer needs, which is why the address pushed is the caller's own.
//
// Then the global at 0x012F3344 is notified if it is there, the flag at +0x58
// comes down, and unless TheWritableGlobalData's byte at +0xBB4 says otherwise
// TheDisplay stops its movie and TheAudio is told to drop the handle at +0x64,
// which is then set to one. That audio call is slot 19 of the same table
// Gen_00417cb0::alt uses.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

class BfmeShellScreen
{
public:
	virtual void _bfme_slot0(void) = 0;
	virtual void _bfme_slot1(void) = 0;
	virtual void _bfme_slot2(void) = 0;
	virtual void bfmeHide(const Bool &hide) = 0;		// slot 3, vtable+0x0C
};

class Glo012F3344Type
{
public:
	virtual void _bfme_slot0(void) = 0;
	virtual void _bfme_slot1(void) = 0;
	virtual void _bfme_slot2(void) = 0;
	virtual void _bfme_slot3(void) = 0;
	virtual void _bfme_slot4(void) = 0;
	virtual void _bfme_slot5(void) = 0;
	virtual void _bfme_slot6(void) = 0;
	virtual void _bfme_slot7(void) = 0;
	virtual void _bfme_slot8(void) = 0;
	virtual void _bfme_slot9(void) = 0;
	virtual void bfmeNotifyHidden(void) = 0;		// slot 10, vtable+0x28
};

extern Glo012F3344Type *Glo012F3344;				// 0x012F3344

class UnicodeString
{
	protected:
	friend class Display;
	void releaseBuffer();
};

class Display
{
public:
	__declspec(noinline) void bfmeStopMovie(void);				// ILT 0x0001992F

private:
	char m_bfmeHead[0x64];
	UnsignedInt m_bfmeMovieFields[18];
	UnicodeString m_bfmeMovieName;
	char m_bfmePadAfterMovieName[0x17];
	UnsignedInt m_bfmeMovieFieldC4;
	UnsignedInt m_bfmeMovieFieldC8;
};

// ?bfmeStopMovie@Display@@QAEXXZ		112 bytes
__declspec(noinline) void Display::bfmeStopMovie(void)
{
	m_bfmeMovieFields[0] = 0;
	m_bfmeMovieFields[1] = 0;
	m_bfmeMovieFields[2] = 0;
	m_bfmeMovieFields[3] = 0;
	m_bfmeMovieFields[4] = 0;
	m_bfmeMovieFields[5] = 0;
	m_bfmeMovieFields[6] = 0;
	m_bfmeMovieFields[7] = 0;
	m_bfmeMovieFields[8] = 0;
	m_bfmeMovieFields[9] = 0;
	m_bfmeMovieFields[10] = 0;
	m_bfmeMovieFields[11] = 0;
	m_bfmeMovieFields[12] = 0;
	m_bfmeMovieFields[13] = 0;
	m_bfmeMovieFields[14] = 0;
	m_bfmeMovieFields[15] = 0;
	m_bfmeMovieFields[16] = 0;
	m_bfmeMovieFields[17] = 0;
	m_bfmeMovieFieldC4 = 0;
	m_bfmeMovieFieldC8 = 0;

	m_bfmeMovieName.releaseBuffer();
}

extern Display *TheDisplay;					// 0x012F1270

class GlobalData
{
public:
	char m_bfmeHead[0xBB4];
	Bool m_bfmeNoShellAudio;				// +0xBB4
};

extern GlobalData *TheWritableGlobalData;			// 0x012ED5C8

class AudioManager
{
public:
	virtual void unused00();
	virtual void unused01();
	virtual void unused02();
	virtual void unused03();
	virtual void unused04();
	virtual void unused05();
	virtual void unused06();
	virtual void unused07();
	virtual void unused08();
	virtual void unused09();
	virtual void unused10();
	virtual void unused11();
	virtual void unused12();
	virtual void unused13();
	virtual void unused14();
	virtual void unused15();
	virtual void unused16();
	virtual void unused17();
	virtual void unused18();
	virtual void bfmeStopAudioEvent(UnsignedInt handle);	// slot 19, vtable+0x4C
};

extern AudioManager *TheAudio;					///< retail [0x012ED668]

class Shell
{
public:
	void hide(Bool hide);

private:
	char m_bfmeHeadA[0x04];
	BfmeShellScreen *m_bfmeStack[17];			// +0x04
	Int m_bfmeTop;						// +0x48
	char m_bfmeHeadB[0x58 - 0x4C];
	Bool m_bfmeShown;					// +0x58
	char m_bfmeHeadC[0x64 - 0x59];
	UnsignedInt m_bfmeMusicHandle;				// +0x64
};

// ?hide@Shell@@QAEX_N@Z
void Shell::hide(Bool hide)
{
	Int top = m_bfmeTop;

	if (top)
	{
		BfmeShellScreen *screen = m_bfmeStack[top];

		if (screen)
		{
			if (hide)
				screen->bfmeHide(true);
		}
	}

	if (Glo012F3344)
		Glo012F3344->bfmeNotifyHidden();

	m_bfmeShown = false;

	if (!TheWritableGlobalData->m_bfmeNoShellAudio)
	{
		TheDisplay->bfmeStopMovie();

		if (TheAudio)
		{
			TheAudio->bfmeStopAudioEvent(m_bfmeMusicHandle);

			m_bfmeMusicHandle = 1;
		}
	}
}
