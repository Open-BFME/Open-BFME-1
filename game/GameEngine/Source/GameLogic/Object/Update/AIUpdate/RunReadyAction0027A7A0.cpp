// cl: /DNDEBUG /DWIN32 /MD /GX
// stlport
// Retail 0x0027A7A0 (1083B). Established caller RunReadyObjectAI.cpp names
// bfmeRunReadyAction through ILT 0x0000E35E; the body also recurses there.
// Object and AI offsets are witnessed by the neighbouring AIUpdate bodies.
// Native inline findObjectByID is deliberately visible at ALL three calls:
// MSVC leaves two out of line and expands the third exactly as retail does.
// Forcing just the last call inline hoists the singleton load and changes
// this-pointer lifetimes. Vector scopes retain retail unwind states 0/1/2.
// VectorSwap00272AA0 is an ABI-only pointer-triple swap (ret 4), reached
// via ILT 0x00003D69; its address token makes no element-type identity claim.
#define _STLP_USE_STATIC_LIB 1
#define _STLP_NO_EXCEPTIONS 1
#define BFME_STLP_NODE_ALLOC 1
#include <vector>
#include <hash_map>
struct Coord3D { float x,y,z; Coord3D() {} Coord3D(const Coord3D& o) { x=o.x;y=o.y;z=o.z; } };
enum KindOfType {}; enum DamageType {}; enum DeathType {}; enum PathfindLayerEnum {};
class Object; class BfmeObjectAI; class Rva001B7200Locomotor;
struct Rva001B7200PathPoint { float real00; Coord3D coord04; float real10[3]; PathfindLayerEnum layer; int int20; };
class Path { public:
 void computePointOnPath(Object*,Rva001B7200Locomotor*,Rva001B7200PathPoint*,bool);
 Coord3D bfmeGetLastValidWaypointPosition() const;
 protected: virtual ~Path(); friend class BfmeObjectAI;
};
class Overridable { public: virtual ~Overridable(); Overridable *next;
 const Overridable *getFinalOverride() const { if(next) return next->getFinalOverride(); return this; }
};
class ThingTemplate : public Overridable { public: char pad08[0xd4-8]; unsigned kindWordD4; };
template<class T> struct OVERRIDE { const T *value; const T *operator->() const { if(!value) return 0; return (const T*)value->getFinalOverride(); } };
class Thing { public: bool isKindOf(KindOfType) const; void setPosition(const Coord3D*); };
class BfmeObjAS { public: BfmeObjAS *bfmeParentAS(int); };
class Rva001BEC40DwordSlot { public: void set(int); };
class AIUpdateInterface { public: void destroyPath(); };
class ReadyRelation0027A7A0;
struct ModelFlags0027A7A0 {
 unsigned words[10];
 __forceinline unsigned test(unsigned n) const { return words[n>>5]&(1u<<(n&31)); }
 __forceinline void set(unsigned n) { words[n>>5]|=1u<<(n&31); }
};
class Object { public:
 void *vptr; OVERRIDE<ThingTemplate> m_template;
 char pad08[0x110-8]; ModelFlags0027A7A0 conditions;
 char pad138[0x204-0x138]; BfmeObjectAI *aiAt204;
 void kill(DamageType,DeathType);
 void notifyModelConditionChanged();
 void *unidentified_001BFE20() const;
};
__forceinline void markKilled(Object *object) { if(!object->conditions.test(115)) { object->conditions.set(115); object->notifyModelConditionChanged(); } }
typedef _STL::vector<int> ObjectIDs;
class VectorSwap00272AA0 { public: void swap(ObjectIDs&); };
typedef _STL::hash_map<int,Object*,_STL::hash<int>,_STL::equal_to<int> > ObjectHash;
class GameLogic { public:
 
 Object *findObjectByID(int id) { if(id==0) return 0; ObjectHash::iterator it=objects.find(id); if(it==objects.end()) return 0; return (*it).second; }
 char pad[0xb0]; ObjectHash objects;
};
extern GameLogic *TheBfmeGameLogic;
class Waypoint;
class TerrainLogic { public:
virtual void unused0();
virtual void unused1();
virtual void unused2();
virtual void unused3();
virtual void unused4();
virtual void unused5();
virtual void unused6();
virtual void unused7();
virtual void unused8();
virtual void unused9();
virtual void unused10();
virtual void unused11();
virtual void unused12();
virtual void unused13();
virtual void unused14();
virtual void unused15();
virtual void unused16();
virtual void unused17();
virtual void unused18();
virtual void unused19();
virtual void unused20();
virtual void unused21();
virtual void unused22();
virtual void unused23();
virtual void unused24();
virtual void unused25();
virtual void unused26();
virtual void unused27();
virtual void unused28();
virtual void unused29();
virtual void unused30();
virtual void unused31();
virtual Waypoint *getWaypointByID(unsigned);
PathfindLayerEnum getLayerForDestination(Object*,const Coord3D*);
};
class ReadyRelation0027A7A0 { public:
virtual void unused0();
virtual void unused1();
virtual void unused2();
virtual void unused3();
virtual void unused4();
virtual void unused5();
virtual void unused6();
virtual void unused7();
virtual void unused8();
virtual void unused9();
virtual void unused10();
virtual void unused11();
virtual void unused12();
virtual void unused13();
virtual void unused14();
virtual void unused15();
virtual void unused16();
virtual void unused17();
virtual void unused18();
virtual void unused19();
virtual void unused20();
virtual void unused21();
virtual void unused22();
virtual void unused23();
virtual void unused24();
virtual void unused25();
virtual void unused26();
virtual void unused27();
virtual void unused28();
virtual void unused29();
virtual void unused30();
virtual void unused31();
virtual void unused32();
virtual void unused33();
virtual void unused34();
virtual void unused35();
virtual void unused36();
virtual void unused37();
virtual void unused38();
virtual void unused39();
virtual void unused40();
virtual void unused41();
virtual void unused42();
virtual void unused43();
virtual void unused44();
virtual void unused45();
virtual void unused46();
virtual void unused47();
virtual void unused48();
virtual void unused49();
virtual void unused50();
virtual void unused51();
virtual void unused52();
virtual void unused53();
virtual void unused54();
virtual void unused55();
virtual void unused56();
virtual void unused57();
virtual void unused58();
virtual void unused59();
virtual void unused60();
virtual void unused61();
virtual void unused62();
virtual void unused63();
virtual void unused64();
virtual void unused65();
virtual void unused66();
virtual void unused67();
virtual void unused68();
virtual void unused69();
virtual void unused70();
virtual void unused71();
virtual void unused72();
virtual void unused73();
virtual void unused74();
virtual void unused75();
virtual void unused76();
virtual void unused77();
virtual void unused78();
virtual void unused79();
virtual void unused80();
virtual void unused81();
virtual void unused82();
virtual void unused83();
virtual void unused84();
virtual void unused85();
virtual void unused86();
virtual void unused87();
virtual void unused88();
virtual void unused89();
virtual void unused90();
virtual void unused91();
virtual void unused92();
virtual void unused93();
virtual void unused94();
virtual void unused95();
virtual void unused96();
virtual void unused97();
virtual void unused98();
virtual void unused99();
virtual void unused100();
virtual void unused101();
virtual void unused102();
virtual void unused103();
virtual void unused104();
virtual void unused105();
virtual void unused106();
virtual void unused107();
virtual void unused108();
virtual void unused109();
virtual void unused110();
virtual void unused111();
virtual void unused112();
virtual void unused113();
virtual void unused114();
virtual void unused115();
virtual void unused116();
virtual void unused117();
virtual void unused118();
virtual void unused119();
virtual void unused120();
virtual void unused121();
virtual void unused122();
virtual void collect(ObjectIDs*,ObjectIDs*,ObjectIDs*);
};
class BfmeObjectAI { public:
virtual void unused0();
virtual void unused1();
virtual void unused2();
virtual void unused3();
virtual void unused4();
virtual void unused5();
virtual void unused6();
virtual void unused7();
virtual void unused8();
virtual void unused9();
virtual void unused10();
virtual void unused11();
virtual void unused12();
virtual void unused13();
virtual void unused14();
virtual void unused15();
virtual void unused16();
virtual void unused17();
virtual void unused18();
virtual void unused19();
virtual void unused20();
virtual void unused21();
virtual void unused22();
virtual void unused23();
virtual void unused24();
virtual void unused25();
virtual void unused26();
virtual void unused27();
virtual void unused28();
virtual void unused29();
virtual void unused30();
virtual void unused31();
virtual void unused32();
virtual void unused33();
virtual void unused34();
virtual void unused35();
virtual void unused36();
virtual void unused37();
virtual void unused38();
virtual void unused39();
virtual void unused40();
virtual void unused41();
virtual void unused42();
virtual void unused43();
virtual void unused44();
virtual void unused45();
virtual void unused46();
virtual void unused47();
virtual void unused48();
virtual void unused49();
virtual void unused50();
virtual void unused51();
virtual void unused52();
virtual void unused53();
virtual void unused54();
virtual void unused55();
virtual void unused56();
virtual void unused57();
virtual void unused58();
virtual void unused59();
virtual void unused60();
virtual void unused61();
virtual void unused62();
virtual void unused63();
virtual void unused64();
virtual void unused65();
virtual void unused66();
virtual void unused67();
virtual void unused68();
virtual void unused69();
virtual void unused70();
virtual void unused71();
virtual void unused72();
virtual void unused73();
virtual void unused74();
virtual void unused75();
virtual void unused76();
virtual void unused77();
virtual void unused78();
virtual void unused79();
virtual void unused80();
virtual void unused81();
virtual void unused82();
virtual void unused83();
virtual void unused84();
virtual void unused85();
virtual void unused86();
virtual void unused87();
virtual void unused88();
virtual void unused89();
virtual void unused90();
virtual void unused91();
virtual void unused92();
virtual void unused93();
virtual void unused94();
virtual void unused95();
virtual void unused96();
virtual void unused97();
virtual void unused98();
virtual void unused99();
virtual void unused100();
virtual void unused101();
virtual void unused102();
virtual void unused103();
virtual void unused104();
virtual void unused105();
virtual void unused106();
virtual void unused107();
virtual void unused108();
virtual void unused109();
virtual void unused110();
virtual void unused111();
virtual void unused112();
virtual void unused113();
virtual void unused114();
virtual void unused115();
virtual void unused116();
virtual void unused117();
virtual void unused118();
virtual void unused119();
virtual void unused120();
virtual void unused121();
virtual void setLocomotorGoalNone();

 void bfmeRunReadyAction();
 __forceinline void clearPath() {
  if(m_path) { Path *path=m_path; path->Path::~Path(); ::operator delete(path); }
  m_path=0; waiting31e=false; m_isBlockedAndStuck=false; m_isAttackPath=false;
  setLocomotorGoalNone();
 }
 char pad04[4]; Object *m_object;
 char pad0c[0x140-0xc]; Path *m_path;
 char pad144[0x1cc-0x144]; Rva001B7200Locomotor *m_curLocomotor;
 char pad1d0[0x31e-0x1d0]; bool waiting31e; bool m_isAttackPath;
 char pad320[6]; bool m_isBlockedAndStuck;
};

extern TerrainLogic *TheTerrainLogic;
void BfmeObjectAI::bfmeRunReadyAction()
{
 Object *object=m_object;
 if(!(object->m_template->kindWordD4&0x1000)) {
  Object *parent=(Object*)((BfmeObjAS*)object)->bfmeParentAS(0);
  if(parent) {
   BfmeObjectAI *parentAI=parent->aiAt204;
   if(parentAI) { if(parentAI->m_path) parentAI->bfmeRunReadyAction(); else ((AIUpdateInterface*)this)->destroyPath(); }
   return;
  }
 }
 if(!m_path) return;
 Rva001B7200PathPoint point;
 m_path->computePointOnPath(object,m_curLocomotor,&point,false);
 if(point.int20==0x7fffffff || TheTerrainLogic->getWaypointByID(point.int20)) { ((AIUpdateInterface*)this)->destroyPath(); return; }
 if(((Thing*)object)->isKindOf((KindOfType)108)) {
  ReadyRelation0027A7A0 *relation=(ReadyRelation0027A7A0*)object->unidentified_001BFE20();
  if(!relation) return;
  ObjectIDs first,second,third;
  relation->collect(&first,&second,&third);
  for(ObjectIDs::iterator it=second.begin();it!=second.end();++it) {
   Object *other=TheBfmeGameLogic->findObjectByID(*it);
   if(other) { other->kill((DamageType)8,(DeathType)0); markKilled(other); }
  }
  bool moved=false;
  if(third.size()<first.size()) { ((VectorSwap00272AA0*)&third)->swap(first); moved=true; }
  for(ObjectIDs::iterator it=first.begin();it!=first.end();++it) {
   Object *other=TheBfmeGameLogic->findObjectByID(*it);
   if(other) { other->kill((DamageType)8,(DeathType)0); markKilled(other); }
  }
  for(ObjectIDs::iterator it=third.begin();it!=third.end();++it) {
   Object *other=TheBfmeGameLogic->findObjectByID(*it);
   if(other) { BfmeObjectAI *ai=other->aiAt204; if(ai) ai->clearPath(); }
  }
  if(moved) {
   Coord3D last=m_path->bfmeGetLastValidWaypointPosition();
   ((Thing*)object)->setPosition(&last);
   PathfindLayerEnum layer=TheTerrainLogic->getLayerForDestination(object,&last);
   ((Rva001BEC40DwordSlot*)object)->set(layer);
  }
  clearPath();
 } else object->kill((DamageType)8,(DeathType)0);
}
