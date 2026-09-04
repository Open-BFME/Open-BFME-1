// cl: /DNDEBUG /DWIN32 /MD /EHsc
// BFME named-unit rank-level condition (template 172).

typedef bool Bool;
typedef int Int;

template <typename T> class StringBase
{
    friend class AsciiString;

private:
    StringBase(const StringBase &);
    ~StringBase();
};

class AsciiString
{
public:
    AsciiString(const char *text);
    AsciiString(const AsciiString &that)
    {
        ((StringBase<char> *)this)->StringBase<char>::StringBase(
            *(const StringBase<char> *)&that);
    }
    ~AsciiString();
    AsciiString &operator+=(const AsciiString &text);

private:
    char *m_text;
};

class Parameter
{
public:
    const AsciiString &getString(void) const { return m_string; }
    Int getInt(void) const { return m_int; }

private:
    unsigned char m_beforeInt[8];
    Int m_int;
    unsigned char m_beforeString[4];
    AsciiString m_string;
};

class Body
{
public:
    Int getRankLevel(void) const { return m_rankLevel; }

private:
    unsigned char m_beforeRankLevel[0x28];
    Int m_rankLevel;
};

class Object
{
public:
    Body *getBody(void) const { return m_body; }

private:
    unsigned char m_beforeBody[0x210];
    Body *m_body;
};

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
    virtual void slot17() = 0;
    virtual void slot18() = 0;
    virtual void slot19() = 0;
    virtual void slot20() = 0;
    virtual void slot21() = 0;
    virtual void slot22() = 0;
    virtual void slot23() = 0;
    virtual void slot24() = 0;
    virtual void slot25() = 0;
    virtual Object *getUnitNamed(const AsciiString &name) = 0;
    void AppendDebugMessage(const AsciiString &message, Bool pause);
};

extern ScriptEngine *TheScriptEngine;

class ScriptConditions
{
protected:
    Bool evaluateNamedUnitRankLevel(Parameter *, Parameter *);
};

// ?evaluateNamedUnitRankLevel@ScriptConditions@@IAE_NPAVParameter@@0@Z
Bool ScriptConditions::evaluateNamedUnitRankLevel(
    Parameter *pUnitParm, Parameter *pRankParm)
{
    static Bool warned = false;
    Object *pUnit = TheScriptEngine->getUnitNamed(
        *(const AsciiString *)pUnitParm);

    if (!pUnit) {
        if (!warned) {
            warned = true;
            AsciiString message(
                "ScriptConditions::evaluateNamedUnitRankLevel: Unit not found: ");
            message += pUnitParm->getString();
            TheScriptEngine->AppendDebugMessage(message, false);
        }
        return false;
    }

    Body *body = pUnit->getBody();
    if (!body)
        return false;

    return body->getRankLevel() >= pRankParm->getInt();
}
