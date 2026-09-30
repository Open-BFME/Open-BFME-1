// ?d_00240b10@@YAXXZ
// partial score=0.1457 date=2026-09-28
// cl: /DNDEBUG /MD /EHsc /Igame/GameEngine/Source
// stlport
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#include <list>
namespace _STL {
template<> __forceinline void list<int,allocator<int> >::push_front(const int& x) { insert(begin(), x); }
}
#define BFME_HAVE_OBJECTID 1
enum ObjectID { INVALID_OBJECT_ID=0 };
#include "GameLogic/Object/object.h"
extern void j_0003251f(); extern void j_0001f91f(); extern void j_0000d517();
extern void j_0001eb1e(); extern void j_0000d990(); extern void j_0001d0de();
class Route00240B10 {};
extern Route00240B10 *g00240B10Va012F0898;
template<int N> class Slots00240B10 : public Slots00240B10<N-1> { public: virtual void unused(char (*)[N])=0; };
template<> class Slots00240B10<0> {};
class Secondary00240B10 : public Slots00240B10<36> {public: virtual void slot090(Object*,bool)=0;};
class Primary00240B10 : public Slots00240B10<34> {public: virtual bool slot088()=0;};
class MemberRemove00240B10 {
public:
 char at000[0x34]; int at034; char at038[0x1c]; _STL::list<int> at054; char at058[0xd0-0x58]; ObjectID at0d0; char at0d4[4]; ObjectID at0d8;
 void run(Object*);
};
__forceinline ObjectID id00240B10(Object *obj) {return obj->m_id;}
void MemberRemove00240B10::run(Object *member) {
 int *value;
 ObjectID first=at0d0;
 ObjectID id=id00240B10(member);
 if(first!=id && at0d8!=id) {
  typedef bool (Route00240B10::*Kind)(int);
  union {void (*fn)(); Kind call;} kind={j_0003251f};
  if(!(((Route00240B10*)member)->*kind.call)(11)) {
   typedef int *(Route00240B10::*Lookup)(const int&);
   union {void (*fn)(); Lookup call;} lookup={j_0001f91f};
   value=(((Route00240B10*)((char*)this+0x3c))->*lookup.call)(int(id));
   at054.push_front(*value);
  }
 }
 typedef void (Route00240B10::*Erase)(const int&);
 union {void (*fn)(); Erase call;} eraseMap={j_0000d517};
 (((Route00240B10*)((char*)this+0x3c))->*eraseMap.call)(id00240B10(member));
 union {void (*fn)(); Erase call;} eraseSet={j_0001eb1e};
 (((Route00240B10*)((char*)this+0x30))->*eraseSet.call)(id00240B10(member));
 ((Secondary00240B10*)((char*)this-0xc4))->slot090(member,false);
 typedef void (Route00240B10::*Producer)(const Object*);
 union {void (*fn)(); Producer call;} producer={j_0000d990};
 (((Route00240B10*)member)->*producer.call)(0);
 while(((Primary00240B10*)((char*)this-0xe4))->slot088()) {}
 if(((_STL::list<Object*>*)((char*)this-0xac))->empty() && at034==0) {
  typedef void (Route00240B10::*Destroy)(Object*);
  union {void (*fn)(); Destroy call;} destroy={j_0001d0de};
  (g00240B10Va012F0898->*destroy.call)(*(Object**)((char*)this-0xdc));
 }
}
