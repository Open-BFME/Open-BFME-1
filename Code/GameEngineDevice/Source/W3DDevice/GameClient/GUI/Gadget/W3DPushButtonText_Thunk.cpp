// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHs-c-
typedef int Int;
typedef unsigned int UnsignedInt;
typedef int Color;
typedef unsigned char Bool;

class GameFont;
struct ICoord2D { Int x, y; };

class DisplayString
{
public:
    virtual void unused00(); virtual void unused01(); virtual void unused02();
    virtual Int getTextLength();
    virtual void unused04(); virtual void unused05();
    virtual void setFont(GameFont *);
    virtual GameFont *getFont();
    virtual void setWordWrap(Int);
    virtual void setWordWrapCentered(Bool);
    virtual void setTextColor(Color, Color);
    virtual void unused11(); virtual void unused12(); virtual void unused13();
    virtual void draw(Int, Int, Int, Int);
    virtual void getSize(Int *, Int *);
};

class WinInstanceData
{
public:
    unsigned char pad00[8];
    UnsignedInt state;
    UnsignedInt style;
    UnsignedInt status;
    unsigned char pad14[0x188];
    DisplayString *text;
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
};

enum { WIN_STATUS_ENABLED = 8, WIN_STATE_HILITED = 2, WIN_STATUS_WRAP_CENTERED = 0x40000 };

void getButtonTextColors(GameWindow *window, WinInstanceData *instData,
                         Color *textColor, Color *dropColor)
{
    if (!(window->winGetStatus() & WIN_STATUS_ENABLED)) {
        *textColor = window->winGetDisabledTextColor();
        *dropColor = window->winGetDisabledTextBorderColor();
    } else if (instData->state & WIN_STATE_HILITED) {
        *textColor = window->winGetHiliteTextColor();
        *dropColor = window->winGetHiliteTextBorderColor();
    } else {
        *textColor = window->winGetEnabledTextColor();
        *dropColor = window->winGetEnabledTextBorderColor();
    }
}
