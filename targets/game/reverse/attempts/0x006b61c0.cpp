// ?d_006b61c0@@YAXXZ
// partial score=0.716 date=2026-09-27
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(void*,unsigned long);
extern "C" __declspec(dllimport) int __stdcall ReleaseMutex(void*);
extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(volatile long*);
extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(volatile long*);
extern "C" __declspec(dllimport) void __stdcall AIL_stop_3D_sample(unsigned);
extern "C" __declspec(dllimport) void __stdcall AIL_start_3D_sample(unsigned);
extern "C" __declspec(dllimport) unsigned __stdcall AIL_3D_sample_offset(unsigned);
extern "C" __declspec(dllimport) void __stdcall AIL_set_3D_sample_loop_count(unsigned,int);
extern void j_0001079e();
extern void j_0003aa6c();
extern void j_0004066f();
extern void j_000298e8();
extern void j_00029910();
extern void j_0002e668();
template<class M> inline M member006B61C0(void (*fn)()) { union { void(*f)(); M m; } u; u.f=fn; return u.m; }
class StreamFileRef006B61C0 {
public:
 void *ptr;
 ~StreamFileRef006B61C0() { typedef void (StreamFileRef006B61C0::*Fn)(); (this->*member006B61C0<Fn>(j_000298e8))(); }
 StreamFileRef006B61C0 &operator=(const StreamFileRef006B61C0 &other) { typedef StreamFileRef006B61C0& (StreamFileRef006B61C0::*Fn)(const StreamFileRef006B61C0&); return (this->*member006B61C0<Fn>(j_0004066f))(other); }
};
struct Event006B61C0 { char pad00[0x45]; bool field45; char pad46[0x1a]; int field60; void advance() { typedef void (Event006B61C0::*Fn)(); (this->*member006B61C0<Fn>(j_0001079e))(); } };
class FileSource006B61C0 {
public:
 StreamFileRef006B61C0 get(Event006B61C0 **event,int flag) { typedef StreamFileRef006B61C0 (FileSource006B61C0::*Fn)(Event006B61C0**,int); return (this->*member006B61C0<Fn>(j_0003aa6c))(event,flag); }
};
class Counted006B61C0 { public: virtual ~Counted006B61C0(); long refs; void addRef() { InterlockedIncrement(&refs); } void release() { if(InterlockedDecrement(&refs)<=0) delete this; } };
class PlayingRef006B61C0 {
public:
 Counted006B61C0 *ptr;
 PlayingRef006B61C0(const PlayingRef006B61C0 &o):ptr(o.ptr) { if(ptr) ptr->addRef(); }
 ~PlayingRef006B61C0() { if(ptr) ptr->release(); }
};
struct StreamSlot006B61C0 {
 bool active,stop; char pad02[2]; unsigned sample; Event006B61C0 *event; char pad0c[4]; PlayingRef006B61C0 playing;
 char pad14[4]; unsigned size; unsigned field1c; char pad20[4]; StreamFileRef006B61C0 file;
 char pad28[8]; unsigned offset; char pad34[8]; bool started; char pad3d[3];
};
class TryMutex006B61C0 {
 void *handle; bool held;
public:
 TryMutex006B61C0(void *h):handle(h),held(false) {}
 bool lock() { if(WaitForSingleObject(handle,0)==0x102) return false; held=true; return true; }
 ~TryMutex006B61C0() { if(held) { ReleaseMutex(handle); held=false; } }
};
class StreamPump006B61C0 {
public:
 char pad00[0x95c]; void *mutex; char pad960[0x1a0]; FileSource006B61C0 *source; char padb04[0x40]; StreamSlot006B61C0 *slots; int count;
 void pump();
 void fill(StreamSlot006B61C0 *slot,unsigned end) { typedef void (StreamPump006B61C0::*Fn)(StreamSlot006B61C0*,unsigned); (this->*member006B61C0<Fn>(j_00029910))(slot,end); }
 void resume(PlayingRef006B61C0 *ref) throw() { typedef void (StreamPump006B61C0::*Fn)(PlayingRef006B61C0*); (this->*member006B61C0<Fn>(j_0002e668))(ref); }
};
void StreamPump006B61C0::pump() {
 static int last=0;
 int original=last;
 int index=last;
 do {
  if(++index>=count) index=0;
  StreamSlot006B61C0 *slot=&slots[index];
  if(slot->active) {
   TryMutex006B61C0 guard(mutex);
   if(!guard.lock()) return;
   last=index;
   if(!slot->active) continue;
   if(slot->stop) { AIL_stop_3D_sample(slot->sample); slot->active=false; continue; }
   if(slot->event->field45 && !slot->file.ptr && slot->event->field60==1) {
    slot->event->advance();
    if(slot->event->field60==2) slot->file=source->get(&slot->event,1);
   }
   unsigned offset=AIL_3D_sample_offset(slot->sample);
   if(offset>=slot->size) offset=0;
   bool started=slot->started;
   if(offset>slot->offset) fill(slot,offset);
   else if(offset<slot->offset) {
    fill(slot,slot->size);
    if(slot->field1c==0 && slot->event->field60==3) {
     AIL_set_3D_sample_loop_count(slot->sample,1); slot->active=false; continue;
    }
    fill(slot,offset);
   }
   if(slot->started && !started) {
    AIL_start_3D_sample(slot->sample);
    PlayingRef006B61C0 ref=slot->playing;
    resume(&ref);
   }
  }
 } while(index!=original);
}
