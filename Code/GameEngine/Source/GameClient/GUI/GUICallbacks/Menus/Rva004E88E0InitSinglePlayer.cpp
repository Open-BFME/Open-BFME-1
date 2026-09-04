// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main

#if 0
template <class T>
class StringBase
{
public:
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	~StringBase();

private:
	void *m_data;
};

class AsciiString
{
public:
	AsciiString(const char *text)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(text);
	}
	AsciiString(const AsciiString &other)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(
			*(const StringBase<char> *)&other);
	}
	~AsciiString() {}

private:
	void *m_data;
};
#endif

#include "../../../../../../reference/shims/stringinline/StringInline.h"

class Player
{
public:
	char m_pad[0x25c];
	float m_skillPoints;
	float getSkillPoints() const { return m_skillPoints; }
};

class PlayerList
{
public:
	char m_pad[0x0c];
	Player *m_localPlayer;
	Player *getLocalPlayer() { return m_localPlayer; }
};

class CampaignManager
{
public:
	char m_pad[0x14];
	int m_rankPoints;
	int m_difficulty;
	void setRankPoints(int value) { m_rankPoints = value; }
	void setGameDifficulty(int value) { m_difficulty = value; }
};

class ScriptEngine
{
public:
	char m_pad[0x17620];
	int m_globalDifficulty;
	int getGlobalDifficulty() const { return m_globalDifficulty; }
};

class GameWindow;

class WindowLayout
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void hide(int immediate) = 0;
	virtual void bringForward() = 0;
	int m_unknown04;
	GameWindow *m_firstWindow;
};

class GameWindow
{
public:
	unsigned int winClearStatus(unsigned int status);
};

class GameWindowManager
{
public:
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2C() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void slot38() = 0;
	virtual void slot3C() = 0;
	virtual void slot40() = 0;
	virtual void slot44() = 0;
	virtual void slot48() = 0;
	virtual void slot4C() = 0;
	virtual void slot50() = 0;
	virtual void slot54() = 0;
	virtual void slot58() = 0;
	virtual void slot5C() = 0;
	virtual void slot60() = 0;
	virtual void slot64() = 0;
	virtual void slot68() = 0;
	virtual WindowLayout *winCreateLayout(AsciiString file) = 0;
};

extern PlayerList *ThePlayerList;
extern CampaignManager *TheCampaignManager;
extern ScriptEngine *TheScriptEngine;
extern GameWindowManager *TheWindowManager;

extern "C" __declspec(dllimport) double __cdecl floor(double value);

void grabSinglePlayerInfo(void);

static unsigned char s_needToFinishSinglePlayerInit;
static WindowLayout *s_blankLayout;
static int screenType;

void initSinglePlayer(void)
{
	screenType = 0;
	float floored;
	long rankPoints;
	floored = (float)floor(
		(double)ThePlayerList->getLocalPlayer()->getSkillPoints());
	__asm
	{
		fld [floored]
		fistp [rankPoints]
	}
	TheCampaignManager->setRankPoints(
		rankPoints);
	TheCampaignManager->setGameDifficulty(
		TheScriptEngine->getGlobalDifficulty());
	grabSinglePlayerInfo();
	s_needToFinishSinglePlayerInit = 1;
	s_blankLayout = TheWindowManager->winCreateLayout(
		AsciiString("Menus/BlankWindow.wnd"));
	s_blankLayout->hide(0);
	s_blankLayout->bringForward();
	s_blankLayout->m_firstWindow->winClearStatus(0x80);
}
