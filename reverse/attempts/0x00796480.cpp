// ?W3DGadgetRadioButtonDraw@@YAXPAVGameWindow@@PAVWinInstanceData@@@Z
// partial score=0.986 date=2026-09-02
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef int Color;
typedef unsigned char Bool;

class Image;
class GameFont;

struct ICoord2D { Int x, y; };
struct WinDrawData { const Image *image; Color color; Color borderColor; };

class DisplayString
{
public:
    virtual void unused00();
    virtual void unused01();
    virtual void unused02();
    virtual Int getTextLength();                 // +0x0c
    virtual void unused04();
    virtual void unused05();
    virtual void setFont(GameFont *font);         // +0x18
    virtual GameFont *getFont();                  // +0x1c
    virtual void unused08();
    virtual void unused09();
    virtual void setTextColor(Color, Color);      // +0x28
    virtual void unused11();
    virtual void unused12();
    virtual void unused13();
    virtual void draw(Int, Int, Int, Int);        // +0x38
    virtual void getSize(Int *, Int *);           // +0x3c
};

class WinInstanceData
{
public:
    unsigned char pad00[8];
    UnsignedInt state;
    unsigned char pad0c[0x190];
    DisplayString *text;                          // +0x19c

    UnsignedInt getState() { return state; }
    DisplayString *getTextDisplayString() { return text; }
    Int getTextLength() { return text ? text->getTextLength() : 0; }
};

class GameWindow
{
public:
    Int winGetScreenPosition(Int *, Int *);
    Int winGetSize(Int *, Int *);
    UnsignedInt winGetStatus();
    GameFont *winGetFont();
    Color winGetEnabledTextColor();
    Color winGetEnabledTextBorderColor();
    Color winGetDisabledTextColor();
    Color winGetDisabledTextBorderColor();
    Color winGetHiliteTextColor();
    Color winGetHiliteTextBorderColor();

    Color winGetEnabledColor(Int i) { return enabledData[i].color; }
    Color winGetEnabledBorderColor(Int i) { return enabledData[i].borderColor; }
    Color winGetDisabledColor(Int i) { return disabledData[i].color; }
    Color winGetDisabledBorderColor(Int i) { return disabledData[i].borderColor; }
    Color winGetHiliteColor(Int i) { return hiliteData[i].color; }
    Color winGetHiliteBorderColor(Int i) { return hiliteData[i].borderColor; }

    unsigned char pad00[0x48];
    WinDrawData enabledData[9];
    WinDrawData disabledData[9];
    WinDrawData hiliteData[9];
};

class GameWindowManager
{
public:
    virtual void unused00(); virtual void unused01(); virtual void unused02();
    virtual void unused03(); virtual void unused04(); virtual void unused05();
    virtual void unused06(); virtual void unused07(); virtual void unused08();
    virtual void unused09(); virtual void unused10(); virtual void unused11();
    virtual void unused12(); virtual void unused13(); virtual void unused14();
    virtual void unused15(); virtual void unused16(); virtual void unused17();
    virtual void unused18(); virtual void unused19(); virtual void unused20();
    virtual void unused21(); virtual void unused22(); virtual void unused23();
    virtual void unused24(); virtual void unused25(); virtual void unused26();
    virtual void unused27(); virtual void unused28(); virtual void unused29();
    virtual void unused30(); virtual void unused31(); virtual void unused32();
    virtual void unused33(); virtual void unused34(); virtual void unused35();
    virtual void unused36(); virtual void unused37(); virtual void unused38();
    virtual void unused39(); virtual void unused40(); virtual void unused41();
    virtual void unused42(); virtual void unused43(); virtual void unused44();
    virtual void unused45(); virtual void unused46(); virtual void unused47();
    virtual void unused48(); virtual void unused49(); virtual void unused50();
    virtual void unused51(); virtual void unused52(); virtual void unused53();
    virtual void unused54(); virtual void unused55(); virtual void unused56();
    virtual void unused57(); virtual void unused58(); virtual void unused59();
    virtual void unused60();
    virtual void winDrawImage(const Image *, Int, Int, Int, Int, Color = -1);
    virtual void winFillRect(Color, Real, Int, Int, Int, Int);       // +0xf8
    virtual void winOpenRect(Color, Real, Int, Int, Int, Int);       // +0xfc
    virtual void winDrawLine(Color, Real, Int, Int, Int, Int);       // +0x100
};

extern GameWindowManager *TheWindowManager;

enum { WIN_STATUS_ENABLED = 8, WIN_STATE_HILITED = 2, WIN_STATE_SELECTED = 4 };
#define FALSE 0
#define WIN_DRAW_LINE_WIDTH 1.0f

inline Color GadgetRadioGetEnabledColor(GameWindow *g) { return g->winGetEnabledColor(0); }
inline Color GadgetRadioGetEnabledBorderColor(GameWindow *g) { return g->winGetEnabledBorderColor(0); }
inline Color GadgetRadioGetEnabledUncheckedBoxColor(GameWindow *g) { return g->winGetEnabledColor(1); }
inline Color GadgetRadioGetEnabledUncheckedBoxBorderColor(GameWindow *g) { return g->winGetEnabledBorderColor(1); }
inline Color GadgetRadioGetEnabledCheckedBoxColor(GameWindow *g) { return g->winGetEnabledColor(2); }
inline Color GadgetRadioGetEnabledCheckedBoxBorderColor(GameWindow *g) { return g->winGetEnabledBorderColor(2); }
inline Color GadgetRadioGetDisabledColor(GameWindow *g) { return g->winGetDisabledColor(0); }
inline Color GadgetRadioGetDisabledBorderColor(GameWindow *g) { return g->winGetDisabledBorderColor(0); }
inline Color GadgetRadioGetDisabledUncheckedBoxColor(GameWindow *g) { return g->winGetDisabledColor(1); }
inline Color GadgetRadioGetDisabledUncheckedBoxBorderColor(GameWindow *g) { return g->winGetDisabledBorderColor(1); }
inline Color GadgetRadioGetDisabledCheckedBoxColor(GameWindow *g) { return g->winGetDisabledColor(2); }
inline Color GadgetRadioGetDisabledCheckedBoxBorderColor(GameWindow *g) { return g->winGetDisabledBorderColor(2); }
inline Color GadgetRadioGetHiliteColor(GameWindow *g) { return g->winGetHiliteColor(0); }
inline Color GadgetRadioGetHiliteBorderColor(GameWindow *g) { return g->winGetHiliteBorderColor(0); }
inline Color GadgetRadioGetHiliteUncheckedBoxColor(GameWindow *g) { return g->winGetHiliteColor(1); }
inline Color GadgetRadioGetHiliteUncheckedBoxBorderColor(GameWindow *g) { return g->winGetHiliteBorderColor(1); }
inline Color GadgetRadioGetHiliteCheckedBoxColor(GameWindow *g) { return g->winGetHiliteColor(2); }
inline Color GadgetRadioGetHiliteCheckedBoxBorderColor(GameWindow *g) { return g->winGetHiliteBorderColor(2); }

static void drawRadioButtonText(GameWindow *window, WinInstanceData *instData)
{
    DisplayString *text = instData->getTextDisplayString();
    ICoord2D origin, size, textPos;
    Int width, height;
    Color textColor, dropColor;

    if (text == 0 || text->getTextLength() == 0)
        return;
    window->winGetScreenPosition(&origin.x, &origin.y);
    window->winGetSize(&size.x, &size.y);

    if ((window->winGetStatus() & WIN_STATUS_ENABLED) == FALSE) {
        textColor = window->winGetDisabledTextColor();
        dropColor = window->winGetDisabledTextBorderColor();
    } else if (instData->getState() & WIN_STATE_HILITED) {
        textColor = window->winGetHiliteTextColor();
        dropColor = window->winGetHiliteTextBorderColor();
    } else {
        textColor = window->winGetEnabledTextColor();
        dropColor = window->winGetEnabledTextBorderColor();
    }

    if (text->getFont() != window->winGetFont())
        text->setFont(window->winGetFont());
    text->getSize(&width, &height);
    textPos.x = origin.x + (size.x / 2) - (width / 2);
    textPos.y = origin.y + (size.y / 2) - (height / 2);
    text->setTextColor(textColor, dropColor);
    text->draw(textPos.x, textPos.y, 1, 1);
}

void W3DGadgetRadioButtonDraw(GameWindow *window, WinInstanceData *instData)
{
    Int checkOffsetFromLeft;
    Color backColor, backBorder, boxColor, boxBorder;
    ICoord2D origin, size, start, end;

    window->winGetScreenPosition(&origin.x, &origin.y);
    window->winGetSize(&size.x, &size.y);
    checkOffsetFromLeft = size.x / 16;

    if ((window->winGetStatus() & WIN_STATUS_ENABLED) == FALSE) {
        backColor = GadgetRadioGetDisabledColor(window);
        backBorder = GadgetRadioGetDisabledBorderColor(window);
        if (instData->getState() & WIN_STATE_SELECTED) {
            boxColor = GadgetRadioGetDisabledCheckedBoxColor(window);
            boxBorder = GadgetRadioGetDisabledCheckedBoxBorderColor(window);
        } else {
            boxColor = GadgetRadioGetDisabledUncheckedBoxColor(window);
            boxBorder = GadgetRadioGetDisabledUncheckedBoxBorderColor(window);
        }
    } else if (instData->getState() & WIN_STATE_HILITED) {
        backColor = GadgetRadioGetHiliteColor(window);
        backBorder = GadgetRadioGetHiliteBorderColor(window);
        if (instData->getState() & WIN_STATE_SELECTED) {
            boxColor = GadgetRadioGetHiliteCheckedBoxColor(window);
            boxBorder = GadgetRadioGetHiliteCheckedBoxBorderColor(window);
        } else {
            boxColor = GadgetRadioGetHiliteUncheckedBoxColor(window);
            boxBorder = GadgetRadioGetHiliteUncheckedBoxBorderColor(window);
        }
    } else {
        backColor = GadgetRadioGetEnabledColor(window);
        backBorder = GadgetRadioGetEnabledBorderColor(window);
        if (instData->getState() & WIN_STATE_SELECTED) {
            boxColor = GadgetRadioGetEnabledCheckedBoxColor(window);
            boxBorder = GadgetRadioGetEnabledCheckedBoxBorderColor(window);
        } else {
            boxColor = GadgetRadioGetEnabledUncheckedBoxColor(window);
            boxBorder = GadgetRadioGetEnabledUncheckedBoxBorderColor(window);
        }
    }

    start.x = origin.x; start.y = origin.y;
    {
        Int sx = start.x;
        end.x = (Int)&*(char *)(sx + (UnsignedInt)(char *)size.x);
    }
    end.y = start.y + size.y;
    TheWindowManager->winOpenRect(backBorder, WIN_DRAW_LINE_WIDTH,
                                  start.x, start.y, end.x, end.y);
    start.x++; start.y++; end.x--; end.y--;
    TheWindowManager->winFillRect(backColor, WIN_DRAW_LINE_WIDTH,
                                  start.x, start.y, end.x, end.y);
    {
        Int ox = origin.x;
        start.x = (Int)&*(char *)(ox + (UnsignedInt)(char *)size.y);
    }
    start.y = origin.y;
    end.x = start.x; end.y = start.y + size.y;
    TheWindowManager->winDrawLine(backBorder, WIN_DRAW_LINE_WIDTH,
                                  start.x, start.y, end.x, end.y);
    start.x = origin.x + 1; start.y = origin.y + 1;
    {
        Int ox = origin.x;
        end.x = (Int)&*(char *)(ox + (UnsignedInt)(char *)size.y) - 1;
    }
    end.y = origin.y + size.y - 1;
    TheWindowManager->winFillRect(boxColor, WIN_DRAW_LINE_WIDTH,
                                  start.x, start.y, end.x, end.y);
    start.x = (Int)((char *)(size.x - size.y) + origin.x); start.y = origin.y;
    end.x = start.x; end.y = start.y + size.y;
    TheWindowManager->winDrawLine(backBorder, WIN_DRAW_LINE_WIDTH,
                                  start.x, start.y, end.x, end.y);
    start.x = (Int)((char *)(size.x - size.y) + origin.x); start.y = origin.y + 1;
    end.x = origin.x + size.x - 1; end.y = origin.y + size.y - 1;
    TheWindowManager->winFillRect(boxColor, WIN_DRAW_LINE_WIDTH,
                                  start.x, start.y, end.x, end.y);

    if (instData->getTextLength())
        drawRadioButtonText(window, instData);
}
