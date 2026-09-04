// cl: /DNDEBUG /DWIN32 /MD
// BFME condition template 168: compare the active player count.

typedef bool Bool;

class Parameter
{
public:
    int getInt(void) const { return m_int; }

private:
    unsigned char m_beforeInt[8];
    int m_int;
};

extern void b_000df510();

class PlayerList
{
public:
    int countPlayers(Bool includeObservers)
    {
        typedef int (PlayerList::*CountFn)(Bool);
        union {
            int (*raw)(void);
            CountFn member;
        } fn;
        fn.raw = (int (*)(void))b_000df510;
        return (this->*fn.member)(includeObservers);
    }
};

extern PlayerList *ThePlayerList;

class ScriptConditions
{
protected:
    Bool evaluateCompareNumPlayersInGame(Parameter *, Parameter *);
};

// ?evaluateCompareNumPlayersInGame@ScriptConditions@@IAE_NPAVParameter@@0@Z
Bool ScriptConditions::evaluateCompareNumPlayersInGame(
    Parameter *pComparisonParm, Parameter *pCountParm)
{
    int count = ThePlayerList->countPlayers(false);
    Bool result = false;

    switch (pComparisonParm->getInt()) {
    case 0: result = count < pCountParm->getInt(); break;
    case 1: result = count <= pCountParm->getInt(); break;
    case 2: result = count == pCountParm->getInt(); break;
    case 3: result = count >= pCountParm->getInt(); break;
    case 4: result = count > pCountParm->getInt(); break;
    case 5: result = count != pCountParm->getInt(); break;
    }

    return result;
}
