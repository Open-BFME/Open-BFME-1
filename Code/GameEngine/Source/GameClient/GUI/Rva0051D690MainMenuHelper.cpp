// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/campaignmanagerascii /Ireference/shims/stringbaseunicode /ICode/Libraries/Source/WWVegas/WWLib
//
// Apt main-menu helper at 0x0051D690: clear this+0x25b, optionally restore
// Shell audio through TheAudio vslot +0x6c, then GameWindowTransitionsHandler
// setGroup on 0x012F3330 with an AsciiString temporary.  Shell predicates
// 0x0057F250 / 0x0057F130 are claimed.

#include <wchar.h>
#include "Common/AsciiString.h"

class Rva0051D690Shell
{
public:
	bool check();
	void restore();
};

class Rva0051D690Audio
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
	virtual void slot68();
	virtual void slot6c(int a, int b, int c);
};

class GameWindowTransitionsHandler
{
public:
	void setGroup(AsciiString name);
};

extern Rva0051D690Shell *g_obj12F4B58;
extern Rva0051D690Audio *TheAudioClientUpdate;
extern GameWindowTransitionsHandler *g_theTransitionHandler;

class Rva0051D690
{
public:
	void apply();

private:
	char m_unmodelled[0x25b];
	char m_flag25b;
};

void Rva0051D690::apply()
{
	m_flag25b = 0;
	if (g_obj12F4B58 && !g_obj12F4B58->check())
	{
		TheAudioClientUpdate->slot6c(2, 1, 0);
		g_obj12F4B58->restore();
	}
	g_theTransitionHandler->setGroup(AsciiString("MainMenuToSubMenu"));
}
