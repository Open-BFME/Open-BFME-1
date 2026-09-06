// cl: /DNDEBUG /DWIN32 /MD /EHsc /O2 /Ob0
// Open-BFME: clean reconstruction of the BFME MainMenuMedium transition init.
// The retail body is the 293-byte boundary at 0x0059E320.  Its fields are the
// BFME layout proven by the adjacent medium update body: frame bounds at +10
// and +14, the normal window at +0c, and the medium grow window at +44.

typedef int Int;
typedef bool Bool;
typedef int NameKeyType;

extern const char g_bfmeEmptyAscii[];

template <typename T>
class StringBase
{
public:
    void set(const StringBase<T> &source);
    void concat(const T *text, Int length);
    void releaseBuffer();
};

class AsciiString
{
public:
    AsciiString &operator=(const AsciiString &source)
    {
        ((StringBase<char> *)this)->set(*(const StringBase<char> *)&source);
        return *this;
    }

    ~AsciiString()
    {
        ((StringBase<char> *)this)->releaseBuffer();
    }

public:
    char *m_text;
};

class GameWindow;

class WinInstanceData
{
public:
    unsigned char m_unreconstructed_00[0x18c];
    AsciiString m_decoratedNameString;
};

class GameWindow
{
public:
    Int winGetSize(Int *x, Int *y);
    Int winGetScreenPosition(Int *x, Int *y);
    WinInstanceData *winGetInstanceData();
};

class NameKeyGenerator
{
public:
    NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class GameWindowManager
{
public:
    virtual void slot00(); virtual void slot04(); virtual void slot08();
    virtual void slot0c(); virtual void slot10(); virtual void slot14();
    virtual void slot18(); virtual void slot1c(); virtual void slot20();
    virtual void slot24(); virtual void slot28(); virtual void slot2c();
    virtual void slot30(); virtual void slot34(); virtual void slot38();
    virtual void slot3c(); virtual void slot40(); virtual void slot44();
    virtual void slot48(); virtual void slot4c(); virtual void slot50();
    virtual void slot54(); virtual void slot58(); virtual void slot5c();
    virtual void slot60(); virtual void slot64(); virtual void slot68();
    virtual void slot6c(); virtual void slot70(); virtual void slot74();
    virtual void slot78(); virtual void slot7c(); virtual void slot80();
    virtual void slot84(); virtual void slot88(); virtual void slot8c();
    virtual void slot90(); virtual void slot94(); virtual void slot98();
    virtual void slot9c(); virtual void slota0(); virtual void slota4();
    virtual void slota8(); virtual void slotac(); virtual void slotb0();
    virtual void slotb4(); virtual void slotb8(); virtual void slotbc();
    virtual void slotc0(); virtual void slotc4(); virtual void slotc8();
    virtual void slotcc(); virtual void slotd0(); virtual void slotd4();
    virtual void slotd8();
    virtual GameWindow *winGetWindowFromId(GameWindow *parent, NameKeyType id);
};

extern GameWindowManager *TheWindowManager;

// The retail vtable call at +0x08 is the already matched medium transition
// update slot.  Only this init body is emitted from this TU; the remaining
// virtuals are declaration-only dispatch views, so this source emits no
// fabricated transition table.
class Rva0059E320MainMenuMediumInit
{
public:
    virtual ~Rva0059E320MainMenuMediumInit();
    virtual void init(GameWindow *window);
    virtual void update(Int frame);
    virtual void reverse();
    virtual void draw();
    virtual void skip();

protected:
    unsigned char m_unreconstructed_04[4];
    Bool m_isFinished;
    Bool m_isForward;
    unsigned char m_unreconstructed_0a[2];
    GameWindow *m_win;
    Int m_startFrame;
    Int m_endFrame;
    Int m_posX;
    Int m_posY;
    Int m_sizeX;
    Int m_sizeY;
    Int m_drawState;
    Int m_growPosX;
    Int m_growPosY;
    Int m_growSizeX;
    Int m_growSizeY;
    Int m_incrementSizeX;
    Int m_incrementSizeY;
    GameWindow *m_growWin;
};

// Address-derived owner for the retail MainMenuMediumScaleUpTransition::init body at 0x0059E320.
void Rva0059E320MainMenuMediumInit::init(GameWindow *window)
{
    if (window)
    {
        m_win = window;
        m_win->winGetSize(&m_sizeX, &m_sizeY);
        m_win->winGetScreenPosition(&m_posX, &m_posY);
    }

    AsciiString growWinName = { 0 };
    GameWindow *nameWindow = m_win;
    growWinName = nameWindow->winGetInstanceData()->m_decoratedNameString;
    ((StringBase<char> *)&growWinName)->concat("Medium", 6);
    const char *growWinNameText = *(char **)(void *)&growWinName
        ? *(char **)(void *)&growWinName + 8
        : g_bfmeEmptyAscii;
    m_growWin = TheWindowManager->winGetWindowFromId(
        0, TheNameKeyGenerator->nameToKey(growWinNameText));
    if (!m_growWin)
        return;

    m_growWin->winGetSize(&m_growSizeX, &m_growSizeY);
    m_growWin->winGetScreenPosition(&m_growPosX, &m_growPosY);

    m_isForward = false;
    update(m_startFrame);
    m_isFinished = false;
    m_isForward = 1;

    m_incrementSizeX = (m_growSizeX - m_sizeX) / m_endFrame;
    m_incrementSizeY = (m_growSizeY - m_sizeY) / m_endFrame;
}
