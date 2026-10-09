// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Include
// Evidence: targets/game/reverse/identity_evidence/004b4010-input-and-private-helper.md
#include "ascii_string.h"

enum WindowMsgHandledType { MSG_IGNORED, MSG_HANDLED };
enum GameWindowMessage
{
    GWM_LEFT_DOWN = 5, GWM_LEFT_UP = 6, GWM_LEFT_DRAG = 8,
    GWM_RIGHT_UP = 14, GWM_WHEEL_UP = 19, GWM_WHEEL_DOWN = 20,
    GWM_CHAR = 21
};
enum { KEY_TAB = 15, KEY_STATE_DOWN = 2, GWS_MOUSE_TRACK = 0x400, GGM_LEFT_DRAG = 0x4000 };
#include "Lib/Coord3D.h"

// The complete constructor and destructor own the opaque event storage.
class AudioEventRTS
{
public:
    AudioEventRTS(const AsciiString &eventName, int timeOfDay);
    virtual void slot00();
    // Retail uses the ledger's direct complete-destructor spelling.
    ~AudioEventRTS();
private:
    unsigned char m_storage[0x6C];
};

typedef char AudioEventRTSSize[(sizeof(AudioEventRTS) == 0x70) ? 1 : -1];

class GameFont;
class WinInstanceData
{
public:
    unsigned char m_head[0x0c];
    unsigned int m_style;
    unsigned char m_middle[0x184-0x10];
    GameFont *m_font;
    // ?getStyle@WinInstanceData@@QAEIXZ absent-from-retail
    unsigned int getStyle() { return m_style; }
    // ?getFont@WinInstanceData@@QAEPAVGameFont@@XZ absent-from-retail
    GameFont *getFont() { return m_font; }
};
class GameWindow
{
public:
    WinInstanceData *winGetInstanceData();
    void *winGetUserData();
    GameWindow *winGetOwner();
    bool winIsHidden();
    int winHide(bool hide);
    int winGetSize(int *width, int *height);
    int winSetSize(int width, int height);
    int winSetPosition(int x, int y);
};
struct ComboBoxData
{
    bool isEditable;
    unsigned char m_pad01[3];
    int maxDisplay;
    unsigned char m_pad08[0x14];
    bool dontHide;
    unsigned char m_pad1d[3];
    int entryCount;
    GameWindow *dropDownButton;
    GameWindow *editBox;
    GameWindow *listBox;
};
struct ListboxData
{
    unsigned char m_pad00[0x12];
    bool m_flag12, m_flag13;
    unsigned char m_pad14[8];
    GameWindow *upButton, *downButton, *slider;
    unsigned char m_pad28[8];
    int m_int30;
    int selectPos;
};
class GameWindowManager
{
public:
    virtual void slot000();
    virtual void slot004();
    virtual void slot008();
    virtual void slot00C();
    virtual void slot010();
    virtual void slot014();
    virtual void slot018();
    virtual void slot01C();
    virtual void slot020();
    virtual void slot024();
    virtual void slot028();
    virtual void slot02C();
    virtual void slot030();
    virtual void slot034();
    virtual void slot038();
    virtual void slot03C();
    virtual void slot040();
    virtual void slot044();
    virtual void slot048();
    virtual void slot04C();
    virtual void slot050();
    virtual void slot054();
    virtual void slot058();
    virtual void slot05C();
    virtual void slot060();
    virtual void slot064();
    virtual void slot068();
    virtual void slot06C();
    virtual void slot070();
    virtual void slot074();
    virtual void slot078();
    virtual void slot07C();
    virtual void slot080();
    virtual void slot084();
    virtual void slot088();
    virtual void slot08C();
    virtual void slot090();
    virtual void winNextTab(GameWindow *window);
    virtual void winPrevTab(GameWindow *window);
    virtual void slot09C();
    virtual void slot0A0();
    virtual void slot0A4();
    virtual void slot0A8();
    virtual void slot0AC();
    virtual void slot0B0();
    virtual void slot0B4();
    virtual void slot0B8();
    virtual void winSetLoneWindow(GameWindow *window);
    virtual GameWindow *rva0047D080();
    virtual void slot0C4();
    virtual void slot0C8();
    virtual void slot0CC();
    virtual void slot0D0();
    virtual WindowMsgHandledType winSendSystemMsg(GameWindow *window, unsigned int msg, unsigned int mData1, unsigned int mData2);
    virtual WindowMsgHandledType winSendInputMsg(GameWindow *window, unsigned int msg, unsigned int mData1, unsigned int mData2);
    virtual void slot0DC();
    virtual void slot0E0();
    virtual void slot0E4();
    virtual void slot0E8();
    virtual void slot0EC();
    virtual void slot0F0();
    virtual void slot0F4();
    virtual void slot0F8();
    virtual void slot0FC();
    virtual void slot100();
    virtual void slot104();
    virtual void slot108();
    virtual int winFontHeight(GameFont *font);
};
extern GameWindowManager *TheWindowManager;
class Keyboard
{
    unsigned char m_head[8];
    int m_modifiers;
public:
    // ?getModifierFlags@Keyboard@@QAEHXZ absent-from-retail
    int getModifierFlags() { return m_modifiers; }
};
extern Keyboard *TheKeyboard;
class AudioManager
{
public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0C();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1C();
    virtual void slot20();
    virtual void slot24();
    virtual void slot28();
    virtual void slot2C();
    virtual void slot30();
    virtual void slot34();
    virtual void slot38();
    virtual void slot3C();
    virtual void slot40();
    virtual unsigned int addAudioEvent(const AudioEventRTS *event);
};
extern AudioManager *TheAudio;
void bfmeGo1017Y(int a, int b, int c);
void HideListBox(GameWindow *window);
struct ICoord2D { int x, y; };
// ?GadgetComboBoxGetEditBox@@YAPAVGameWindow@@PAV1@@Z absent-from-retail
static __forceinline GameWindow *GadgetComboBoxGetEditBox(GameWindow *window)
{
    ComboBoxData *data = (ComboBoxData *)window->winGetUserData();
    return data && data->editBox ? data->editBox : 0;
}
// ?GadgetComboBoxGetListBox@@YAPAVGameWindow@@PAV1@@Z absent-from-retail
static __forceinline GameWindow *GadgetComboBoxGetListBox(GameWindow *window)
{
    ComboBoxData *data = (ComboBoxData *)window->winGetUserData();
    return data ? data->listBox : 0;
}
// ?Rva004B3E30@@YAXPAVGameWindow@@@Z
static __declspec(noinline) void Rva004B3E30(GameWindow *window)
{
    if (!window) return;
    ComboBoxData *comboData = (ComboBoxData *)window->winGetUserData();
    comboData->dontHide = false;
    GameWindow *listBox = GadgetComboBoxGetListBox(window);
    if (!listBox) return;
    if (listBox->winIsHidden())
    {
        TheWindowManager->winSetLoneWindow(window);
        if (comboData->entryCount <= 1) return;
        listBox->winHide(false);
        ICoord2D winSize;
        window->winGetSize(&winSize.x, &winSize.y);
        WinInstanceData *listInstData = listBox->winGetInstanceData();
        ListboxData *listData = (ListboxData *)listBox->winGetUserData();
        listData->m_flag12 = true;
        listData->m_flag13 = true;
        listData->m_int30 = listData->selectPos;
        int multiplier;
        int listX;
        if (comboData->entryCount <= comboData->maxDisplay)
        {
            multiplier = comboData->entryCount;
            listX = winSize.x;
            if (listData->upButton) listData->upButton->winHide(true);
            if (listData->downButton) listData->downButton->winHide(true);
            if (listData->slider) listData->slider->winHide(true);
        }
        else
        {
            multiplier = comboData->maxDisplay;
            listX = winSize.x;
            if (listData->upButton) listData->upButton->winHide(false);
            if (listData->downButton) listData->downButton->winHide(false);
            if (listData->slider) listData->slider->winHide(false);
        }
        ICoord2D newSize;
        newSize.y = (TheWindowManager->winFontHeight(listInstData->getFont()) + 2) * multiplier + 4;
        window->winSetSize(winSize.x, winSize.y + newSize.y);
        listBox->winSetPosition(0, winSize.y);
        listBox->winSetSize(listX, newSize.y);
    }
    else
    {
        HideListBox(window);
        TheWindowManager->winSetLoneWindow(0);
    }
}
// ?GadgetComboBoxInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z
WindowMsgHandledType GadgetComboBoxInput(GameWindow *window, unsigned int msg, unsigned int mData1, unsigned int mData2)
{
    WinInstanceData *instData = window->winGetInstanceData();
    GameWindow *editBox = GadgetComboBoxGetEditBox(window);
    switch (msg)
    {
    case GWM_CHAR:
        switch (mData1)
        {
        case KEY_TAB:
            if (mData2 & KEY_STATE_DOWN)
            {
                if ((unsigned char)TheKeyboard->getModifierFlags() & 0x10)
                    TheWindowManager->winPrevTab(window);
                else
                    TheWindowManager->winNextTab(window);
            }
            break;
        default:
            return TheWindowManager->winSendInputMsg(editBox, GWM_CHAR, mData1, mData2);
        }
        break;
    case GWM_WHEEL_UP:
    case GWM_WHEEL_DOWN:
    case GWM_RIGHT_UP:
        break;
    case GWM_LEFT_UP:
        if (TheAudio)
        {
            AudioEventRTS buttonClick("GUIComboBoxClick", 2);
            TheAudio->addAudioEvent(&buttonClick);
        }
        // The complete static helper lets VC7.1 pass window in EBX.
        Rva004B3E30(window);
        bfmeGo1017Y(0, 1, 1);
        break;
    case GWM_LEFT_DRAG:
        if (instData->getStyle() & GWS_MOUSE_TRACK)
            TheWindowManager->winSendSystemMsg(window->winGetOwner(), GGM_LEFT_DRAG, (unsigned int)window, 0);
        break;
    case GWM_LEFT_DOWN:
        if (TheWindowManager->rva0047D080() == window) return MSG_IGNORED;
        break;
    default:
        return MSG_IGNORED;
    }
    return MSG_HANDLED;
}
