// cl: /DNDEBUG /MD /EHsc /Igame/GameEngine/Include /Igame/Libraries/Source/WWVegas/WWLib
// BFME init, retail RVA 0x004A0F70 through 0x004A1DBC (3660 bytes).
// Reference algorithm: ControlBar.cpp::init, with BFME overlay creation and
// 20 command slots. See docs/analysis/control_bar_init_004a0f70.md.
#include "ascii_string.h"
#include "Common/INI/INI.h"
#include <string.h>

class GameWindow;
class WinInstanceData;
class Drawable;
class Image;
typedef void (*TooltipFunc)(GameWindow *, WinInstanceData *, unsigned);
void rva0049ca90(GameWindow *, WinInstanceData *, unsigned);
// Same 52-byte creation record witnessed in AptPalantirHeroSelectorRva00595D40.cpp.
// The winCreate body consumes x/y/width/height at +08/+0C/+10/+14.
struct Rva0047EDE0CreateInfo
{
    Rva0047EDE0CreateInfo()
        : parent(0), field04(0), x(0), y(0), width(0), height(0), allocator(0), field1C(0),
          field20(0), field24(0), field28(0), field2C(0), field30(0)
    {
    }
    GameWindow *parent;
    unsigned field04;
    int x, y, width, height;
    void *allocator;
    void *field1C;
    int field20, field24, field28, field2C, field30;
};
class Open2479440Record;
class Rva00479440
{
  public:
    void publish(Open2479440Record *, char);
};
class GameWindow
{
  public:
    int winGetPosition(int *, int *);
    int winGetScreenPosition(int *, int *);
    int winGetSize(int *, int *);
    int winSetSize(int, int);
    int winSetPosition(int, int);
    unsigned _bfme_winSetStatus(unsigned);
    unsigned winClearStatus(unsigned);
    unsigned winGetStatus();
    void winSetUserData(void *);
    int winSetTooltipFunc(TooltipFunc);
    GameWindow *winGetNextInLayout();
};
class WindowLayout;
typedef void (*WindowLayoutUpdateFunc)(WindowLayout *, void *);
class WindowLayout
{
  public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0C();
    virtual void hide(bool);
    void setUpdate(WindowLayoutUpdateFunc func)
    {
        update = func;
    }
    GameWindow *getFirstWindow()
    {
        return first;
    }
    int field04;
    GameWindow *first;
    char field0C[0x10];
    WindowLayoutUpdateFunc update;
};
enum NameKeyType
{
    NAMEKEY_INVALID = 0
};
class NameKeyGenerator
{
  public:
    NameKeyType nameToKey(const char *);
    NameKeyType nameToKey(const AsciiString &s)
    {
        return nameToKey(s.str());
    }
};
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
    virtual WindowLayout *winCreateLayout(AsciiString);
    virtual void slot28();
    virtual GameWindow *winCreate(Rva0047EDE0CreateInfo *);
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
    virtual void slot44();
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
    virtual GameWindow *winGetWindowFromId(GameWindow *, int);
};
class Display
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
    virtual int slot11();
    virtual int slot12();
};
extern Display *TheDisplay;
extern GameWindowManager *TheWindowManager;
extern NameKeyGenerator *TheNameKeyGenerator;
class ImageCollection
{
  public:
    const Image *findImageByName(const AsciiString &);
};
extern ImageCollection *TheMappedImageCollection;
extern void j_0001e9bb();
extern void j_00011bf8();
class Overridable
{
  public:
    Overridable *friend_getFinalOverride();
    void *vptr;
    Overridable *next;
};
class CommandButton : public Overridable
{
  public:
    void cacheButtonImage();
    char field08[12];
    CommandButton *nextButton;
};
class ControlBarSchemeManager
{
  public:
    ControlBarSchemeManager();
    void init();
    char bytes[16];
};
class WindowVideoManager
{
  public:
    WindowVideoManager();
    char bytes[32];
};
class AnimateWindowManager
{
  public:
    AnimateWindowManager();
    char bytes[52];
};
enum ControlBarContext
{
    CB_CONTEXT_NONE = 0
};
// The old ledger calls this observer-window setup body a destructor. Keep its
// address identity until the separate 0x004A9CD0 observer claim is audited.
class Rva004A9980
{
  public:
    void call();
};
class ControlBar
{
  public:
    virtual void init();
    void setControlCommand(GameWindow *, const CommandButton *);
    void update();

  protected:
    CommandButton *findNonConstCommandButton(const AsciiString &);
    void switchToContext(ControlBarContext, Drawable *);
    static const Image *m_rankVeteranIcon, *m_rankEliteIcon, *m_rankHeroicIcon;
    const CommandButton *findCommandButton(const AsciiString &name)
    {
        CommandButton *b = findNonConstCommandButton(name);
        if (b && b->next)
            b = (CommandButton *)b->next->friend_getFinalOverride();
        return b;
    }
    int field04;
    WindowVideoManager *field08;
    AnimateWindowManager *field0C, *field10, *field14;
    int field18, field1C;
    char field20[8];
    CommandButton *field28;
    int field2C;
    ControlBarSchemeManager *field30;
    GameWindow *field34[10];
    char field5C[24];
    GameWindow *field74, *field78, *field7C[5], *field90, *field94;
    WindowLayout *field98;
    GameWindow *field9C[12];
    char fieldCC[0x34];
    GameWindow *field100[20], *field150[20], *field1A0[20];
    char field1F0[0x50];
    bool field240;
    char field241[0x37];
    WindowLayout *field278;
    char field27C[0x1c];
    Image *field298, *field29C;
    char field2A0[0x28];
    bool field2C8;
    char field2C9[3];
    int field2CC, field2D0, field2D4, field2D8, field2DC;
    char field2E0[8];
    GameWindow *field2E8;
    int field2EC;
    void *field2F0;
};
// Retail RVA 004A0F70, full 3660-byte body. BFME offsets witnessed directly;
// address-derived fields avoid assigning ZH member names to changed layouts.
void ControlBar::init()
{
    INI ini;
    field240 = false;
    ini.loadFile(AsciiString("Data\\INI\\Default\\CommandButton.ini"), INI_LOAD_OVERWRITE, 0);
    ini.loadFile(AsciiString("Data\\INI\\CommandButton.ini"), INI_LOAD_OVERWRITE, 0);
    ini.loadFile(AsciiString("Data\\INI\\CommandSet.ini"), INI_LOAD_OVERWRITE, 0);
    for (CommandButton *b = field28; b; b = b->nextButton)
        b->cacheButtonImage();
    field30 = new ControlBarSchemeManager;
    field30->init();
    if (TheWindowManager)
    {
        NameKeyType id;
        id = TheNameKeyGenerator->nameToKey("ControlBar.wnd:ControlBarParent");
        field34[0] = TheWindowManager->winGetWindowFromId(0, id);
        field34[0]->winGetPosition(&field18, &field1C);
        field98 = TheWindowManager->winCreateLayout("GeneralsExpPoints.wnd");
        field98->hide(true);
        id = TheNameKeyGenerator->nameToKey("GeneralsExpPoints.wnd:GenExpParent");
        field34[1] = TheWindowManager->winGetWindowFromId(0, id);
        id = TheNameKeyGenerator->nameToKey("ControlBar.wnd:UnderConstructionWindow");
        field34[5] = TheWindowManager->winGetWindowFromId(0, id);
        id = TheNameKeyGenerator->nameToKey("ControlBar.wnd:OCLTimerWindow");
        field34[8] = TheWindowManager->winGetWindowFromId(0, id);
        id = TheNameKeyGenerator->nameToKey("ControlBar.wnd:BeaconWindow");
        field34[4] = TheWindowManager->winGetWindowFromId(0, id);
        id = TheNameKeyGenerator->nameToKey("ControlBar.wnd:CommandWindow");
        field34[2] = TheWindowManager->winGetWindowFromId(0, id);
        id = TheNameKeyGenerator->nameToKey("ControlBar.wnd:ProductionQueueWindow");
        field34[3] = TheWindowManager->winGetWindowFromId(0, id);
        id = TheNameKeyGenerator->nameToKey("ControlBar.wnd:ObserverPlayerListWindow");
        field34[7] = TheWindowManager->winGetWindowFromId(0, id);
        id = TheNameKeyGenerator->nameToKey("ControlBar.wnd:ObserverPlayerInfoWindow");
        field34[6] = TheWindowManager->winGetWindowFromId(0, id);

        GameWindow *parent = field34[2];
        Rva0047EDE0CreateInfo info;
        ((Rva00479440 *)parent)->publish((Open2479440Record *)&info, 0);
        info.field04 = parent->winGetStatus();
        info.width = TheDisplay->slot11();
        info.height = TheDisplay->slot12();
        info.field24 = (int)j_0001e9bb;
        info.field2C = 0;
        GameWindow *overlay = TheWindowManager->winCreate(&info);
        field34[9] = overlay;
        overlay->winSetUserData(field2F0);
        overlay->_bfme_winSetStatus(0x200);
        overlay->winClearStatus(0x10000);
        // Keep the actual two coordinate aggregates: splitting them into scalar
        // locals changes MSVC 7.1's frame alignment and register allocation.
        struct ICoord2D
        {
            int x, y;
        };
        ICoord2D commandSize, commandPos;
        AsciiString windowName;
        for (int i = 0; i < 20; ++i)
        {
            windowName.format("ControlBar.wnd:ButtonCommand%02d", i + 1);
            id = TheNameKeyGenerator->nameToKey(windowName.str());
            GameWindow *window = TheWindowManager->winGetWindowFromId(field34[2], id);
            field150[i] = window;
            if (window)
            {
                window->winGetPosition(&commandPos.x, &commandPos.y);
                window->winGetSize(&commandSize.x, &commandSize.y);
                window->_bfme_winSetStatus(0x200000);
                Rva0047EDE0CreateInfo buttonInfo;
                ((Rva00479440 *)window)->publish((Open2479440Record *)&buttonInfo, 0);
                buttonInfo.parent = overlay;
                buttonInfo.field2C = 0;
                buttonInfo.y = (i * 100 / 640) * 100;
                buttonInfo.width = buttonInfo.height = 64;
                buttonInfo.x = i * 100 % 640;
                window = TheWindowManager->winCreate(&buttonInfo);
                window->_bfme_winSetStatus(0x20000000);
                window->_bfme_winSetStatus(0x20000);
                field100[i] = field1A0[i] = window;
                window->winSetSize(1, 1);
                window->winSetPosition(-1, -1);
            }
        }
        for (int i = 0; i < 12; ++i)
        {
            windowName.format("GeneralsExpPoints.wnd:ButtonRank3Number%d", i);
            id = TheNameKeyGenerator->nameToKey(windowName.str());
            field9C[i] = TheWindowManager->winGetWindowFromId(field34[1], id);
            field9C[i]->_bfme_winSetStatus(0x200000);
        }
        id = TheNameKeyGenerator->nameToKey("ControlBar.wnd:RightHUD");
        field74 = TheWindowManager->winGetWindowFromId(0, id);
        id = TheNameKeyGenerator->nameToKey("ControlBar.wnd:WinUnitSelected");
        field90 = TheWindowManager->winGetWindowFromId(0, id);
        id = TheNameKeyGenerator->nameToKey("ControlBar.wnd:CameoWindow");
        field78 = TheWindowManager->winGetWindowFromId(0, id);

        for (int i = 0; i < 5; ++i)
        {
            windowName.format("ControlBar.wnd:UnitUpgrade%d", i + 1);
            id = TheNameKeyGenerator->nameToKey(windowName.str());
            field7C[i] = TheWindowManager->winGetWindowFromId(field74, id);
            field7C[i]->_bfme_winSetStatus(0x200000);
        }
        id = TheNameKeyGenerator->nameToKey("ControlBar.wnd:PopupCommunicator");
        field94 = TheWindowManager->winGetWindowFromId(0, id);
        setControlCommand(field94, findCommandButton("NonCommand_Communicator"));
        field94->winSetTooltipFunc(rva0049ca90);
        GameWindow *win = TheWindowManager->winGetWindowFromId(
            0, TheNameKeyGenerator->nameToKey("ControlBar.wnd:ButtonOptions"));
        win = TheWindowManager->winGetWindowFromId(
            0, TheNameKeyGenerator->nameToKey("ControlBar.wnd:ButtonIdleWorker"));
        if (win)
        {
            setControlCommand(win, findCommandButton("NonCommand_IdleWorker"));
            win->winSetTooltipFunc(rva0049ca90);
        }
        win = TheWindowManager->winGetWindowFromId(
            0, TheNameKeyGenerator->nameToKey("ControlBar.wnd:ButtonPlaceBeacon"));
        if (win)
        {
            setControlCommand(win, findCommandButton("NonCommand_Beacon"));
            win->winSetTooltipFunc(rva0049ca90);
        }
        win = TheWindowManager->winGetWindowFromId(
            0, TheNameKeyGenerator->nameToKey("ControlBar.wnd:ButtonGeneral"));
        if (win)
        {
            setControlCommand(win, findCommandButton("NonCommand_GeneralsExperience"));
            win->winSetTooltipFunc(rva0049ca90);
        }
        win = TheWindowManager->winGetWindowFromId(
            0, TheNameKeyGenerator->nameToKey("ControlBar.wnd:ButtonLarge"));
        if (win)
        {
            setControlCommand(win, findCommandButton("NonCommand_UpDown"));
            win->winSetTooltipFunc(rva0049ca90);
        }
        win = TheWindowManager->winGetWindowFromId(
            0, TheNameKeyGenerator->nameToKey("ControlBar.wnd:PowerWindow"));
        if (win)
            win->winSetTooltipFunc(rva0049ca90);
        win = TheWindowManager->winGetWindowFromId(
            0, TheNameKeyGenerator->nameToKey("ControlBar.wnd:MoneyDisplay"));
        if (win)
            win->winSetTooltipFunc(rva0049ca90);
        win = TheWindowManager->winGetWindowFromId(
            0, TheNameKeyGenerator->nameToKey("ControlBar.wnd:GeneralsExp"));
        if (win)
            win->winSetTooltipFunc(rva0049ca90);

        field2E8 = TheWindowManager->winGetWindowFromId(
            0, TheNameKeyGenerator->nameToKey("ControlBar.wnd:WinUAttack"));
        win = TheWindowManager->winGetWindowFromId(
            0, TheNameKeyGenerator->nameToKey(AsciiString("ControlBar.wnd:BackgroundMarker")));
        win->winGetScreenPosition(&field2D0, &field2D4);
        win = TheWindowManager->winGetWindowFromId(
            0, TheNameKeyGenerator->nameToKey(AsciiString("ControlBar.wnd:BackgroundMarker")));
        win->winGetScreenPosition(&field2D8, &field2DC);
        if (!field08)
            field08 = new WindowVideoManager;
        if (!field0C)
            field0C = new AnimateWindowManager;
        if (!field14)
            field14 = new AnimateWindowManager;
        if (!field10)
            field10 = new AnimateWindowManager;
        field278 = TheWindowManager->winCreateLayout("ControlBarPopupDescription.wnd");
        if (field278)
        {
            field278->hide(true);
            field278->setUpdate((WindowLayoutUpdateFunc)j_00011bf8);
            for (GameWindow *w = field278->getFirstWindow(); w; w = w->winGetNextInLayout())
            {
                w->winSetSize(1, 1);
                w->winSetPosition(-1, -1);
            }
        }
        field298 = TheMappedImageCollection
                       ? (Image *)TheMappedImageCollection->findImageByName("BarButtonGenStarON")
                       : 0;
        field29C = TheMappedImageCollection
                       ? (Image *)TheMappedImageCollection->findImageByName("BarButtonGenStarOFF")
                       : 0;
        field2C8 = true;
        field2CC = -1;
        m_rankVeteranIcon =
            TheMappedImageCollection ? TheMappedImageCollection->findImageByName("SSChevron1L") : 0;
        m_rankEliteIcon =
            TheMappedImageCollection ? TheMappedImageCollection->findImageByName("SSChevron2L") : 0;
        m_rankHeroicIcon =
            TheMappedImageCollection ? TheMappedImageCollection->findImageByName("SSChevron3L") : 0;
        ((Rva004A9980 *)this)->call();
        memcpy(field100, field1A0, sizeof(field100));
        field2EC = 1;
        update();
        switchToContext(CB_CONTEXT_NONE, 0);
    }
}
