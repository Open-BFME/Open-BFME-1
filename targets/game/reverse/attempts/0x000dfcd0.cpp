// ?bfmeTail938A@BfmeGlob938A@@QAEXH@Z
// partial score=0.39 date=2026-09-20
// cl: /DNDEBUG /MD /EHsc
// BFME-only observer-player cycling method.  The receiver global is the same
// address as ThePlayers; the address-derived class/name is retained because
// no surviving header supplies the original method name.

template<class T> struct StringData { int refs; unsigned short len, cap; T text[1]; };
template<class T> class StringBase {
    friend class UnicodeString;
    StringData<T> *data;
    StringBase(): data(0) {}
    StringBase(const StringBase&);
    ~StringBase();
};
class UnicodeString : private StringBase<unsigned short> {
public:
    UnicodeString() {}
    UnicodeString(const UnicodeString& s): StringBase<unsigned short>(s) {}
    ~UnicodeString() {}
    void __cdecl format(UnicodeString, ...);
};

class PlayerTemplate {
public:
    UnicodeString getDisplayName() const;
};

class Player {
public:
    bool isPlayerActive() const;
    UnicodeString getPlayerDisplayName();

    unsigned char pad00[4];
    PlayerTemplate *playerTemplate;
    unsigned char pad08[0x1c];
    int playerIndex;
    unsigned char pad28[4];
    int field2c;
};

class GameTextInterface {
public:
    virtual void slot00() = 0; virtual void slot04() = 0;
    virtual void slot08() = 0; virtual void slot0c() = 0;
    virtual void slot10() = 0; virtual void slot14() = 0;
    virtual void slot18() = 0; virtual void slot1c() = 0;
    virtual void slot20() = 0; virtual void slot24() = 0;
    virtual UnicodeString fetch(const char *, bool *) = 0;
};

class InGameUI {
public:
    virtual void slot00() = 0; virtual void slot04() = 0;
    virtual void slot08() = 0; virtual void slot0c() = 0;
    virtual void slot10() = 0; virtual void slot14() = 0;
    virtual void slot18() = 0; virtual void slot1c() = 0;
    virtual void slot20() = 0; virtual void slot24() = 0;
    virtual void slot28() = 0; virtual void slot2c() = 0;
    virtual void slot30() = 0; virtual void slot34() = 0;
    virtual void slot38() = 0; virtual void slot3c() = 0;
    virtual void showMessage(UnicodeString) = 0;
};

typedef void (*RefreshProc3)(int, int, int);
typedef void (*RefreshProc0)();
class ShroudManager { public: void m_008F7380(int, RefreshProc3); };
class TaintManager { public: void m(RefreshProc0); };

struct ControlBarView {
    unsigned char pad[0x274];
    Player *observerLookAtPlayer;
};
struct LogicView { unsigned char pad[0x10c]; int mode; };

extern GameTextInterface *TheGameText;
extern InGameUI *TheInGameUI;
extern ControlBarView *TheControlBar;
extern LogicView *TheBfmeGameLogic;
extern ShroudManager *TheShroudManager;
extern TaintManager *TheTaintManager;
void d_0003f431(int, int, int);
void d_0001d98a();

class SubsystemInterface {
public:
    virtual ~SubsystemInterface();
private:
    void *name;
};
class Snapshot {
public:
    ~Snapshot() {}
    virtual void crc() = 0;
    virtual void xfer() = 0;
    virtual void loadPostProcess() = 0;
};

class BfmeGlob938A : public SubsystemInterface, public Snapshot {
public:
    void bfmeTail938A(int forward);
    void destroyNotify(Player *player);

    Player *m_local;
    int m_playerCount;
    Player *m_players[32];
};

extern BfmeGlob938A *g_bfme938GlobA;

void BfmeGlob938A::bfmeTail938A(int forward)
{
    if (m_local->isPlayerActive())
        return;

    Player *selected = g_bfme938GlobA->m_local;
    if (!selected->isPlayerActive() && TheControlBar && TheControlBar->observerLookAtPlayer)
        selected = TheControlBar->observerLookAtPlayer;
    if (!selected || TheBfmeGameLogic->mode == 8 || TheBfmeGameLogic->mode == 4)
        return;

    const int step = forward ? 1 : -1;
    const int start = selected->playerIndex;
    int fallback = selected->isPlayerActive() ? -1 : selected->playerIndex;
    for (int i = 0; i < g_bfme938GlobA->m_playerCount; ++i) {
        Player *candidate = g_bfme938GlobA->m_players[i];
        if (fallback == -1 && candidate && !candidate->isPlayerActive() &&
            candidate->field2c == 0)
            fallback = 0;
    }

    int index = start;
    for (;;) {
        index += step;
        if (index >= g_bfme938GlobA->m_playerCount) index = 0;
        else if (index < 0) index = g_bfme938GlobA->m_playerCount;
        if (index == start) break;
        if (index >= 0 && index < 32) {
            Player *candidate = g_bfme938GlobA->m_players[index];
            if (!candidate || candidate->field2c != 0)
                continue;
            if (!candidate->isPlayerActive() || index != fallback)
                break;
        }
    }

    selected = (index >= 0 && index < 32) ? g_bfme938GlobA->m_players[index] : 0;

    TheControlBar->observerLookAtPlayer = selected;
    UnicodeString message;
    if (!selected->isPlayerActive()) {
        message.format(TheGameText->fetch("GUI:PlayerObservingAll", 0));
    } else {
        UnicodeString side = selected->playerTemplate->getDisplayName();
        UnicodeString player = selected->getPlayerDisplayName();
        message.format(TheGameText->fetch("GUI:PlayerObservingSpecificHuman", 0),
                       side, player);
    }
    TheInGameUI->showMessage(message);
    if (TheShroudManager)
        TheShroudManager->m_008F7380(selected->playerIndex, d_0003f431);
    if (TheTaintManager)
        TheTaintManager->m(d_0001d98a);
    destroyNotify(selected);
}
