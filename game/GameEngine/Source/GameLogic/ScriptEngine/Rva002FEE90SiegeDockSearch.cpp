// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/stringinline
#include "StringInline.h"

struct Coord3D { float x,y,z; };
class Object;
class PartitionManager;
class NameKeyGenerator { public: int nameToKey(const char *); };
extern NameKeyGenerator *TheNameKeyGenerator;
extern void j_000022bb();
extern void j_0001b185();
extern void j_0002ae23();
extern void j_0002c471();
extern void j_0003add7();

class Rva002FEE90Calls {};
template<class R> __forceinline R call0(void (*p)(), void *self) {
 typedef R (Rva002FEE90Calls::*F)(); union {void (*p)(); F f;} u; u.p=p;
 return (((Rva002FEE90Calls*)self)->*u.f)();
}
template<class R,class A> __forceinline R call1(void (*p)(), void *self,A a) {
 typedef R (Rva002FEE90Calls::*F)(A); union {void (*p)(); F f;} u; u.p=p;
 return (((Rva002FEE90Calls*)self)->*u.f)(a);
}
struct Rva002FEE90Template { int unknown00; Rva002FEE90Template *next; char pad08[0xc8]; unsigned flagsD0; };
struct Rva002FEE90Parameter { char pad00[12]; float value0C; AsciiString string10; };
class Rva002FEE90Special {
public:
 virtual void slot00()=0;
 virtual bool ready()=0;
 virtual void slot02()=0; virtual void slot03()=0; virtual void slot04()=0;
 virtual void slot05()=0; virtual void slot06()=0; virtual void slot07()=0;
 virtual void slot08()=0; virtual void slot09()=0; virtual void slot10()=0;
 virtual void slot11()=0; virtual void apply(Object*,int)=0;
};
class Object { public: int unknown00; Rva002FEE90Template *template04; char pad08[0x6c]; unsigned m_id; };
class Rva002FEE90Dock { public: virtual void slot00()=0; virtual void slot01()=0; virtual void slot02()=0; virtual bool accepts(unsigned)=0; };
class ScriptEngine { public:
 virtual void slot00()=0; virtual void slot01()=0; virtual void slot02()=0;
 virtual void slot03()=0; virtual void slot04()=0; virtual void slot05()=0;
 virtual void slot06()=0; virtual void slot07()=0; virtual void slot08()=0;
 virtual void slot09()=0; virtual void slot10()=0; virtual void slot11()=0;
 virtual void slot12()=0; virtual void slot13()=0; virtual void slot14()=0;
 virtual void slot15()=0; virtual void slot16()=0; virtual void slot17()=0;
 virtual void slot18()=0; virtual void slot19()=0; virtual void slot20()=0;
 virtual void slot21()=0; virtual void slot22()=0; virtual void slot23()=0;
 virtual void slot24()=0; virtual void slot25()=0;
 virtual Object *getUnitNamed(const AsciiString&)=0;
};
struct Rva002FEE90Waypoint { char pad00[12]; Coord3D position; };
class TerrainLogic { public:
 virtual void slot00()=0; virtual void slot01()=0; virtual void slot02()=0;
 virtual void slot03()=0; virtual void slot04()=0; virtual void slot05()=0;
 virtual void slot06()=0; virtual void slot07()=0; virtual void slot08()=0;
 virtual void slot09()=0; virtual void slot10()=0; virtual void slot11()=0;
 virtual void slot12()=0; virtual void slot13()=0; virtual void slot14()=0;
 virtual void slot15()=0; virtual void slot16()=0; virtual void slot17()=0;
 virtual void slot18()=0; virtual void slot19()=0; virtual void slot20()=0;
 virtual void slot21()=0; virtual void slot22()=0; virtual void slot23()=0;
 virtual void slot24()=0; virtual void slot25()=0; virtual void slot26()=0;
 virtual void slot27()=0; virtual void slot28()=0; virtual void slot29()=0;
 virtual void slot30()=0; virtual Rva002FEE90Waypoint *findWaypoint(AsciiString)=0;
};
template<unsigned N> class BitFlags { public: enum BogusInitType {kInit}; BitFlags(BogusInitType,int); unsigned bits[6]; };
extern const BitFlags<192> KINDOFMASK_NONE;
class PartitionFilter { public:
 PartitionFilter():m_next(0) {} virtual ~PartitionFilter() {} virtual bool allow(Object*)=0; virtual int getPlayerMask(); PartitionFilter *m_next;
};
class PartitionFilterAcceptByKindOf: public PartitionFilter {public:
 PartitionFilterAcceptByKindOf(const BitFlags<192>&,const BitFlags<192>&);
 virtual bool allow(Object*); BitFlags<192> first,second;
};
struct Rva002FEE90Entry { Object *object; int unknown04; };
struct Rva002FEE90Data { Rva002FEE90Entry *begin,*end,*capacity,*current; };
struct BfmeWideResult { Rva002FEE90Data *value; BfmeWideResult(const BfmeWideResult&); ~BfmeWideResult() {call0<void>(j_0002c471,this);} Rva002FEE90Entry *endPointer() { return value->end; } Object *next(Object *&object) {Rva002FEE90Entry *end=endPointer(); if(value->current==end)return 0; object=(value->current++)->object; return object;} };
// The matched 57-byte wrapper at 0x009F2960 forwards raw stack words.
// Keep the radius's IEEE bits when calling its ledger-owned integer signature.
class BfmeWideForwardC {public: BfmeWideResult bfmeForwardWideC(int,int,int,int,int);};
extern PartitionManager *ThePartitionManager;
extern ScriptEngine *TheScriptEngine;
extern TerrainLogic *TheTerrainLogic;
class Rva002FEE90ScriptActions {public: void apply(const AsciiString&,Rva002FEE90Parameter*,Rva002FEE90Parameter*);};
// TerrainLogic identity: established DIR32 VA 0x012EF4CC; virtual waypoint lookup at +0x7C.
// Retail 0x002FEE90: ScriptActions dispatcher callee; method identity unknown.
void Rva002FEE90ScriptActions::apply(const AsciiString &name,Rva002FEE90Parameter *waypoint,Rva002FEE90Parameter *radius) {
 Object *unit=TheScriptEngine->getUnitNamed(name); if(!unit)return;
 Rva002FEE90Template *data=unit->template04;
 if(data && data->next) data=call0<Rva002FEE90Template*>(j_000022bb,data->next);
 if(!(data->flagsD0&0x10000000))return;
 Rva002FEE90Special *power=call1<Rva002FEE90Special*>(j_0001b185,unit,0x2e);
 if(!power || !power->ready())return;
 Rva002FEE90Waypoint *wp=TheTerrainLogic->findWaypoint(waypoint->string10); if(!wp)return;
 Coord3D position; position.x=wp->position.x; position.y=wp->position.y; position.z=wp->position.z; float distance=radius->value0C;
 BfmeWideResult iterator=((BfmeWideForwardC*)ThePartitionManager)->bfmeForwardWideC((int)&position,*reinterpret_cast<const int*>(&distance),0,(int)&PartitionFilterAcceptByKindOf(BitFlags<192>(BitFlags<192>::kInit,59),KINDOFMASK_NONE),1);
 Object *target;
 while((iterator.next(target))!=0) {
  static int key=call1<int>(j_0003add7,TheNameKeyGenerator,(const char*)"SiegeDockingBehavior");
  char *module=call1<char*>(j_0002ae23,target,key);
  if(!module)continue; unsigned id=unit->m_id; if(((Rva002FEE90Dock*)(module+0x20))->accepts(id)) {power->apply(target,2);break;}
 }
}
