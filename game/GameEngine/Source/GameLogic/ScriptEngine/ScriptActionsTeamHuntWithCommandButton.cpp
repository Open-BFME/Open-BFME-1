// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/shims/objectdlink
#include <string.h>
#include "string_base.h"
template <> inline void StringBase<char>::concat(const char *s)
{
    concat(s, s ? strlen(s) : 0);
}
template <> inline void StringBase<char>::concat(const StringBase<char> &s)
{
    const int len = s.m_data ? s.m_data->length : 0;
    const char *text = s.m_data ? s.m_data->data : "";
    concat(text, len);
}
#include "ascii_string.h"
#include "ObjectDlinkPmf.h"
class Team;
class ScriptEngine
{
  public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0c();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1c();
    virtual void slot20();
    virtual void slot24();
    virtual void slot28();
    virtual void slot2c();
    virtual void slot30();
    virtual void slot34();
    virtual void slot38();
    virtual void slot3c();
    virtual void slot40();
    virtual Team *getTeamNamed(AsciiString, bool);
    void AppendDebugMessage(const AsciiString &, bool);
};
class CommandButton
{
  public:
    char pad00[0x10];
    int m_command;
    char pad14[4];
    unsigned m_options;
    char pad1c[0x18];
    void *m_specialPower;
    int getCommandType() const
    {
        return m_command;
    }
    const void *getSpecialPowerTemplate() const
    {
        return m_specialPower;
    }
    unsigned getOptions() const
    {
        return m_options;
    }
};
class CommandSet
{
  public:
    const CommandButton *getCommandButton(int) const;
};
class ControlBar
{
  public:
    const CommandButton *findCommandButton(const AsciiString &);
    const CommandSet *findCommandSet(const AsciiString &);
};
class Overridable
{
  public:
    void *vptr;
    Overridable *nextOverride;
    const Overridable *getFinalOverride() const;
};
class HuntTemplate002F7B80 : public Overridable
{
  public:
    char pad08[0x18];
    AsciiString name20;
    const AsciiString &getName() const
    {
        return name20;
    }
};
extern void j_00029dc0();
extern void j_0002ae23();
extern void j_00011ac2();
class HuntUpdate002F7B80
{
  public:
    void setCommandButton(const AsciiString &s)
    {
        typedef void (HuntUpdate002F7B80::*Fn)(const AsciiString &);
        union {
            void (*raw)();
            Fn member;
        } c;
        c.raw = j_00011ac2;
        (this->*c.member)(s);
    }
};
class HuntObject002F7B80
{
  public:
    void *vptr;
    HuntTemplate002F7B80 *template04;
    char pad08[0x1fc];
    void *ai204;
    void *getAIUpdateInterface() const
    {
        return ai204;
    }
    const HuntTemplate002F7B80 *getTemplate() const
    {
        HuntTemplate002F7B80 *t = template04;
        if (t && t->nextOverride)
            t = (HuntTemplate002F7B80 *)t->nextOverride->getFinalOverride();
        return t;
    }
    const AsciiString &getCommandSetString() const
    {
        typedef const AsciiString &(HuntObject002F7B80::*Fn)() const;
        union {
            void (*raw)();
            Fn member;
        } c;
        c.raw = j_00029dc0;
        return (this->*c.member)();
    }
    HuntUpdate002F7B80 *findUpdateModule(int key)
    {
        typedef HuntUpdate002F7B80 *(HuntObject002F7B80::*Fn)(int);
        union {
            void (*raw)();
            Fn member;
        } c;
        c.raw = j_0002ae23;
        return (this->*c.member)(key);
    }
};
template <class T> class DLINK_ITERATOR
{
  public:
    typedef T *(T::*Next)() const;
    DLINK_ITERATOR(T *cur, Next next) : m_cur(cur), m_next(next)
    {
    }
    bool done() const
    {
        return m_cur == 0;
    }
    T *cur() const
    {
        return m_cur;
    }
    void advance()
    {
        if (m_cur)
            m_cur = (m_cur->*m_next)();
    }

  private:
    T *m_cur;
    Next m_next;
};
class Team
{
  public:
    char pad00[0xc];
    Object *head0c;
    DLINK_ITERATOR<Object> iterate_TeamMemberList() const
    {
        return DLINK_ITERATOR<Object>(head0c, Object::dlink_next_TeamMemberList);
    }
};
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h
// Retail's nameToKey returns this enum by value; MSVC mangles a by-value enum
// return as ?AW4NameKeyType@@, the matched defining symbol (0x0008FFC0).
enum NameKeyType
{
    NAMEKEY_INVALID = 0,
    NAMEKEY_MAX = 1 << 23,
    FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};
class NameKeyGenerator
{
  public:
    NameKeyType nameToKey(const char *);
};
extern ScriptEngine *TheScriptEngine;
extern ControlBar *TheControlBar;
extern NameKeyGenerator *TheNameKeyGenerator;
class ScriptActions
{
  protected:
    void doTeamHuntWithCommandButton(const AsciiString &, const AsciiString &);
};
void ScriptActions::doTeamHuntWithCommandButton(const AsciiString &teamName,
                                                const AsciiString &ability)
{
    Team *theTeam = TheScriptEngine->getTeamNamed(teamName, false);
    if (!theTeam)
        return;
    const CommandButton *commandButton = TheControlBar->findCommandButton(ability);
    if (!commandButton)
        return;
    switch (commandButton->getCommandType())
    {
    case 23:
    case 36:
        if (commandButton->getSpecialPowerTemplate())
        {
            if (commandButton->getOptions() & 7)
                break;
            AsciiString msg = "ERROR-Team hunt with command button - cannot hunt with ability ";
            msg.StringBase<char>::concat(ability);
            TheScriptEngine->AppendDebugMessage(msg, false);
            return;
        }
        return;
    case 22:
    case 26:
        break;
    default: {
        AsciiString msg = "ERROR-Team hunt with command button - cannot hunt with ability ";
        msg.StringBase<char>::concat(ability);
        TheScriptEngine->AppendDebugMessage(msg, false);
        return;
    }
    }
    for (DLINK_ITERATOR<Object> iter = theTeam->iterate_TeamMemberList(); !iter.done();
         iter.advance())
    {
        HuntObject002F7B80 *obj = (HuntObject002F7B80 *)iter.cur();
        void *ai = obj->getAIUpdateInterface();
        if (!ai)
            continue;
        bool foundCommand = false;
        const CommandSet *commandSet = TheControlBar->findCommandSet(obj->getCommandSetString());
        if (commandSet)
        {
            for (int i = 0; i < 20; ++i)
            {
                const CommandButton *aCommandButton = commandSet->getCommandButton(i);
                if (commandButton == aCommandButton)
                {
                    foundCommand = true;
                    break;
                }
            }
        }
        if (!foundCommand)
        {
            AsciiString msg = "Error - Team hunt with command button - unit type '";
            msg.concat(obj->getTemplate()->getName().str());
            msg.concat("' is not valid for ability ");
            msg.StringBase<char>::concat(ability);
            TheScriptEngine->AppendDebugMessage(msg, false);
            continue;
        }
        switch (commandButton->getCommandType())
        {
        case 22:
        case 23:
        case 26:
        case 36: {
            static NameKeyType key_CommandButtonHuntUpdate =
                TheNameKeyGenerator->nameToKey("CommandButtonHuntUpdate");
            HuntUpdate002F7B80 *huntUpdate = obj->findUpdateModule(key_CommandButtonHuntUpdate);
            if (huntUpdate)
                huntUpdate->setCommandButton(ability);
            else
            {
                AsciiString msg = "Error - Team hunt with command button - unit type '";
                msg.concat(obj->getTemplate()->getName().str());
                msg.concat("' requires CommandButtonHuntUpdate in .ini definition to hunt with ");
                msg.StringBase<char>::concat(ability);
                TheScriptEngine->AppendDebugMessage(msg, false);
            }
        }
        break;
        }
    }
}
