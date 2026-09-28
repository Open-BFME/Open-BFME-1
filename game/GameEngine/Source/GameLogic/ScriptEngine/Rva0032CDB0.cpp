// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/objectdlink /Igame/Libraries/Source/WWVegas/WWLib
// stlport
#include "ascii_string.h"
#include "ObjectDlinkPmf.h"

// ScriptEngine dispatches case 174 here, and its condition template names EVAL_TEAM_HEALTH.
// The method keeps its retail address because the C++ name is unproven.
class Parameter
{
public:
    const AsciiString &getString() const
    {
        return *(const AsciiString *)((const char *)this + 0x10);
    }
    int getInt() const
    {
        return *(const int *)((const char *)this + 8);
    }
};

class Team;
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
    virtual Team *getTeamNamed(AsciiString name, bool exact) = 0;
};
extern ScriptEngine *TheScriptEngine;

template<class OBJCLASS>
class DLINK_ITERATOR
{
public:
    typedef OBJCLASS *(OBJCLASS::*GetNextFunc)() const;
private:
    OBJCLASS *m_cur;
    GetNextFunc m_getNextFunc;
public:
    DLINK_ITERATOR(OBJCLASS *cur, GetNextFunc getNextFunc)
        : m_cur(cur), m_getNextFunc(getNextFunc) {}
    void advance()
    {
        if (m_cur)
            m_cur = (m_cur->*m_getNextFunc)();
    }
    bool done() const { return m_cur == 0; }
    OBJCLASS *cur() const { return m_cur; }
};

class Team
{
public:
    void *m_vptr;
    void *m_proto;
    void *m_id;
    Object *m_head;
    DLINK_ITERATOR<Object> iterate_TeamMemberList() const
    {
        return DLINK_ITERATOR<Object>(m_head, Object::dlink_next_TeamMemberList);
    }
};

class Overridable
{
public:
    const Overridable *getFinalOverride() const;
    void *m_vptr;
    Overridable *m_nextOverride;
    bool m_isOverride;
};

class Rva0032CDB0TemplateView : public Overridable
{
public:
    unsigned char m_beforeFlags[0xC0];
    int m_flagsCC;
    int m_flagsD0;
    int m_flagsD4;
};

class Rva0032CDB0ObjectView
{
public:
    void *m_vptr;
    Rva0032CDB0TemplateView *m_template;
    unsigned char m_beforeTeamHealthStatus[0x94 - 8];
    unsigned char m_teamHealthStatus;
};

class BfmeX1004
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
    virtual void slot26() = 0;
    virtual void slot27() = 0;
    virtual void slot28() = 0;
    virtual void slot29() = 0;
    virtual void slot30() = 0;
    virtual void slot31() = 0;
    virtual void slot32() = 0;
    virtual void slot33() = 0;
    virtual void slot34() = 0;
    virtual void slot35() = 0;
    virtual void slot36() = 0;
    virtual void slot37() = 0;
    virtual void slot38() = 0;
    virtual void slot39() = 0;
    virtual void slot40() = 0;
    virtual void slot41() = 0;
    virtual void slot42() = 0;
    virtual void slot43() = 0;
    virtual void slot44() = 0;
    virtual void slot45() = 0;
    virtual void slot46() = 0;
    virtual void slot47() = 0;
    virtual void slot48() = 0;
    virtual void slot49() = 0;
    virtual void slot50() = 0;
    virtual void slot51() = 0;
    virtual void slot52() = 0;
    virtual void slot53() = 0;
    virtual void slot54() = 0;
    virtual void slot55() = 0;
    virtual void slot56() = 0;
    virtual void slot57() = 0;
    virtual void slot58() = 0;
    virtual void slot59() = 0;
    virtual void slot60() = 0;
    virtual void slot61() = 0;
    virtual void slot62() = 0;
    virtual void slot63() = 0;
    virtual void slot64() = 0;
    virtual void slot65() = 0;
    virtual void slot66() = 0;
    virtual void slot67() = 0;
    virtual void slot68() = 0;
    virtual void slot69() = 0;
    virtual void slot70() = 0;
    virtual void slot71() = 0;
    virtual void slot72() = 0;
    virtual void slot73() = 0;
    virtual void slot74() = 0;
    virtual void slot75() = 0;
    virtual void slot76() = 0;
    virtual void slot77() = 0;
    virtual void slot78() = 0;
    virtual void slot79() = 0;
    virtual void slot80() = 0;
    virtual void slot81() = 0;
    virtual void slot82() = 0;
    virtual int valueAt14C() const = 0;
    virtual int valueAt150(bool mode) const = 0;
};

class BfmeHold1004
{
public:
    BfmeX1004 *bfmeFind1004();
};

class Rva0032CDB0
{
public:
    bool method(Parameter *teamParameter, Parameter *comparisonParameter,
        Parameter *percentParameter);
};

bool Rva0032CDB0::method(Parameter *teamParameter,
    Parameter *comparisonParameter, Parameter *percentParameter)
{
    Team *team = TheScriptEngine->getTeamNamed(teamParameter->getString(), false);
    if (team) {
        int denominator = 0;
        int numerator = 0;
        int percent;
        DLINK_ITERATOR<Object> iter = team->iterate_TeamMemberList();
        if (!iter.done()) {
            for (; !iter.done(); iter.advance()) {
                Object *object = iter.cur();
                Rva0032CDB0ObjectView *view = (Rva0032CDB0ObjectView *)object;
                const Rva0032CDB0TemplateView *thingTemplate = view->m_template;
                if (thingTemplate && thingTemplate->m_nextOverride)
                    thingTemplate = (const Rva0032CDB0TemplateView *)thingTemplate->m_nextOverride->getFinalOverride();
                if (thingTemplate->m_flagsD0 & 0x01000000)
                    continue;
                thingTemplate = view->m_template;
                if (thingTemplate && thingTemplate->m_nextOverride)
                    thingTemplate = (const Rva0032CDB0TemplateView *)thingTemplate->m_nextOverride->getFinalOverride();
                if (thingTemplate->m_flagsCC & 0x00008000)
                    continue;
                thingTemplate = view->m_template;
                if (thingTemplate && thingTemplate->m_nextOverride)
                    thingTemplate = (const Rva0032CDB0TemplateView *)thingTemplate->m_nextOverride->getFinalOverride();
                if (thingTemplate->m_flagsD4 & 0x00001000) {
                    BfmeX1004 *value = ((BfmeHold1004 *)object)->bfmeFind1004();
                    if (value) {
                        denominator += value->valueAt14C();
                        numerator += value->valueAt150(false);
                    }
                } else if (!(view->m_teamHealthStatus & 0x20)) {
                    ++denominator;
                    ++numerator;
                }
            }

            if (denominator)
                percent = numerator * 100 / denominator;
            else
                percent = 0;
        } else {
            percent = 0;
        }

        bool result;
        switch (comparisonParameter->getInt()) {
        case 0: result = percent < percentParameter->getInt(); break;
        case 1: result = percent <= percentParameter->getInt(); break;
        case 2: result = percent == percentParameter->getInt(); break;
        case 3: result = percent >= percentParameter->getInt(); break;
        case 4: result = percent > percentParameter->getInt(); break;
        case 5: result = percent != percentParameter->getInt(); break;
        default: return false;
        }
        if (result)
            return true;
    }
    return false;
}
