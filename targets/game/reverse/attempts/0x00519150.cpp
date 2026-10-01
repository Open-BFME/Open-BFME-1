// ?rva00519150@BfmeAptScreenLanLobby@@QAEHXZ
// partial score=0.9853 date=2026-10-01
// Retail vtable 0x01105A78 slot 5 (int return); only the tail game slot differs.
// Retail shares the tail game slot with case 7's game; ours gives it its own.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

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
    char *bfmeBuildAN(unsigned int, const char *, int, int, int, int, int, int);
};

extern BfmeLevelAN *g_theWindowManager;

class MpGameSetup
{
public:
    bool flushPendingUpdates();

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

void j_0003c065();

void GadgetListBoxGetSelected(GameWindow *, int *);
int GadgetListBoxAddEntryText(GameWindow *, UnicodeString, int, int, int, bool);
GameWindow *MessageBoxOk(UnicodeString, UnicodeString, void (*)(void));
void SignalUIInteraction(int);

class BfmeGlobal_012f19e8
{
public:
    void bfmeCall_000290d2();
};

extern BfmeGlobal_012f19e8 *g_bfmeManager;

class BfmeAptScreenLanLobby
{
public:
    bool initLanRva00517D00();
    bool callSelection(int row, GameInfo **item)
    {
        return rva00516850(row, item);
    }
    bool rva00516850(int, GameInfo **);
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

extern BfmeAptScreenLanLobby *g_bfme935GlobC;

int BfmeAptScreenLanLobby::rva00519150()
{
    if (m_tail.m_flag4)
    {
        m_state.flushPendingUpdates();
        return 0;
    }

    if (TheLAN)
        TheLAN->slot05();

    GameInfo *games[1];
    switch (m_3a8)
    {
    case 0:
        if (!((BfmeAptScreenLanLobby *)this)->initLanRva00517D00())
            break;
        {
            unsigned int actionOwner = (unsigned int)m_actionOwner;
            g_theWindowManager->bfmeBuildAN(actionOwner,
            "StartLobby", 0, 0, 0, 0, 0, 0);
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
            g_theWindowManager->bfmeBuildAN(actionOwner,
                "EnablePlayGame", 0, 0, 0, 0, 0, 0);
        }
        break;

    case 7:
    {
        ((Rva0051A5A0Host *)this)->setup(0);
        m_3a8 = 1;
        int selected = -1;
        GadgetListBoxGetSelected(m_customGamesList, &selected);
        {
            games[0] = 0;
            if (callSelection(selected, &games[0]))
            {
                m_3a8 = 8;
                BfmeNetAddress address;
                TheLAN->RequestGameJoin((LANGameInfo *)games[0], &address);
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
        games[0] = 0;
        callSelection(selected, &games[0]);
    }

    if (TheGameLogic->m_gameState == 4 && TheGameLogic->m_gameMode == 1)
        SignalUIInteraction(0x1c);

    if (m_tail.m_flag2 == true)
    {
        m_tail.m_flag2 = false;
        MessageBoxOk(
            TheGameText->fetch("GUI:NetworkError", 0),
            TheGameText->fetch("GUI:SocketError", 0), 0);
        if (g_bfme935GlobC)
            g_bfmeManager->bfmeCall_000290d2();
    }

    m_state.flushPendingUpdates();
    return 1;
}
