// cl: /O2 /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/sweep /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// ?translateGameMessage@HotKeyTranslator@@UAE?AW4GameMessageDisposition@@PBVGameMessage@@@Z
// Clean C++ conversion of the HotKeyTranslator retail body.

typedef int Int;
typedef bool Bool;
typedef unsigned char UnsignedByte;
typedef unsigned short WideChar;

union GameMessageArgumentType
{
    Int integer;
    Int pixel[2];
};

class GameMessage
{
public:
    enum Type
    {
        MSG_RAW_KEY_UP = 22
    };

    Type getType() const
    {
        return (Type)m_type;
    }

    const GameMessageArgumentType *getArgument(Int index) const;

private:
    char m_pad[0x10];
    Int m_type;
};

enum GameMessageDisposition
{
    KEEP_MESSAGE,
    DESTROY_MESSAGE
};

class Keyboard
{
public:
    WideChar getPrintableKey(UnsignedByte key, Int state);
};

extern Keyboard *TheKeyboard;

#include "ascii_string.h"
#include <map>

class UnicodeString : private StringBase<WideChar>
{
public:
    UnicodeString() : StringBase<WideChar>() {}
    ~UnicodeString() {}
    void set(const WideChar *text, Int length);
};

class BfmeTransitionMD
{
public:
    Bool dispatch(AsciiString *key, Bool shiftOnly);
};

class HotKeyManager;
extern HotKeyManager *TheHotKeyManager;

class HotKeyTranslator
{
public:
    virtual GameMessageDisposition translateGameMessage(const GameMessage *msg);
};

static __forceinline void setHotKey(UnicodeString &text, WideChar key)
{
    ((StringBase<WideChar> *)&text)->set(&key, sizeof(key) / sizeof(key));
}

GameMessageDisposition HotKeyTranslator::translateGameMessage(const GameMessage *msg)
{
    GameMessageDisposition disp = KEEP_MESSAGE;
    GameMessage::Type t = msg->getType();

    if (t == GameMessage::MSG_RAW_KEY_UP)
    {
        Int keyState = msg->getArgument(1)->integer;
        Int newModState = 0;
        Bool shiftOnly = false;

        if (keyState & 0x430)
        {
            newModState = 0x10;
            shiftOnly = true;
        }

        if (keyState & 0x0C)
        {
            newModState |= 0x04;
            shiftOnly = false;
        }

        if (keyState & 0xC0)
        {
            newModState |= 0x40;
            shiftOnly = false;
        }

        if (newModState != 0)
        {
            if (!shiftOnly)
                return disp;
        }

        WideChar key = TheKeyboard->getPrintableKey(
            (UnsignedByte)msg->getArgument(0)->integer, 0);
        UnicodeString uKey;
        setHotKey(uKey, key);
        AsciiString aKey;
        aKey.translate(uKey);
        if (reinterpret_cast<BfmeTransitionMD *>(TheHotKeyManager) && reinterpret_cast<BfmeTransitionMD *>(TheHotKeyManager)->dispatch(&aKey, shiftOnly))
            disp = DESTROY_MESSAGE;
    }

    return disp;
}

typedef unsigned int UnsignedInt;
typedef int ObjectID;
typedef UnsignedInt WindowMsgData;

enum { WIN_STATUS_ENABLED = 8, WIN_STATUS_HIDDEN = 16 };
enum WindowMsgHandledType { MSG_IGNORED, MSG_HANDLED };

class GameWindow;
class WinInstanceData
{
public:
    char m_pad[0x14];
    GameWindow *m_owner;
};

class GameWindow
{
public:
    UnsignedInt winGetStatus();
    WinInstanceData *winGetInstanceData();
    int winGetWindowId();
};

class GameWindowManager
{
public:
#define WINDOW_SLOT(n) virtual void slot##n();
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
    WINDOW_SLOT(52)
    virtual WindowMsgHandledType winSendSystemMsg(GameWindow *, UnsignedInt, WindowMsgData, WindowMsgData);
#undef WINDOW_SLOT
};
extern GameWindowManager *TheWindowManager;

class InGameUI;
class Rva005B3AD0InGameUIView
{
public:
#define UI_SLOT(n) virtual void slot##n();
    UI_SLOT(00) UI_SLOT(01) UI_SLOT(02) UI_SLOT(03) UI_SLOT(04) UI_SLOT(05)
    UI_SLOT(06) UI_SLOT(07) UI_SLOT(08) UI_SLOT(09) UI_SLOT(10) UI_SLOT(11)
    UI_SLOT(12) UI_SLOT(13) UI_SLOT(14) UI_SLOT(15) UI_SLOT(16) UI_SLOT(17)
    UI_SLOT(18) UI_SLOT(19) UI_SLOT(20) UI_SLOT(21) UI_SLOT(22) UI_SLOT(23)
    UI_SLOT(24) UI_SLOT(25) UI_SLOT(26) UI_SLOT(27) UI_SLOT(28) UI_SLOT(29)
    UI_SLOT(30) UI_SLOT(31) UI_SLOT(32) UI_SLOT(33) UI_SLOT(34) UI_SLOT(35)
    UI_SLOT(36) UI_SLOT(37) UI_SLOT(38) UI_SLOT(39) UI_SLOT(40) UI_SLOT(41)
    UI_SLOT(42) UI_SLOT(43) UI_SLOT(44) UI_SLOT(45) UI_SLOT(46) UI_SLOT(47)
    UI_SLOT(48) UI_SLOT(49) UI_SLOT(50) UI_SLOT(51) UI_SLOT(52) UI_SLOT(53)
    UI_SLOT(54) UI_SLOT(55) UI_SLOT(56) UI_SLOT(57) UI_SLOT(58) UI_SLOT(59)
    UI_SLOT(60) UI_SLOT(61) UI_SLOT(62) UI_SLOT(63) UI_SLOT(64) UI_SLOT(65)
    UI_SLOT(66) UI_SLOT(67) UI_SLOT(68) UI_SLOT(69) UI_SLOT(70) UI_SLOT(71)
    UI_SLOT(72) UI_SLOT(73) UI_SLOT(74) UI_SLOT(75) UI_SLOT(76) UI_SLOT(77)
    UI_SLOT(78) UI_SLOT(79) UI_SLOT(80) UI_SLOT(81) UI_SLOT(82) UI_SLOT(83)
    UI_SLOT(84)
    virtual Bool slot85();
#undef UI_SLOT
};
extern InGameUI *TheInGameUI;

struct Rva005A00B0AudioClient
{
#define AUDIO_SLOT(n) virtual void slot##n();
    AUDIO_SLOT(00) AUDIO_SLOT(01) AUDIO_SLOT(02) AUDIO_SLOT(03)
    AUDIO_SLOT(04) AUDIO_SLOT(05) AUDIO_SLOT(06) AUDIO_SLOT(07)
    AUDIO_SLOT(08) AUDIO_SLOT(09) AUDIO_SLOT(10) AUDIO_SLOT(11)
    AUDIO_SLOT(12) AUDIO_SLOT(13) AUDIO_SLOT(14) AUDIO_SLOT(15)
    AUDIO_SLOT(16)
    virtual void addAudioEvent(void *event);
    AUDIO_SLOT(18) AUDIO_SLOT(19) AUDIO_SLOT(20) AUDIO_SLOT(21)
    AUDIO_SLOT(22) AUDIO_SLOT(23) AUDIO_SLOT(24) AUDIO_SLOT(25)
    AUDIO_SLOT(26) AUDIO_SLOT(27) AUDIO_SLOT(28) AUDIO_SLOT(29)
    AUDIO_SLOT(30) AUDIO_SLOT(31) AUDIO_SLOT(32) AUDIO_SLOT(33)
    AUDIO_SLOT(34) AUDIO_SLOT(35) AUDIO_SLOT(36) AUDIO_SLOT(37)
    AUDIO_SLOT(38) AUDIO_SLOT(39) AUDIO_SLOT(40) AUDIO_SLOT(41)
    AUDIO_SLOT(42) AUDIO_SLOT(43) AUDIO_SLOT(44) AUDIO_SLOT(45)
    AUDIO_SLOT(46) AUDIO_SLOT(47) AUDIO_SLOT(48) AUDIO_SLOT(49)
    AUDIO_SLOT(50) AUDIO_SLOT(51) AUDIO_SLOT(52) AUDIO_SLOT(53)
    AUDIO_SLOT(54) AUDIO_SLOT(55) AUDIO_SLOT(56) AUDIO_SLOT(57)
    AUDIO_SLOT(58) AUDIO_SLOT(59) AUDIO_SLOT(60) AUDIO_SLOT(61)
    AUDIO_SLOT(62) AUDIO_SLOT(63) AUDIO_SLOT(64) AUDIO_SLOT(65)
    AUDIO_SLOT(66) AUDIO_SLOT(67) AUDIO_SLOT(68) AUDIO_SLOT(69)
    AUDIO_SLOT(70) AUDIO_SLOT(71) AUDIO_SLOT(72)
    virtual void *getMiscAudio();
#undef AUDIO_SLOT
};
// The linked build has one mangled name for the global at 0x012ED668: the
// canonical `AudioManager *TheAudio`, defined in GameAudio.cpp.
// Rva005A00B0AudioClient is this TU's view of it.
class AudioManager;
extern AudioManager *TheAudio;

class AudioEventRTS
{
public:
    AudioEventRTS(const AsciiString &, ObjectID);
    ~AudioEventRTS();
private:
    void *rva005b3ad0_vptr;
    char rva005b3ad0_rest[0x6c];
};

struct Rva00367E30Logic
{
    Bool isGamePaused();
};
class GameLogic;
extern GameLogic *TheGameLogic;

class BfmeGameLogicPause
{
public:
    Bool isGamePaused();
};

class HotKey
{
public:
    GameWindow *m_win;
    AsciiString m_key;
};

namespace _STL
{
template <>
struct less<AsciiString>
{
    bool operator()(const AsciiString &lhs, const AsciiString &rhs) const
    {
        return lhs.compare(rhs) < 0;
    }
};
}

typedef std::map<AsciiString, HotKey> Rva005B3AD0HotKeyMap;

Bool BfmeTransitionMD::dispatch(AsciiString *key, Bool shiftOnly)
{
    if (((BfmeGameLogicPause *)TheGameLogic)->isGamePaused())
        return false;

    unsigned char *uiFlags = (unsigned char *)TheInGameUI;
    if (!uiFlags[0x0d] || !uiFlags[0x0e]
        || ((Rva005B3AD0InGameUIView *)TheInGameUI)->slot85())
        return false;

    AsciiString keyCopy = *key;
    keyCopy.toLower();
    Bool disabled = false;
    GameWindow *window = 0;
    Rva005B3AD0HotKeyMap::iterator it = ((Rva005B3AD0HotKeyMap *)((char *)this + 8))->find(keyCopy);
    if (it != ((Rva005B3AD0HotKeyMap *)((char *)this + 8))->end())
        window = it->second.m_win;
    if (!window)
    {
        it = ((Rva005B3AD0HotKeyMap *)((char *)this + 0x14))->find(keyCopy);
        if (it != ((Rva005B3AD0HotKeyMap *)((char *)this + 0x14))->end())
            window = it->second.m_win;
    }
    if (window && !(window->winGetStatus() & WIN_STATUS_HIDDEN))
    {
        if (window->winGetStatus() & WIN_STATUS_ENABLED)
            goto sendWindowMessage;
        disabled = true;
    }

    keyCopy.toUpper();
    window = 0;
    it = ((Rva005B3AD0HotKeyMap *)((char *)this + 8))->find(keyCopy);
    if (it != ((Rva005B3AD0HotKeyMap *)((char *)this + 8))->end())
        window = it->second.m_win;
    if (!window)
    {
        it = ((Rva005B3AD0HotKeyMap *)((char *)this + 0x14))->find(keyCopy);
        if (it != ((Rva005B3AD0HotKeyMap *)((char *)this + 0x14))->end())
            window = it->second.m_win;
    }
    if (window && !(window->winGetStatus() & WIN_STATUS_HIDDEN))
    {
        if (window->winGetStatus() & WIN_STATUS_ENABLED)
            goto sendWindowMessage;
        goto playDisabledAudio;
    }

    if (disabled)
        goto playDisabledAudio;
    return false;

playDisabledAudio:
    {
        AudioEventRTS sound(AsciiString("GUIClickDisabled"), 0);
        if (((Rva005A00B0AudioClient *)TheAudio))
        {
            if (((Rva005A00B0AudioClient *)TheAudio)->getMiscAudio())
                ((Rva005A00B0AudioClient *)TheAudio)->addAudioEvent(
                    (char *)((Rva005A00B0AudioClient *)TheAudio)->getMiscAudio() + 0xd20);
        }
    }
    return false;

sendWindowMessage:
    WinInstanceData *instance = window->winGetInstanceData();
    if (!instance)
        return false;
    Bool shift = shiftOnly;
    WindowMsgData message = 0x4008 + (shift ? 3 : 0);
    GameWindow *owner = instance->m_owner;
    volatile Bool playEnabledFeedback = true;
    WindowMsgHandledType handled = TheWindowManager->winSendSystemMsg(
        owner,
        message,
        (WindowMsgData)window,
        window->winGetWindowId());
    if (!handled && shift)
        playEnabledFeedback = false;
    if (((Rva005A00B0AudioClient *)TheAudio))
    {
        if (((Rva005A00B0AudioClient *)TheAudio)->getMiscAudio() && playEnabledFeedback)
            ((Rva005A00B0AudioClient *)TheAudio)->addAudioEvent(
                (char *)((Rva005A00B0AudioClient *)TheAudio)->getMiscAudio() + 0xcb0);
    }
    return true;
}
