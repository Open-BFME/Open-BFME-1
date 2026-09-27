// ?d_006b2230@@YAXXZ
// partial score=0.762 date=2026-09-27
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
#include <list>
extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(volatile long*);
extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(volatile long*);
extern void j_0000f380();
extern void j_00002f13();
extern void j_000280f6();
extern void j_00011fcc();
extern void j_0001ed17();
extern void j_0002669d();
extern void j_00020d24();
template<class M> inline M member006B2230(void (*fn)()) { union { void(*f)(); M m; } u; u.f=fn; return u.m; }
class Event006B2230 {
public:
 bool positional() { typedef bool (Event006B2230::*Fn)(); return (this->*member006B2230<Fn>(j_0000f380))(); }
 bool moreLoops() { typedef bool (Event006B2230::*Fn)(); return (this->*member006B2230<Fn>(j_00011fcc))(); }
};
class Counted006B2230 {
public:
 virtual ~Counted006B2230();
 long refs;
 void addRef() { InterlockedIncrement(&refs); }
 void release() { if(InterlockedDecrement(&refs)<=0) delete this; }
};
class Playing006B2230 : public Counted006B2230 { public: char pad08[12]; Event006B2230 *event; };
class PlayingRef006B2230 {
private:
 Playing006B2230 *ptr;
public:
 PlayingRef006B2230(const PlayingRef006B2230 &o) { Playing006B2230 *p=o.ptr; if(p) p->addRef(); ptr=p; }
 ~PlayingRef006B2230() { Playing006B2230 *p=ptr; if(p) p->release(); }
 operator Playing006B2230*() const { return ptr; }
 Playing006B2230 *operator->() const { return ptr; }
};
typedef _STL::list<PlayingRef006B2230> List006B2230;
typedef List006B2230::iterator Iterator006B2230;
namespace _STL { template<> List006B2230::iterator List006B2230::erase(List006B2230::iterator); }
class AudioListRetirer006B2230 {
public:
 char pad00[0x9c4]; List006B2230 list9c4,list9c8,list9cc;
 bool retire(Event006B2230 *event);
 void sweep() { typedef void (AudioListRetirer006B2230::*Fn)(); (this->*member006B2230<Fn>(j_00002f13))(); }
 Event006B2230 *find(Event006B2230 *event) { typedef Event006B2230* (AudioListRetirer006B2230::*Fn)(Event006B2230*); return (this->*member006B2230<Fn>(j_000280f6))(event); }
 void loop(PlayingRef006B2230 *ref) { typedef void (AudioListRetirer006B2230::*Fn)(PlayingRef006B2230*); (this->*member006B2230<Fn>(j_0001ed17))(ref); }
 void release(Playing006B2230 *p) { typedef void (AudioListRetirer006B2230::*Fn)(Playing006B2230*); (this->*member006B2230<Fn>(j_0002669d))(p); }
};
bool AudioListRetirer006B2230::retire(Event006B2230 *event) {
 if(event->positional()) { sweep(); if(!list9c4.empty()) return true; }
 Event006B2230 *found=find(event);
 if(found) {
  if(event->positional()) {
   for(Iterator006B2230 it=list9cc.begin();it!=list9cc.end();++it) {
    PlayingRef006B2230 playing=*it;
    if(playing && playing->event==found) {
     if(playing->event->moreLoops()) loop(&playing);
     release(playing);
     list9cc.erase(it);
     return true;
    }
   }
  } else {
   for(Iterator006B2230 it=list9c8.begin();it!=list9c8.end();++it) {
    PlayingRef006B2230 playing=*it;
    if(playing && playing->event==found) {
     if(playing->event->moreLoops()) loop(&playing);
     release(playing);
     list9c8.erase(it);
     return true;
    }
   }
  }
 }
 return false;
}
