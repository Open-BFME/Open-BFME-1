// ?checkConditionsForTeamNames@ScriptEngine@@QAEXPAVScript@@ABVAsciiString@@@Z
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// BFME's map loader checks team-condition names before evaluating scripts.

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

#include "ascii_string.h"

struct AsciiStringDataLayout
{
    int references;
    unsigned short length;
    unsigned short capacity;
    char data[1];
};

static __forceinline Bool isStringEmpty(const AsciiString &value)
{
    const AsciiStringDataLayout *data = *(const AsciiStringDataLayout **)&value;
    return data == 0 || data->length == 0;
}

class Xfer;

class Snapshot
{
public:
    Snapshot() {}
    virtual ~Snapshot();

protected:
    virtual void loadPostProcess() = 0;
    virtual const char *getSnapshotName() const = 0;
    virtual void xfer(Xfer *xfer) = 0;
};

class Condition;

class OrCondition
{
public:
    OrCondition *getNextOrCondition(void) const { return m_nextOr; }
    Condition *getFirstAndCondition(void) const { return m_firstAnd; }

private:
    void *m_vtable;
    OrCondition *m_nextOr;
    Condition *m_firstAnd;
};

class Script : public Snapshot
{
public:
    virtual ~Script();
    virtual void loadPostProcess();
    virtual const char *getSnapshotName() const;
    virtual void xfer(Xfer *xfer);

    Int getDelayEvalSeconds(void) const { return m_delayEvaluationSeconds; }
    void setFrameToEvaluate(UnsignedInt frame) { m_frameToEvaluateAt = frame; }
    OrCondition *getOrCondition(void) const { return m_condition; }
    void setConditionTeamName(AsciiString teamName) { m_conditionTeamName = teamName; }

private:
    AsciiString m_scriptName;
    AsciiString m_comment;
    AsciiString m_conditionComment;
    Int m_delayEvaluationSeconds;
    Bool m_isActive;
    Bool m_isOneShot;
    Bool m_easy;
    Bool m_isSubroutine;
    Bool m_normal;
    Bool m_hard;
    Bool m_bfmeFlag;
    OrCondition *m_condition;
    void *m_action;
    void *m_actionFalse;
    UnsignedInt m_frameToEvaluateAt;
    Bool m_hasWarnings;
    AsciiString m_conditionTeamName;
    float m_conditionTime;
    float m_curTime;
    Int m_conditionExecutedCount;
};

class Parameter
{
public:
    enum ParameterType { TEAM = 3 };

    Int getParameterType(void) const { return m_type; }
    const AsciiString &getString(void) const { return m_string; }

private:
    Int m_type;
    Int m_initialized;
    Int m_integer;
    float m_real;
    AsciiString m_string;
};

class Condition
{
public:
    Int getNumParameters(void) const { return m_numParms; }
    Parameter *getParameter(Int index) const
    {
        if (index >= 0 && index < m_numParms)
            return m_parameters[index];
        return 0;
    }
    Condition *getNext(void) const { return m_nextAndCondition; }

private:
    void *m_vtable;
    Int m_conditionType;
    Int m_numParms;
    Parameter *m_parameters[12];
    Condition *m_nextAndCondition;
};

class TeamTemplateInfoView
{
private:
    char m_beforeMaxInstances[0x98];

public:
    Int m_maxInstances;
};

class TeamPrototype
{
private:
    char m_beforeFlags[0x18];

public:
    unsigned int m_flags;

private:
    char m_beforeTemplateInfo[0x110];

public:
    TeamTemplateInfoView m_templateInfo;

    Bool getIsSingleton(void) const { return (m_flags & 1) != 0; }
    const TeamTemplateInfoView *getTemplateInfo(void) const { return &m_templateInfo; }
};

class TeamFactory
{
public:
    TeamPrototype *findTeamPrototype(const AsciiString &name, const AsciiString &ownerName);
};

extern TeamFactory *TheTeamFactory;

class BFMEScriptEngineFlagLookup
{
    friend class ScriptEngine;

private:
    AsciiString canonicalFlagName(const AsciiString &name);
};

class ScriptEngine
{
public:
    void AppendDebugMessage(const AsciiString &message, Bool forcePause);
    void checkConditionsForTeamNames(Script *pScript, const AsciiString &scriptName);
};

class BfmeStringLiteralBase
{
    friend class BFMERetailAsciiString;

private:
    BfmeStringLiteralBase(const char *string);
};

class BFMERetailAsciiString
{
public:
    BFMERetailAsciiString(const char *string)
    {
        ((BfmeStringLiteralBase *)this)->BfmeStringLiteralBase::BfmeStringLiteralBase(string);
    }

    ~BFMERetailAsciiString() { releaseBuffer(); }

private:
    void releaseBuffer();
    char *m_data;
};

void ScriptEngine::checkConditionsForTeamNames(Script *pScript, const AsciiString &scriptName)
{
    AsciiString singletonTeamName;
    AsciiString multiTeamName;

    if (pScript->getDelayEvalSeconds() > 0)
    {
        extern Int GetGameLogicRandomValue(Int, Int, char *, Int);
        pScript->setFrameToEvaluate(GetGameLogicRandomValue(0, 10, (char *)0x010E7820, 0x979));
    }
    else
    {
        pScript->setFrameToEvaluate(0);
    }

    OrCondition *pOr;
    for (pOr = pScript->getOrCondition(); pOr; pOr = pOr->getNextOrCondition())
    {
        Condition *pCondition;
        for (pCondition = pOr->getFirstAndCondition(); pCondition; pCondition = pCondition->getNext())
        {
            Int i;
            for (i = 0; i < pCondition->getNumParameters(); ++i)
            {
                if (Parameter::TEAM == pCondition->getParameter(i)->getParameterType())
                {
                    AsciiString teamName = pCondition->getParameter(i)->getString();
                    AsciiString canonical = ((BFMEScriptEngineFlagLookup *)this)->canonicalFlagName(teamName);
                    TeamPrototype *proto = TheTeamFactory->findTeamPrototype(canonical, teamName);
                    if (proto == 0)
                        continue;

                    Bool singleton = proto->getIsSingleton();
                    if (proto->getTemplateInfo()->m_maxInstances < 2)
                        singleton = true;
                    if (singleton)
                    {
                        singletonTeamName = teamName;
                    }
                    else
                    {
                        if (isStringEmpty(multiTeamName))
                        {
                            multiTeamName = teamName;
                        }
                        else if (multiTeamName.compare(teamName) != 0)
                        {
                            {
                                BFMERetailAsciiString message((const char *)0x010E77C8);
                                AppendDebugMessage(*(const AsciiString *)&message, false);
                            }
                            AppendDebugMessage(scriptName, false);
                            AppendDebugMessage(multiTeamName, false);
                            AppendDebugMessage(teamName, false);
                        }
                    }
                }
            }
        }
    }

    if (isStringEmpty(multiTeamName))
    {
        if (!isStringEmpty(singletonTeamName))
            pScript->setConditionTeamName(singletonTeamName);
    }
    else
    {
        pScript->setConditionTeamName(multiTeamName);
    }
}
