// ?clearGameData@GameLogic@@QAEX_N_N@Z
// partial score=0.55 date=2026-09-11
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// BFME GameLogic::clearGameData grew a second Bool over the ZH one-arg
// version; ZH's copy stays in GameLogicDispatch.cpp as present-unmatched.
// Retail 0x00396B00, 451B.

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

struct BfmeStringData
{
	Int m_refCount;
	unsigned short m_length;
};

class AsciiString
{
public:
	Bool isNotEmpty() const
	{
		return m_data != 0 && ((const BfmeStringData *)m_data)->m_length != 0;
	}

private:
	void *m_data;
};

class BfmeGlobalData
{
public:
	unsigned char m_unmodelled000[0xb80];
	AsciiString m_initialFile;
};

extern BfmeGlobalData *TheWritableGlobalData;

class GameMessage
{
public:
	void appendBooleanArgument(Bool arg);
};

class MessageStream
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual GameMessage *appendMessage(Int type) = 0;
};

extern MessageStream *TheMessageStream;

class Watchdog
{
public:
	void suppressTimeouts();
	void resumeTimeouts();
};
#define TheWatchdog (*(Watchdog **)0x012ef18c)

class StatsCollector
{
public:
	void writeFileEnd();
};
#define TheStatsCollector (*(StatsCollector **)0x012ed63c)

class Glo012F7048
{
public:
	virtual void g00();
	virtual void g01();
	virtual void g02();
	virtual void g03();
	virtual void g04(Bool arg);
	unsigned char m_pad4[4];
	unsigned char m_flag8;
};
#define Glo012F7048Ptr (*(Glo012F7048 **)0x012f7048)

class ScriptActions
{
public:
	virtual void sa00();
	virtual void sa01();
	virtual void sa02();
	virtual void sa03();
	virtual void sa04();
	virtual void sa05();
	virtual void sa06();
	virtual void sa07();
	virtual void sa08();
	virtual void sa09();
	virtual void closeWindows(Bool arg);
};
#define TheScriptActions (*(ScriptActions **)0x012f0620)

class AudioManager
{
public:
	virtual void a00();
	virtual void a01();
	virtual void a02();
	virtual void a03();
	virtual void a04();
	virtual void a05();
	virtual void a06();
	virtual void a07();
	virtual void a08();
	virtual void a09();
	virtual void a10();
	virtual void a11();
	virtual void a12();
	virtual void a13();
	virtual void a14();
	virtual void a15isValid(Int arg);  // slot15, 0x3c
	virtual Int a16check();          // slot16, 0x40
	virtual void a17();
	virtual void a18();
	virtual void a19();
	virtual void a20();
	virtual void a21();
	virtual void a22();
	virtual void a23();
	virtual void a24();
	virtual void a25();
	virtual void a26();
	virtual void a27();
	virtual void a28();
	virtual void a29();
	virtual void a30();
	virtual void a31();
	virtual void a32();
	virtual void a33();
	virtual void a34();
	virtual void a35();
	virtual void a36();
	virtual void a37();
	virtual void a38();
	virtual void a39();
	virtual void a40();
	virtual void a41();
	virtual void a42();
	virtual void a43();
	virtual void a44();
	virtual void a45();
	virtual void a46();
	virtual void a47();
	virtual void a48();
	virtual void a49();
	virtual void a50();
	virtual void a51();
	virtual void a52();
	virtual void a53();
	virtual void a54();
	virtual void a55();
	virtual void a56();
	virtual void a57();
	virtual void a58();
	virtual void a59();
	virtual void a60();
	virtual void a61();
	virtual void a62();
	virtual void a63();
	virtual void a64();
	virtual void a65();
	virtual void a66();
	virtual void a67();
	virtual void a68();
	virtual void a69();
	virtual void a70();
	virtual void a71();
	virtual void a72();
	virtual void a73();
	virtual void a74();
	virtual void a75();
	virtual void a76();
	virtual void a77();
	virtual void a78();
	virtual void a79();
	virtual void a80();
	virtual void a81();
	virtual void a82();
	virtual void a83();
	virtual void a84();
	virtual void a85();
	virtual void a86();
	virtual void a87();
	virtual void a88();
	virtual void a89();
	virtual void a90();
	virtual void a91();
	virtual void a92();
	virtual void a93();
	virtual void a94setup();          // slot94, 0x178
};
#define TheAudio (*(AudioManager **)0x012ed668)

class Glo012F1028
{
public:
	unsigned char m_pad[0x2c];
	unsigned char m_flag2c;
	unsigned char m_flag2d;
};
#define Glo012F1028Ptr (*(Glo012F1028 **)0x012f1028)

class Shell
{
public:
	void showShell(Bool bringForward);
	Bool showShellMap(Bool useShellMap);
};
extern Shell *TheShell;

Bool _bfme_showScoreScreen();

class GameEngine
{
public:
	virtual void ge00();
	virtual void ge01();
	virtual void ge02();
	virtual void ge03();
	virtual void reset();              // slot4, 0x10
	virtual void ge05();
	virtual void ge06();
	virtual void ge07();
	virtual void ge08();
	virtual void ge09();
	virtual void ge10();
	virtual void ge11();
	virtual void ge12();
	virtual void setQuitting(Bool arg); // slot13, 0x34
};
#define TheGameEngine (*(GameEngine **)0x012ed524)

class InGameUI
{
public:
	virtual void iu00(); virtual void iu01(); virtual void iu02(); virtual void iu03();
	virtual void iu04(); virtual void iu05(); virtual void iu06(); virtual void iu07();
	virtual void iu08(); virtual void iu09(); virtual void iu10(); virtual void iu11();
	virtual void iu12(); virtual void iu13(); virtual void iu14(); virtual void iu15();
	virtual void iu16(); virtual void iu17(); virtual void iu18(); virtual void iu19();
	virtual void iu20(); virtual void iu21(); virtual void iu22(); virtual void iu23();
	virtual void iu24(); virtual void iu25(); virtual void iu26(); virtual void iu27();
	virtual void iu28(); virtual void iu29(); virtual void iu30(); virtual void iu31();
	virtual void iu32(); virtual void iu33(); virtual void iu34(); virtual void iu35();
	virtual void iu36(); virtual void iu37(); virtual void iu38(); virtual void iu39();
	virtual void iu40(); virtual void iu41(); virtual void iu42(); virtual void iu43();
	virtual void iu44(); virtual void iu45(); virtual void iu46(); virtual void iu47();
	virtual void iu48(); virtual void iu49(); virtual void iu50(); virtual void iu51();
	virtual void iu52(); virtual void iu53(); virtual void iu54(); virtual void iu55();
	virtual void iu56(); virtual void iu57();
	virtual void iu58clear();          // slot58, 0xe8
};
#define TheInGameUI (*(InGameUI **)0x012f148c)

class ControlBar
{
public:
	virtual void cb00();
	virtual void cb01();
	virtual void cb02();
	virtual void cb03();
	virtual void cb04();
	virtual void cb05reset();           // slot5, 0x14
};
#define TheControlBar (*(ControlBar **)0x012f33f8)

void HideControlBar(Bool arg);

class Mouse
{
public:
	void setVisibility(Bool visible);
};
#define TheMouse (*(Mouse **)0x012f4c5c)

class WindowLayout
{
public:
	virtual void wl00();
	virtual void deleteInstance(Bool arg);  // slot1, 0x04
	virtual void wl02();
	virtual void wl03();
	virtual void wl04();
	virtual void wl05();
	virtual void wl06();
	virtual void wl07();
	virtual void destroyWindows();            // slot8, 0x20
};

#define BfmeSavedClientFrame (*(int *)0x012ed508)
#define Rva00579160Flag (*(int *)0x012f4b54)

class GameLogic
{
public:
	void clearGameData(const Bool showScoreScreen, Bool arg2);
	void closeWindows();       // matched elsewhere: Code/GameEngine/Source/Common/GameLogic_closeWindows_Thunk.cpp

private:
	unsigned char m_pad000[0xa4];
	WindowLayout *m_background;         // 0xa4
	unsigned char m_pad0a8[0x10c - 0xa4 - 4];
	Int m_gameMode;                      // 0x10c
};

void GameLogic::clearGameData(const Bool showScoreScreen, Bool arg2)
{
	Watchdog *watchdog = TheWatchdog;
	if (watchdog)
		watchdog->suppressTimeouts();

	TheAudio->a94setup();

	Glo012F7048 *state7048 = Glo012F7048Ptr;
	if (state7048)
	{
		if (state7048->m_flag8)
			state7048->g04(false);
	}

	StatsCollector *statsCollector = TheStatsCollector;
	if (statsCollector)
		statsCollector->writeFileEnd();

	ScriptActions *scriptActions = TheScriptActions;
	if (scriptActions)
		scriptActions->closeWindows(false);

	AudioManager *audio2 = TheAudio;
	if (audio2 && audio2->a16check() == 0)
		TheAudio->a15isValid(2);     // vslot 0x3c

	if ((m_gameMode != 8 && m_gameMode != 4) ||
		(Glo012F1028Ptr && Glo012F1028Ptr->m_flag2c && Glo012F1028Ptr->m_flag2d))
	{
		if (showScoreScreen)
		{
			TheShell->showShell(false);
			if (!_bfme_showScoreScreen())
			{
				if (Rva00579160Flag == 0)
					TheShell->showShellMap(true);
				TheShell->showShell(true);
			}
		}
		else if (arg2)
		{
			if (Rva00579160Flag == 0)
				TheShell->showShellMap(true);
			TheShell->showShell(true);
		}
	}

	TheGameEngine->reset();
	m_gameMode = 8;

	if (TheWritableGlobalData->m_initialFile.isNotEmpty())
		TheGameEngine->setQuitting(true);

	{
		GameMessage *msg = TheMessageStream->appendMessage(0x3eb);
		msg->appendBooleanArgument(true);
	}

	TheInGameUI->iu58clear();
	TheControlBar->cb05reset();
	HideControlBar(true);
	closeWindows();

	TheMouse->setVisibility(true);

	if (m_background)
		m_background->destroyWindows();
	if (m_background)
		m_background->deleteInstance(true);
	m_background = 0;

	BfmeSavedClientFrame = 0;
	if (TheWatchdog)
		TheWatchdog->resumeTimeouts();
}
