// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// ?getGameInfoRva00516850@BfmeAptScreenLanLobby@@QAE_NHPAPAX@Z 0x00516850 239 B
// ?rva00519150@BfmeAptScreenLanLobby@@QAEHXZ 0x00519150 884 B
// Name: the matched caller BfmeAptScreenLanLobby::rva00518610
// (BfmeAptScreenLanLobby_rva00518610.cpp) declares and calls it for both
// list-box messages; RET 8 and the INT3 after +0xEE close the extent.
//
// Looks up the game under list row `index`, clears it when TheLAN no longer
// knows it, and toggles the join button through the scripted-UI forwarder:
// enabled (bit 2 of +0x3D4 set) while the game has fewer players than open
// slots, disabled otherwise. Source shape that reproduces retail:
// - one `return ok` at the end with `ok = true` as the last statement of the
//   enable arm keeps `ok` in BL for the disable paths while the enable path
//   returns a literal 1 and reuses EBX for the constant 2;
// - the game test wraps the player-count compare, so the compare's else arm
//   gets its own disable copy (the +0x3D4 byte load hoisted above the jge)
//   while the missing-game path shares the first copy.

//
// rva00519150: retail vtable 0x01105A78 slot 5 (int return); RET at +0x34B,
// ten-entry jump table +0x34C..+0x373, INT3 at +0x374. Retail's TU defines
// getGameInfoRva00516850 beside it, and the caller's frame depends on that:
// with the callee's body visible (never inlined, it is too large), &game no
// longer escapes, so VC7.1 packs case 7's and the tail's block-scoped game
// locals onto one slot. The selected rows escape into the opaque
// GadgetListBoxGetSelected, so they keep their own. With the callee only
// declared the frame is 0x18 (14 B off). Handoff:
// targets/game/reverse/attempt_support/20261106-00519150-lanlobby-update-visible-callee.md.

template <typename T> class StringBase
{
    friend class UnicodeString;

private:
    StringBase() : m_data(0) {}
    StringBase(const T *text);
    StringBase(const StringBase<T> &other);
    ~StringBase();

    void *m_data;
};

class UnicodeString : private StringBase<unsigned short>
{
public:
    UnicodeString() : StringBase<unsigned short>() {}
    UnicodeString(const unsigned short *text)
        : StringBase<unsigned short>(text) {}
    UnicodeString(const UnicodeString &other)
        : StringBase<unsigned short>(other) {}
    ~UnicodeString() {}
};

class GameWindow;
class GameInfo
{
public:
    virtual void slot00();
    virtual void slot01();
    virtual void slot02();
    virtual void slot03();
    virtual void slot04();
    virtual int getLocalSlotNum() const;
    int getNumPlayers(void) const;
};

class LANGameInfo : public GameInfo
{
};

struct BfmeNetAddress
{
    BfmeNetAddress() : m_ip(0), m_port(0) {}

    unsigned int m_ip;
    unsigned short m_port;
};

class LANAPI
{
public:
    virtual void slot00(); virtual void slot01(); virtual void slot02();
    virtual void slot03(); virtual void slot04(); virtual void slot05();
    virtual void slot06(); virtual void slot07(); virtual void slot08();
    virtual void slot09(); virtual void slot10();
    virtual void RequestGameJoin(LANGameInfo *, BfmeNetAddress *);
    virtual void slot12(); virtual void slot13(); virtual void slot14();
    virtual void slot15(); virtual void slot16(); virtual void slot17();
    virtual void slot18(); virtual void slot19(); virtual void slot20();
    virtual void slot21();
    virtual void slot22(UnicodeString, bool);
    virtual void slot23(); virtual void slot24(); virtual void slot25();
    virtual void slot26(); virtual void slot27(); virtual void slot28();
    virtual void slot29(); virtual void slot30(); virtual void slot31();
    virtual void slot32(); virtual void slot33(); virtual void slot34();
    virtual void slot35(); virtual void slot36(); virtual void slot37();
    virtual void slot38(); virtual void slot39(); virtual void slot40();
    virtual void slot41(); virtual void slot42(); virtual void slot43();
    virtual void slot44(); virtual void slot45(); virtual void slot46();
    virtual void slot47();
    virtual LANGameInfo *GetMyGame();
};

extern LANAPI *TheLAN;
extern const unsigned short g_Rva01088AF4EmptyWideString[];

class GameTextInterface
{
public:
    virtual void slot00(); virtual void slot01(); virtual void slot02();
    virtual void slot03(); virtual void slot04(); virtual void slot05();
    virtual void slot06(); virtual void slot07(); virtual void slot08();
    virtual void slot09();
    virtual UnicodeString fetch(const char *, bool *exists = 0);
};

extern GameTextInterface *TheGameText;

class GameLogic
{
public:
    char m_pad03c[0x3c];
    int m_gameMode;
    char m_pad040[0xcc];
    int m_gameState;
};

extern GameLogic *TheGameLogic;
extern int chatSystemColor;

class BfmeLevelAN
{
public:
    char *bfmeBuildAN(unsigned int a, int b, int c, int d, int e, int f, int g, int h);
};

class BfmeR1078;
extern BfmeR1078 *g_bfmeR1078;

// The state object at +0x25C is one class that the ledger knows under two
// placeholder names: its pending-update dispatcher 0x0052AD00 is matched as
// SkirmishScreenState::flushPendingUpdates, and 0x00527930/0x005280A0 as
// MpGameSetup methods.
class SkirmishScreenState
{
public:
    bool flushPendingUpdates();
};

class MpGameSetup
{
public:
    bool flushPendingUpdates() { return ((SkirmishScreenState *)this)->flushPendingUpdates(); }

    bool callWithInt(int value) { return rva00527930(value != 0); }
    bool callNoArg() { return rva005280A0(); }

private:
    char m_extent[0x134];
public:
    bool rva00527930(bool value);
    bool rva005280A0();
};

class BfmeQ1072
{
public:
    void bfmeGo1072C(char);
};

class BfmeQ1073
{
public:
    void bfmeGo1073A(char);
};

class Rva0051A5A0Host
{
public:
    void setup(int);
};

class BfmeA1061
{
public:
    void bfmeGo1061A();
};


void GadgetListBoxGetSelected(GameWindow *, int *);
int GadgetListBoxAddEntryText(GameWindow *, UnicodeString, int, int, int, bool);
GameWindow *MessageBoxOk(UnicodeString, UnicodeString, void (*)(void));
void SignalUIInteraction(int);

class BfmeGlobal_012f19e8
{
public:
    void bfmeCall_000290d2();
};


class BfmeAptScreenLanLobby
{
public:
    bool initLanRva00517D00();
    bool getGameInfoRva00516850(int index, void **game);
    int rva00519150();

private:
    char m_head[0x250];
    void *m_actionOwner;
    char m_gap254[8];
    MpGameSetup m_state;
    char m_gap390[0x18];
    int m_3a8;
    int m_3ac;
    GameWindow *m_chat;
    GameWindow *m_customGamesList;
    int m_3b8;
    int m_3bc;

    struct LanLobbyTail
    {
        void *m_vptr;
        char m_base[8];
        int m_value;
        bool m_flag0;
        bool m_flag1;
        bool m_flag2;
        bool m_flag3;
        int m_kind;
        bool m_flag4;
        char m_pad[3];
    } m_tail;
};

extern BfmeAptScreenLanLobby *g_rva012F4998LanLobby;

int BfmeAptScreenLanLobby::rva00519150()
{
    if (m_tail.m_flag4)
    {
        m_state.flushPendingUpdates();
        return 0;
    }

    if (TheLAN)
        TheLAN->slot05();

    switch (m_3a8)
    {
    case 0:
        if (!((BfmeAptScreenLanLobby *)this)->initLanRva00517D00())
            break;
        {
            unsigned int actionOwner = (unsigned int)m_actionOwner;
            ((BfmeLevelAN *)g_bfmeR1078)->bfmeBuildAN(actionOwner,
            (int)"StartLobby", 0, 0, 0, 0, 0, 0);
        }
        m_3a8 = 1;
        ((BfmeQ1072 *)this)->bfmeGo1072C(1);
        ((BfmeQ1073 *)this)->bfmeGo1073A(2);
        ((Rva0051A5A0Host *)this)->setup(1);
        m_tail.m_flag4 = false;
        break;

    case 2:
        ((Rva0051A5A0Host *)this)->setup(0);
        m_3a8 = 3;
        TheLAN->slot22(UnicodeString(g_Rva01088AF4EmptyWideString),
            false);
        break;

    case 5:
        if (m_state.callWithInt(1))
        {
            m_3a8 = 6;
            break;
        }
        goto launchPlay;
    case 6:
        if (m_state.callNoArg())
            break;
    launchPlay:
        {
            unsigned int actionOwner = (unsigned int)m_actionOwner;
            m_3a8 = 4;
            ((BfmeLevelAN *)g_bfmeR1078)->bfmeBuildAN(actionOwner,
                (int)"EnablePlayGame", 0, 0, 0, 0, 0, 0);
        }
        break;

    case 7:
    {
        ((Rva0051A5A0Host *)this)->setup(0);
        m_3a8 = 1;
        int selected = -1;
        GadgetListBoxGetSelected(m_customGamesList, &selected);
        {
            GameInfo *game = 0;
            if (getGameInfoRva00516850(selected, (void **)&game))
            {
                m_3a8 = 8;
                BfmeNetAddress address;
                TheLAN->RequestGameJoin((LANGameInfo *)game, &address);
                break;
            }
        }
        GadgetListBoxAddEntryText(m_chat,
            TheGameText->fetch("GUI:GSKickedGameFull", 0),
            chatSystemColor, -1, 0, true);
        break;
    }

    case 9:
    {
        LANGameInfo *game = TheLAN->GetMyGame();
        if (game == 0 || game->getLocalSlotNum() == -1)
        {
            MessageBoxOk(
                TheGameText->fetch("GUI:GSErrorTitle", 0),
                TheGameText->fetch("GUI:GSKicked", 0), 0);
            ((BfmeA1061 *)this)->bfmeGo1061A();
            m_3a8 = 0;
        }
        break;
    }
    }

    if (m_customGamesList)
    {
        int selected = -1;
        GadgetListBoxGetSelected(m_customGamesList, &selected);
        GameInfo *game = 0;
        getGameInfoRva00516850(selected, (void **)&game);
    }

    if (TheGameLogic->m_gameState == 4 && TheGameLogic->m_gameMode == 1)
        SignalUIInteraction(0x1c);

    if (m_tail.m_flag2 == true)
    {
        m_tail.m_flag2 = false;
        MessageBoxOk(
            TheGameText->fetch("GUI:NetworkError", 0),
            TheGameText->fetch("GUI:SocketError", 0), 0);
        if (g_rva012F4998LanLobby)
            ((BfmeGlobal_012f19e8 *)g_bfmeR1078)->bfmeCall_000290d2();
    }

    m_state.flushPendingUpdates();
    return 1;
}

void *GadgetListBoxGetItemData(GameWindow *window, int row, int column);
struct Rva00685200Node;
class Rva00685200
{
public:
    bool has(Rva00685200Node *p);
};
class Rva0061EE90GameInfo
{
public:
    int countNonClosed(void) const;
};
extern char g_bfmeFmtB1073[];
extern char g_bfmeFmt1078[];

bool BfmeAptScreenLanLobby::getGameInfoRva00516850(int index, void **game)
{
    bool ok = false;
    *game = GadgetListBoxGetItemData(m_customGamesList, index, 0);
    if (!((Rva00685200 *)TheLAN)->has((Rva00685200Node *)*game))
        *game = 0;
    if (*game)
    {
        int players = ((GameInfo *)*game)->getNumPlayers();
        if (players < ((Rva0061EE90GameInfo *)*game)->countNonClosed())
        {
            if (!(m_tail.m_kind & 2))
            {
                ((BfmeLevelAN *)g_bfmeR1078)->bfmeBuildAN((unsigned int)m_actionOwner, (int)g_bfmeFmt1078, 0, 0, 0, 0, 0, 0);
                m_tail.m_kind |= 2;
            }
            ok = true;
        }
        else if (m_tail.m_kind & 2)
        {
            ((BfmeLevelAN *)g_bfmeR1078)->bfmeBuildAN((unsigned int)m_actionOwner, (int)g_bfmeFmtB1073, 0, 0, 0, 0, 0, 0);
            m_tail.m_kind &= ~2;
        }
    }
    else if (m_tail.m_kind & 2)
    {
        ((BfmeLevelAN *)g_bfmeR1078)->bfmeBuildAN((unsigned int)m_actionOwner, (int)g_bfmeFmtB1073, 0, 0, 0, 0, 0, 0);
        m_tail.m_kind &= ~2;
    }
    return ok;
}
