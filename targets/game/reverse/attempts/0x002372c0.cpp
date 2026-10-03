// ?d_002372c0@@YAXXZ
// partial score=0.2072 date=2026-10-02
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib /Igame/GameEngine/Source/GameLogic/Object /Igame/GameEngine/Source/GameLogic /Igame/Libraries/Include
// stlport
#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <hash_map>
#include <list>
#include "basetype.h"
enum PathfindLayerEnum { PATHFIND_LAYER_GROUND=0 };
#define BFME_HAVE_COORD3D 1
#define THING_TU_MEMBERS void setPosition(const Coord3D *);
#define OBJECT_TU_MEMBERS int getLayer() const; void setLayer(PathfindLayerEnum);
#include "object.h"
#include "game_logic.h"
class Gen_001C5BE0 { public: unsigned char bfmeIsClear() const; };
class Pathfinder { public: bool validMovementPosition(const Coord3D *,PathfindLayerEnum,unsigned int,Object *); };
class AI;
extern AI *TheAI;
struct Rva002372C0AIView { char head[12]; Pathfinder *pathfinder; };
struct Rva002372C0AIUpdateView { char head[0x1b8]; unsigned int m_1b8; };
typedef _STL::list<Object *> Rva002372C0Members;
typedef _STL::hash_map<unsigned int,Object *,_STL::hash<unsigned int>,_STL::equal_to<unsigned int> > Rva002372C0Hash;
struct Rva002372C0LogicView {
 char head[0xb0]; Rva002372C0Hash objects;
 __forceinline Object *find(unsigned int id) {
  Rva002372C0Hash::iterator it=objects.find(id);
  if(it==objects.end()) return 0;
  return it->second;
 }
};
template<int N> class Rva002372C0PrimarySlots: public Rva002372C0PrimarySlots<N-1> { public: virtual int unused(char (*)[N])=0; };
template<> class Rva002372C0PrimarySlots<0> {};
class Rva002372C0Primary:public Rva002372C0PrimarySlots<65> { public: virtual const Rva002372C0Members &getMemberList() const=0; };
struct Rva002372C0Node { unsigned int color; Rva002372C0Node *parent,*next,*right; unsigned int key; };
namespace _STL { struct _Rb_tree_node_base; template<class T> struct _Rb_global { static _Rb_tree_node_base *_M_increment(_Rb_tree_node_base *); }; }
class Rva002372C0Owner {
 public: void rva002372C0(Object *target);
 char head[0x30]; Rva002372C0Node *index;
};
void Rva002372C0Owner::rva002372C0(Object *target)
{
 Coord3D centroid; centroid.zero();
 int count=0;
 int layer=1;
 for(Rva002372C0Node *it=index->next;it!=index;it=(Rva002372C0Node*)_STL::_Rb_global<bool>::_M_increment((_STL::_Rb_tree_node_base*)it)) {
  unsigned int id=it->key;
  if(id!=0) {
   Object *object=((Rva002372C0LogicView*)TheGameLogic)->find(id);
   if(object && ((Gen_001C5BE0*)object)->bfmeIsClear()) { ++count; centroid.add(&object->m_cachedPos); }
  }
 }
 const Rva002372C0Members &members=((Rva002372C0Primary*)((char*)this-0xc4))->getMemberList();
 for(Rva002372C0Members::const_iterator it=members.begin();it!=members.end();++it) {
  Object *object=*it;
  if(object) { ++count; centroid.add(&object->m_cachedPos); }
 }
 if(count>0) {
  centroid.scale(1.0f/count);
  Coord3D selected=target->m_cachedPos;
  float nearest=-1.0f;
  Coord3D candidate;
  for(Rva002372C0Node *it=index->next;it!=index;it=(Rva002372C0Node*)_STL::_Rb_global<bool>::_M_increment((_STL::_Rb_tree_node_base*)it)) {
   unsigned int id=it->key;
   if(id!=0) {
    Object *object=((Rva002372C0LogicView*)TheGameLogic)->find(id);
    if(object && ((Gen_001C5BE0*)object)->bfmeIsClear()) {
     candidate=object->m_cachedPos;
     float dx=candidate.x-centroid.x,dy=candidate.y-centroid.y,dz=candidate.z-centroid.z;
     if(nearest<0.0f || dx*dx+dy*dy+dz*dz<nearest) {
      selected=candidate; nearest=dx*dx+dy*dy+dz*dz; layer=object->getLayer();
     }
    }
   }
  }
  for(Rva002372C0Members::const_iterator it=members.begin();it!=members.end();++it) {
   Object *object=*it;
   candidate=object->m_cachedPos;
   unsigned int surfaces=((Rva002372C0AIUpdateView*)target->m_ai)->m_1b8;
   Pathfinder *pathfinder=((Rva002372C0AIView*)TheAI)->pathfinder;
   if(pathfinder->validMovementPosition(&candidate,(PathfindLayerEnum)target->getLayer(),surfaces,target)) {
    float dx=candidate.x-centroid.x,dy=candidate.y-centroid.y,dz=candidate.z-centroid.z;
    if(nearest<0.0f || dx*dx+dy*dy+dz*dz<nearest) {
     selected=candidate; nearest=dx*dx+dy*dy+dz*dz; layer=object->getLayer();
    }
   }
  }
  target->setPosition(&selected); target->setLayer((PathfindLayerEnum)layer);
 }
}
