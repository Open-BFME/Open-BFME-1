// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport

#include <vector>

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	StringBase(const T *text);
	~StringBase();

	void *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString(const char *text) : StringBase<char>(text) {}
	~AsciiString() {}
};

class _bfme_AptGameWindow
{
public:
	virtual ~_bfme_AptGameWindow();

private:
	unsigned char m_unmodelled[0x214];
};

class InGameUI
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
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual void slot30() = 0;
	virtual void slot31() = 0;
	virtual void slot32() = 0;
	virtual void slot33() = 0;
	virtual void slot34() = 0;
	virtual void slot35() = 0;
	virtual void slot36() = 0;
	virtual void slot37() = 0;
	virtual void slot38() = 0;
	virtual void slot39() = 0;
	virtual void slot40() = 0;
	virtual void slot41() = 0;
	virtual void slot42() = 0;
	virtual void slot43() = 0;
	virtual void slot44() = 0;
	virtual void slot45() = 0;
	virtual void slot46() = 0;
	virtual void slot47() = 0;
	virtual void slot48() = 0;
	virtual void slot49() = 0;
	virtual void slot50() = 0;
	virtual void slot51() = 0;
	virtual void slot52() = 0;
	virtual void slot53() = 0;
	virtual void slot54() = 0;
	virtual void slot55() = 0;
	virtual void slot56() = 0;
	virtual void slot57() = 0;
	virtual void slot58() = 0;
	virtual void slot59() = 0;
	virtual void slot60() = 0;
	virtual void slot61() = 0;
	virtual void slot62() = 0;
	virtual void slot63() = 0;
	virtual void slot64() = 0;
	virtual void slot65() = 0;
	virtual void slot66() = 0;
	virtual void slot67() = 0;
	virtual void slot68() = 0;
	virtual void slot69() = 0;
	virtual void slot70() = 0;
	virtual void slot71() = 0;
	virtual void slot72() = 0;
	virtual void slot73() = 0;
	virtual void slot74() = 0;
	virtual void slot75() = 0;
	virtual void slot76() = 0;
	virtual void slot77() = 0;
	virtual void slot78() = 0;
	virtual void slot79() = 0;
	virtual void slot80() = 0;
	virtual void slot81() = 0;
	virtual void slot82() = 0;
	virtual void slot83() = 0;
	virtual void slot84(int value) = 0;
};

class BfmeGameLogicPause
{
public:
	void setGamePaused(bool paused, int pauseMode, bool affectMouse);

	public:
	unsigned char m_unmodelled[0x10c];
	int m_gameMode;
};

class Shell
{
public:
	void hide(bool immediate);
};

class BfmeOtherYH
{
public:
	void bfmeRefreshYH(int value);
};

void _bfme_closeAptScreen(const AsciiString &name);

extern InGameUI *TheInGameUI;
extern BfmeGameLogicPause *TheGameLogic;
extern Shell *TheShell;
extern BfmeOtherYH *g_bfmeOtherYH;
#define g_obj12F49E4 (*(void **)0x012F49E4)

class AptPlayerStatus : public _bfme_AptGameWindow
{
public:
	virtual ~AptPlayerStatus();

private:
	unsigned char m_unmodelled[0x40];
	std::vector<void *> m_gadgets;
};

// ??1AptPlayerStatus@@UAE@XZ
AptPlayerStatus::~AptPlayerStatus()
{
	*(const void ***)(this) = (const void **)0x01106DEC;
	*(const void ***)(reinterpret_cast<unsigned char *>(this) + 0x218) =
		(const void **)0x01106DE8;

	if (this == g_obj12F49E4)
	{
		InGameUI *ui = TheInGameUI;
		g_obj12F49E4 = 0;
		if (ui)
			ui->slot84(0);

		BfmeGameLogicPause *gameLogic = TheGameLogic;
		if (gameLogic && gameLogic->m_gameMode != 1 && gameLogic->m_gameMode != 5)
			gameLogic->setGamePaused(false, 0, true);

		if (TheShell)
			TheShell->hide(false);

		if (g_bfmeOtherYH)
			g_bfmeOtherYH->bfmeRefreshYH(0);

		AsciiString callback("AptPlayerStatus::InitGadgets");
		_bfme_closeAptScreen(callback);
	}
}
