// ?updateContextCommand@ControlBar@@AAEXXZ
// partial score=0.11 date=2026-09-10
// cl: /DNDEBUG /MD /EHsc /Ireference/CnC_Generals_Zero_Hour/Generals/Code/Libraries/Include
// Open-BFME: ControlBar::updateContextCommand, retail 0x004A5950 (959 bytes).
//
// The method is private in the vendored ControlBar.h.  Its caller is the
// CB_CONTEXT_COMMAND branch of ControlBar::update.  These declarations keep
// the BFME offsets and the existing retail callees local to this TU; they do
// not define substitute callbacks or duplicate any global storage.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;

enum NameKeyType { NAMEKEY_INVALID = 0 };
enum CommandAvailability
{
	COMMAND_RESTRICTED = 0,
	COMMAND_AVAILABLE = 1,
	COMMAND_ACTIVE = 2,
	COMMAND_HIDDEN = 3,
	COMMAND_NOT_READY = 4,
	COMMAND_CANT_AFFORD = 5
};

class Image;
class ThingTemplate;
class ProductionEntry;
class ProductionUpdateInterface;
class Object;

class Drawable
{
public:
	Object *getObject(void) const
	{
		return *(Object *const *)((const char *)this + 0xFC);
	}
};

class ContainModuleInterface
{
public:
#define CONTAIN_SLOT(n) virtual void slot##n(void) = 0;
	CONTAIN_SLOT(00) CONTAIN_SLOT(01) CONTAIN_SLOT(02) CONTAIN_SLOT(03)
	CONTAIN_SLOT(04) CONTAIN_SLOT(05) CONTAIN_SLOT(06) CONTAIN_SLOT(07)
	CONTAIN_SLOT(08) CONTAIN_SLOT(09) CONTAIN_SLOT(10) CONTAIN_SLOT(11)
	CONTAIN_SLOT(12) CONTAIN_SLOT(13) CONTAIN_SLOT(14) CONTAIN_SLOT(15)
	CONTAIN_SLOT(16) CONTAIN_SLOT(17) CONTAIN_SLOT(18) CONTAIN_SLOT(19)
	CONTAIN_SLOT(20) CONTAIN_SLOT(21) CONTAIN_SLOT(22)
	virtual Int getContainMax(void) const = 0;
#define CONTAIN_SLOT2(n) virtual void slot##n(void) = 0;
	CONTAIN_SLOT2(24) CONTAIN_SLOT2(25) CONTAIN_SLOT2(26) CONTAIN_SLOT2(27)
	CONTAIN_SLOT2(28) CONTAIN_SLOT2(29) CONTAIN_SLOT2(30) CONTAIN_SLOT2(31)
	CONTAIN_SLOT2(32) CONTAIN_SLOT2(33) CONTAIN_SLOT2(34) CONTAIN_SLOT2(35)
	CONTAIN_SLOT2(36) CONTAIN_SLOT2(37) CONTAIN_SLOT2(38) CONTAIN_SLOT2(39)
	CONTAIN_SLOT2(40) CONTAIN_SLOT2(41) CONTAIN_SLOT2(42) CONTAIN_SLOT2(43)
	CONTAIN_SLOT2(44) CONTAIN_SLOT2(45) CONTAIN_SLOT2(46) CONTAIN_SLOT2(47)
	CONTAIN_SLOT2(48) CONTAIN_SLOT2(49) CONTAIN_SLOT2(50) CONTAIN_SLOT2(51)
	CONTAIN_SLOT2(52) CONTAIN_SLOT2(53) CONTAIN_SLOT2(54) CONTAIN_SLOT2(55)
	CONTAIN_SLOT2(56) CONTAIN_SLOT2(57) CONTAIN_SLOT2(58) CONTAIN_SLOT2(59)
	CONTAIN_SLOT2(60) CONTAIN_SLOT2(61) CONTAIN_SLOT2(62) CONTAIN_SLOT2(63)
	virtual Int getContainCount(Bool countRiders) const = 0;
#undef CONTAIN_SLOT2
#undef CONTAIN_SLOT
};

class ProductionEntry
{
public:
	Real getPercentComplete(void) const
	{
		return *(const Real *)((const char *)this + 0x14);
	}
};

class ProductionUpdateInterface
{
public:
#define PRODUCTION_SLOT(n) virtual void slot##n(void) = 0;
	PRODUCTION_SLOT(00) PRODUCTION_SLOT(01) PRODUCTION_SLOT(02)
	PRODUCTION_SLOT(03) PRODUCTION_SLOT(04) PRODUCTION_SLOT(05)
	PRODUCTION_SLOT(06) PRODUCTION_SLOT(07) PRODUCTION_SLOT(08)
	PRODUCTION_SLOT(09) PRODUCTION_SLOT(10) PRODUCTION_SLOT(11)
	PRODUCTION_SLOT(12) PRODUCTION_SLOT(13) PRODUCTION_SLOT(14)
	PRODUCTION_SLOT(15) PRODUCTION_SLOT(16) PRODUCTION_SLOT(17)
	virtual ProductionEntry *firstProduction(void) = 0;
#undef PRODUCTION_SLOT
};

class Object
{
public:
	ContainModuleInterface *getContain(void) const
	{
		return *(ContainModuleInterface *const *)((const char *)this + 0x1FC);
	}
	ProductionUpdateInterface *getProductionUpdateInterface(void);
	Bool isLocallyControlled(void) const;
};

class GameWindow
{
public:
	Bool winIsHidden(void);
	Int winHide(Bool hide);
	Int winEnable(Bool enable);
	UnsignedInt winSetStatus(UnsignedInt status);
	UnsignedInt winClearStatus(UnsignedInt status);
	UnsignedInt winGetStatus(void);
};

class CommandButton
{
public:
	Int getCommandType(void) const
	{
		return *(const Int *)((const char *)this + 0x10);
	}
	UnsignedInt getOptions(void) const
	{
		return *(const UnsignedInt *)((const char *)this + 0x18);
	}
	Bool hasOverlayStatus(void) const
	{
		return *(const unsigned char *)((const char *)this + 0x151) != 0;
	}
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};

class GameWindowManager
{
public:
#define WINDOW_SLOT(n) virtual void slot##n(void) = 0;
	WINDOW_SLOT(00) WINDOW_SLOT(01) WINDOW_SLOT(02) WINDOW_SLOT(03)
	WINDOW_SLOT(04) WINDOW_SLOT(05) WINDOW_SLOT(06) WINDOW_SLOT(07)
	WINDOW_SLOT(08) WINDOW_SLOT(09) WINDOW_SLOT(10) WINDOW_SLOT(11)
	WINDOW_SLOT(12) WINDOW_SLOT(13) WINDOW_SLOT(14) WINDOW_SLOT(15)
	WINDOW_SLOT(16) WINDOW_SLOT(17) WINDOW_SLOT(18) WINDOW_SLOT(19)
	WINDOW_SLOT(20) WINDOW_SLOT(21) WINDOW_SLOT(22) WINDOW_SLOT(23)
	WINDOW_SLOT(24) WINDOW_SLOT(25) WINDOW_SLOT(26) WINDOW_SLOT(27)
	WINDOW_SLOT(28) WINDOW_SLOT(29) WINDOW_SLOT(30) WINDOW_SLOT(31)
	WINDOW_SLOT(32) WINDOW_SLOT(33) WINDOW_SLOT(34) WINDOW_SLOT(35)
	WINDOW_SLOT(36) WINDOW_SLOT(37) WINDOW_SLOT(38) WINDOW_SLOT(39)
	WINDOW_SLOT(40) WINDOW_SLOT(41) WINDOW_SLOT(42) WINDOW_SLOT(43)
	WINDOW_SLOT(44) WINDOW_SLOT(45) WINDOW_SLOT(46) WINDOW_SLOT(47)
	WINDOW_SLOT(48) WINDOW_SLOT(49) WINDOW_SLOT(50) WINDOW_SLOT(51)
	WINDOW_SLOT(52) WINDOW_SLOT(53) WINDOW_SLOT(54)
	virtual GameWindow *winGetWindowFromId(GameWindow *parent, NameKeyType id) = 0;
#undef WINDOW_SLOT
};

class Player
{
public:
	Bool isPlayerActive(void) const;
};

class PlayerList
{
private:
	char m_pad[0x0C];
public:
	Player *m_localPlayer;
};

class ControlBar
{
private:
	void updateContextCommand(void);
	void setPortraitByObject(Object *obj);
	CommandAvailability getCommandAvailability(const CommandButton *command,
		GameWindow *win, Object *obj, Real *percent, Bool forceDisabledEvaluation) const;


	protected:
	void evaluateContextUI(void);

	char m_pad00[0x34];
	GameWindow *m_contextParent[9];
	char m_pad58[4];
	Drawable *m_currentSelectedDrawable;
	char m_pad60[0x10];
	UnsignedInt m_lastRecordedInventoryCount;
	char m_pad74[0x8C];
	GameWindow *m_commandWindows[20];
	char m_pad150[0x11C];
	Int m_buildUpClockColor;
};

extern NameKeyGenerator *TheNameKeyGenerator;
extern GameWindowManager *TheWindowManager;
extern PlayerList *Rva002EE330ThePlayers;
extern Real g_bfmeDefaultBU;
extern Real g_bfmeScaleBC;

void *GadgetButtonGetData(GameWindow *window);
void GadgetButtonDrawInverseClock(GameWindow *window, Int percent, Int color);
void GadgetButtonDrawOverlayImage(GameWindow *window, const Image *image);
void GadgetCheckLikeButtonSetVisualCheck(GameWindow *window, Bool checked);

// The BFME command-button resolver is an existing typed retail callee.  The
// call is retained because the retail command path clears the overlay after
// resolving the button's final override.
class BfmeCommandButtonDispatchILT;
class BfmeCommandButtonResolveILT
{
public:
	BfmeCommandButtonDispatchILT *resolve(void);
};

void ControlBar::updateContextCommand(void)
{
	Object *obj = 0;
	Int i;

	if (m_currentSelectedDrawable)
		obj = m_currentSelectedDrawable->getObject();

	ContainModuleInterface *contain = obj ? obj->getContain() : 0;
	if (contain && contain->getContainMax() > 0 &&
		m_lastRecordedInventoryCount != contain->getContainCount(false))
	{
		m_lastRecordedInventoryCount = contain->getContainCount(false);
		evaluateContextUI();
	}

	ProductionUpdateInterface *pu = obj ? obj->getProductionUpdateInterface() : 0;
	if (!m_contextParent[3]->winIsHidden())
	{
		setPortraitByObject(0);
		if (pu)
		{
			ProductionEntry *produce = pu->firstProduction();
			if (produce)
			{
				static NameKeyType winID =
					TheNameKeyGenerator->nameToKey("ControlBar.wnd:ButtonQueue01");
				GameWindow *win = TheWindowManager->winGetWindowFromId(
					m_contextParent[3], winID);
				GadgetButtonDrawInverseClock(win,
					(Int)produce->getPercentComplete(), m_buildUpClockColor);
			}
		}
	}

	for (i = 0; i < 20; ++i)
	{
		GameWindow *win;
		const CommandButton *command;
		if (!m_commandWindows[i])
			continue;
		win = m_commandWindows[i];
		command = (const CommandButton *)GadgetButtonGetData(win);
		if (!command)
			continue;

		win->winClearStatus(0x04000000);
		win->winClearStatus(0x01000000);
		win->winClearStatus(0x40000000);
		win->winClearStatus(0x80000000);

		Real percent = 0.0f;
		CommandAvailability availability =
			getCommandAvailability(command, win, obj, &percent, false);

		switch (availability)
		{
		case COMMAND_HIDDEN:
			win->winHide(true);
			break;
		case COMMAND_RESTRICTED:
			win->winEnable(false);
			break;
		case COMMAND_NOT_READY:
			win->winEnable(false);
			win->winSetStatus(0x80000000);
			break;
		case COMMAND_CANT_AFFORD:
			win->winEnable(false);
			win->winSetStatus(0x01000000);
			break;
		default:
			win->winEnable(true);
			break;
		}

		if (availability == COMMAND_NOT_READY &&
			percent != g_bfmeDefaultBU)
		{
			GadgetButtonDrawInverseClock(win,
				(Int)(percent * g_bfmeScaleBC), m_buildUpClockColor);
		}

		if (command->getCommandType() != 0x0F &&
			!command->hasOverlayStatus())
		{
			((BfmeCommandButtonResolveILT *)command)->resolve();
			GadgetButtonDrawOverlayImage(win, 0);
		}

		if (command->getOptions() & 0x00000400)
			GadgetCheckLikeButtonSetVisualCheck(win,
				availability == COMMAND_ACTIVE);
	}
}
