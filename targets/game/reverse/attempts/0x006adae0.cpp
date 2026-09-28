// ?helper@Rva006AE610@@AAEXHPAX@Z
// partial score=0.9847161572052402 date=2026-09-28
// stlport
// cl: /O2 /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /MD /D_STLP_USE_STATIC_LIB
#define _STLP_NO_EXCEPTIONS 1
#include <list>
#include <deque>
extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(volatile long*);
extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(volatile long*);
extern "C" __declspec(dllimport) void __stdcall AIL_pause_stream(void*,int);
extern void j_00020d24();
extern void j_0001815b();
struct Event006ADAE0 { char pad0[0x64]; int inner64; };
class RefCountedThing { public:
 virtual ~RefCountedThing(); long count4; void *stream8; int dwordc,dword10; Event006ADAE0 *event14;
 char pad18[0x10]; float value28; char pad2c[8]; bool flag34,flag35;
 void release() { if(InterlockedDecrement(&count4)<=0) delete this; }
};
class ThingRef { public:
 RefCountedThing *ptr;
 ThingRef(const ThingRef &r):ptr(r.ptr) { if(ptr) InterlockedIncrement(&ptr->count4); }
 ~ThingRef() { if(ptr) ptr->release(); }
 void clear() { if(ptr) { ptr->release(); ptr=0; } }
};
struct Rva0069F740Ref { _STL::list<ThingRef>::iterator it; };
class Rva0069F740Owner { public: Rva0069F740Ref getSlot(int,int); };
struct Clock006ADAE0 { char pad0[0x3c]; int value3c; };
class Rva006AE610 {
 void helper(int,void*);
public:
 char pad0[0xc]; Clock006ADAE0 *clockc; char pad10[0x9d0-0x10]; _STL::list<ThingRef> streams;
 _STL::deque<ThingRef> queues[3][2]; int current[3]; ThingRef refs[3];
};
void Rva006AE610::helper(int index,void *extra) {
 int selected=current[index];
 if(refs[index].ptr) {
  queues[index][refs[index].ptr->event14->inner64].push_back(refs[index]);
  refs[index].clear();
 } else {
  typedef void (Rva006AE610::*Find)(_STL::list<ThingRef>::iterator*,int,int);
  union { void (__cdecl *raw)(); Find member; } find; find.raw=j_0001815b;
  _STL::list<ThingRef>::iterator it; (this->*find.member)(&it,index,selected);
  if(it!=streams.end()) {
   ThingRef ref=*it;
   queues[index][selected].push_back(ref);
   ref.ptr->flag35=false;
   if(!extra) ref.ptr->flag34=true;
   else {
    ref.ptr->flag34=false;
    AIL_pause_stream(ref.ptr->stream8,1);
    ref.ptr->value28=(float)clockc->value3c;
    typedef void (_STL::list<ThingRef>::*Erase)(_STL::list<ThingRef>::iterator*,_STL::list<ThingRef>::iterator);
    union { void (__cdecl *raw)(); Erase member; } call;
    call.raw=j_00020d24; (streams.*call.member)(&it,it);
   }
  }
 }
}
