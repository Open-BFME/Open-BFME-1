// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned int WindowMsgData;
typedef bool Bool;
typedef int NameKeyType;

#define TRUE 1

enum WindowMsgHandledType
{
	MSG_IGNORED,
	MSG_HANDLED
};

enum
{
	GWM_CREATE = 1,
	GWM_DESTROY = 2,
	GWM_INPUT_FOCUS = 23,
	GBM_SELECTED = 0x4008
};

enum GameDifficulty
{
	DIFFICULTY_EASY,
	DIFFICULTY_NORMAL,
	DIFFICULTY_HARD
};

#include "string_base.h"

class AsciiString : private StringBase<char>
{
public:
	static const AsciiString TheEmptyString;
	AsciiString(const AsciiString &that) : StringBase<char>(that) {}
	~AsciiString() {}
};

class WindowLayout
{
public:
	virtual void runInit();
	virtual ~WindowLayout();
	virtual void runUpdate();
	virtual void runShutdown();
	virtual void hide();
	virtual void bringForward();
	virtual void addWindow();
	virtual void removeWindow();
	virtual void destroyWindows();
};

class GameWindow
{
public:
	Int winGetWindowId();
	WindowLayout *winGetLayout();
};

class GameWindowManager
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot0A(); virtual void slot0B();
	virtual void slot0C(); virtual void slot0D(); virtual void slot0E(); virtual void slot0F();
	virtual void slot10(); virtual void slot11(); virtual void slot12(); virtual void slot13();
	virtual void slot14(); virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot1A(); virtual void slot1B();
	virtual void slot1C(); virtual void slot1D(); virtual void slot1E(); virtual void slot1F();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot2A(); virtual void slot2B();
	virtual void slot2C(); virtual void slot2D(); virtual void slot2E(); virtual void slot2F();
	virtual void slot30(); virtual void slot31(); virtual void slot32(); virtual void slot33();
	virtual void slot34(); virtual void slot35(); virtual void slot36(); virtual void slot37();
	virtual void slot38(); virtual void slot39(); virtual void slot3A(); virtual void slot3B();
	virtual int winUnsetModal(GameWindow *window);
};

class CampaignManager
{
public:
	AsciiString getCurrentMap();
	void setCampaign(AsciiString campaign);
};

class ScriptEngine
{
public:
	void setObjectsShouldReceiveDifficultyBonus(Bool receive);
};

typedef void (ScriptEngine::*SetDifficultyBonus)(int);

static GameDifficulty s_AIDiff = DIFFICULTY_NORMAL;
static NameKeyType buttonOkID = -1;
static NameKeyType buttonCancelID = -1;
static NameKeyType radioButtonEasyAIID = -1;
static NameKeyType radioButtonMediumAIID = -1;
static NameKeyType radioButtonHardAIID = -1;

extern GameWindowManager *TheWindowManager;
extern CampaignManager *TheCampaignManager;
extern ScriptEngine *TheScriptEngine;
void setupGameStart(AsciiString mapName, int diff);

// ?DifficultySelectSystem@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z
WindowMsgHandledType DifficultySelectSystem(GameWindow *window, UnsignedInt msg,
	WindowMsgData mData1, WindowMsgData mData2)
{
	switch (msg)
	{
	case GWM_CREATE:
	{
		break;
	}
	case GWM_DESTROY:
	{
		break;
	}
	case GWM_INPUT_FOCUS:
	{
		if (mData1 == TRUE)
			*(Bool *)mData2 = TRUE;
		return MSG_HANDLED;
	}
	case GBM_SELECTED:
	{
		GameWindow *control = (GameWindow *)mData1;
		Int controlID = control->winGetWindowId();

		if (controlID == buttonOkID)
		{
			(TheScriptEngine->*reinterpret_cast<SetDifficultyBonus>(
				&ScriptEngine::setObjectsShouldReceiveDifficultyBonus))(*(int *)&s_AIDiff);
			WindowLayout *layout = window->winGetLayout();
			layout->destroyWindows();
			delete layout;
			setupGameStart(TheCampaignManager->getCurrentMap(), s_AIDiff);
		}
		else if (controlID == buttonCancelID)
		{
			TheCampaignManager->setCampaign(AsciiString::TheEmptyString);
			TheWindowManager->winUnsetModal(window);
			WindowLayout *layout = window->winGetLayout();
			layout->destroyWindows();
			delete layout;
		}
		else if (controlID == radioButtonEasyAIID)
		{
			s_AIDiff = DIFFICULTY_EASY;
		}
		else if (controlID == radioButtonMediumAIID)
		{
			s_AIDiff = DIFFICULTY_NORMAL;
		}
		else if (controlID == radioButtonHardAIID)
		{
			s_AIDiff = DIFFICULTY_HARD;
		}
		break;
	}
	default:
		return MSG_IGNORED;
	}

	return MSG_HANDLED;
}
