// ?d_0023c5e0@@YAXXZ
// partial score=0.9911616161616161 date=2026-09-27
// Compile symbol: ?select@MemberSelection0023C5E0@@QAEPAVObject@@_NPBUCoord3D@@M@Z
// Complete retail extent is 792 bytes: 0023C5E0..0023C8F8.
// The 784-byte dump ends before pop ebp/pop ebx/add esp,18/ret 0xc.
// Retail literal at VA010AEB50 and random-call line numbers 4092/4151 verified.
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
extern void j_0001f253();
extern float Rva0002CCA5GetGameLogicRandomValueRealThunk(float,float,char*,int);
class Route0023C5E0 {};
extern Route0023C5E0 *g0023C5E0Va012F0898;
__forceinline Object *find0023C5E0(unsigned id) {
 typedef Object *(Route0023C5E0::*Find)(unsigned);
 union {void(*fn)();Find call;} find={j_0001f253};
 return (g0023C5E0Va012F0898->*find.call)(id);
}
template<int N> class Slots0023C5E0 : public Slots0023C5E0<N-1> { public: virtual void unused(char (*)[N])=0; };
template<> class Slots0023C5E0<0> {};
class Secondary0023C5E0 : public Slots0023C5E0<65> { public: virtual const _STL::list<Object*> *slot104()=0; };
class MemberSelection0023C5E0 {
public:
 char pad[0x30]; _STL::set<unsigned> at030;
 Object *select(bool exclude,const Coord3D *position,float radius);
};
Object *MemberSelection0023C5E0::select(bool exclude,const Coord3D *position,float radius) {
 const _STL::list<Object*> *members=((Secondary0023C5E0*)((char*)this-0xc4))->slot104();
 float limit=99999.0f;
 if(radius>0.0f) limit=radius;
 if(members->empty()) {
  if(at030.empty()) return 0;
  if(position) {
   float bestDistance=99999.0f;
   Object *best=0;
   for(_STL::set<unsigned>::iterator it=at030.begin();it!=at030.end();++it) {
    Object *obj=find0023C5E0(*it);
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
    Object *obj=find0023C5E0(*it);
    if(obj && !(obj->m_status[1]&0x40000000)) return obj;
   }
   return 0;
  }
  return find0023C5E0(*at030.begin());
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
