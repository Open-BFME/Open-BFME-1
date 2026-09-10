// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// ControlBar::populateUnderConstruction, retail 0x004AF6A0, 627 bytes.
// Zero Hour's body (ControlBarUnderConstruction.cpp) with BFME's additions:
// the twenty command windows are cleared first, the cancel button is
// m_commandWindows[0] rather than a winGetWindowFromId lookup, and the
// overlay pass collects the windows it lit into a vector the object at
// this+0x2f0 consumes. The string literal is Zero Hour's own
// "Command_CancelConstruction".
//
// BFME's ExitInterface reaches getRallyPoint at vtable+0x20, one slot later
// than Zero Hour's declaration order puts it.

#include <vector>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;

enum { MAX_COMMANDS_PER_SET = 20 };

class Object;
class CommandButton;

template <class Type>
class StringBase
{
private:
	StringBase(const char *s);
	friend class AsciiString;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:

	AsciiString(const char *s)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(s);
	}

	~AsciiString() { releaseBuffer(); }

protected:

	void releaseBuffer();

private:

	void *m_text;

};

struct Coord3D
{
	Real x;
	Real y;
	Real z;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class ExitInterface
{
public:
	virtual void slot0() = 0;
	virtual void slot1() = 0;
	virtual void slot2() = 0;
	virtual void slot3() = 0;
	virtual void slot4() = 0;
	virtual void slot5() = 0;
	virtual void slot6() = 0;
	virtual void slot7() = 0;
	virtual const Coord3D *getRallyPoint(void) const = 0;	// slot 8, vtable+0x20
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	ExitInterface *getObjectExitInterface(void) const;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
class GameWindow
{
public:
	void bfmeClose(Bool hide);
	UnsignedInt winSetStatus(UnsignedInt status);
	UnsignedInt winClearStatus(UnsignedInt status);
};

// The enable/disable call the cancel button takes; named by the pin that
// already stands at its thunk.
class BfmeUnit1013
{
public:
	void bfmeStop1013(char enable);
};

// The predicate the object under construction answers, and the one the
// player list answers; both reached through their existing pins.
class BfmeTargetJB
{
public:
	Bool bfmeTailJB(void);
};

class BfmePlayersERH
{
public:
	char bfmeBusyERH(void);
};

class BfmeMemberRV
{
public:
	Bool bfmeAskRV(void);
};

class Player;

class Rva002EE330PlayerList
{
private:
	char m_slice_pad[0x0C];

public:
	Player *m_localPlayer;
};

extern Rva002EE330PlayerList *Rva002EE330ThePlayers;

// The global at 0x012F4B98. Its two entry points here are the already
// matched bodies at 0x0058C040 and 0x005976B0, reached through their
// incremental-link thunks.
class Rva0058C040
{
public:
	void invoke(void);
};

class Rva005976B0
{
public:
	void update(void *object);
};

class Glo012F4B98Type;

extern Glo012F4B98Type *Glo012F4B98;

// The object ControlBar keeps at +0x2f0, identified only by the body it runs.
class Rva004B19E0
{
public:
	void apply(void *windows);
};

class ControlBar;

extern ControlBar *TheControlBar;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class ControlBar
{
public:
	void updateConstructionTextDisplay(Object *obj);

private:
	const CommandButton *findCommandButton(const AsciiString &name);
	void setPortraitByObject(Object *obj);
	void setControlCommand(GameWindow *window, const CommandButton *commandButton);

protected:
	void populateUnderConstruction(Object *objectUnderConstruction);
	void showRallyPoint(const Coord3D *loc);

	char m_slice_pad[0x100];				// retail this+0x00 .. +0xFF, untouched
	GameWindow *m_commandWindows[MAX_COMMANDS_PER_SET];	// this+0x100
	char m_slice_padA[0x2EC - 0x150];			// this+0x150 .. +0x2EB, untouched

public:
	Int m_bfmeOverlayMode;					// this+0x2EC
	Rva004B19E0 *m_bfmeOverlaySink;				// this+0x2F0

};

// ?populateUnderConstruction@ControlBar@@IAEXPAVObject@@@Z
void ControlBar::populateUnderConstruction(Object *objectUnderConstruction)
{

	// sanity
	if (objectUnderConstruction == 0)
	{
		if (Glo012F4B98)
			((Rva0058C040 *)Glo012F4B98)->invoke();
		return;
	}

	// clear every command window before the cancel button is placed
	for (Int i = 0; i < MAX_COMMANDS_PER_SET; ++i)
	{
		if (m_commandWindows[i])
		{
			m_commandWindows[i]->bfmeClose(true);
			setControlCommand(m_commandWindows[i], 0);
		}
	}

	Bool overlay = (TheControlBar->m_bfmeOverlayMode == 1);

	_STL::vector<GameWindow *> windows;

	Bool underConstruction = ((BfmeTargetJB *)objectUnderConstruction)->bfmeTailJB();
	Bool lit = ((BfmePlayersERH *)Rva002EE330ThePlayers)->bfmeBusyERH() || underConstruction;

	// set the cancel construction button
	const CommandButton *commandButton = findCommandButton("Command_CancelConstruction");
	GameWindow *win = m_commandWindows[0];

	if (commandButton && win)
	{
		win->bfmeClose(false);

		if (overlay && lit)
		{
			win->winSetStatus(0x4000000);				// WIN_STATUS_USE_OVERLAY_STATES
			windows.push_back(win);
		}
		else
			win->winClearStatus(0x4000000);

		setControlCommand(win, commandButton);

		if (underConstruction)
		{
			((BfmeUnit1013 *)win)->bfmeStop1013(1);
			win->winClearStatus(0x40000000);
		}
		else if (((BfmeMemberRV *)Rva002EE330ThePlayers->m_localPlayer)->bfmeAskRV())
		{
			((BfmeUnit1013 *)win)->bfmeStop1013(0);
			win->winClearStatus(0x40000000);
		}
		else
		{
			((BfmeUnit1013 *)win)->bfmeStop1013(0);
			win->winSetStatus(0x40000000);
		}
	}

	// set the text description of what is building
	updateConstructionTextDisplay(objectUnderConstruction);

	// set the portrait for the thing being constructed
	setPortraitByObject(objectUnderConstruction);

	// and show the rally point, if it should have one,
	ExitInterface *exit = objectUnderConstruction->getObjectExitInterface();
	if (exit)
		showRallyPoint(exit->getRallyPoint());

	if (Glo012F4B98)
		((Rva005976B0 *)Glo012F4B98)->update(objectUnderConstruction);

	m_bfmeOverlaySink->apply(&windows);

}  // end populateUnderConstruction
