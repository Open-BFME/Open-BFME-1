// ?helper@Rva006AE610@@AAEXHPAX@Z
// partial score=1.0 date=2026-11-10
// cl: /O2 /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /MD /D_STLP_USE_STATIC_LIB
// stlport
// ?helper@Rva006AE610@@AAEXHPAX@Z
// Retail 0x006ADAE0, 458 bytes (ret 8 at +0x1C7); reached through ILT
// 0x00021C1F from the matched setIfGreater (0x006AE610).
//
// Codegen requirement (measured): retail loads the by-value erase iterator
// before the x87 store to value28 and hands erase the iterator's own slot as
// its sret temp. VC7.1 /O2 only does that when the iterator is NOT treated as
// escaped, which happens only when every body that receives its address is
// visible in this TU: the slot lookup at 0x0069D620 (sret into `it`) and the
// STLport list<ThingRef>::erase COMDAT (0x0069DBE0). With either callee
// opaque (ILT member-pointer union, or a declared-only member) the load stays
// after the fstp (7 bytes off at +0x17A) or the sret moves to the `extra` slot.
#define _STLP_NO_EXCEPTIONS 1
#include <list>
#include <deque>
extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(volatile long*);
extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(volatile long*);
extern "C" __declspec(dllimport) void __stdcall AIL_pause_stream(void*,int);
struct Holder006ADAE0 { char pad0[0x84]; void *busy84; };
struct Event006ADAE0 { char pad0[8]; Holder006ADAE0 *holder8; char padc[0x28-0xc]; int group28; char pad2c[0x64-0x2c]; int inner64; };
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
struct Clock006ADAE0 { char pad0[0x3c]; int value3c; };
class Rva006AE610 {
 void helper(int,void*);
public:
 _STL::list<ThingRef>::iterator getSlot(int,int);
 char pad0[0xc]; Clock006ADAE0 *clockc; char pad10[0x9d0-0x10]; _STL::list<ThingRef> streams;
 _STL::deque<ThingRef> queues[3][2]; int current[3]; ThingRef refs[3];
};
// 0x0069D620 (285 bytes, ILT 0x0001815B). Not yet byte-exact: 13 register
// bytes in the two release tails (see attempts/0x0069d620.cpp history).
_STL::list<ThingRef>::iterator Rva006AE610::getSlot(int group,int inner) {
 for(_STL::list<ThingRef>::iterator it=streams.begin(); it!=streams.end(); ++it) {
  ThingRef ref=*it;
  if(!ref.ptr) continue;
  if(ref.ptr->flag34) continue;
  Event006ADAE0 *event=ref.ptr->event14;
  if(event->holder8->busy84) continue;
  if(event->group28==group && event->inner64==inner) return it;
 }
 return streams.end();
}
void Rva006AE610::helper(int index,void *extra) {
 int selected=current[index];
 if(refs[index].ptr) {
  queues[index][refs[index].ptr->event14->inner64].push_back(refs[index]);
  refs[index].clear();
 } else {
  _STL::list<ThingRef>::iterator it=getSlot(index,selected);
  if(it!=streams.end()) {
   ThingRef ref=*it;
   queues[index][selected].push_back(ref);
   ref.ptr->flag35=false;
   if(!extra) ref.ptr->flag34=true;
   else {
    ref.ptr->flag34=false;
    AIL_pause_stream(ref.ptr->stream8,1);
    ref.ptr->value28=(float)clockc->value3c;
    streams.erase(it);
   }
  }
 }
}
