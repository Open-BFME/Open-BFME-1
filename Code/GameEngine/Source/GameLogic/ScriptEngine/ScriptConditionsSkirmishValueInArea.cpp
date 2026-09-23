// ?evaluateSkirmishValueInArea@ScriptConditions@@IAE_NPAVCondition@@PAVParameter@@111@Z
// BFME RVA 0x0032BC80, 828 bytes. Last ret 20 ends at 0x0032BFA1;
// alignment to 0x0032BFA4, then six switch targets, int3 at 0x0032BFBC.
// Identity: ScriptConditions.cpp source sequence between evaluateTeamHasObjectStatus
// and evaluateSkirmishSuppliesWithinDistancePerimeter; dispatcher calls through
// ILT RVA 0x00037097 at 0x0032ED48 and 0x0032ED5B with the five matching arguments.
// BFME iterates a player mask and caches per-condition results, unlike the ZH body.
// Team next-link helper is independently decoded at RVA 0x000C8A30 as
// mov eax,[ecx+0x14]; ret. Its visible noinline definition tells VC7.1 it cannot
// mutate the prototype list and preserves retail's cached first/end iterators.
// Layout: Player +0x288, prototype head +0x274, Team +0x0C/+0x14/+0x30,
// Object +0x04/+0x344, ThingTemplate +0xD0/+0x47A, ScriptEngine +0x170D8.
// Unknown prototype identity remains address-derived; no shared layout is changed.
// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /ICode/Libraries/Source/WWVegas/WWLib /Ireference/shims/objectdlink
// stlport
#include "ascii_string.h"
#include "ObjectDlinkPmf.h"
#include <list>

typedef bool Bool;
typedef unsigned short PlayerMaskType;
class PolygonTrigger;

class Parameter {
public:
    int getInt() const { return field08; }
    const AsciiString &getString() const { return field10; }
    char pad00[8]; int field08; float field0c; AsciiString field10;
};
class Condition {
public:
    int getCustomData() const { return field44; }
    unsigned getCustomFrame() const { return field48; }
    void setCustomData(int v) { field44=v; }
    void setCustomFrame(unsigned v) { field48=v; }
    char pad00[0x44]; int field44; unsigned field48;
};
class Overridable {
public:
    virtual ~Overridable();
    const Overridable *getFinalOverride() const;
    Overridable *m_nextOverride;
};
class ThingTemplate : public Overridable {
public:
    char pad08[0xd0-8]; unsigned fieldd0;
    char pade0[0x47a-0xd4]; unsigned short m_buildCost;
};
class BfmeObjectInsideView {
public:
    Bool isInside(PolygonTrigger *) const;
};
static const ThingTemplate *getTemplate(const Object *o) {
    const ThingTemplate *t=*(const ThingTemplate *const *)((const char*)o+4);
    if (t && t->m_nextOverride)
        return (const ThingTemplate*)t->m_nextOverride->getFinalOverride();
    return t;
}
template<class T> class DLINK_ITERATOR {
public:
    typedef T *(T::*Next)() const;
    DLINK_ITERATOR(T *p, Next fn) : p(p),fn(fn) {}
    bool done() const { return p==0; }
    T *cur() const { return p; }
    void advance() { if(p) p=(p->*fn)(); }
private: T *p; Next fn;
};
class Team {
public:
    __declspec(noinline) Team *_bfme_nextInInstanceList() { return field14; }
    char pad00[12]; Object *field0c;
    char pad10[4]; Team *field14; char pad18[0x30-0x18]; bool m_enteredOrExited;
    bool didEnterOrExit() const { return m_enteredOrExited; }
    DLINK_ITERATOR<Object> iterate_TeamMemberList() const {
        return DLINK_ITERATOR<Object>(field0c,Object::dlink_next_TeamMemberList);
    }
};
class TeamIterator {
public:
    typedef Team *(Team::*Next)();
    TeamIterator(Team *p) : p(p),fn(&Team::_bfme_nextInInstanceList) {}
    bool done() const { return p==0; }
    Team *cur() const { return p; }
    void advance() { if(p) p=(p->*fn)(); }
private: Team *p; Next fn;
};
class Rva0032BC80Prototype {
public:
    char pad00[0x274]; Team *field274;
    TeamIterator iterate_TeamInstanceList() const { return TeamIterator(field274); }
};
class Player {
public:
    typedef _STL::list<Rva0032BC80Prototype*> PlayerTeamList;
    char pad00[0x288]; PlayerTeamList m_playerTeamPrototypes;
    const PlayerTeamList *getPlayerTeams() const { return &m_playerTeamPrototypes; }
};
class PlayerList {
public: Player *getEachPlayerFromMask(PlayerMaskType &);
};
class ScriptEngine {
public:
    virtual void slot00(); virtual void slot01(); virtual void slot02();
    virtual void slot03(); virtual void slot04(); virtual void slot05();
    virtual void slot06(); virtual void slot07(); virtual void slot08();
    virtual void slot09(); virtual void slot10(); virtual void slot11();
    virtual void slot12(); virtual void slot13(); virtual void slot14();
    virtual void slot15(); virtual void slot16(); virtual void slot17();
    virtual void slot18(); virtual void slot19(); virtual void slot20();
    virtual void slot21(); virtual PolygonTrigger *getQualifiedTriggerAreaByName(AsciiString);
    PlayerMaskType unidentified_0034DB40(const AsciiString &);
    unsigned getFrameObjectCountChanged() const { return field170d8; }
    char pad04[0x170d8-4]; unsigned field170d8;
};
extern ScriptEngine *TheScriptEngine;
extern PlayerList *ThePlayerList;
class ScriptConditions {
protected:
    Bool evaluateSkirmishValueInArea(Condition*,Parameter*,Parameter*,Parameter*,Parameter*);
};

Bool ScriptConditions::evaluateSkirmishValueInArea(Condition *pCondition,
    Parameter *pSkirmishPlayerParm, Parameter *pComparisonParm,
    Parameter *pMoneyParm, Parameter *pTriggerParm)
{
    // Existing ILT alias is spelled AsciiString&, but retail passes Parameter*.
    PlayerMaskType mask=TheScriptEngine->unidentified_0034DB40(*(const AsciiString*)pSkirmishPlayerParm);
    int totalCost=0;
    while(mask) {
        Player *player=ThePlayerList->getEachPlayerFromMask(mask);
        if(!player) continue;
        AsciiString triggerName=pTriggerParm->getString();
        PolygonTrigger *pTrig=TheScriptEngine->getQualifiedTriggerAreaByName(pTriggerParm->getString());
        if(!pTrig) continue;
        Player::PlayerTeamList::const_iterator it;
        Bool anyChanges=false;
        if(pCondition->getCustomData()==0) anyChanges=true;
        for(it=player->getPlayerTeams()->begin(); it!=player->getPlayerTeams()->end(); ++it) {
            if(anyChanges) break;
            for(TeamIterator iter=(*it)->iterate_TeamInstanceList(); !iter.done(); iter.advance()) {
                if(anyChanges) break;
                Team *team=iter.cur();
                if(!team) continue;
                if(team->didEnterOrExit()) anyChanges=true;
            }
        }
        if(TheScriptEngine->getFrameObjectCountChanged()!=pCondition->getCustomFrame()) anyChanges=true;
        if(!anyChanges) {
            if(pCondition->getCustomData()==-1) continue;
            if(pCondition->getCustomData()==1) return true;
        }
        for(it=player->getPlayerTeams()->begin(); it!=player->getPlayerTeams()->end(); ++it) {
            for(TeamIterator iter=(*it)->iterate_TeamInstanceList(); !iter.done(); iter.advance()) {
                Team *team=iter.cur();
                if(!team) continue;
                for(DLINK_ITERATOR<Object> iter=team->iterate_TeamMemberList(); !iter.done(); iter.advance()) {
                    Object *pObj=iter.cur();
                    if(!pObj) continue;
                    if(!(getTemplate(pObj)->fieldd0 & 0x1000000) && ((BfmeObjectInsideView*)pObj)->isInside(pTrig)) {
                        if(!(*(const unsigned char*)((char*)pObj+0x344)&1)) {
                            const ThingTemplate *tt=getTemplate(pObj);
                            if(!tt) continue;
                            totalCost+=tt->m_buildCost;
                        }
                    }
                }
            }
        }
    }
    Bool comparison=false;
    switch(pComparisonParm->getInt()) {
    case 0: comparison=totalCost<pMoneyParm->getInt(); break;
    case 1: comparison=totalCost<=pMoneyParm->getInt(); break;
    case 2: comparison=totalCost==pMoneyParm->getInt(); break;
    case 3: comparison=totalCost>=pMoneyParm->getInt(); break;
    case 4: comparison=totalCost>pMoneyParm->getInt(); break;
    case 5: comparison=totalCost!=pMoneyParm->getInt(); break;
    }
    pCondition->setCustomFrame(TheScriptEngine->getFrameObjectCountChanged());
    if(comparison) { pCondition->setCustomData(1); return true; }
    pCondition->setCustomData(-1);
    return false;
}

