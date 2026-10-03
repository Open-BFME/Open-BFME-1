// Retail 0x0023C5E0 spans 792 bytes, including ret 12 at +0x315.
// The old 784-byte dump omitted the final eight epilogue bytes.
// Retail random-call literals name HordeContain.cpp at lines 4092/4151,
// but no caller or aligned vtable proves this method's owner or full name.
// Keep an opaque address identity. The secondary view reaches a member-list
// query through [this-0xC4] vtable slot +0x104; the set is observed at +0x30.
// The existing noinline lookup body exposes its read-only effects to MSVC,
// reproducing retail's register allocation without changing its call ABI.
// cl: /DNDEBUG /MD /EHsc- /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/GameEngine/Source/GameLogic/Object /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include
// stlport
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <list>
#include <set>
#include <math.h>
#include "basetype.h"
#define BFME_HAVE_COORD3D
#include "object.h"
extern float Rva0002CCA5GetGameLogicRandomValueRealThunk(float,float,char*,int);
#define BFME_GAMELOGIC_LOOKUP_VISIBLE
#include "../../../Common/Thing/GameLogicObjectLookup.h"
extern GameLogic *TheGameLogic;
template<int N> class Slots0023C5E0 : public Slots0023C5E0<N-1> { public: virtual void unused(char (*)[N])=0; };
template<> class Slots0023C5E0<0> {};
class Secondary0023C5E0 : public Slots0023C5E0<65> { public: virtual const _STL::list<Object*> *slot104()=0; };
class Rva0023C5E0 {
public:
 char pad[0x30]; _STL::set<unsigned> at030;
 Object *method(bool exclude,const Coord3D *position,float radius);
};
Object *Rva0023C5E0::method(bool exclude,const Coord3D *position,float radius) {
 const _STL::list<Object*> *members=((Secondary0023C5E0*)((char*)this-0xc4))->slot104();
 float limit=99999.0f;
 if(radius>0.0f) limit=radius;
 if(members->empty()) {
  if(at030.empty()) return 0;
  if(position) {
   float bestDistance=99999.0f;
   Object *best=0;
   for(_STL::set<unsigned>::iterator it=at030.begin();it!=at030.end();++it) {
    Object *obj=TheGameLogic->findObjectByID(*it);
    if(!obj || (obj->m_privateStatus&1)) continue;
    if((obj->m_status[1]&0x40000000) && exclude) continue;
    Coord3D delta; delta.set(position);
    delta.sub(&obj->m_cachedPos);
    float distance=delta.length();
    if(distance<limit) {
     if(radius>0.0f) distance*=Rva0002CCA5GetGameLogicRandomValueRealThunk(0.66f,1.33f,"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Contain\\HordeContain\\HordeContain.cpp",4092);
     if(distance<bestDistance) {best=obj;bestDistance=distance;}
    }
   }
   return best;
  }
  if(exclude) {
   for(_STL::set<unsigned>::iterator it=at030.begin();it!=at030.end();++it) {
    Object *obj=TheGameLogic->findObjectByID(*it);
    if(obj && !(obj->m_status[1]&0x40000000)) return obj;
   }
   return 0;
  }
  unsigned id = *at030.begin();
  return TheGameLogic->findObjectByID(id);
 }
 if(position) {
  float bestDistance=99999.0f;
  Object *best=0;
  for(_STL::list<Object*>::const_iterator it=members->begin();it!=members->end();++it) {
   Object *obj=*it;
   if(!obj) continue;
   if((obj->m_status[1]&0x40000000) && exclude) continue;
   Coord3D delta; delta.set(position);
   delta.sub(&obj->m_cachedPos);
   float distance=delta.length();
   if(distance<limit) {
    if(radius>0.0f) {float factor=Rva0002CCA5GetGameLogicRandomValueRealThunk(0.66f,1.33f,"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Contain\\HordeContain\\HordeContain.cpp",4151); distance*=factor;}
    if(distance<bestDistance) {best=obj;bestDistance=distance;}
   }
  }
  return best;
 }
 if(exclude) {
  for(_STL::list<Object*>::const_iterator it=members->begin();it!=members->end();++it) {
   Object *obj=*it;
   if(obj && !(obj->m_status[1]&0x40000000)) return obj;
  }
 }
 return *members->begin();
}
