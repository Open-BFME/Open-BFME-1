// Retail 0x00243070 complete 474-byte ret-12 body; address-qualified identity.
// Packet slots agree with Rva0015A190Owner_applyOrFallback.cpp and ILT 48C43.
// Snapshot list and Object hash use the native STLport layouts.
// cl: /DNDEBUG /MD /EHsc
// stlport
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <list>
#include <set>
#include <hash_map>
#include "../../object.h"
extern void j_0003b570(); extern void j_0002b7e2(); extern void j_00024d70();
extern void j_00048c43(); extern void j_00015f69();
class Route00243070 {};
extern Route00243070 *g00243070Va012EF214;
typedef _STL::hash_map<unsigned,Object*,_STL::hash<unsigned>,_STL::equal_to<unsigned> > Hash00243070;
struct Logic00243070 {
 char pad[0xb0]; Hash00243070 at0b0;
 __forceinline Object *find(unsigned id) {
  if(!id) return 0;
  Hash00243070::iterator it=at0b0.find(id);
  if(it==at0b0.end()) return 0;
  return it->second;
 }
};
extern Logic00243070 *g00243070Va012F0898;
template<int N> class Slots00243070 : public Slots00243070<N-1> { public: virtual void unused(char (*)[N])=0; };
template<> class Slots00243070<0> {};
class Secondary00243070 : public Slots00243070<65> { public: virtual const _STL::list<Object*> *slot104()=0; };
class AI00243070 : public Slots00243070<99> { public: virtual bool slot18c()=0; };
struct Packet00243070 {
 void *at000; bool at004; void *at008; void *at00c;
 Packet00243070(void *p,void *value) { at000=p; at004=false; at00c=0; at008=value; }
};
class GroupPacket00243070 : public Slots00243070<40> {
public:
 virtual void slot0a0(Object*)=0;
 char pad004[0x30-4]; _STL::set<unsigned> at030;
 void run(void *target,int source,void *value);
};
void GroupPacket00243070::run(void *target,int source,void *value) {
 _STL::list<Object*> snapshot;
 const _STL::list<Object*> *members=((Secondary00243070*)((char*)this-0xc4))->slot104();
 for(_STL::list<Object*>::const_iterator it=members->begin();it!=members->end();++it) snapshot.push_back(*it);
 typedef Route00243070 *(Route00243070::*Create)();
 union {void(*fn)();Create call;} create={j_0003b570};
 Route00243070 *group=(g00243070Va012EF214->*create.call)();
 for(_STL::list<Object*>::iterator it=snapshot.begin();it!=snapshot.end();++it) slot0a0(*it);
 for(_STL::set<unsigned>::iterator it=at030.begin();it!=at030.end();++it) {
  Object *obj=g00243070Va012F0898->find(*it);
  if(obj) {
   typedef void (Route00243070::*Add)(Object*);
   union {void(*fn)();Add call;} add={j_0002b7e2};
   (group->*add.call)(obj);
   AI00243070 *ai=(AI00243070*)obj->m_ai;
   if(ai && ai->slot18c()) {
    typedef void (Route00243070::*Idle)(int);
    union {void(*fn)();Idle call;} idle={j_00024d70};
    (((Route00243070*)((char*)ai+0x20))->*idle.call)(source);
   }
  }
 }
 Packet00243070 packet(target,value);
 typedef void (Route00243070::*Apply)(Packet00243070*,int);
 union {void(*fn)();Apply call;} apply={j_00048c43};
 (group->*apply.call)(&packet,source);
 typedef void (Route00243070::*Destroy)(Route00243070*);
 union {void(*fn)();Destroy call;} destroy={j_00015f69};
 (g00243070Va012EF214->*destroy.call)(group);
}
