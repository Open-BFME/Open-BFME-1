// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Retail 0x004DE270. This clean callback keeps PopupReplay's name-key, window,
// and replay-list setup while using the inline UnicodeString shape from retail.

template <typename T> class StringBase
{
    friend class UnicodeString;

private:
    StringBase() : m_data(0) {}
    StringBase(const StringBase<T> &other);
    ~StringBase();

    void *m_data;
};

class UnicodeString : private StringBase<unsigned short>
{
public:
    static UnicodeString TheEmptyString;

    UnicodeString() : StringBase<unsigned short>() {}
    UnicodeString(const UnicodeString &other)
        : StringBase<unsigned short>(other)
    {
    }
    ~UnicodeString() {}
};

typedef bool Bool;

#define DEBUG_ASSERTCRASH(condition, message) ((void)0)

enum NameKeyType
{
    NAMEKEY_INVALID = 0,
    FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

class NameKeyGenerator
{
public:
    NameKeyType nameToKey(const char *name);
};

class GameWindow;
class WindowLayout;

class GameWindowManager
{
public:
    virtual void slot00() = 0; virtual void slot01() = 0;
    virtual void slot02() = 0; virtual void slot03() = 0;
    virtual void slot04() = 0; virtual void slot05() = 0;
    virtual void slot06() = 0; virtual void slot07() = 0;
    virtual void slot08() = 0; virtual void slot09() = 0;
    virtual void slot10() = 0; virtual void slot11() = 0;
    virtual void slot12() = 0; virtual void slot13() = 0;
    virtual void slot14() = 0; virtual void slot15() = 0;
    virtual void slot16() = 0; virtual void slot17() = 0;
    virtual void slot18() = 0; virtual void slot19() = 0;
    virtual void slot20() = 0; virtual void slot21() = 0;
    virtual void slot22() = 0; virtual void slot23() = 0;
    virtual void slot24() = 0; virtual void slot25() = 0;
    virtual void slot26() = 0; virtual void slot27() = 0;
    virtual void slot28() = 0; virtual void slot29() = 0;
    virtual void slot30() = 0; virtual void slot31() = 0;
    virtual void slot32() = 0; virtual void slot33() = 0;
    virtual void slot34() = 0; virtual void slot35() = 0;
    virtual void slot36() = 0; virtual void slot37() = 0;
    virtual void slot38() = 0; virtual void slot39() = 0;
    virtual void slot40() = 0; virtual void slot41() = 0;
    virtual void slot42() = 0; virtual void slot43() = 0;
    virtual int winSetFocus(GameWindow *window);
    virtual void slot45() = 0; virtual void slot46() = 0;
    virtual void slot47() = 0; virtual void slot48() = 0;
    virtual void slot49() = 0; virtual void slot50() = 0;
    virtual void slot51() = 0; virtual void slot52() = 0;
    virtual void slot53() = 0; virtual void slot54() = 0;
    virtual GameWindow *winGetWindowFromId(GameWindow *window, int id);
};

class GameWindow
{
public:
    int winEnable(Bool enable);
    int winHide(Bool hide);
};

extern NameKeyGenerator *TheNameKeyGenerator;
extern GameWindowManager *TheWindowManager;
extern void PopulateReplayFileListbox(GameWindow *listbox);
extern void GadgetTextEntrySetText(GameWindow *window, UnicodeString text);

namespace PopupReplayState
{
extern NameKeyType buttonBackKey;
extern NameKeyType buttonSaveKey;
extern NameKeyType listboxGamesKey;
extern NameKeyType textEntryReplayNameKey;
extern GameWindow *parent;
extern GameWindow *replaySavedParent;
}
using namespace PopupReplayState;


void PopupReplayInit(WindowLayout *layout, void *userData)
{
    buttonBackKey = TheNameKeyGenerator->nameToKey("PopupReplay.wnd:ButtonBack");
    buttonSaveKey = TheNameKeyGenerator->nameToKey("PopupReplay.wnd:ButtonSave");
    listboxGamesKey = TheNameKeyGenerator->nameToKey("PopupReplay.wnd:ListboxGames");
    textEntryReplayNameKey = TheNameKeyGenerator->nameToKey("PopupReplay.wnd:TextEntryReplayName");

    NameKeyType parentID = TheNameKeyGenerator->nameToKey("PopupReplay.wnd:PopupReplayMenu");
    GameWindow *newParent = TheWindowManager->winGetWindowFromId(0, parentID);
    GameWindowManager *manager = TheWindowManager;
    // Slot 44 is winSetFocus (retail 0x0047CA80): ECX is the receiver,
    // one window argument is on the stack, and EDX is caller-saved. This
    // register-ABI view supplies the already loaded vtable in EDX, preserving
    // retail's vtable load before the shared parent store (VC7.1 scheduling).
    typedef int (__fastcall *FocusCall)(GameWindowManager *, void *, GameWindow *);
    FocusCall *table = *reinterpret_cast<FocusCall **>(manager);
    parent = newParent;
    table[44](manager, table, newParent);

    NameKeyType replaySavedParentID = TheNameKeyGenerator->nameToKey("PopupReplay.wnd:PopupReplaySaved");
    replaySavedParent = TheWindowManager->winGetWindowFromId(0, replaySavedParentID);
    if (replaySavedParent == 0)
        DEBUG_ASSERTCRASH(false, ("replaySavedParent == NULL"));

    if (replaySavedParent != 0)
        replaySavedParent->winHide(true);

    GameWindow *buttonFrame = TheWindowManager->winGetWindowFromId(parent,
        TheNameKeyGenerator->nameToKey("PopupReplay.wnd:MenuButtonFrame"));
    buttonFrame->winEnable(true);

    GameWindow *listboxGames = TheWindowManager->winGetWindowFromId(0, listboxGamesKey);
    if (listboxGames == 0)
        DEBUG_ASSERTCRASH(false, ("PopupReplayInit - Unable to find games listbox\n"));
    PopulateReplayFileListbox(listboxGames);

    GameWindow *textEntryReplayName = TheWindowManager->winGetWindowFromId(
        parent, textEntryReplayNameKey);
    GadgetTextEntrySetText(textEntryReplayName, UnicodeString::TheEmptyString);
    TheWindowManager->winSetFocus(textEntryReplayName);

    GameWindow *control = TheWindowManager->winGetWindowFromId(parent, buttonSaveKey);
    if (control)
        control->winEnable(false);
}
