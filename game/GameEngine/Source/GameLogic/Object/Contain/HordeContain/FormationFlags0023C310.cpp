// Retail 0x0023C310 full 348-byte body. Address-qualified identity.
// Interior receiver -0xe4 is primary; -0xac list; +0x30 ID tree.
// Bit 60 is accessed through the full Object model-condition field.
// cl: /DNDEBUG /MD /EHsc-
// stlport
#define _STLP_USE_NEWALLOC 1
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <hash_map>
#include <set>
#include <list>
#include <bitset>
class ConditionBits0023C310 { _STL::bitset<320> bits; public: bool test(int bit) const { return bits.test(bit); } void reset(int bit) { bits.reset(bit); } };
typedef ConditionBits0023C310 ModelConditionFlags;
#define BFME_HAVE_MODELCONDITIONFLAGS
#include "../../object.h"
extern void j_00018223(); extern void j_00044774(); extern void j_0002191d();
class Route0023C310 {};
__forceinline bool clear0023C310(Object *obj) {
 typedef bool (Route0023C310::*Call)();
 union { void (*fn)(); Call call; } route={j_00018223};
 return (((Route0023C310*)obj)->*route.call)();
}
__forceinline bool blocked0023C310(AIUpdateInterface *ai) {
 typedef bool (Route0023C310::*Call)();
 union { void (*fn)(); Call call; } route={j_00044774};
 return (((Route0023C310*)ai)->*route.call)();
}
__forceinline void reset0023C310(Object *obj, int bit) {
 if(obj->m_modelConditionFlags.test(bit)) {
  obj->m_modelConditionFlags.reset(bit);
  typedef void (Route0023C310::*Call)();
  union { void (*fn)(); Call call; } route={j_0002191d};
  (((Route0023C310*)obj)->*route.call)();
 }
}
typedef _STL::hash_map<unsigned,Object*,_STL::hash<unsigned>,_STL::equal_to<unsigned> > Hash0023C310;
struct Logic0023C310 {
 char pad[0xb0]; Hash0023C310 at0b0;
 __forceinline Object *find(unsigned id) {
  if(!id) return 0;
  Hash0023C310::iterator it=at0b0.find(id);
  if(it==at0b0.end()) return 0;
  return it->second;
 }
};
class GameLogic;
// 0x012F0898 is retail's `GameLogic *TheGameLogic`; Logic0023C310 is this TU's
// local view of the same global, so cast at the use.
extern GameLogic *TheGameLogic;
template<int N> class Slots0023C310 : public Slots0023C310<N-1> { public: virtual void unused(char (*)[N])=0; };
template<> class Slots0023C310<0> {};
class Primary0023C310 : public Slots0023C310<29> { public: virtual void slot074(Object*)=0; };
struct Queue0023C310 { int at000,at004; };
struct State0023C310 { char pad[0x1c]; Queue0023C310 *at01c; __forceinline int count() { return at01c ? at01c->at004 : 999999; } };
struct AI0023C310 { char pad[0x30]; State0023C310 *at030; __forceinline State0023C310 *state() { return at030; } };
class FormationFlags0023C310 {
public:
 void run();
 char pad[0x30]; _STL::set<unsigned> at030; char pad03c[0x5c-0x3c]; int at05c;
 __forceinline _STL::list<Object*>& members() { return *(_STL::list<Object*>*)((char*)this-0xac); }
 __forceinline Primary0023C310 *primary() { return (Primary0023C310*)((char*)this-0xe4); }
};
void FormationFlags0023C310::run() {
 Object *owner=*(Object**)((char*)this-0xdc);
 at05c=((AI0023C310*)owner->m_ai)->state()->count();
 for(_STL::list<Object*>::iterator it=members().begin();it!=members().end();++it) {
  Object *obj=*it;
  if(obj && clear0023C310(obj)) {
   if(!blocked0023C310(obj->m_ai)) reset0023C310(obj,60);
   primary()->slot074(obj);
  }
 }
 for(_STL::set<unsigned>::iterator it=at030.begin();it!=at030.end();++it) {
  Object *obj=((Logic0023C310*)TheGameLogic)->find(*it);
  if(obj && clear0023C310(obj)) {
   if(!blocked0023C310(obj->m_ai)) reset0023C310(obj,60);
   primary()->slot074(obj);
  }
 }
}
