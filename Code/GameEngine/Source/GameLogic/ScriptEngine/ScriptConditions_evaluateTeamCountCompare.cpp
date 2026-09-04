// cl: /DNDEBUG /MD /EHsc
// BFME reconstruction of the team object-count comparison condition.

typedef bool Bool;

template <class T> class StringBase
{
    friend class AsciiString;

private:
    StringBase(const StringBase &);
    ~StringBase();
};

class AsciiString
{
public:
    AsciiString(const AsciiString &that)
    {
        ((StringBase<char> *)this)->StringBase<char>::StringBase(
            *(const StringBase<char> *)&that);
    }
    ~AsciiString();
};

class Parameter
{
public:
    const AsciiString &getString(void) const { return m_string; }
    int getInt(void) const { return m_value; }

private:
    unsigned char m_beforeValue[0x8];
    int m_value;
    unsigned char m_beforeString[0x4];
    AsciiString m_string;
};

class Team
{
};

class BfmeTeamCountKindCall
{
public:
    int countKind(int kind, Bool includeContained, Bool includeDead);
};

extern void j_0000a957();

static __forceinline int bfmeCountKind(Team *team, int kind)
{
    typedef int (BfmeTeamCountKindCall::*Function)(int, Bool, Bool);
    union { void (*raw)(void); Function member; } fn;
    fn.raw = j_0000a957;
    return (reinterpret_cast<BfmeTeamCountKindCall *>(team)->*fn.member)(
        kind, false, true);
}

class ScriptEngine
{
public:
    virtual void slot00() = 0;
    virtual void slot01() = 0;
    virtual void slot02() = 0;
    virtual void slot03() = 0;
    virtual void slot04() = 0;
    virtual void slot05() = 0;
    virtual void slot06() = 0;
    virtual void slot07() = 0;
    virtual void slot08() = 0;
    virtual void slot09() = 0;
    virtual void slot10() = 0;
    virtual void slot11() = 0;
    virtual void slot12() = 0;
    virtual void slot13() = 0;
    virtual void slot14() = 0;
    virtual void slot15() = 0;
    virtual void slot16() = 0;
    virtual Team *getTeamNamed(AsciiString, Bool) = 0;
};

extern ScriptEngine *TheScriptEngine;

class ScriptConditions
{
protected:
    Bool evaluateTeamCountCompare(Parameter *, Parameter *, Parameter *);
};

// ?evaluateTeamCountCompare@ScriptConditions@@IAE_NPAVParameter@@00@Z
Bool ScriptConditions::evaluateTeamCountCompare(
    Parameter *teamParm, Parameter *countParm, Parameter *kindParm)
{
    Team *team = TheScriptEngine->getTeamNamed(teamParm->getString(), false);
    if (team) {
        int kind = kindParm->getInt();
        if (countParm->getInt() < bfmeCountKind(team, kind)) {
            return true;
        }
        return false;
    }

    return false;
}
