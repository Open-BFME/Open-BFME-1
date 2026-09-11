// ?bfmeNewMap@BfmePlayerMapState@@QAEXH_N@Z

typedef int Int;
typedef bool Bool;

#pragma comment(linker, "/alternatename:?getNthPlayer@PlayerList@@QAEPAVPlayer@@H@Z=?j_00044f30@@YAXXZ")

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
    Player *getNthPlayer(Int index);
};

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
    int m_valueE70;
    int m_valueE74;
    int m_valueE78;
    int m_valueE7C;
    int m_valueE80;
    int m_valueE84;
    int m_valueE88;
    int m_valueE8C;
    int m_valueE90;
    int m_valueE94;
    int m_valueE98;
    int m_valueE9C;
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

extern PlayerList * volatile Rva002EE330ThePlayers;
extern GameLogic *TheBfmeGameLogic;
extern BfmeGlobalState *TheWritableGlobalData;
extern Glo012F1028Type *Glo012F1028;

static __forceinline PlayerList *readPlayersForNewMap()
{
    return *(PlayerList * volatile *)0x012ED748;
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

    void bfmeNewMap(Int field, Bool flag);
};

void BfmePlayerMapState::bfmeNewMap(Int field, Bool flag)
{
    if (field < 0 || field >= 0x20)
        return;
    if (!Rva002EE330ThePlayers)
        return;
    if (!TheBfmeGameLogic)
        return;

    m_field = field;
    if (((GameLogicPortraitShim *)TheBfmeGameLogic)->isInMultiplayerOrSkirmishGame())
    {
        const volatile int *multiplier = &m_value14;
        int count = Rva002EE330ThePlayers->unidentified_000df510(true);
        int x;
        int y;
        if (count >= 7)
        {
            x = TheWritableGlobalData->m_valueEAC;
            y = TheWritableGlobalData->m_valueEA8;
        }
        else if (count >= 5)
        {
            x = TheWritableGlobalData->m_valueEA4;
            y = TheWritableGlobalData->m_valueEA0;
        }
        else
        {
            if (count == 4)
            {
                x = TheWritableGlobalData->m_valueE9C;
                y = TheWritableGlobalData->m_valueE98;
            }
            else if (count == 3)
            {
                x = TheWritableGlobalData->m_valueE94;
                y = TheWritableGlobalData->m_valueE90;
            }
            else
            {
                x = TheWritableGlobalData->m_valueE8C;
                y = TheWritableGlobalData->m_valueE88;
            }
        }

        if (flag)
            m_value04 = x;
        else
            m_value04 = y;
        m_value04 = *multiplier * x + m_value10 * y + m_value04;
        return;
    }

    Player *player = Rva002EE330ThePlayers->getNthPlayer(m_field);
    if (!player)
        return;

    if (!player->m_mapState)
    {
        if (flag)
        {
            int &globalValue = TheWritableGlobalData->m_valueE74;
            m_value04 = globalValue;
        }
        else
        {
            int &globalValue = TheWritableGlobalData->m_valueE70;
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
            int &globalValue = TheWritableGlobalData->m_valueE84;
            m_value04 = globalValue;
        }
        else
        {
            int &globalValue = TheWritableGlobalData->m_valueE80;
            m_value04 = globalValue;
        }
    }
}
