// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/stringinline
// stlport
// Clean C++ reconstruction of ControlBar::populateObserverInfoWindow.
// Retail: 0x004AA200, 923 bytes.  Static GUI globals use their BFME data RVAs.

#include <bitset>

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned int Color;
typedef bool Bool;
#ifndef TRUE
#define TRUE true
#define FALSE false
#endif

// BFME uses STLport's six-word bitset for KindOfMaskType (192 bits).
template <int NUMBITS>
class BitFlags
{
private:
    _STL::bitset<NUMBITS> m_bits;
public:
    enum BogusInitType { kInit = 0 };
    BitFlags() {}
    void clear() { m_bits.reset(); }
    void set(Int i, Int value = 1)
    {
        if (value)
            m_bits._Unchecked_set((size_t)i);
        else
            m_bits._Unchecked_reset((size_t)i);
    }
};
typedef BitFlags<192> KindOfMaskType;
enum
{
    KINDOF_STRUCTURE = 7,
    KINDOF_SCORE = 39,
    KINDOF_SCORE_CREATE = 40,
    KINDOF_SCORE_DESTROY = 41
};

// BFME's by-value UnicodeString is a one-pointer StringBase<unsigned short>
// wrapper.  The inline forwarding constructors/destructor reproduce the
// retail temporary construction and +0x381D0 cleanup calls.
template <typename T>
class StringBase
{
    friend class UnicodeString;
private:
    StringBase() : m_data(0) {}
    StringBase(const T *text);
    StringBase(const StringBase<T> &other);
    ~StringBase();
    void releaseBuffer();
    void *m_data;
};

class UnicodeString : private StringBase<unsigned short>
{
public:
    UnicodeString() : StringBase<unsigned short>() {}
    UnicodeString(const unsigned short *text) : StringBase<unsigned short>(text) {}
    UnicodeString(const UnicodeString &other) : StringBase<unsigned short>(other) {}
    ~UnicodeString() {}
    void __cdecl format(UnicodeString format, ...);
};

class Image;
class PlayerTemplate
{
public:
    const Image *getFlagWaterMarkImage(void) const;
};

class ScoreKeeper
{
public:
    Int getTotalUnitsDestroyed(void);
    Int getTotalUnitsLost(void) const
    {
        return *(const Int *)((const char *)this + 0x90);
    }
};

class Player
{
public:
    Int countObjects(KindOfMaskType setMask, KindOfMaskType clearMask);
    ScoreKeeper *getScoreKeeper(void)
    {
        return (ScoreKeeper *)((char *)this + 0x348);
    }
    UnicodeString getPlayerDisplayName(void);
    Color getPlayerColor(void) const
    {
        return *(const Color *)((const char *)this + 0x1c4);
    }
    const PlayerTemplate *getPlayerTemplate(void) const
    {
        return *(const PlayerTemplate *const *)((const char *)this + 4);
    }
};

class GameWindow
{
public:
    Bool winIsHidden(void);
    Int winHide(Bool hide);
    Int winSetEnabledImage(Int index, const Image *image);
    void winSetEnabledTextColors(Int color, Int borderColor);
};

void GadgetStaticTextSetText(GameWindow *window, UnicodeString text);

class ControlBar
{
public:
    void populateObserverInfoWindow(void);
    void populateObserverList(void);
};

struct BfmeControlBarObserverView
{
    char pad00[0x274];
    Player *m_observerLookAtPlayer;
};

inline Color GameMakeColor(Int red, Int green, Int blue, Int alpha)
{
    return ((Color)(red & 0xff) << 0) |
           ((Color)(green & 0xff) << 8) |
           ((Color)(blue & 0xff) << 16) |
           ((Color)(alpha & 0xff) << 24);
}

// The initObserverControls body establishes these exact BFME data slots.
#define BFME_WINDOW_AT(rva) (*(GameWindow **)(rva))
#define ObserverPlayerInfoWindow BFME_WINDOW_AT(0x012F358C)
#define ObserverPlayerListWindow BFME_WINDOW_AT(0x012F3590)
#define staticTextNumberOfUnits BFME_WINDOW_AT(0x012F35E0)
#define staticTextNumberOfBuildings BFME_WINDOW_AT(0x012F35E4)
#define staticTextNumberOfUnitsKilled BFME_WINDOW_AT(0x012F35E8)
#define staticTextNumberOfUnitsLost BFME_WINDOW_AT(0x012F35EC)
#define staticTextPlayerName BFME_WINDOW_AT(0x012F35F0)
#define winFlag BFME_WINDOW_AT(0x012F35D8)
#define winGeneralPortrait BFME_WINDOW_AT(0x012F35DC)

void ControlBar::populateObserverInfoWindow(void)
{
    BfmeControlBarObserverView *self = (BfmeControlBarObserverView *)this;

    if (ObserverPlayerInfoWindow->winIsHidden())
        return;

    if (!self->m_observerLookAtPlayer)
    {
        ObserverPlayerInfoWindow->winHide(TRUE);
        ObserverPlayerListWindow->winHide(FALSE);
        populateObserverList();
        return;
    }

    UnicodeString uString;
    KindOfMaskType mask, clearMask;
    mask.set(KINDOF_SCORE);
    clearMask.set(KINDOF_STRUCTURE);

    uString.format(L"%d", self->m_observerLookAtPlayer->countObjects(mask, clearMask));
    GadgetStaticTextSetText(staticTextNumberOfUnits, uString);

    Int numBuildings = 0;
    mask.clear();
    mask.set(KINDOF_SCORE);
    mask.set(KINDOF_STRUCTURE);
    clearMask.clear();
    numBuildings = self->m_observerLookAtPlayer->countObjects(mask, clearMask);
    mask.clear();
    mask.set(KINDOF_SCORE_CREATE);
    mask.set(KINDOF_STRUCTURE);
    numBuildings += self->m_observerLookAtPlayer->countObjects(mask, clearMask);
    mask.clear();
    mask.set(KINDOF_SCORE_DESTROY);
    mask.set(KINDOF_STRUCTURE);
    numBuildings += self->m_observerLookAtPlayer->countObjects(mask, clearMask);

    uString.format(L"%d", numBuildings);
    GadgetStaticTextSetText(staticTextNumberOfBuildings, uString);

    uString.format(L"%d", self->m_observerLookAtPlayer->getScoreKeeper()->getTotalUnitsDestroyed());
    GadgetStaticTextSetText(staticTextNumberOfUnitsKilled, uString);

    uString.format(L"%d", self->m_observerLookAtPlayer->getScoreKeeper()->getTotalUnitsLost());
    GadgetStaticTextSetText(staticTextNumberOfUnitsLost, uString);

    GadgetStaticTextSetText(staticTextPlayerName, self->m_observerLookAtPlayer->getPlayerDisplayName());
    Color color = self->m_observerLookAtPlayer->getPlayerColor();
    staticTextPlayerName->winSetEnabledTextColors(color, GameMakeColor(0, 0, 0, 255));
    winFlag->winSetEnabledImage(0, self->m_observerLookAtPlayer->getPlayerTemplate()->getFlagWaterMarkImage());
    winGeneralPortrait->winHide(FALSE);
}


