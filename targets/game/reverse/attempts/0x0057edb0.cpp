// ?rva0057EDB0@BfmeAptScreenSkirmish@@UAEHXZ
// partial score=0.7607 date=2026-10-29
// cl: /O2 /DNDEBUG /MD /Igame/Libraries/Source/WWVegas/WWLib
// BfmeAptScreenSkirmish::rva0057EDB0 (retail 0x0057EDB0, 514 bytes of code
// plus its 10-entry jump table).
//
// Identity: slot 5 of the BfmeAptScreenSkirmish vtable 0x0110B030 (installed
// by the matched constructor 0x0057DA50 and destructor 0x00579480); the body
// re-dispatches through its own slot (+0x14) after moving to modes 5 and 6.
// It steps the screen's mode machine at +0x400: clear a pending profile
// popup, then per mode open the persona popup or the default screen, wait for
// the preferences/profile checks, refresh, forward, or close the main menu,
// and finally flush the state object's pending updates. Its meaning beyond
// that is not proven, so the name keeps the address.
//
// Layout follows the matched siblings (SkirmishScreenClose.cpp: movie +0x250,
// preferences +0x3AC, mode +0x400, profile-open flag +0x409).

#include "string_base.h"

class GameWindow;

class UnicodeString : private StringBase<unsigned short>
{
public:
	UnicodeString(const UnicodeString &that) : StringBase<unsigned short>(that) {}
	~UnicodeString() {}

	static const UnicodeString TheEmptyString;
};

void GadgetTextEntrySetText(GameWindow *window, UnicodeString text);

#define RVA0057EDB0_SLOT(n) virtual void slot##n(void);

class GameWindowManager
{
public:
	RVA0057EDB0_SLOT(00) RVA0057EDB0_SLOT(01) RVA0057EDB0_SLOT(02) RVA0057EDB0_SLOT(03)
	RVA0057EDB0_SLOT(04) RVA0057EDB0_SLOT(05) RVA0057EDB0_SLOT(06) RVA0057EDB0_SLOT(07)
	RVA0057EDB0_SLOT(08) RVA0057EDB0_SLOT(09) RVA0057EDB0_SLOT(10) RVA0057EDB0_SLOT(11)
	RVA0057EDB0_SLOT(12) RVA0057EDB0_SLOT(13) RVA0057EDB0_SLOT(14) RVA0057EDB0_SLOT(15)
	RVA0057EDB0_SLOT(16) RVA0057EDB0_SLOT(17) RVA0057EDB0_SLOT(18) RVA0057EDB0_SLOT(19)
	RVA0057EDB0_SLOT(20) RVA0057EDB0_SLOT(21) RVA0057EDB0_SLOT(22) RVA0057EDB0_SLOT(23)
	RVA0057EDB0_SLOT(24) RVA0057EDB0_SLOT(25) RVA0057EDB0_SLOT(26) RVA0057EDB0_SLOT(27)
	RVA0057EDB0_SLOT(28) RVA0057EDB0_SLOT(29) RVA0057EDB0_SLOT(30) RVA0057EDB0_SLOT(31)
	RVA0057EDB0_SLOT(32) RVA0057EDB0_SLOT(33) RVA0057EDB0_SLOT(34) RVA0057EDB0_SLOT(35)
	RVA0057EDB0_SLOT(36) RVA0057EDB0_SLOT(37) RVA0057EDB0_SLOT(38) RVA0057EDB0_SLOT(39)
	RVA0057EDB0_SLOT(40) RVA0057EDB0_SLOT(41) RVA0057EDB0_SLOT(42) RVA0057EDB0_SLOT(43)
	virtual void slot44(GameWindow *window);
};

extern GameWindowManager *TheWindowManager;

class WindowManager
{
public:
	void unidentified_00015235( int movie, const char *function,
		int argumentCount, const void *argument1, const void *argument2,
		int unused1, int unused2, int unused3 );
};

extern WindowManager *g_rva012F19E8WindowManager;	// retail 0x012F19E8

#undef RVA0057EDB0_SLOT

class SkirmishPreferences
{
public:
	bool unidentified_00017AF8();
};

class SkirmishScreenState
{
public:
	bool flushPendingUpdates();

	char m_unmodelled00[0x10];
	bool m_dirty;							// +0x10
};

// The same +0x25C object is reached under its MpGameSetup name by 0x00527930.
class MpGameSetup
{
public:
	bool rva00527930(bool flag);
};

class Gen_0057ED70
{
public:
	void bfmeForward();
};

class BfmeAptScreenSkirmish
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual int rva0057EDB0();
	virtual bool rva0057BE50();

	void _bfme_updateProfileDisplay();
	bool _bfme_refresh();

private:
	char m_unmodelled004[0x250 - 0x4];
	int m_movie;							// +0x250
	char m_unmodelled254[0x25c - 0x254];
	SkirmishScreenState m_screenState;		// +0x25C
	char m_unmodelled26D[0x3ac - 0x26d];
	SkirmishPreferences m_preferences;		// +0x3AC
	char m_unmodelled3AD[0x400 - 0x3ad];
	int m_mode;								// +0x400
	char m_unmodelled404[5];
	bool m_profileOpen;						// +0x409
	char m_unmodelled40A[0x42c - 0x40a];
	GameWindow *m_personaEntry;				// +0x42C
};

// ?rva0057EDB0@BfmeAptScreenSkirmish@@UAEHXZ
int BfmeAptScreenSkirmish::rva0057EDB0()
{
	if (m_profileOpen)
	{
		m_screenState.m_dirty = true;
		m_profileOpen = false;
	}

	switch (m_mode)
	{
	case 1:
		if (!m_preferences.unidentified_00017AF8())
		{
			_bfme_updateProfileDisplay();
			m_mode = 2;
			TheWindowManager->slot44(m_personaEntry);
			GadgetTextEntrySetText(m_personaEntry, UnicodeString::TheEmptyString);
			g_rva012F19E8WindowManager->unidentified_00015235(m_movie, "PopUpPersona", 0, 0, 0, 0, 0, 0);
			break;
		}
		g_rva012F19E8WindowManager->unidentified_00015235(m_movie, "OpenDefault", 0, 0, 0, 0, 0, 0);
		m_mode = 5;
		return rva0057EDB0();

	case 5:
		if (m_preferences.unidentified_00017AF8() && BfmeAptScreenSkirmish::rva0057BE50())
		{
			m_mode = 6;
			return rva0057EDB0();
		}
		break;

	case 6:
		if (_bfme_refresh())
		{
			m_mode = 7;
			break;
		}
		break;

	case 10:
		if (reinterpret_cast<MpGameSetup *>(&m_screenState)->rva00527930(false))
		{
			g_rva012F19E8WindowManager->unidentified_00015235(m_movie, "CloseMain", 0, 0, 0, 0, 0, 0);
			m_mode = 11;
			break;
		}
		else
		{
			g_rva012F19E8WindowManager->unidentified_00015235(m_movie, "ButtonReset", 0, 0, 0, 0, 0, 0);
			m_mode = 7;
			break;
		}
		break;

	case 8:
		reinterpret_cast<Gen_0057ED70 *>(this)->bfmeForward();
		m_mode = 9;
		break;
	}

	m_screenState.flushPendingUpdates();
	return 1;
}
