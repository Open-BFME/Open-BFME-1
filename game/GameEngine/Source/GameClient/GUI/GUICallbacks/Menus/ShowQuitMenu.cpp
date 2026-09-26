// cl: /DNDEBUG /MD
// BFME's quit-menu opener is the null-singleton arm reached by bfmeGo947C.
// QuitMenu.apt and InGameUI::setQuitMenuVisible identify the screen action.

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	StringBase(const T *text);
	StringBase(const StringBase<T> &other);
	~StringBase();

	void *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString(const char *text) : StringBase<char>(text) {}
	AsciiString(const AsciiString &other) : StringBase<char>(other) {}
	~AsciiString() {}
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
	virtual void slot84(int) = 0;
	virtual bool slot85() = 0;
};

class Display
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
	virtual bool slot77() = 0;
	virtual bool slot78() = 0;
};

class BfmeVirtualMouseSetCursor
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
	virtual void setCursor(int cursor) = 0;
};

class BfmeHistoryYR
{
public:
	void bfmeSetYR(unsigned char answer);
};

class GameWindowTransitionsHandler
{
public:
	bool isFinished();
};

class Shell
{
public:
	void showShell(bool);
	void push(AsciiString, bool);
};

class BfmeThingFGA
{
public:
	int bfmeGoFGA();
	char m_pad[0x69];
	char m_flag;
};

class GameLogic
{
public:
	bool isInMultiplayerGame();
	};

class BfmeGameLogicPause
{
public:
	void setGamePaused(bool paused, int pauseMode, bool affectMouse);
};

extern Display *TheDisplay;
extern void _bfme_hidePurchaseScience();
extern void HideInGameChat();
extern void HideDiplomacy();

void showQuitMenu()
{
	if (*(void **)0x012F4B40 != 0)
		return;

	if ((*(InGameUI **)0x012F148C)->slot85())
		return;

	if (*(void **)0x012F49B0 != 0)
		return;

	if ((unsigned char)((BfmeThingFGA *)*(void **)0x012F0898)->bfmeGoFGA())
		return;

	if ((*(BfmeThingFGA **)0x012F0898)->m_flag)
		return;

	if (*(int *)((char *)*(void **)0x012F076C + 0x17080) >= 0)
		return;

	if ((*(GameWindowTransitionsHandler **)0x012F3330)->isFinished() == false)
		return;

	if (*(void **)0x012F4964 != 0)
		return;

	if (TheDisplay != 0) {
		if (TheDisplay->slot78())
			return;
		if (TheDisplay->slot77())
			return;
	}

	_bfme_hidePurchaseScience();
	HideInGameChat();
	HideDiplomacy();
	((BfmeHistoryYR *)*(void **)0x012F4C5C)->bfmeSetYR(1);

	GameLogic *logic = *(GameLogic **)0x012F0898;
	if (!logic->isInMultiplayerGame())
		((BfmeGameLogicPause *)logic)->setGamePaused(true, 0, true);

	((BfmeVirtualMouseSetCursor *)*(void **)0x012F4C5C)->setCursor(2);
	(*(Shell **)0x012F4B58)->showShell(false);
	(*(Shell **)0x012F4B58)->push(AsciiString("QuitMenu.apt"), false);
	(*(InGameUI **)0x012F148C)->slot84(1);
}
