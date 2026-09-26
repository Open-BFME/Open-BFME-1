// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/campaignmanagerascii /Iinputs/reference/shims/stringbaseunicode /Igame/Libraries/Source/WWVegas/WWLib
//
// Apt main-menu helper at 0x0051D690: clear this+0x25b, optionally restore
// Shell audio through TheAudio vslot +0x6c, then GameWindowTransitionsHandler
// setGroup on 0x012F3330 with an AsciiString temporary.  Shell predicates
// 0x0057F250 checks the shell music handle. 0x0057F130 restores shell music.

#include <wchar.h>
#include "Common/AsciiString.h"

class Rva0051D690Shell
{
public:
	bool check();
	void restore();

private:
	char m_padding[0x64];
	unsigned int m_musicHandle;
};

typedef unsigned int AudioHandle;

class AudioEventRTS
{
public:
	AudioEventRTS(const AudioEventRTS &source);
	virtual void slot00();
	~AudioEventRTS();

private:
	char m_padding[0x6C];
};

#pragma comment(linker, "/alternatename:??0AudioEventRTS@@QAE@ABV0@@Z=?j_00047b27@@YAXXZ")
#pragma comment(linker, "/alternatename:??1AudioEventRTS@@QAE@XZ=?j_00026f35@@YAXXZ")

class Rva000B21A0Object
{
public:
	void setValue(unsigned int value);
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
	virtual void slot40();
	virtual AudioHandle addAudioEvent(AudioEventRTS *event);
	virtual void slot48(); virtual void slot4C();
	virtual void slot50(); virtual void slot54();
	virtual void slot58(); virtual void slot5C();
	virtual void slot60(); virtual void slot64();
	virtual void slot68();
	virtual void slot6c(int a, int b, int c);
	virtual void slot70(); virtual void slot74();
	virtual void slot78(); virtual void slot7C();
	virtual void slot80(); virtual void slot84();
	virtual void slot88(); virtual void slot8C();
	virtual void slot90(); virtual void slot94();
	virtual void slot98(); virtual void slot9C();
	virtual void slotA0(); virtual void slotA4();
	virtual void slotA8(); virtual void slotAC();
	virtual bool isCurrentlyPlaying(AudioHandle handle);
	virtual void slotB4(); virtual void slotB8();
	virtual void slotBC(); virtual void slotC0();
	virtual void slotC4(); virtual void slotC8();
	virtual void slotCC(); virtual void slotD0();
	virtual void slotD4(); virtual void slotD8();
	virtual void slotDC(); virtual void slotE0();
	virtual void slotE4(); virtual void slotE8();
	virtual void slotEC(); virtual void slotF0();
	virtual void slotF4(); virtual void slotF8();
	virtual void slotFC(); virtual void slot100();
	virtual void slot104(); virtual void slot108();
	virtual void slot10C(); virtual void slot110();
	virtual void slot114(); virtual void slot118();
	virtual void slot11C(); virtual void slot120();
	virtual void *getMiscAudio();
};

class Rva0051D690GlobalData
{
public:
	char m_padding[0xBB4];
	bool m_noShellAudio;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindowTransitions.h
class GameWindowTransitionsHandler
{
public:
	void setGroup(AsciiString name);
};

extern Rva0051D690Shell *g_obj12F4B58;
extern Rva0051D690Audio *TheAudioClientUpdate;
extern Rva0051D690GlobalData *TheWritableGlobalData;
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

void Rva0051D690Shell::restore()
{
	if (TheWritableGlobalData && !TheWritableGlobalData->m_noShellAudio)
	{
		if (TheAudioClientUpdate && TheAudioClientUpdate->getMiscAudio() &&
			!TheAudioClientUpdate->isCurrentlyPlaying(m_musicHandle))
		{
			TheAudioClientUpdate->slot6c(2, 1, 0);
			AudioEventRTS event(*reinterpret_cast<AudioEventRTS *>(
				reinterpret_cast<char *>(TheAudioClientUpdate->getMiscAudio()) + 0xD90));
			reinterpret_cast<Rva000B21A0Object *>(&event)->setValue(2);
			m_musicHandle = TheAudioClientUpdate->addAudioEvent(&event);
		}
	}
}
