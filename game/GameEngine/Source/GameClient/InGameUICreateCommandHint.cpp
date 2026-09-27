// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// RVA 0x00445080: InGameUI vtable VA 0x010F5B38 slot 31 -> ILT 0x0003B0F7.
// Port of GeneralsMD InGameUI::createCommandHint reconciled with BFME retail.
// The ctor at RVA 0x0044B800 installs this table. Slots 30/32 are the
// createMouseoverHint/createGarrisonHint neighbours in the upstream interface.
// Layout witnesses: InGameUI +230 pending command; +820 scrolling; +824 mouse
// mode; +828 cached cursor. Its existing setMouseCursor body proves +821
// selecting. The drawable lookup here proves +82c moused-over drawable ID.
// BFME adds the APT window gate and messages 0x7d6..0x7d8, and chooses between
// the radius cursor and named cursor rather than doing both as Zero Hour does.
// The native switch case order is retained: it controls the shared cursor tails.
// All offsets below are retail offsets, not the Zero Hour class sizes.
#include "ascii_string.h"
enum RecorderModeType { RECORDER_PLAYBACK=1 };
class RecorderClass { public: RecorderModeType getMode(); };
extern RecorderClass *TheRecorder;
enum KindOfType { KINDOF_STRUCTURE=7 };
enum ObjectShroudStatus { OBJECTSHROUD_SHROUDED=4 };
class Thing { public: bool isKindOf(KindOfType) const; };
class Object : public Thing { public: ObjectShroudStatus getShroudedStatus(int) const; bool isLocallyControlled() const; };
class Drawable { public: char pad000[0xfc]; Object *m_object; Object *getObject() const { return m_object; } };
bool CanSelectDrawable(const Drawable *,bool);
class Player { public: char pad000[0x24]; int m_playerIndex; bool hasRadar() const; };
class PlayerList { public: char pad000[0xc]; Player *m_local; };
extern PlayerList *ThePlayerList;
#define SLOT(n) virtual void slot##n();
class GameClient { public:
SLOT(0) SLOT(1) SLOT(2) SLOT(3) SLOT(4) SLOT(5) SLOT(6) SLOT(7) SLOT(8) SLOT(9) SLOT(10) 
virtual const Drawable *findDrawableByID(unsigned int);
};
extern GameClient *TheGameClient;
class GameWindow { public:
SLOT(0) SLOT(1) SLOT(2) SLOT(3) SLOT(4) SLOT(5)
virtual bool slot18();
unsigned int winGetStatus();
GameWindow *winGetParent();
};
class GameWindowManager { public:
SLOT(0) SLOT(1) SLOT(2) SLOT(3) SLOT(4) SLOT(5) SLOT(6) SLOT(7) SLOT(8) SLOT(9) SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15) SLOT(16) SLOT(17) SLOT(18) SLOT(19) SLOT(20) SLOT(21) SLOT(22) SLOT(23) SLOT(24) SLOT(25) SLOT(26) SLOT(27) SLOT(28) SLOT(29) SLOT(30) SLOT(31) SLOT(32) SLOT(33) SLOT(34) SLOT(35) SLOT(36) SLOT(37) SLOT(38) SLOT(39) SLOT(40) SLOT(41) SLOT(42) SLOT(43) SLOT(44) SLOT(45) SLOT(46) SLOT(47) SLOT(48) SLOT(49) SLOT(50) SLOT(51) SLOT(52) SLOT(53) SLOT(54) SLOT(55) SLOT(56) SLOT(57) SLOT(58) SLOT(59) SLOT(60) SLOT(61) SLOT(62) SLOT(63) SLOT(64) SLOT(65) SLOT(66) SLOT(67) SLOT(68) SLOT(69) SLOT(70) SLOT(71) 
virtual GameWindow *getWindowUnderCursor(int,int,bool);
};
extern GameWindowManager *TheWindowManager;
class BfmeC977 { public: char bfmeGo977C(); };
class WindowManager;
extern WindowManager *g_theWindowManager;
// Radar booleans +0xc/+0xd are read here; their names remain unproven.
class Radar { public:
char pad000[0xc]; bool m_field00c; bool m_field00d;
bool isRadarWindow(GameWindow *);
};
extern Radar *TheRadar;
struct ICoord2D { int x,y; };
class Mouse { public:
enum MouseCursor { ARROW=2, SCROLL=3, CROSS=4 };
SLOT(0) SLOT(1) SLOT(2) SLOT(3) SLOT(4) SLOT(5) SLOT(6) SLOT(7) SLOT(8) SLOT(9) SLOT(10) SLOT(11) SLOT(12) SLOT(13) 
virtual void setCursor(MouseCursor);
char pad004[0x4d10-4]; ICoord2D m_currMouse;
int getCursorIndex(const AsciiString &);
};
extern Mouse *TheMouse;
class SpecialPowerTemplate;
class CommandButton { public:
char pad000[0x10]; int m_command; char pad014[4]; unsigned int m_options;
char pad01c[0x34-0x1c]; const SpecialPowerTemplate *m_specialPower;
int m_radiusCursor; AsciiString m_cursorName; AsciiString m_invalidCursorName;
char pad044[0x6c-0x44]; int m_weaponSlot;
bool isContextCommand() const;
};
union GameMessageArgumentType { int integer; };
class GameMessage { public: char pad000[0x10]; int m_type;
const GameMessageArgumentType *getArgument(int) const;
};
// The selected-drawable list is a sentinel plus next/prev/value node layout.
struct CommandHint00445080Node { CommandHint00445080Node *next, *prev; Drawable *value; };
struct CommandHint00445080List { CommandHint00445080Node *head; const Drawable *front() const { return head->next->value; } };
class InGameUI { public:
SLOT(0)
SLOT(1)
SLOT(2)
SLOT(3)
SLOT(4)
SLOT(5)
SLOT(6)
SLOT(7)
SLOT(8)
SLOT(9)
SLOT(10)
SLOT(11)
SLOT(12)
SLOT(13)
SLOT(14)
SLOT(15)
SLOT(16)
SLOT(17)
SLOT(18)
SLOT(19)
SLOT(20)
SLOT(21)
SLOT(22)
SLOT(23)
SLOT(24)
SLOT(25)
SLOT(26)
SLOT(27)
SLOT(28)
SLOT(29)
SLOT(30)
virtual void createCommandHint(const GameMessage *);
SLOT(32)
SLOT(33)
SLOT(34)
SLOT(35)
SLOT(36)
SLOT(37)
SLOT(38)
SLOT(39)
SLOT(40)
SLOT(41)
SLOT(42)
SLOT(43)
SLOT(44)
SLOT(45)
SLOT(46)
SLOT(47)
SLOT(48)
SLOT(49)
SLOT(50)
SLOT(51)
SLOT(52)
SLOT(53)
SLOT(54)
SLOT(55)
SLOT(56)
SLOT(57)
SLOT(58)
SLOT(59)
virtual int getSelectCount();
SLOT(61)
SLOT(62)
virtual const CommandHint00445080List *getAllSelectedDrawables() const;
SLOT(64)
SLOT(65)
SLOT(66)
SLOT(67)
SLOT(68)
SLOT(69)
virtual void setRadiusCursor(int,const SpecialPowerTemplate *,int,bool);
virtual void setRadiusCursorNone();

char pad004[0x230-4]; const CommandButton *m_pendingGUICommand;
char pad234[0x820-0x234]; bool m_isScrolling; bool m_isSelecting;
char pad822[2]; int m_mouseMode; Mouse::MouseCursor m_mouseModeCursor;
unsigned int m_mousedOverDrawableID;
void setMouseCursor(Mouse::MouseCursor cursor);
};
// Shared existing method, exposed here for the constant-cursor inlines.
void InGameUI::setMouseCursor(Mouse::MouseCursor cursor)
{
    if (m_isSelecting || m_isScrolling) return;
    if (TheMouse == 0) return;
    TheMouse->setCursor(cursor);
    if (m_mouseMode == 2 && cursor != Mouse::ARROW && cursor != Mouse::SCROLL)
        m_mouseModeCursor = cursor;
}
#define CURSOR(n) setMouseCursor((Mouse::MouseCursor)(n))
void InGameUI::createCommandHint(const GameMessage *msg)
{
    if (TheRecorder->getMode() == RECORDER_PLAYBACK) return;
    const Drawable *draw = TheGameClient->findDrawableByID(m_mousedOverDrawableID);
    int t = msg->m_type;
    if (draw && (t == 0x99 || t == 0xb2)) {
        const Object *obj = draw->getObject();
        int localPlayerIndex = ThePlayerList ? ThePlayerList->m_local->m_playerIndex : 0;
        ObjectShroudStatus ss = !obj ? (ObjectShroudStatus)0 : obj->getShroudedStatus(localPlayerIndex);
        if (ss == OBJECTSHROUD_SHROUDED) t = 0xa5;
    }
    GameWindow *window = 0;
    char underWindow = ((BfmeC977 *)g_theWindowManager)->bfmeGo977C();
    if (!underWindow) {
        const ICoord2D *io = &TheMouse->m_currMouse;
        if (io && TheWindowManager)
            window = TheWindowManager->getWindowUnderCursor(io->x,io->y,false);
        while (window) {
            if (window->slot18()) { underWindow = false; break; }
            if (!(window->winGetStatus() & 0x10000)) { underWindow = true; break; }
            window = window->winGetParent();
        }
    }
    const Object *obj = draw ? draw->getObject() : 0;
    bool drawSelectable = CanSelectDrawable(draw,false);
    if (!obj) drawSelectable = false;
    const Drawable *srcDraw = 0;
    const Object *srcObj = 0;
    if (getSelectCount() == 1) {
        srcDraw = getAllSelectedDrawables()->front();
        srcObj = srcDraw ? srcDraw->getObject() : 0;
    }
    switch (m_mouseMode) {
    case 0:
        if (underWindow || (srcObj && !srcObj->isLocallyControlled())) { CURSOR(2); return; }
        switch (t) {
        case 0xa5:
            if (!drawSelectable && srcObj && srcObj->isLocallyControlled() && srcObj->isKindOf(KINDOF_STRUCTURE))
                CURSOR(12);
            else if (drawSelectable && obj->isLocallyControlled())
                CURSOR(13);
            else {
                Radar *radar = TheRadar;
                if (radar->isRadarWindow(window) && !radar->m_field00d &&
                    (radar->m_field00c || !ThePlayerList->m_local->hasRadar()))
                    CURSOR(2);
                else CURSOR(5);
            }
            break;
        case 0xa6:
            if (drawSelectable && obj->isLocallyControlled()) CURSOR(13);
            else CURSOR(6);
            break;
        case 0xa7: CURSOR(34); break;
        case 0x99: CURSOR(7); break;
        case 0xb2: CURSOR(35); break;
        case 0x9b: CURSOR(8); break;
        case 0x9c: CURSOR(9); break;
        case 0x9d: CURSOR(17); break;
        case 0xa3: CURSOR(29); break;
        case 0xa4: CURSOR(47); break;
        case 0x9e: CURSOR(18); break;
        case 0x9f: CURSOR(19); break;
        case 0xa0: CURSOR(20); break;
        case 0xa1: CURSOR(14); break;
        case 0xa2: CURSOR(15); break;
        case 0xa8:
        case 0xaa: CURSOR(15); break;
        case 0xad: CURSOR(28); break;
        case 0xab: CURSOR(21); break;
        case 0x9a: CURSOR(12); break;
        case 0xae:
            if (!drawSelectable) CURSOR(16);
            else CURSOR(13);
            break;
        case 0xaf: CURSOR(39); break;
        case 0xb0: CURSOR(5); break;
        case 0xb1: CURSOR(12); break;
        case 0x7d6: CURSOR(msg->getArgument(1)->integer); break;
        case 0x7d7: CURSOR(42); break;
        case 0x7d8: CURSOR(49); break;
        }
        break;
    case 1:
        if (underWindow) { CURSOR(2); return; }
        switch (t) {
        case 0xa5: case 0xa6: case 0x431: CURSOR(10); break;
        case 0x99: case 0xb2: CURSOR(11); break;
        }
        break;
    case 2:
        if (underWindow) { CURSOR(2); return; }
        if (m_pendingGUICommand) {
            if (m_pendingGUICommand->isContextCommand() || m_pendingGUICommand->m_command == 0x17 ||
                m_pendingGUICommand->m_command == 0x24 || m_pendingGUICommand->m_command == 0x1f ||
                m_pendingGUICommand->m_command == 0x1e) {
                if (m_pendingGUICommand->m_radiusCursor == 0) {
                    setRadiusCursorNone();
                    int index;
                    switch(t) {
                    case 0x96: index = TheMouse->getCursorIndex(m_pendingGUICommand->m_cursorName); break;
                    default: index = TheMouse->getCursorIndex(m_pendingGUICommand->m_invalidCursorName); break;
                    }
                    if (index != -1) CURSOR(index); else CURSOR(4);
                } else {
                    CURSOR(0);
                    setRadiusCursor(m_pendingGUICommand->m_radiusCursor,m_pendingGUICommand->m_specialPower,
                                    m_pendingGUICommand->m_weaponSlot,t == 0x96);
                }
            } else if (m_pendingGUICommand->m_options & 0x227) {
                if (m_pendingGUICommand->m_radiusCursor == 0) {
                    setRadiusCursorNone();
                    int index = TheMouse->getCursorIndex(m_pendingGUICommand->m_cursorName);
                    if (index != -1) CURSOR(index); else CURSOR(4);
                } else {
                    CURSOR(0);
                    setRadiusCursor(m_pendingGUICommand->m_radiusCursor,m_pendingGUICommand->m_specialPower,
                                    m_pendingGUICommand->m_weaponSlot,true);
                }
            } else setRadiusCursorNone();
        }
        break;
    }
}
