// cl: /DNDEBUG /MD /EHsc /Oa
// PopupJoinGameInit, RVA 0x004D7300: 510 byte-verified bytes.
// TU-local retail ABI views preserve the literal-string and vtable call
// order while keeping all control flow and temporary lifetimes ordinary C++.

typedef int NameKeyType;
typedef bool Bool;

class WindowLayout;
class GameWindow;
class GameSpyStagingRoom;
class AsciiString;
class UnicodeString;

template <typename T> class StringBase
{
private:
    friend class AsciiString;
    friend class UnicodeString;
    StringBase(const T *text);
    StringBase(const StringBase<T> &other);
    void releaseBuffer();
protected:
    T *m_data;
};

class AsciiString : private StringBase<char>
{
public:
    AsciiString(const char *text) : StringBase<char>(text) {}
    ~AsciiString() { ((StringBase<char> *)this)->releaseBuffer(); }
    const char *str() const
    {
        return m_data ? (const char *)m_data + 8 : (const char *)0x0107388B;
    }
};

class UnicodeString : private StringBase<unsigned short>
{
public:
    static UnicodeString TheEmptyString;
    UnicodeString(const UnicodeString &other)
        : StringBase<unsigned short>(other) {}
    ~UnicodeString() {}
};

class NameKeyGenerator
{
public:
    NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class GameWindow {};

class GameWindowManager
{
public:
    virtual void slot00();
    virtual void slot01();
    virtual void slot02();
    virtual void slot03();
    virtual void slot04();
    virtual void slot05();
    virtual void slot06();
    virtual void slot07();
    virtual void slot08();
    virtual void slot09();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void slot16();
    virtual void slot17();
    virtual void slot18();
    virtual void slot19();
    virtual void slot20();
    virtual void slot21();
    virtual void slot22();
    virtual void slot23();
    virtual void slot24();
    virtual void slot25();
    virtual void slot26();
    virtual void slot27();
    virtual void slot28();
    virtual void slot29();
    virtual void slot30();
    virtual void slot31();
    virtual void slot32();
    virtual void slot33();
    virtual void slot34();
    virtual void slot35();
    virtual void slot36();
    virtual void slot37();
    virtual void slot38();
    virtual void slot39();
    virtual void slot40();
    virtual void slot41();
    virtual void slot42();
    virtual void slot43();
    virtual int winSetFocus(GameWindow *window);
    virtual void slot45();
    virtual void slot46();
    virtual void slot47();
    virtual void slot48();
    virtual void slot49();
    virtual void slot50();
    virtual void slot51();
    virtual void slot52();
    virtual void slot53();
    virtual void slot54();
    virtual GameWindow *winGetWindowFromId(GameWindow *parent, NameKeyType id);
    virtual void slot56();
    virtual void slot57();
    virtual void slot58();
    virtual int winSetModal(GameWindow *window);
};
extern GameWindowManager *TheWindowManager;

class GameSpyInfoInterface
{
public:
    virtual void slot00();
    virtual void slot01();
    virtual void slot02();
    virtual void slot03();
    virtual void slot04();
    virtual void slot05();
    virtual void slot06();
    virtual void slot07();
    virtual void slot08();
    virtual void slot09();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void slot16();
    virtual void slot17();
    virtual void slot18();
    virtual void slot19();
    virtual void slot20();
    virtual void slot21();
    virtual void slot22();
    virtual void slot23();
    virtual void slot24();
    virtual void slot25();
    virtual void slot26();
    virtual void slot27();
    virtual void slot28();
    virtual void slot29();
    virtual void slot30();
    virtual void slot31();
    virtual void slot32();
    virtual void slot33();
    virtual void slot34();
    virtual void slot35();
    virtual void slot36();
    virtual void slot37();
    virtual void slot38();
    virtual GameSpyStagingRoom *findStagingRoomByID(int id);
    virtual void slot40();
    virtual void slot41();
    virtual void slot42();
    virtual void slot43();
    virtual void slot44();
    virtual void slot45();
    virtual void slot46();
    virtual void slot47();
    virtual void slot48();
    virtual void slot49();
    virtual void slot50();
    virtual void slot51();
    virtual int getCurrentStagingRoomID();
};
extern GameSpyInfoInterface *TheGameSpyInfo;

class GameSpyStagingRoom
{
public:
    UnicodeString getGameName();
};

void GadgetTextEntrySetText(GameWindow *window, UnicodeString text);
void GadgetStaticTextSetText(GameWindow *window, UnicodeString text);

namespace PopupJoinGameState
{
    extern NameKeyType parentPopupID;
    extern NameKeyType textEntryGamePasswordID;
    extern NameKeyType buttonCancelID;
    extern GameWindow *parentPopup;
    extern GameWindow *textEntryGamePassword;
}
using namespace PopupJoinGameState;

void PopupJoinGameInit(WindowLayout *, void *);

void PopupJoinGameInit(WindowLayout *layout, void *userData)
{
    {
        AsciiString name("PopupJoinGame.wnd:ParentJoinPopUp");
        parentPopupID = TheNameKeyGenerator->nameToKey(name.str());
    }
    parentPopup = TheWindowManager->winGetWindowFromId(0, parentPopupID);

    {
        AsciiString name("PopupJoinGame.wnd:TextEntryGamePassword");
        textEntryGamePasswordID = TheNameKeyGenerator->nameToKey(name.str());
    }
    textEntryGamePassword = TheWindowManager->winGetWindowFromId(parentPopup, textEntryGamePasswordID);
    GadgetTextEntrySetText(textEntryGamePassword, UnicodeString::TheEmptyString);

    NameKeyType staticTextGameNameID;
    GameWindow *staticTextGameName;
    {
        AsciiString name("PopupJoinGame.wnd:StaticTextGameName");
        staticTextGameNameID = TheNameKeyGenerator->nameToKey(name.str());
    }
    staticTextGameName = TheWindowManager->winGetWindowFromId(parentPopup, staticTextGameNameID);
    GadgetStaticTextSetText(staticTextGameName, UnicodeString::TheEmptyString);

    buttonCancelID = TheNameKeyGenerator->nameToKey("PopupJoinGame.wnd:ButtonCancel");

    GameSpyStagingRoom *ourRoom =
        TheGameSpyInfo->findStagingRoomByID(TheGameSpyInfo->getCurrentStagingRoomID());
    if (ourRoom)
        GadgetStaticTextSetText(staticTextGameName, ourRoom->getGameName());

    TheWindowManager->winSetFocus(parentPopup);
    TheWindowManager->winSetModal(parentPopup);
}
