// ?setTriggerAreaFlagsForChangeInPosition@Object@@IAEXXZ
// partial score=0.978043 date=2026-09-28
// cl: /O2 /Ob1 /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath /Igame/GameEngine/Include/Precompiled
// Full retail boundary: ILT0001B5D1 targets001C8D80; RET at001C9169.
// Existing001C8E7D claim starts inside this function. ZH Object.cpp establishes
// the trigger transition algorithm; BFME adds path result and Lua events.
#include "ascii_string.h"
#include "coord.h"
#include "../../Common/System/snapshot.h"
enum KindOfType { KINDOF_INVALID=0 };
class Overridable { public: const Overridable *getFinalOverride() const; void *vptr; Overridable *next; };
class ThingTemplate : public Overridable { public: char pad08[0xc0]; unsigned kind[3]; bool isKindOf(KindOfType k) const { return (kind[(unsigned)k>>5] & (1<<((unsigned)k&31)))!=0; } };
#define BFME_HAVE_COORD3D
#define THING_TU_MEMBERS const ThingTemplate *getTemplate() const { const ThingTemplate *t=m_template; if(!t) return 0; if(t->next) t=(const ThingTemplate *)t->next->getFinalOverride(); return t; } bool isKindOf(KindOfType) const;
#define OBJECT_TU_MEMBERS protected: void setTriggerAreaFlagsForChangeInPosition(); void updateTriggerAreaFlags();
#include "object.h"
class PolygonTrigger { public: void *vptr; PolygonTrigger *next; AsciiString name; bool pointInTrigger(ICoord3D &) const; };
class Rva0018F050TriggerArea { public: void notifyObjectExited(Object *); void notifyObjectEntered(Object *); };
struct BfmeThingENG { void bfmeGoENG(void *); };
class GameLogic { public: char pad00[0x3c]; unsigned frame; char pad40[0x12c]; unsigned changed; void sendObjectDestroyed(Object *); };
extern GameLogic *TheGameLogic;
class AI { public: char pad00[0xc]; void *pathfinder; };
extern AI *TheAI;
extern void *TheTerrainLogic;
extern "C" PolygonTrigger **g_bfmePolygonTriggerTable;
class ScriptEngine { public: void AppendDebugMessage(const AsciiString &,bool); };
extern ScriptEngine *TheScriptEngine;
class DelayedLuaEventList;
class BfmeOwnerBR { public: void bfmeGo939B(int,Object *,DelayedLuaEventList *); };
extern "C" BfmeOwnerBR *g_bfmeOwnerBR;
struct BfmeDelayedLuaEventList { BfmeDelayedLuaEventList(); ~BfmeDelayedLuaEventList(); char bytes[0x4c]; };
class BfmeDelayedLuaEvent { public: BfmeDelayedLuaEvent(); ~BfmeDelayedLuaEvent(); char pad00[0x10]; AsciiString text; int type; };
// Head-only ABI view; the enclosing storage owns the three events.
extern int bfmeVtable000A1B30[];
class DelayedLuaEventList {
public:
    DelayedLuaEventList() throw() {}
    ~DelayedLuaEventList() { *(int **)this=bfmeVtable000A1B30; }
    virtual const char *GetSnapshotName(); virtual void LoadPostProcess(); virtual void DoXfer(Xfer &);
};
struct Rva001C8D80EntryList { DelayedLuaEventList head; BfmeDelayedLuaEvent events[3]; };
void d_001af550(); void d_003e9d80();
class Rva001C8D80Call {};
inline void terrainMoved(void *p,Object *o) { union { void (*raw)(); void (Rva001C8D80Call::*fn)(Object *); } c; c.raw=d_001af550; (((Rva001C8D80Call *)p)->*c.fn)(o); }
inline bool pathMoved(void *p,Object *o,const Coord3D *v) { union { void (*raw)(); bool (Rva001C8D80Call::*fn)(Object *,const Coord3D *); } c; c.raw=d_003e9d80; return (((Rva001C8D80Call *)p)->*c.fn)(o,v); }
struct Rva001C8D80Record { PolygonTrigger *trigger; bool entered,exited,inside; char pad; };
inline Rva001C8D80Record *records(Object *p) { return (Rva001C8D80Record *)((char *)p+0x2d8); }
inline unsigned &eventFrame(Object *p) { return *(unsigned *)((char *)p+0x300); }
inline ICoord3D &lastPos(Object *p) { return *(ICoord3D *)((char *)p+0x304); }
inline signed char &active(Object *p) { return *(signed char *)((char *)p+0x346); }
void Object::setTriggerAreaFlagsForChangeInPosition()
{
    if(getTemplate()->isKindOf((KindOfType)25) || getTemplate()->isKindOf((KindOfType)88)) return;
    ICoord3D iPos;
    Coord3D pos; pos.x=m_cachedPos.x; pos.y=m_cachedPos.y; pos.z=m_cachedPos.z;
    iPos.x=(int)pos.x; iPos.y=(int)pos.y; iPos.z=0;
    if(lastPos(this).x==iPos.x && lastPos(this).y==iPos.y) return;
    if(!isKindOf((KindOfType)2)) {
        if(isKindOf((KindOfType)8)||isKindOf((KindOfType)9)||isKindOf((KindOfType)11)||isKindOf((KindOfType)10)) terrainMoved(TheTerrainLogic,this);
    }
    if(pathMoved(TheAI->pathfinder,this,&m_cachedPos) && TheGameLogic->frame>3) TheGameLogic->sendObjectDestroyed(this);
    unsigned now=TheGameLogic->frame;
    if(eventFrame(this)!=0 && eventFrame(this)!=now) updateTriggerAreaFlags();
    int i;
    for(i=0;i<active(this);++i) {
        if(records(this)[i].trigger && !records(this)[i].trigger->pointInTrigger(lastPos(this))) {
            records(this)[i].inside=false; records(this)[i].exited=true; eventFrame(this)=now;
            if(m_team) ((BfmeThingENG *)m_team)->bfmeGoENG(this);
            TheGameLogic->changed=TheGameLogic->frame;
            BfmeDelayedLuaEventList list;
            ((AsciiString *)(list.bytes+0x14))->set(records(this)[i].trigger->name);
            *(int *)(list.bytes+0x18)=4;
            g_bfmeOwnerBR->bfmeGo939B(5,this,(DelayedLuaEventList *)&list);
            ((Rva0018F050TriggerArea *)records(this)[i].trigger)->notifyObjectExited(this);
        }
    }
    lastPos(this)=iPos;
    for(PolygonTrigger *trigger=*g_bfmePolygonTriggerTable;trigger;trigger=trigger->next) {
        bool skip=false;
        for(i=0;i<active(this);i++) { if(records(this)[i].trigger==trigger) { skip=true; break; } }
        if(skip) continue;
        if(trigger->pointInTrigger(lastPos(this))) {
            if(active(this)<5) {
                records(this)[active(this)].inside=true;
                records(this)[active(this)].entered=true;
                records(this)[active(this)].exited=false;
                records(this)[active(this)].trigger=trigger;
                eventFrame(this)=now;
                if(m_team) ((BfmeThingENG *)m_team)->bfmeGoENG(this);
                TheGameLogic->changed=TheGameLogic->frame;
                ++active(this);
                Rva001C8D80EntryList list;
                list.events[0].text.set(records(this)[i].trigger->name);
                list.events[0].type=4;
                g_bfmeOwnerBR->bfmeGo939B(3,this,&list.head);
                ((Rva0018F050TriggerArea *)trigger)->notifyObjectEntered(this);
            } else {
                static bool didWarn=false;
                if(!didWarn) { didWarn=true; TheScriptEngine->AppendDebugMessage("***WARNING - Too many nested trigger areas. ***",true); }
            }
        }
    }
}


