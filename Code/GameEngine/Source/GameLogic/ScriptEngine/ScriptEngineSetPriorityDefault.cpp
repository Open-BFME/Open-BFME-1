// cl: /DNDEBUG /MD /EHsc

typedef bool Bool;
typedef int Int;

class AsciiString
{
public:
    const char *str(void) const;

private:
    void *m_data;
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

class Parameter
{
public:
    Int getInt(void) const { return m_integer; }
    const AsciiString &getString(void) const { return m_string; }

private:
    char m_unknown[8];
    Int m_integer;
    float m_real;
    AsciiString m_string;
};

class ScriptAction
{
public:
    Parameter *getParameter(Int index)
    {
        if (index >= 0 && index < m_parameterCount)
            return m_parameters[index];
        return 0;
    }

private:
    char m_unknown[8];
    Int m_parameterCount;
    Parameter *m_parameters[12];
};

class AttackPriorityInfo
{
public:
    void setDefaultPriority(Int priority) { m_defaultPriority = priority; }

private:
    char m_unknown[8];
    Int m_defaultPriority;
};

class ScriptEngine
{
public:
    AttackPriorityInfo *findAttackInfo(const AsciiString &name, Bool addIfNotFound);
    void AppendDebugMessage(const AsciiString &message, Bool forcePause);
    void setPriorityDefault(ScriptAction *action);
};

void ScriptEngine::setPriorityDefault(ScriptAction *action)
{
    AttackPriorityInfo *info = findAttackInfo(action->getParameter(0)->getString(), true);
    if (info == 0)
    {
        BFMERetailAsciiString message("***Error allocating attack priority set - fix or raise limit. ***");
        AppendDebugMessage(*(const AsciiString *)&message, false);
        return;
    }
    info->setDefaultPriority(action->getParameter(1)->getInt());
}
