// cl: /DNDEBUG /MD /EHsc
// Retail 0x00168AE0 is a 486-byte team-production eligibility check.
// The body proves the queue, production-condition, limit, and factory checks,
// but no caller or vtable proves a semantic owner beyond this address.

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

class TeamInQueue
{
public:
    char m_pad[0x1c];
    Team *m_team;
    TeamInQueue *next();
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

class AIPlayer
{
public:
    Bool isPossibleToBuildTeam(TeamPrototype *proto, Bool requireIdleFactory,
        Bool &notEnoughMoney);
};

class Rva00168AE0TeamBuildCheckOwner
{
protected:
    virtual Bool checkTeamBuild(TeamPrototype *proto);

public:
    TeamInQueue *m_teamBuildQueue;
};

extern GlobalData *TheWritableGlobalData;
extern ScriptEngine *TheScriptEngine;

extern void j_00002c98();
extern void j_000077b1();
extern void j_0000e372();
extern void j_00028ce0();
extern void j_0002fee6();
extern void j_0003de8d();

static Bool evaluateProductionCondition(TeamPrototype *proto)
{
    typedef Bool (TeamPrototype::*Call)();
    union
    {
        void (*raw)();
        Call member;
    } call;
    call.raw = j_00002c98;
    return (proto->*call.member)();
}

static Int countTeamInstances(TeamPrototype *proto)
{
    typedef Int (TeamPrototype::*Call)();
    union
    {
        void (*raw)();
        Call member;
    } call;
    call.raw = j_0003de8d;
    return (proto->*call.member)();
}

static TeamInQueue *nextTeam(TeamInQueue *queue)
{
    typedef TeamInQueue *(TeamInQueue::*Call)();
    union
    {
        void (*raw)();
        Call member;
    } call;
    call.raw = j_0002fee6;
    return (queue->*call.member)();
}

static Bool quickTeamCheck(AIPlayer *player, TeamPrototype *proto)
{
    typedef Bool (AIPlayer::*Call)(TeamPrototype *);
    union
    {
        void (*raw)();
        Call member;
    } call;
    call.raw = j_000077b1;
    return (player->*call.member)(proto);
}

static Bool isPossibleToBuildTeam(AIPlayer *player, TeamPrototype *proto,
    Bool requireIdleFactory, Bool &notEnoughMoney)
{
    typedef Bool (AIPlayer::*Call)(TeamPrototype *, Bool, Bool &);
    union
    {
        void (*raw)();
        Call member;
    } call;
    call.raw = j_0000e372;
    return (player->*call.member)(proto, requireIdleFactory, notEnoughMoney);
}

static void appendDebugMessage(ScriptEngine *engine,
    const AsciiString &message, Bool forcePause)
{
    typedef void (ScriptEngine::*Call)(const AsciiString &, Bool);
    union
    {
        void (*raw)();
        Call member;
    } call;
    call.raw = j_00028ce0;
    (engine->*call.member)(message, forcePause);
}

Bool Rva00168AE0TeamBuildCheckOwner::checkTeamBuild(TeamPrototype *proto)
{
    if (!evaluateProductionCondition(proto))
        return false;

    if (countTeamInstances(proto) >= proto->getTemplateInfo()->m_maxInstances)
    {
        if (TheWritableGlobalData->m_debugAI)
        {
            AsciiString message;
            message.format(AsciiString("Team %s not chosen - %d already exist."),
                proto->getName().str(), countTeamInstances(proto));
            appendDebugMessage(TheScriptEngine, message, false);
        }
        return false;
    }

    TeamInQueue *queue = m_teamBuildQueue;
    if (queue != 0)
    {
        do
        {
            if (queue->m_team->getPrototype() == proto)
                return false;
            queue = nextTeam(queue);
        } while (queue != 0);
    }

    if (quickTeamCheck((AIPlayer *)this, proto))
        return true;

    Bool needMoney;
    if (!::isPossibleToBuildTeam((AIPlayer *)this, proto, true, needMoney))
    {
        if (TheWritableGlobalData->m_debugAI)
        {
            AsciiString message;
            if (needMoney)
            {
                message.format(AsciiString("Team %s not chosen - Not enough money."),
                    proto->getName().str());
            }
            else
            {
                message.format(AsciiString("Team %s not chosen - Factory/tech missing or busy."),
                    proto->getName().str());
            }
            appendDebugMessage(TheScriptEngine, message, false);
        }
        return false;
    }
    return true;
}
