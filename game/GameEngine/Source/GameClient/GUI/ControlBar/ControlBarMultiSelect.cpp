// cl: /DNDEBUG /MD /EHsc
// ControlBar::updateContextMultiSelect, retail 0x004A9620, 688 bytes including the eight-entry jump table.
// Twin: Zero Hour ControlBarMultiSelect.cpp; reached from ControlBar::update for context 7.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef bool Bool;

extern "C" void *__cdecl memset(void *dst, int value, unsigned int size);
#pragma intrinsic(memset)

enum { MAX_COMMANDS_PER_SET = 20 };

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Overridable.h
class Overridable
{
public:
	virtual ~Overridable();
	const Overridable *getFinalOverride() const;
	Overridable *m_nextOverride;
};

class ThingTemplate : public Overridable
{
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class CommandButton
{
public:
	unsigned char m_pad00[0x10];
	Int m_commandType;
	unsigned char m_pad14[4];
	Int m_options;
	Int getOptions() const
	{
		return *(const Int *)((const char *)this + 0x18);
	}
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
class GameWindow
{
public:
	int winHide(bool hide);
	void bfmeClose(Bool hide);
	Bool winIsHidden(void);
	UnsignedInt _bfme_winSetStatus(UnsignedInt status);
	UnsignedInt winClearStatus(UnsignedInt status);
	Int winEnable(Bool enable);
};

class Object;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/Drawable.h
class Drawable
{
public:
	// Existing field view for retail's inlined object access.

	char m_slice_pad[0xFC];					// retail this+0x00 .. +0xFB, untouched
	Object *m_object;					// this+0xFC
};

static __forceinline Object *drawableObject(const Drawable *draw)
{
    return draw->m_object;
}

// BFME list layout: the list holds its sentinel node at +0; nodes link next/prev
// at +0/+4 and carry the drawable at +8.
struct BfmeControlBarDrawableListNode
{
	BfmeControlBarDrawableListNode *next;
	BfmeControlBarDrawableListNode *prev;
	Drawable *value;
};

struct BfmeControlBarDrawableList
{
	BfmeControlBarDrawableListNode *head;
};

class InGameUI;
extern InGameUI *TheInGameUI;

#define BFME_CONTROLBAR_INGAME_SLOT(n) virtual void slot##n(void) = 0;
class BfmeControlBarInGameUISelectionView
{
public:
	BFME_CONTROLBAR_INGAME_SLOT(0)  BFME_CONTROLBAR_INGAME_SLOT(1)
	BFME_CONTROLBAR_INGAME_SLOT(2)  BFME_CONTROLBAR_INGAME_SLOT(3)
	BFME_CONTROLBAR_INGAME_SLOT(4)  BFME_CONTROLBAR_INGAME_SLOT(5)
	BFME_CONTROLBAR_INGAME_SLOT(6)  BFME_CONTROLBAR_INGAME_SLOT(7)
	BFME_CONTROLBAR_INGAME_SLOT(8)  BFME_CONTROLBAR_INGAME_SLOT(9)
	BFME_CONTROLBAR_INGAME_SLOT(10) BFME_CONTROLBAR_INGAME_SLOT(11)
	BFME_CONTROLBAR_INGAME_SLOT(12) BFME_CONTROLBAR_INGAME_SLOT(13)
	BFME_CONTROLBAR_INGAME_SLOT(14) BFME_CONTROLBAR_INGAME_SLOT(15)
	BFME_CONTROLBAR_INGAME_SLOT(16) BFME_CONTROLBAR_INGAME_SLOT(17)
	BFME_CONTROLBAR_INGAME_SLOT(18) BFME_CONTROLBAR_INGAME_SLOT(19)
	BFME_CONTROLBAR_INGAME_SLOT(20) BFME_CONTROLBAR_INGAME_SLOT(21)
	BFME_CONTROLBAR_INGAME_SLOT(22) BFME_CONTROLBAR_INGAME_SLOT(23)
	BFME_CONTROLBAR_INGAME_SLOT(24) BFME_CONTROLBAR_INGAME_SLOT(25)
	BFME_CONTROLBAR_INGAME_SLOT(26) BFME_CONTROLBAR_INGAME_SLOT(27)
	BFME_CONTROLBAR_INGAME_SLOT(28) BFME_CONTROLBAR_INGAME_SLOT(29)
	BFME_CONTROLBAR_INGAME_SLOT(30) BFME_CONTROLBAR_INGAME_SLOT(31)
	BFME_CONTROLBAR_INGAME_SLOT(32) BFME_CONTROLBAR_INGAME_SLOT(33)
	BFME_CONTROLBAR_INGAME_SLOT(34) BFME_CONTROLBAR_INGAME_SLOT(35)
	BFME_CONTROLBAR_INGAME_SLOT(36) BFME_CONTROLBAR_INGAME_SLOT(37)
	BFME_CONTROLBAR_INGAME_SLOT(38) BFME_CONTROLBAR_INGAME_SLOT(39)
	BFME_CONTROLBAR_INGAME_SLOT(40) BFME_CONTROLBAR_INGAME_SLOT(41)
	BFME_CONTROLBAR_INGAME_SLOT(42) BFME_CONTROLBAR_INGAME_SLOT(43)
	BFME_CONTROLBAR_INGAME_SLOT(44) BFME_CONTROLBAR_INGAME_SLOT(45)
	BFME_CONTROLBAR_INGAME_SLOT(46) BFME_CONTROLBAR_INGAME_SLOT(47)
	BFME_CONTROLBAR_INGAME_SLOT(48) BFME_CONTROLBAR_INGAME_SLOT(49)
	BFME_CONTROLBAR_INGAME_SLOT(50) BFME_CONTROLBAR_INGAME_SLOT(51)
	BFME_CONTROLBAR_INGAME_SLOT(52) BFME_CONTROLBAR_INGAME_SLOT(53)
	BFME_CONTROLBAR_INGAME_SLOT(54) BFME_CONTROLBAR_INGAME_SLOT(55)
	BFME_CONTROLBAR_INGAME_SLOT(56) BFME_CONTROLBAR_INGAME_SLOT(57)
	BFME_CONTROLBAR_INGAME_SLOT(58) BFME_CONTROLBAR_INGAME_SLOT(59)
	BFME_CONTROLBAR_INGAME_SLOT(60) BFME_CONTROLBAR_INGAME_SLOT(61)
	BFME_CONTROLBAR_INGAME_SLOT(62)
	virtual const BfmeControlBarDrawableList *getAllSelectedDrawables(void) const = 0;
};
#undef BFME_CONTROLBAR_INGAME_SLOT

// The body at 0x004A5950 that a non-null current selection is handed to,
// reached through ILT 0x0003672D; kept address-derived because its identity is unproven.
class BfmeRva004A5950ControlBarContextCommandView
{
public:
	void call(void);
};

extern void j_0003672d(void);


// 0x004A4240 takes command, window, object, percent out-pointer and force flag
// and returns one of eight availability values; reached through ILT 0x000414D4.
class BfmeRva004A4240CommandAvailabilityView
{
public:
	Int call(const CommandButton *command, GameWindow *window, Object *object,
		Real *percent, Bool forceDisabledEvaluation) const;
};

extern void j_000414d4(void);


extern Real g_bfmeDefaultBU;					// 1.0f at 0x01075334
void *GadgetButtonGetData(GameWindow *window);
void GadgetCheckLikeButtonSetVisualCheck(GameWindow *window, Bool checked);
void GadgetButtonDrawInverseClock(GameWindow *window, Int percent, Int color);

enum KindOfType { KINDOF_FIRST = 0 };

class AsciiString;
class CommandButton;

class Thing
{
public:
	Bool isKindOf( KindOfType kind ) const;
};

class Object : public Thing
{
public:
	const AsciiString &getCommandSetString( void ) const;
	Bool testStatus( Int status ) const;
	Object *bfmeResolveMeleeTarget( Int mode );
	void *unidentified_001BFE20( void ) const;
};


class BfmeUnit1013
{
public:
	void bfmeStop1013( char value );
};

class CommandSet
{
public:
	const CommandButton *getCommandButton( Int index ) const;
};


struct Rva004A9010Drawable
{
	unsigned char m_pad00[ 0xFC ];
	Object *m_object;
};

struct Rva004A9010SelNode
{
	Rva004A9010SelNode *m_next;
	Rva004A9010SelNode *m_prev;
	void *m_drawable;
};

struct Rva004A9010SelList
{
	Rva004A9010SelNode *m_node;
};

class Rva004A9010Relation
{
public:
	#define REL_SLOT(n) virtual void slot##n( void ) = 0;
	REL_SLOT(00) REL_SLOT(04) REL_SLOT(08) REL_SLOT(0C) REL_SLOT(10) REL_SLOT(14)
	REL_SLOT(18) REL_SLOT(1C) REL_SLOT(20) REL_SLOT(24) REL_SLOT(28) REL_SLOT(2C)
	REL_SLOT(30) REL_SLOT(34) REL_SLOT(38) REL_SLOT(3C) REL_SLOT(40) REL_SLOT(44)
	REL_SLOT(48) REL_SLOT(4C) REL_SLOT(50) REL_SLOT(54) REL_SLOT(58) REL_SLOT(5C)
	REL_SLOT(60) REL_SLOT(64) REL_SLOT(68) REL_SLOT(6C) REL_SLOT(70) REL_SLOT(74)
	REL_SLOT(78) REL_SLOT(7C) REL_SLOT(80) REL_SLOT(84) REL_SLOT(88) REL_SLOT(8C)
	REL_SLOT(90) REL_SLOT(94) REL_SLOT(98) REL_SLOT(9C) REL_SLOT(A0) REL_SLOT(A4)
	REL_SLOT(A8) REL_SLOT(AC) REL_SLOT(B0) REL_SLOT(B4) REL_SLOT(B8) REL_SLOT(BC)
	REL_SLOT(C0) REL_SLOT(C4) REL_SLOT(C8) REL_SLOT(CC) REL_SLOT(D0) REL_SLOT(D4)
	#undef REL_SLOT
	virtual Bool slotD8( void ) = 0;
};

class InGameUI
{
public:
	#define UI_SLOT(n) virtual void slot##n( void ) = 0;
	UI_SLOT(00) UI_SLOT(04) UI_SLOT(08) UI_SLOT(0C) UI_SLOT(10) UI_SLOT(14)
	UI_SLOT(18) UI_SLOT(1C) UI_SLOT(20) UI_SLOT(24) UI_SLOT(28) UI_SLOT(2C)
	UI_SLOT(30) UI_SLOT(34) UI_SLOT(38) UI_SLOT(3C) UI_SLOT(40) UI_SLOT(44)
	UI_SLOT(48) UI_SLOT(4C) UI_SLOT(50) UI_SLOT(54) UI_SLOT(58) UI_SLOT(5C)
	UI_SLOT(60) UI_SLOT(64) UI_SLOT(68) UI_SLOT(6C) UI_SLOT(70) UI_SLOT(74)
	UI_SLOT(78) UI_SLOT(7C) UI_SLOT(80) UI_SLOT(84) UI_SLOT(88) UI_SLOT(8C)
	UI_SLOT(90) UI_SLOT(94) UI_SLOT(98) UI_SLOT(9C) UI_SLOT(A0) UI_SLOT(A4)
	UI_SLOT(A8) UI_SLOT(AC) UI_SLOT(B0) UI_SLOT(B4) UI_SLOT(B8) UI_SLOT(BC)
	UI_SLOT(C0) UI_SLOT(C4) UI_SLOT(C8) UI_SLOT(CC) UI_SLOT(D0) UI_SLOT(D4)
	UI_SLOT(D8) UI_SLOT(DC) UI_SLOT(E0) UI_SLOT(E4) UI_SLOT(E8) UI_SLOT(EC)
	UI_SLOT(F0) UI_SLOT(F4) UI_SLOT(F8)
	#undef UI_SLOT
	virtual Rva004A9010SelList *slotFC( void ) = 0;
};

extern InGameUI *TheInGameUI;

extern void j_00011cd4( void );
extern void j_00006938( void );

struct Rva004A9010ButtonCalls
{
	void applyState( Int value );
	void applyObject( Object *object, Int mode );
};

typedef void (Rva004A9010ButtonCalls::*Rva004A9010StateCall)( Int );
typedef void (Rva004A9010ButtonCalls::*Rva004A9010ObjectCall)( Object *, Int );

// ?callRva00011CD4@@YAXPBVCommandButton@@H@Z absent-from-retail
static void callRva00011CD4( const CommandButton *button, Int value )
{
	union
	{
		void (*asFunction)();
		Rva004A9010StateCall asMember;
	} functionCast;
	functionCast.asFunction = j_00011cd4;
	(((Rva004A9010ButtonCalls *)button)->*functionCast.asMember)( value );
}

// ?callRva00006938@@YAXPBVCommandButton@@PAVObject@@H@Z absent-from-retail
static void callRva00006938( const CommandButton *button, Object *object, Int mode )
{
	union
	{
		void (*asFunction)();
		Rva004A9010ObjectCall asMember;
	} functionCast;
	functionCast.asFunction = j_00006938;
	(((Rva004A9010ButtonCalls *)button)->*functionCast.asMember)( object, mode );
}


// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class ControlBar
{
public:
	void rva004A9010(void *draw, Bool populate);
	const CommandSet *findCommandSet(const AsciiString &name);
	void setControlCommand(GameWindow *window, const CommandButton *button);

protected:
	void updateContextMultiSelect(void);

private:
	char m_slice_pad[0x5C];					// retail this+0x00 .. +0x5B, untouched
	Drawable *m_currentSelectedDrawable;			// this+0x5C
	char m_slice_padC[0x100 - 0x60];			// this+0x60 .. +0xFF, untouched
	GameWindow *m_commandWindows[MAX_COMMANDS_PER_SET];	// this+0x100
	char m_slice_padD[0x1F0 - (0x100 + MAX_COMMANDS_PER_SET * 4)];
	const CommandButton *m_commonCommands[MAX_COMMANDS_PER_SET];	// this+0x1F0
	char m_slice_padE[0x26C - (0x1F0 + MAX_COMMANDS_PER_SET * 4)];
	Int m_buildUpClockColor;				// this+0x26C
};

// ?updateContextMultiSelect@ControlBar@@IAEXXZ
void ControlBar::updateContextMultiSelect(void)
{
	Drawable *draw;
	Object *obj;
	const CommandButton *command;
	GameWindow *win;
	Int objectsThatCanDoCommand[MAX_COMMANDS_PER_SET];
	Int i;

	if (m_currentSelectedDrawable != 0)
	{
		typedef void (BfmeRva004A5950ControlBarContextCommandView::*ContextFunction)(void);
		union { void (*raw)(void); ContextFunction member; } contextCall;
		contextCall.raw = j_0003672d;
		(reinterpret_cast<BfmeRva004A5950ControlBarContextCommandView *>(this)->*contextCall.member)();
		return;
	}

	memset(objectsThatCanDoCommand, 0, sizeof(objectsThatCanDoCommand));

	const BfmeControlBarDrawableList *selectedDrawables =
		((BfmeControlBarInGameUISelectionView *)TheInGameUI)->getAllSelectedDrawables();

	for (BfmeControlBarDrawableListNode *it = selectedDrawables->head->next;
		it != selectedDrawables->head; it = it->next)
	{
		draw = it->value;

		// Object::isKindOf(KINDOF_IGNORED_IN_GUI): bit 15 of the final template's mask at +0xCC.
		obj = drawableObject(draw);
		const ThingTemplate *thingTemplate = *(const ThingTemplate *const *)((const char *)drawableObject(draw) + 4);
		if (thingTemplate && thingTemplate->m_nextOverride)
			thingTemplate = (const ThingTemplate *)thingTemplate->m_nextOverride->getFinalOverride();
		if (*(const UnsignedInt *)((const char *)thingTemplate + 0xCC) & 0x8000)
			continue;

		if (obj == 0)
			continue;

		for (i = 0; i < MAX_COMMANDS_PER_SET; i++)
		{
			win = m_commandWindows[i];
			if (!win)
				continue;

			if (win->winIsHidden() == true)
				continue;

			command = (const CommandButton *)GadgetButtonGetData(win);
			if (command == 0)
				continue;

			Real percent;
			typedef Int (BfmeRva004A4240CommandAvailabilityView::*AvailabilityFunction)(
				const CommandButton *, GameWindow *, Object *, Real *, Bool) const;
			union { void (*raw)(void); AvailabilityFunction member; } availabilityCall;
			availabilityCall.raw = j_000414d4;
			Int availability =
				(reinterpret_cast<const BfmeRva004A4240CommandAvailabilityView *>(this)->*availabilityCall.member)(
					command, win, obj, &percent, false);

			win->winClearStatus(0x00400000);
			win->winClearStatus(0x01000000);
			win->winClearStatus(0x40000000);
			win->winClearStatus(0x80000000);

			Int color = 0;
			switch (availability)
			{
				case 3:
					win->winHide(true);
					break;

				case 0:
				case 7:
					win->winEnable(false);
					win->_bfme_winSetStatus(0x80000000);
					if (availability == 7)
						win->_bfme_winSetStatus(0x01000000);
					break;

				case 4:
					color = m_buildUpClockColor;
					win->winEnable(false);
					win->_bfme_winSetStatus(0x00400000);
					break;

				case 5:
				case 6:
					win->winEnable(false);
					win->_bfme_winSetStatus(0x01000000);
					break;

				default:
					win->winEnable(true);
					break;
			}

			if (percent < g_bfmeDefaultBU)
				GadgetButtonDrawInverseClock(win, (Int)(percent * 100.0f), color);

			if ((command->getOptions() & 0x400) != 0)
				GadgetCheckLikeButtonSetVisualCheck(win, availability == 2);

			if (availability == 1 || availability == 2)
				objectsThatCanDoCommand[i]++;
		}
	}

	for (i = 0; i < MAX_COMMANDS_PER_SET; i++)
	{
		win = m_commandWindows[i];
		if (!win)
			continue;

		if (win->winIsHidden() == true)
			continue;

		if (m_commonCommands[i] == 0)
			continue;

		if (objectsThatCanDoCommand[i] > 0)
		{
			win->winEnable(true);
			win->winClearStatus(0x80000000);
			win->winClearStatus(0x01000000);
		}
		else
			win->winEnable(false);
	}
}

// ?rva004A9010@ControlBar@@QAEXPAX_N@Z
// Open BFME 2: Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBarMultiSelect.cpp.
void ControlBar::rva004A9010(void *draw, bool populate)
{
    Int i;
    const CommandButton *button;
    if (draw == 0) return;
    Object *obj = ((Rva004A9010Drawable *)draw)->m_object;
    if (!obj) return;
    if (obj->isKindOf((KindOfType)0x2F))
        return;
    const CommandSet *commandSet = findCommandSet(obj->getCommandSetString());
    if (commandSet == 0) {
        for (i = 0; i < 20; i++) {
            m_commonCommands[i] = 0;
            if (m_commandWindows[i]) m_commandWindows[i]->winHide(true);
        }
        return;
    }
    if (populate == true) {
        for (i = 0; i < 20; i++) {
            button = commandSet->getCommandButton(i);
            if (button && (button->m_options & 0x100) != 0) {
                m_commonCommands[i] = button;
                if (m_commandWindows[i]) {
                    m_commandWindows[i]->winHide(false);
                    m_commandWindows[i]->winEnable(true);
                    if (button->m_commandType == 0x23) {
                        int modeVote = 0;
                        Rva004A9010SelList *list =
                            TheInGameUI->slotFC();
                        for (Rva004A9010SelNode *entry = list->m_node->m_next;
                             entry != list->m_node; entry = entry->m_next) {
                            void *selectedDraw = entry->m_drawable;
                            if (!selectedDraw || !((Rva004A9010Drawable *)selectedDraw)->m_object) continue;
                            Object *selectedObject = ((Rva004A9010Drawable *)selectedDraw)->m_object;
                            if (selectedObject->isKindOf((KindOfType)0x2F))
                                continue;
                            if (selectedObject->testStatus(0x13)) continue;
                            Object *resolved = selectedObject->bfmeResolveMeleeTarget(0);
                            if (!resolved) continue;
                            Rva004A9010Relation *mode = (Rva004A9010Relation *)resolved->unidentified_001BFE20();
                            if (!mode) continue;
                            if (mode->slotD8()) --modeVote;
                            else ++modeVote;
                        }
                        callRva00011CD4(button, modeVote >= 0);
                    } else {
                        callRva00006938(button, obj, 0);
                    }
                    setControlCommand(m_commandWindows[i], button);
                }
            }
        }
    } else {
        for (i = 0; i < 20; i++) {
            button = commandSet->getCommandButton(i);
            bool attackMove = (button && button->m_commandType == 9) ||
                (m_commonCommands[i] && m_commonCommands[i]->m_commandType == 9);
            if (attackMove && !m_commonCommands[i]) {
                m_commonCommands[i] = button;
                if (m_commandWindows[i]) {
                    m_commandWindows[i]->winHide(false);
                    m_commandWindows[i]->winEnable(true);
                    setControlCommand(m_commandWindows[i], button);
                }
            } else if (button != m_commonCommands[i] && !attackMove) {
                m_commonCommands[i] = 0;
                if (m_commandWindows[i]) m_commandWindows[i]->winHide(true);
            }
        }
    }
}
