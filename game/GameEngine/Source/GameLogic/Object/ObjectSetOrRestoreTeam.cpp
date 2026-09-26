// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
// Retail001D4530/581. Object's slot20 setTeam calls slot21 setTemporaryTeam;
// its 001D5D90 wrapper calls ILT0002C566 -> this body with restoring=false.
// The aligned Team DLink calls, player notifications, AI attitude/priority,
// drawable notification, capture, radar and UI sequence match the released
// Object::setOrRestoreTeam. BFME moved Team+0C and Object+23C/25C/260.
// StringBase::isNotEmpty has its real definition visible for exception
// analysis. The noinline boundary preserves the two witnessed retail calls;
// it does not add an exception specification or change string semantics.
// The prior pinharvest at ILT0002BF2B actually reaches setScriptStatus and
// cannot establish this function's identity.
#include "ascii_string.h"
template <typename T> inline bool StringBase<T>::isEmpty() const
{
    return m_data == 0 || m_data->length == 0;
}
template <typename T> __declspec(noinline) bool StringBase<T>::isNotEmpty() const
{
    return !isEmpty();
}
inline AsciiString::~AsciiString()
{
    ((StringBase<char> *)this)->releaseBuffer();
}
typedef bool Bool;
typedef int Int;
class Object;
class Team;
class Player;
class Drawable;
class AttackPriorityInfo;
enum AttitudeType
{
    ATTITUDE_ZERO = 0
};
class Player
{
  public:
    unsigned char pad[0x24];
    int m_playerIndex;
    int getPlayerIndex() const
    {
        return m_playerIndex;
    }
    void becomingTeamMember(Object *, bool);
};
struct TeamTemplateInfo
{
    unsigned char pad[0xa8];
    AttitudeType m_initialTeamAttitude;
};
class TeamPrototype
{
  public:
    unsigned char pad[0x12c];
    TeamTemplateInfo m_teamTemplate;
    const TeamTemplateInfo *getTemplateInfo() const
    {
        return &m_teamTemplate;
    }
    AsciiString getAttackPriorityName() const;
};
class AttackPriorityInfo
{
  public:
    AsciiString getName() const;
};
class AIUpdateInterface
{
  public:
    unsigned char pad[0x70];
    const AttackPriorityInfo *m_attackInfo;
    void setAttitude(AttitudeType);
    void setAttackInfo(const AttackPriorityInfo *info)
    {
        m_attackInfo = info;
    }
};
class Drawable
{
  public:
    void changedTeam();
};
class ScriptEngine
{
  public:
    const AttackPriorityInfo *getAttackInfo(const AsciiString &);
};
class Radar
{
  public:
    void removeObject(Object *);
    void addObject(Object *);
};
class InGameUI
{
  public:
#define UI_SLOT(n) virtual void slot##n();
    UI_SLOT(00)
    UI_SLOT(01)
    UI_SLOT(02) UI_SLOT(03) UI_SLOT(04) UI_SLOT(05) UI_SLOT(06) UI_SLOT(07) UI_SLOT(08) UI_SLOT(09) UI_SLOT(10)
        UI_SLOT(11) UI_SLOT(12) UI_SLOT(13) UI_SLOT(14) UI_SLOT(15) UI_SLOT(16) UI_SLOT(17) UI_SLOT(18) UI_SLOT(19)
            UI_SLOT(20) UI_SLOT(21) UI_SLOT(22) UI_SLOT(23) UI_SLOT(24) UI_SLOT(25) UI_SLOT(26) UI_SLOT(27) UI_SLOT(28)
                UI_SLOT(29) UI_SLOT(30) UI_SLOT(31) UI_SLOT(32) UI_SLOT(33) UI_SLOT(34)
#undef UI_SLOT
                    virtual void objectChangedTeam(Object *, int, int);
};
extern ScriptEngine *TheScriptEngine;
extern Radar *TheRadar;
extern InGameUI *TheInGameUI;
class Object
{
  public:
#define OB_SLOT(n) virtual void slot##n();
    OB_SLOT(00)
    OB_SLOT(01)
    OB_SLOT(02) OB_SLOT(03) OB_SLOT(04) OB_SLOT(05) OB_SLOT(06) OB_SLOT(07) OB_SLOT(08) OB_SLOT(09)
#undef OB_SLOT
        virtual Drawable *getDrawable() const;
    unsigned char pad004[0x204 - 4];
    AIUpdateInterface *m_ai;
    unsigned char pad208[4];
    void *m_radarData;
    unsigned char pad210[0x23c - 0x210];
    Team *m_team;
    unsigned char pad240[0x25c - 0x240];
    struct
    {
        Object *m_prev, *m_next;
    } m_dlink_TeamMemberList;
    AIUpdateInterface *getAIUpdateInterface()
    {
        return m_ai;
    }
    void onCapture(Player *, Player *);

  protected:
    void setOrRestoreTeam(Team *, Bool);
};
class Team
{
  public:
    void *m_vtable;
    TeamPrototype *m_prototype;
    Team *m_next;
    Object *m_head;
    bool isInList_TeamMemberList(Object *o) const
    {
        return m_head == o || o->m_dlink_TeamMemberList.m_prev || o->m_dlink_TeamMemberList.m_next;
    }
    void removeFrom_TeamMemberList(Object *);
    void prependTo_TeamMemberList(Object *);
    Player *getControllingPlayer() const;
    const TeamPrototype *getPrototype() const
    {
        return m_prototype;
    }
};

void Object::setOrRestoreTeam(Team *team, Bool restoring)
{
    // don't do anything if the team hasn't changed
    if (m_team == team)
        return;

    Team *oldTeam = m_team;

    // Before Switch //////////////////////////
    if (m_team)
    {
        if (m_team->isInList_TeamMemberList(this))
        {
            m_team->removeFrom_TeamMemberList(this);
            m_team->getControllingPlayer()->becomingTeamMember(this, false);
        }
    }

    // Switch //////////////////////////
    m_team = team;

    // After Switch //////////////////////////
    if (m_team)
    {
        if (!m_team->isInList_TeamMemberList(this))
        {
            m_team->prependTo_TeamMemberList(this);
            m_team->getControllingPlayer()->becomingTeamMember(this, true);
        }

        // now, adjust the attitude of the unit to its new team.
        const TeamPrototype *proto = m_team->getPrototype();
        if (proto && proto->getTemplateInfo())
        {
            AIUpdateInterface *ai = getAIUpdateInterface();
            if (ai)
            {
                ai->setAttitude(proto->getTemplateInfo()->m_initialTeamAttitude);
                if (proto->getAttackPriorityName().isNotEmpty())
                {
                    AsciiString name = proto->getAttackPriorityName();
                    const AttackPriorityInfo *info = TheScriptEngine->getAttackInfo(name);
                    if (info && info->getName().isNotEmpty())
                    {
                        ai->setAttackInfo(info);
                    }
                }
            }
        }
        // emit message announcing object's new alliance
        Drawable *draw = getDrawable();
        if (draw)
            draw->changedTeam();
    }

    // This can't just go in ::defect, because some things just do setTeam.  The act of
    // setting a new team needs to tell the modules and do other important stuff.
    // And it needs to happen after the switch.
    if (oldTeam && team && !restoring)
        onCapture(oldTeam->getControllingPlayer(), team->getControllingPlayer());

    //
    // the team changed we have a change in priorities on the radar if we are
    // a candidate for the radar as it is
    //
    if (m_radarData)
    {

        // removing it and adding it will cause a resort to happen
        TheRadar->removeObject(this);
        TheRadar->addObject(this);
    }

    // Tell TheInGameUI that the object has changed hands
    Int oldPlayerIndex = (oldTeam) ? (oldTeam->getControllingPlayer()->getPlayerIndex()) : -1;
    Int newPlayerIndex = (m_team) ? (m_team->getControllingPlayer()->getPlayerIndex()) : -1;
    if (oldPlayerIndex != newPlayerIndex)
        TheInGameUI->objectChangedTeam(this, oldPlayerIndex, newPlayerIndex);
}
