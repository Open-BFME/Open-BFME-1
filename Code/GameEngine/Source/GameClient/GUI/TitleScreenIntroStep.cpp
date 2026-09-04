// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: title-screen intro timed-op at 0x0042EDC0 (139B).
// Same (int, bool) ABI as mapRollLoadGame / parchmentMapFadeLoadGame.
// serviceWindowsOS at GameEngine +0x40, Display::isMoviePlaying at +0xF0,
// then showShellMap/showShell when m_initialFile is empty. FieldParse
// PlayIntro is GlobalData+0xBB6; +0xB80 is m_initialFile; +0xBB7 is the
// after-intro flag the ZH GameClient::update twin clears after showShell.

#define BFME_VSLOT(n) virtual void slot##n();

class GameEngine
{
public:
	BFME_VSLOT(0) BFME_VSLOT(1) BFME_VSLOT(2) BFME_VSLOT(3) BFME_VSLOT(4)
	BFME_VSLOT(5) BFME_VSLOT(6) BFME_VSLOT(7) BFME_VSLOT(8) BFME_VSLOT(9)
	BFME_VSLOT(10) BFME_VSLOT(11) BFME_VSLOT(12) BFME_VSLOT(13) BFME_VSLOT(14)
	BFME_VSLOT(15)
	virtual void serviceWindowsOS();
};

class Display
{
public:
	BFME_VSLOT(0) BFME_VSLOT(1) BFME_VSLOT(2) BFME_VSLOT(3) BFME_VSLOT(4)
	BFME_VSLOT(5) BFME_VSLOT(6) BFME_VSLOT(7) BFME_VSLOT(8) BFME_VSLOT(9)
	BFME_VSLOT(10) BFME_VSLOT(11) BFME_VSLOT(12) BFME_VSLOT(13) BFME_VSLOT(14)
	BFME_VSLOT(15) BFME_VSLOT(16) BFME_VSLOT(17) BFME_VSLOT(18) BFME_VSLOT(19)
	BFME_VSLOT(20) BFME_VSLOT(21) BFME_VSLOT(22) BFME_VSLOT(23) BFME_VSLOT(24)
	BFME_VSLOT(25) BFME_VSLOT(26) BFME_VSLOT(27) BFME_VSLOT(28) BFME_VSLOT(29)
	BFME_VSLOT(30) BFME_VSLOT(31) BFME_VSLOT(32) BFME_VSLOT(33) BFME_VSLOT(34)
	BFME_VSLOT(35) BFME_VSLOT(36) BFME_VSLOT(37) BFME_VSLOT(38) BFME_VSLOT(39)
	BFME_VSLOT(40) BFME_VSLOT(41) BFME_VSLOT(42) BFME_VSLOT(43) BFME_VSLOT(44)
	BFME_VSLOT(45) BFME_VSLOT(46) BFME_VSLOT(47) BFME_VSLOT(48) BFME_VSLOT(49)
	BFME_VSLOT(50) BFME_VSLOT(51) BFME_VSLOT(52) BFME_VSLOT(53) BFME_VSLOT(54)
	BFME_VSLOT(55) BFME_VSLOT(56) BFME_VSLOT(57) BFME_VSLOT(58) BFME_VSLOT(59)
	virtual bool isMoviePlaying();
};

#undef BFME_VSLOT

class Shell
{
public:
	void showShellMap(bool);
	void showShell(bool);
};

class GlobalData
{
public:
	unsigned char m_padB80[0xB80];
	void *m_initialFile;
	unsigned char m_padB84[0x32];
	bool m_playIntro;
	bool m_afterIntro;
};

extern GameEngine *TheGameEngine;
extern Display *TheDisplay;
extern Shell *TheShell;
extern GlobalData *TheWritableGlobalData;

// ?titleScreenIntroStep@@YAHH_N@Z
int titleScreenIntroStep(int, bool start)
{
	int result = 5;
	TheGameEngine->serviceWindowsOS();
	if (start)
	{
		GlobalData *gd = TheWritableGlobalData;
		if (gd->m_playIntro)
		{
			gd->m_playIntro = false;
			return result;
		}
	}
	if (!TheDisplay->isMoviePlaying())
	{
		result = 7;
		void *data = TheWritableGlobalData->m_initialFile;
		if (!data || *(unsigned short *)((char *)data + 4) == 0)
		{
			TheShell->showShellMap(true);
			TheShell->showShell(true);
		}
		TheWritableGlobalData->m_afterIntro = false;
	}
	return result;
}
