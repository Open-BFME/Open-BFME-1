// ?init@BfmePlayerMapState@@QAEXH_N@Z

typedef int Int;
typedef bool Bool;

class Player
{
public:
    char m_padding[0x2c];
    void *m_mapState;
};

class PlayerList
{
public:
    int unidentified_000df510(Bool includeObservers);
};

// Retail reaches PlayerList::getNthPlayer through ILT thunk 0x00044F30
// (?j_00044f30@@YAXXZ); the call sites therefore name the thunk.
extern void j_00044f30();

class GameLogic;

class GameLogicPortraitShim
{
public:
    Bool isInMultiplayerOrSkirmishGame();
};

class BfmeGlobalState
{
public:
    char m_padding[0xe70];
    int m_goodCommandPoints;
    int m_evilCommandPoints;
    int m_valueE78;
    int m_valueE7C;
    int m_goodCommandPointsAI;
    int m_evilCommandPointsAI;
    int m_goodCommandPointsMP2;
    int m_evilCommandPointsMP2;
    int m_goodCommandPointsMP3;
    int m_evilCommandPointsMP3;
    int m_goodCommandPointsMP4;
    int m_evilCommandPointsMP4;
    int m_valueEA0;
    int m_valueEA4;
    int m_valueEA8;
    int m_valueEAC;
};

class Glo012F1028Type
{
public:
    int j_0000353f();
};

extern PlayerList *ThePlayerList;              // retail [0x012ED748]
// Retail VA 0x012F0898 is the canonical pointer defined in GameLogic.cpp.
extern GameLogic *TheGameLogic;
class GlobalData;

// Retail [0x012ED5C8] is EA's writable GlobalData (Common/GlobalData.cpp); this
// file views the same object through BfmeGlobalState.
extern GlobalData *TheWritableGlobalData;
extern Glo012F1028Type *Glo012F1028;

static __forceinline PlayerList *readPlayersForNewMap()
{
    return ThePlayerList;
}

class BfmePlayerMapState
{
public:
    int m_value00;
    int m_value04;
    int m_value08;
    int m_field;
    int m_value10;
    int m_value14;

    void init(Int field, Bool flag);
};

void BfmePlayerMapState::init(Int field, Bool flag)
{
    if (field < 0 || field >= 0x20)
        return;
    if (!ThePlayerList)
        return;
    if (!TheGameLogic)
        return;

    m_field = field;
    if (((GameLogicPortraitShim *)TheGameLogic)->isInMultiplayerOrSkirmishGame())
    {
        const volatile int *multiplier = &m_value14;
        int count = ThePlayerList->unidentified_000df510(true);
        int x;
        int y;
        if (count >= 7)
        {
            x = ((BfmeGlobalState *)TheWritableGlobalData)->m_valueEAC;
            y = ((BfmeGlobalState *)TheWritableGlobalData)->m_valueEA8;
        }
        else if (count >= 5)
        {
            x = ((BfmeGlobalState *)TheWritableGlobalData)->m_valueEA4;
            y = ((BfmeGlobalState *)TheWritableGlobalData)->m_valueEA0;
        }
        else
        {
            if (count == 4)
            {
                x = ((BfmeGlobalState *)TheWritableGlobalData)->m_evilCommandPointsMP4;
                y = ((BfmeGlobalState *)TheWritableGlobalData)->m_goodCommandPointsMP4;
            }
            else if (count == 3)
            {
                x = ((BfmeGlobalState *)TheWritableGlobalData)->m_evilCommandPointsMP3;
                y = ((BfmeGlobalState *)TheWritableGlobalData)->m_goodCommandPointsMP3;
            }
            else
            {
                x = ((BfmeGlobalState *)TheWritableGlobalData)->m_evilCommandPointsMP2;
                y = ((BfmeGlobalState *)TheWritableGlobalData)->m_goodCommandPointsMP2;
            }
        }

        if (flag)
            m_value04 = x;
        else
            m_value04 = y;
        m_value04 = *multiplier * x + m_value10 * y + m_value04;
        return;
    }

    typedef Player *(PlayerList::*GetNthPlayer)(Int index);
    union { void (*fn)(); GetNthPlayer call; } getNth = { j_00044f30 };
    Player *player = (ThePlayerList->*getNth.call)(m_field);
    if (!player)
        return;

    if (!player->m_mapState)
    {
        if (flag)
        {
            int &globalValue = ((BfmeGlobalState *)TheWritableGlobalData)->m_evilCommandPoints;
            m_value04 = globalValue;
        }
        else
        {
            int &globalValue = ((BfmeGlobalState *)TheWritableGlobalData)->m_goodCommandPoints;
            m_value04 = globalValue;
        }
        if (Glo012F1028)
            m_value04 += Glo012F1028->j_0000353f();
        return;
    }
    else
    {
        if (flag)
        {
            int &globalValue = ((BfmeGlobalState *)TheWritableGlobalData)->m_evilCommandPointsAI;
            m_value04 = globalValue;
        }
        else
        {
            int &globalValue = ((BfmeGlobalState *)TheWritableGlobalData)->m_goodCommandPointsAI;
            m_value04 = globalValue;
        }
    }
}
