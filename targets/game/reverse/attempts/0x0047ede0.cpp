// ?winCreate@GameWindowManager@@UAEPAVGameWindow@@PAURva0047EDE0CreateInfo@@@Z
// partial score=1.0 date=2026-10-08
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// BFME creation record and virtual dispatch at retail 0x0047EDE0.
#include "ascii_string.h"

template <typename T> inline bool StringBase<T>::isEmpty() const
{
    return m_data == 0 || m_data->length == 0;
}
template <typename T> inline bool StringBase<T>::isNotEmpty() const
{
    return !isEmpty();
}

class GameFont;
class WinInstanceData;
class GameWindow;

struct Rva0047EDE0CreateInfo
{
    GameWindow *m_parent;
    unsigned int m_field04;
    int m_field08, m_field0C, m_field10, m_field14;
    GameWindow *(__stdcall *m_allocator)(Rva0047EDE0CreateInfo *);
    void *m_field1C;
    int m_field20, m_field24, m_field28, m_field2C;
    WinInstanceData *m_field30;
};

class GameWindow
{
public:
    virtual void slot00(); virtual void slot01(); virtual void slot02();
    virtual void slot03(); virtual void slot04(); virtual void slot05();
    virtual void slot06(); virtual void slot07(); virtual void slot08();
    virtual void slot09();
    virtual bool rva0047EDE0Slot10();
    void *m_field04;
    unsigned char m_unmodelled008[0x1f0];
    GameWindow *m_next;
    GameWindow *m_prev;
    GameWindow *m_parent;
    GameWindow *m_child;

    int winSetInstanceData(WinInstanceData *data);
    virtual void winSetFont(GameFont *font);
};

struct Rva00477DF0
{
    void orderPairs();
};

struct FontDesc
{
    AsciiString name;
    int size;
    bool bold;
};

class GlobalLanguage
{
public:
    unsigned char m_unmodelled000[0xa0];
    FontDesc m_defaultWindowFont;
};
extern GlobalLanguage *TheGlobalLanguageData;

enum WindowMsgHandledType { MSG_IGNORED, MSG_HANDLED };

class GameWindowManager
{
public:
    virtual void slot00(); virtual void slot01(); virtual void slot02();
    virtual void slot03(); virtual void slot04(); virtual void slot05();
    virtual void slot06(); virtual void slot07(); virtual void slot08();
    virtual void *rva0047EDE0Slot09();
    virtual GameWindow *rva0078F520Slot10(Rva0047EDE0CreateInfo *);
    virtual void slot11(); virtual void slot12(); virtual void slot13();
    virtual void slot14(); virtual void slot15(); virtual void slot16();
    virtual void slot17(); virtual void slot18(); virtual void slot19();
    virtual void slot20(); virtual void slot21(); virtual void slot22();
    virtual void slot23(); virtual void slot24(); virtual void slot25();
    virtual void slot26(); virtual void slot27(); virtual void slot28();
    virtual GameWindow *winCreate(Rva0047EDE0CreateInfo *info);
    virtual void slot30(); virtual void slot31(); virtual void slot32();
    virtual void slot33(); virtual void slot34(); virtual void slot35();
    virtual void slot36(); virtual void slot37(); virtual void slot38();
    virtual void slot39(); virtual void slot40(); virtual void slot41();
    virtual void slot42(); virtual void slot43(); virtual void slot44();
    virtual void slot45(); virtual void slot46(); virtual void slot47();
    virtual void slot48(); virtual void slot49(); virtual void slot50();
    virtual void addWindowToParent(GameWindow *, GameWindow *);
    virtual void slot52();
    virtual WindowMsgHandledType winSendSystemMsg(GameWindow *, unsigned int, unsigned int, unsigned int);
    virtual void slot54(); virtual void slot55(); virtual void slot56();
    virtual void slot57(); virtual void slot58(); virtual void slot59();
    virtual void slot60(); virtual void slot61(); virtual void slot62();
    virtual void slot63(); virtual void slot64(); virtual void slot65();
    virtual void slot66(); virtual void slot67(); virtual void slot68();
    virtual void slot69(); virtual void slot70();
    virtual GameFont *winFindFont(AsciiString, int, bool);

    unsigned int m_field04;
    GameWindow *m_windowList;
    void linkWindow(GameWindow *window);
protected:
    void dumpWindow(GameWindow *window);
};

// ?dumpWindow@GameWindowManager@@IAEXPAVGameWindow@@@Z
void GameWindowManager::dumpWindow(GameWindow *window)
{
    if (window == 0)
        return;
    for (GameWindow *child = window->m_child; child; child = child->m_next)
        dumpWindow(child);
}

// ?winCreate@GameWindowManager@@UAEPAVGameWindow@@PAURva0047EDE0CreateInfo@@@Z
GameWindow *GameWindowManager::winCreate(Rva0047EDE0CreateInfo *info)
{
    GameWindow *window;
    if (info->m_allocator)
    {
        window = info->m_allocator(info);
        if (window->m_field04 == 0 && window->rva0047EDE0Slot10())
            window->m_field04 = rva0047EDE0Slot09();
    }
    else
    {
        window = rva0078F520Slot10(info);
        if (window == 0)
        {
            for (GameWindow *win = m_windowList; win; win = win->m_next)
                dumpWindow(win);
            return 0;
        }
    }
    if (info->m_parent)
        addWindowToParent(window, info->m_parent);
    else
        linkWindow(window);
    if (info->m_field30)
        window->winSetInstanceData(info->m_field30);
    ((Rva00477DF0 *)window)->orderPairs();
    winSendSystemMsg(window, 1, 0, 0);
    if (TheGlobalLanguageData && TheGlobalLanguageData->m_defaultWindowFont.name.isNotEmpty())
        window->GameWindow::winSetFont(winFindFont(TheGlobalLanguageData->m_defaultWindowFont.name,
            TheGlobalLanguageData->m_defaultWindowFont.size, TheGlobalLanguageData->m_defaultWindowFont.bold));
    else
        window->GameWindow::winSetFont(winFindFont(AsciiString("Times New Roman"), 14, false));
    return window;
}
