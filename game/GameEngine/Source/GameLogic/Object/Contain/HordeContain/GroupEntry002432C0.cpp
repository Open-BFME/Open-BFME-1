// Retail 0x002432C0 complete 384-byte ret-8 body; address-qualified identity.
// The native STLport list-base destructor remains visible but out of line,
// as witnessed by ILT 0xE68D -> 0xCEBD0. Specialization repeats its native body.
// cl: /DNDEBUG /MD /EHsc
// stlport
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <list>
#include <set>
#include "../../object.h"
namespace _STL { template<> __declspec(noinline) _List_base<Object*,allocator<Object*> >::~_List_base() { clear(); _M_node.deallocate(_M_node._M_data,1); } }
extern void j_0000f30d(); extern void j_0003b570(); extern void j_0001f253();
extern void j_0002b7e2(); extern void j_0003756a(); extern void j_00015f69();
class Route002432C0 {};
struct Hub002432C0 {};
extern Hub002432C0 *g002432C0Va012EF214;
extern Route002432C0 *g002432C0Va012F0898;
template<int N> class Slots002432C0 : public Slots002432C0<N-1> { public: virtual void unused(char (*)[N])=0; };
template<> class Slots002432C0<0> {};
class TargetContain002432C0 : public Slots002432C0<33> { public: virtual bool slot084(Object*,bool)=0; };
class Secondary002432C0 : public Slots002432C0<65> { public: virtual const _STL::list<Object*> *slot104()=0; };
class GroupEntry002432C0 : public Slots002432C0<40> {
public:
 virtual void slot0a0(Object*)=0;
 char pad004[0x30-4]; _STL::set<unsigned> at030;
 void run(Object *target,int source);
};
void GroupEntry002432C0::run(Object *target,int source) {
 if(!target) return;
 TargetContain002432C0 *contain=(TargetContain002432C0*)target->m_contain;
 if(!contain) return;
 Object *firstOwner=*(Object**)((char*)this-0xdc);
 if(!contain->slot084(firstOwner,true)) return;
 Object *owner=*(Object**)((char*)this-0xdc);
 if(!owner->m_ai) return;
 typedef void (Route002432C0::*Command)(Object*,int);
 union { void (*fn)(); Command call; } command={j_0000f30d};
 (((Route002432C0*)((char*)owner->m_ai+0x20))->*command.call)(target,source);
 _STL::list<Object*> snapshot;
 const _STL::list<Object*> *members=((Secondary002432C0*)((char*)this-0xc4))->slot104();
 for(_STL::list<Object*>::const_iterator it=members->begin();it!=members->end();++it) snapshot.push_back(*it);
 typedef Route002432C0 *(Route002432C0::*Create)();
 union { void (*fn)(); Create call; } create={j_0003b570};
 Route002432C0 *group=(((Route002432C0*)g002432C0Va012EF214)->*create.call)();
 for(_STL::list<Object*>::iterator it=snapshot.begin();it!=snapshot.end();++it) slot0a0(*it);
 for(_STL::set<unsigned>::iterator it=at030.begin();it!=at030.end();++it) {
  typedef Object *(Route002432C0::*Find)(unsigned);
  union { void (*fn)(); Find call; } find={j_0001f253};
  unsigned id=*it;
  Object *obj=(g002432C0Va012F0898->*find.call)(id);
  if(obj) {
   typedef void (Route002432C0::*Add)(Object*);
   union { void (*fn)(); Add call; } add={j_0002b7e2};
   (group->*add.call)(obj);
  }
 }
 union { void (*fn)(); Command call; } enter={j_0003756a};
 (group->*enter.call)(target,source);
 typedef void (Route002432C0::*Destroy)(Route002432C0*);
 union { void (*fn)(); Destroy call; } destroy={j_00015f69};
 (((Route002432C0*)g002432C0Va012EF214)->*destroy.call)(group);
}
