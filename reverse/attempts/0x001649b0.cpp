// ?isAGoodIdeaToBuildTeam@AIPlayer@@MAE_NPAVTeamPrototype@@@Z
// partial score=0.957 date=2026-09-23
// ?isAGoodIdeaToBuildTeam@AIPlayer@@MAE_NPAVTeamPrototype@@@Z
// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x001649B0, 486 bytes. IDENTITY CORRECTION: this is AIPlayer's
// override, not AISkirmishPlayer's. Slot 25 of vtable 0x010968B0 (pinned
// ??_7AIPlayer@@6B@; slot 0 reaches ??_GAIPlayer) jumps through ILT
// 0x000320EC to this body, while slot 25 of 0x01096FB0 (??_7AISkirmishPlayer,
// installed by ??0AISkirmishPlayer at 0x00168660) holds ILT 0x0001272E ->
// 0x00168AE0, the landed "Rva00168AE0TeamBuildCheckOwner" body. The body sits
// in the AIPlayer.cpp run (isPossibleToBuildTeam 0x001645B0, dump 0x00164750).
// NOTE: the ledger already spends ?isAGoodIdeaToBuildTeam@AIPlayer@@ on a naked
// lift at 0x00167E80 (786 B); that row needs review before this can land.
//
// Callees are the ledger names: TeamPrototype::evaluateProductionCondition,
// countTeamInstances, AIPlayer::isPossibleToBuildTeam, ScriptEngine::
// AppendDebugMessage, Gen_001604e0::m (queue next) and the dump
// ?d_00164750@@YAXXZ through the neighbours' typed union cast.
//
// STATE: 486/486, 21 non-relocation bytes. Retail packs the first message,
// needMoney and the second arg-temp tracker into the dead proto argument slot
// (frame 8); this compiler gives that slot to needMoney alone (frame 0xC),
// which is exactly what retail did for the AISkirmishPlayer copy at
// 0x00168AE0. A micro test shows the first message does take the proto slot
// when needMoney is absent. Block-scoping needMoney, an else block, a
// parameter copy, DLINK_ITERATOR, and /Ob and /O flag variants do not move it.

typedef bool Bool;
typedef int Int;

extern char Rva006A16B0Empty[];

template <typename T>
class StringBase
{
    friend class AsciiString;

    struct Data
    {
        int m_refCount;
        int m_length;
        T m_text[1];
    };

private:
    StringBase() : m_data(0) {}
    StringBase(const T *text);
    StringBase(const StringBase &other);
    ~StringBase();
    Data *m_data;
};

class AsciiString : private StringBase<char>
{
public:
    AsciiString() : StringBase<char>() {}
    AsciiString(const char *text) : StringBase<char>(text) {}
    AsciiString(const AsciiString &other) : StringBase<char>(other) {}
    ~AsciiString() {}
    void format(AsciiString fmt, ...);

    const char *str() const
    {
        return m_data != 0 ? m_data->m_text : Rva006A16B0Empty;
    }
};

class TeamPrototype;
class Team;

// ?m@Gen_001604e0@@QAEHXZ
class Gen_001604e0
{
public:
    int m();
};

class TeamInQueue
{
public:
    TeamInQueue *getNext() { return (TeamInQueue *)((Gen_001604e0 *)this)->m(); }
    char m_pad[0x1c];
    Team *m_team;
};

class TeamPrototypeInfo
{
public:
    char m_pad[4];
    Int m_maxInstances;
};

class TeamPrototype
{
public:
    Bool evaluateProductionCondition();
    Int countTeamInstances();

    const TeamPrototypeInfo *getTemplateInfo() const
    {
        return (const TeamPrototypeInfo *)((const char *)this + 0x1c0);
    }

    const AsciiString &getName() const
    {
        return m_name;
    }

private:
    char m_pad[0x14];
    AsciiString m_name;
};

class Team
{
public:
    TeamPrototype *getPrototype() const
    {
        return *(TeamPrototype **)((const char *)this + 4);
    }
};

class GlobalData
{
public:
    char m_pad[0xa88];
    Int m_debugAI;
};

class ScriptEngine
{
public:
    void AppendDebugMessage(const AsciiString &message, Bool forcePause);
};

extern void d_00164750();

class AIPlayer
{
protected:
    virtual Bool isAGoodIdeaToBuildTeam(TeamPrototype *proto);
    Bool isPossibleToBuildTeam(TeamPrototype *proto, Bool requireIdleFactory,
        Bool &notEnoughMoney);
    Bool rva00164750Check(TeamPrototype *proto)
    {
        // retail 0x00164750 is still the dump ?d_00164750@@YAXXZ
        typedef Bool (AIPlayer::*Call)(TeamPrototype *);
        union { void (*raw)(); Call member; } call;
        call.raw = d_00164750;
        return (this->*call.member)(proto);
    }

    TeamInQueue *m_teamBuildQueue;
};



extern GlobalData *TheWritableGlobalData;
extern ScriptEngine *TheScriptEngine;

// ?isAGoodIdeaToBuildTeam@AIPlayer@@MAE_NPAVTeamPrototype@@@Z
Bool AIPlayer::isAGoodIdeaToBuildTeam(TeamPrototype *proto)
{
    if (!proto->evaluateProductionCondition())
        return false;

    if (proto->countTeamInstances() >= proto->getTemplateInfo()->m_maxInstances)
    {
        if (TheWritableGlobalData->m_debugAI)
        {
            AsciiString str;
            str.format(AsciiString("Team %s not chosen - %d already exist."),
                proto->getName().str(), proto->countTeamInstances());
            TheScriptEngine->AppendDebugMessage(str, false);
        }
        return false;
    }

    for (TeamInQueue *team = m_teamBuildQueue; team; team = team->getNext())
    {
        if (team->m_team->getPrototype() == proto)
            return false;
    }

    if (rva00164750Check(proto))
        return true;

    Bool needMoney;
    if (!isPossibleToBuildTeam(proto, true, needMoney))
    {
        if (TheWritableGlobalData->m_debugAI)
        {
            AsciiString str;
            if (needMoney)
                str.format(AsciiString("Team %s not chosen - Not enough money."), proto->getName().str());
            else
                str.format(AsciiString("Team %s not chosen - Factory/tech missing or busy."), proto->getName().str());
            TheScriptEngine->AppendDebugMessage(str, false);
        }
        return false;
    }
    return true;
}
