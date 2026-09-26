// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/objectdlink /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include
// stlport
#include <vector>
#include <math.h>
#include "basetype.h"
#include "ascii_string.h"
#include "Common/GameCommon.h"
#include "ObjectDlinkPmf.h"

class BfmeStringArgBase
{
    friend class BfmeAsciiStringArg;
private:
    BfmeStringArgBase(const BfmeStringArgBase &);
    ~BfmeStringArgBase();
};

class BfmeAsciiStringArg
{
public:
    BfmeAsciiStringArg(const AsciiString &that)
    {
        ((BfmeStringArgBase *)this)->BfmeStringArgBase::BfmeStringArgBase(
            *(const BfmeStringArgBase *)&that);
    }
    ~BfmeAsciiStringArg();
private:
    char *m_text;
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

class BfmeScriptEngineVtbl_44
{
public:
    virtual void slot00() = 0; virtual void slot01() = 0;
    virtual void slot02() = 0; virtual void slot03() = 0;
    virtual void slot04() = 0; virtual void slot05() = 0;
    virtual void slot06() = 0; virtual void slot07() = 0;
    virtual void slot08() = 0; virtual void slot09() = 0;
    virtual void slot10() = 0; virtual void slot11() = 0;
    virtual void slot12() = 0; virtual void slot13() = 0;
    virtual void slot14() = 0; virtual void slot15() = 0;
    virtual void slot16() = 0;
    virtual Team *getTeamNamed(BfmeAsciiStringArg name, Bool exact) = 0;
};

class ScriptEngine;
extern ScriptEngine *TheScriptEngine;

class CommandButton;
class ControlBar
{
public:
    const CommandButton *findCommandButton(const AsciiString &name);
};
extern ControlBar *TheControlBar;

struct Coord3D;
class CommandButton
{
public:
    Bool isValidToUseOn(const Object *obj, const Object *other,
        const Coord3D *pos, CommandSourceType source) const;
};

class BfmeObjectDoCommandButton
{
public:
    void doCommandButton(const CommandButton *button, Int source, Int extra);
};

class ScriptActions
{
protected:
    void doTeamPartialUseCommandButton(Real percentage, const AsciiString &teamName,
        const AsciiString &commandAbility);
};

void ScriptActions::doTeamPartialUseCommandButton(Real percentage,
    const AsciiString &teamName, const AsciiString &commandAbility)
{
    Team *team = ((BfmeScriptEngineVtbl_44 *)TheScriptEngine)->getTeamNamed(teamName, false);
    if (!team) return;

    const CommandButton *commandButton = TheControlBar->findCommandButton(commandAbility);
    if (!commandButton) return;

    std::vector<Object *> objList;
    DLINK_ITERATOR<Object> iter = team->iterate_TeamMemberList();
    for (iter = team->iterate_TeamMemberList(); !iter.done(); iter.advance()) {
        Object *obj = iter.cur();
        if (commandButton->isValidToUseOn(obj, 0, 0, CMD_FROM_SCRIPT))
            objList.push_back(obj);
    }

    Int numObjs = fast_float2long_round((float)ceil(percentage * objList.size() * 0.01f));
    Int count = 0;
    for (std::vector<Object *>::const_iterator it = objList.begin(); it != objList.end(); ++it) {
        Object *obj = *it;
        if (count >= numObjs) return;
        ((BfmeObjectDoCommandButton *)obj)->doCommandButton(commandButton, CMD_FROM_SCRIPT, 0);
        ++count;
    }
}
