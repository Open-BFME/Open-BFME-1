// ScriptEngine::evaluateConditions at retail RVA 0x00346380.
// The BFME body follows the Zero Hour condition-list evaluator with BFME layouts.
// Its three arguments, vtable slot 23, latch fields, and helper calls are witnessed.
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common

#include "ascii_string.h"
#include "LatchRestore.h"

typedef bool Bool;

class Player;

class Team
{
public:
    Player *getControllingPlayer() const;
};

class Parameter
{
public:
    int getInt() const { return m_int; }
    const AsciiString &getString() const { return m_string; }

private:
    char m_unknown[8];
    int m_int;
    float m_real;
    AsciiString m_string;
};

class Condition
{
public:
    enum ConditionType
    {
        CONDITION_FALSE,
        COUNTER,
        FLAG,
        CONDITION_TRUE,
        TIMER_EXPIRED
    };

    ConditionType getConditionType() const { return m_conditionType; }
    Parameter *getParameter(int index) const
    {
        if (index >= 0 && index < m_numParms)
            return m_parms[index];
        return 0;
    }
    Condition *getNext() const { return m_nextAndCondition; }

private:
    void *m_vtable;
    ConditionType m_conditionType;
    int m_numParms;
    Parameter *m_parms[12];
    Condition *m_nextAndCondition;
};

class OrCondition
{
public:
    OrCondition *getNextOrCondition() const { return m_nextOr; }
    Condition *getFirstAndCondition() const { return m_firstAnd; }

private:
    void *m_vtable;
    OrCondition *m_nextOr;
    Condition *m_firstAnd;
};

class Script
{
public:
    OrCondition *getOrCondition() const { return m_condition; }

private:
    char m_unknown[0x1c];
    OrCondition *m_condition;
};

class ScriptConditionsInterface
{
public:
    virtual void slot00();
    virtual void slot01();
    virtual void slot02();
    virtual void slot03();
    virtual void slot04();
    virtual void slot05();
    virtual void slot06();
    virtual void slot07();
    virtual void slot08();
    virtual bool evaluateCondition(Condition *condition);
};

extern ScriptConditionsInterface *TheScriptConditions;

struct ScriptCounter
{
    int m_value;
    bool m_isCountdownTimer;
    bool m_isMillisecondTimer;
};

class ScriptEngineBase
{
public:
    virtual void slot00();
    virtual void slot01();
    virtual void slot02();
    virtual void slot03();
    virtual void slot04();
    virtual void slot05();
    virtual void slot06();
    virtual void slot07();
    virtual void slot08();
    virtual void slot09();
    virtual void slot10();
    virtual void slot11();
    virtual void slot12();
    virtual void slot13();
    virtual void slot14();
    virtual void slot15();
    virtual void slot16();
    virtual void slot17();
    virtual void slot18();
    virtual void slot19();
    virtual void slot20();
    virtual void slot21();
    virtual void slot22();
    virtual Bool evaluateConditions(Script *script, Team *team, Player *player);
};

class ScriptEngine : public ScriptEngineBase
{
protected:
    ScriptCounter *bfmeCounter(AsciiString name);
    bool evaluateCounter(Condition *condition);
    bool evaluateFlag(Condition *condition);
    __forceinline bool evaluateTimer(Condition *condition)
    {
        ScriptCounter *counter = bfmeCounter(
            condition->getParameter(0)->getString());
        if (!counter->m_isCountdownTimer)
            return false;
        return counter->m_value < 1;
    }
    __forceinline Bool evaluateConditionForList(Condition *condition)
    {
        switch (condition->getConditionType())
        {
        default:
            return TheScriptConditions->evaluateCondition(condition);
        case Condition::CONDITION_FALSE:
            return false;
        case Condition::COUNTER:
            return evaluateCounter(condition);
        case Condition::FLAG:
            return evaluateFlag(condition);
        case Condition::CONDITION_TRUE:
            return true;
        case Condition::TIMER_EXPIRED:
            return evaluateTimer(condition);
        }
    }

public:
    Bool evaluateConditions(Script *script, Team *team, Player *player);
};

// ?evaluateConditions@ScriptEngine@@UAE_NPAVScript@@PAVTeam@@PAVPlayer@@@Z
Bool ScriptEngine::evaluateConditions(Script *script, Team *thisTeam, Player *player)
{
    LatchRestore<Team *> latch(*(Team **)((char *)this + 0x1708c), thisTeam);
    if (thisTeam)
        player = thisTeam->getControllingPlayer();
    if (player == 0)
        player = *(Player **)((char *)this + 0x170ac);
    LatchRestore<Player *> latch2(*(Player **)((char *)this + 0x170ac), player);
    OrCondition *conditionHead = script->getOrCondition();
    Bool testValue = false;
    OrCondition *currentOr;
    for (currentOr = conditionHead; currentOr; currentOr = currentOr->getNextOrCondition())
    {
        Condition *condition = currentOr->getFirstAndCondition();
        if (!condition)
            continue;
        Bool andTerm = true;
        while (condition)
        {
            if (!evaluateConditionForList(condition))
            {
                andTerm = false;
                break;
            }
            condition = condition->getNext();
        }
        if (andTerm)
        {
            testValue = true;
            break;
        }
    }
    return testValue;
}
