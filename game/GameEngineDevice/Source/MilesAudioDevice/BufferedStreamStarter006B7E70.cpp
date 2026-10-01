// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /Igame/Libraries/Source/WWVegas/WWLib
// Retail 0x006B7E70 (748 bytes; ret 8 at +0x2E9): choose a free 0x40-byte
// stream slot, attach its counted event and file, fill a sample buffer and
// configure/start a Miles 3D sample. The owner identity is not proven; all
// private layout views retain this address. Calls use existing ILT identities
// with thiscall signatures established from their retail bodies.
// Event base extent 0x70 and secondary count +0x74 agree with the matched
// Rva006A1790Event and StartAudioStream006AE2C0 families. Other offsets below
// are witnessed by this body, not inferred from the Zero Hour layout.
#include "ascii_string.h"
void *__cdecl operator new[](unsigned int);
extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(volatile long*);
extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(volatile long*);
extern "C" __declspec(dllimport) int __stdcall AIL_3D_sample_status(unsigned);
extern "C" __declspec(dllimport) void __stdcall AIL_start_timer(int);
extern "C" __declspec(dllimport) void __stdcall AIL_start_3D_sample(unsigned);
extern "C" __declspec(dllimport) void* __stdcall AIL_register_3D_EOS_callback(unsigned,void*);
extern "C" __declspec(dllimport) int __stdcall AIL_set_3D_sample_info(unsigned,const void*);
extern "C" __declspec(dllimport) void __stdcall AIL_set_3D_sample_loop_count(unsigned,int);
extern void j_0003b741(); extern void j_00001ece(); extern void j_00016f86(); extern void j_000311bf();
extern void j_0001dff2(); extern void j_00029910(); extern void j_00047519(); extern void j_0002e668();
template<class M> inline M member006B7E70(void (*fn)()) { union { void(*f)(); M m; } u; u.f=fn; return u.m; }
struct Coord3D { float x,y,z; };
struct WaveInfo006B7E70 { int format; void *data; unsigned size; int rate,bits,channels; unsigned extra[3]; };
struct SampleFile006B7E70 { char pad00[8]; WaveInfo006B7E70 info; };
class FileRef006B7E70 {
public:
 SampleFile006B7E70 *ptr;
 WaveInfo006B7E70 *info() const { return ptr ? &ptr->info : 0; }
 void release() { typedef void (FileRef006B7E70::*Fn)(); (this->*member006B7E70<Fn>(j_000311bf))(); }
};
class Counted006B7E70 {
public:
 virtual ~Counted006B7E70(); long refs;
 void addRef() { InterlockedIncrement(&refs); }
 void release() { if(InterlockedDecrement(&refs)<=0) delete this; }
};
class EventBase006B7E70 {
public:
 virtual ~EventBase006B7E70();
 char pad04[0x10]; AsciiString name; char pad18[0x10]; int field28; char pad2c[0x44];
 const AsciiString &getName() const { return name; }
};
class Event006B7E70 : public EventBase006B7E70, public Counted006B7E70 {};
class EventRef006B7E70 {
public:
 Event006B7E70 *ptr;
 EventRef006B7E70 &operator=(const EventRef006B7E70 &o) { if(this!=&o) { if(o.ptr)o.ptr->addRef(); if(ptr)ptr->release(); ptr=o.ptr; } return *this; }
};
struct Playing006B7E70 { char pad00[8]; unsigned handle; int type; char pad10[4]; EventRef006B7E70 event; FileRef006B7E70 file; char pad1c[0x1f]; bool field3b; };
struct PlayingRef006B7E70 { Playing006B7E70 *ptr; };
struct StreamSlot006B7E70 {
 bool active,stop; char pad02[2]; unsigned sample; EventRef006B7E70 event; bool allocated; char pad0d[3]; Playing006B7E70 *playing;
 unsigned *data; int size; char pad1c[0x14]; unsigned offset; int rate,bits; bool started; char pad3d[3];
 bool available() const { if(sample==0)return true; return AIL_3D_sample_status(sample)!=4; }
};
struct Settings006B7E70 { char pad00[0x50]; int bufferMilliseconds; };
class BufferedStreamStarter006B7E70 {
public:
 char pad00[12]; Settings006B7E70 *settings; char pad10[0x5f4]; int field604; char pad608[12]; unsigned pending;
 char pad618[0x52c]; StreamSlot006B7E70 *slots; int count,timer,activeCount;
 bool start(PlayingRef006B7E70 *ref,unsigned sample);
 void close(StreamSlot006B7E70 *s) { typedef void (BufferedStreamStarter006B7E70::*Fn)(StreamSlot006B7E70*); (this->*member006B7E70<Fn>(j_0003b741))(s); }
 Coord3D *position(Coord3D *out,Event006B7E70 *e,bool *valid) { typedef Coord3D* (BufferedStreamStarter006B7E70::*Fn)(Coord3D*,Event006B7E70*,bool*); return (this->*member006B7E70<Fn>(j_00001ece))(out,e,valid); }
 void attach(StreamSlot006B7E70 *s,FileRef006B7E70 *f,int mode) { typedef void (BufferedStreamStarter006B7E70::*Fn)(StreamSlot006B7E70*,FileRef006B7E70*,int); (this->*member006B7E70<Fn>(j_0001dff2))(s,f,mode); }
 void fill(StreamSlot006B7E70 *s,unsigned end) { typedef void (BufferedStreamStarter006B7E70::*Fn)(StreamSlot006B7E70*,unsigned); (this->*member006B7E70<Fn>(j_00029910))(s,end); }
 void configure(PlayingRef006B7E70 *r,const Coord3D *p) { typedef void (BufferedStreamStarter006B7E70::*Fn)(PlayingRef006B7E70*,const Coord3D*); (this->*member006B7E70<Fn>(j_00047519))(r,p); }
 void resume(PlayingRef006B7E70 *r) { typedef void (BufferedStreamStarter006B7E70::*Fn)(PlayingRef006B7E70*); (this->*member006B7E70<Fn>(j_0002e668))(r); }
};
class BfmeAwakenLog {
public:
 virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
 virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
 virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
 virtual void v30(); virtual void v34(); virtual BfmeAwakenLog *v38(const char *);
 virtual void v3c(); virtual void v40(); virtual void v44(); virtual void v48(); virtual BfmeAwakenLog *v4c(int);
};
class BfmeAwakenDebug {
public:
 virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
 virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
 virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
 virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
 virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
 virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c(); virtual void v60();
 virtual void v64(); virtual void v68(); virtual BfmeAwakenLog *v6c(int,int);
};
// Existing owned pointer cell; the original singleton class type is unproven.
extern void *g_Rva00F36E5C;
extern bool _bfme_debugReportingEnabled();
extern void _bfme_debugRecordCallsite(int);
bool BufferedStreamStarter006B7E70::start(PlayingRef006B7E70 *ref,unsigned sample) {
 int index;
 for(index=0;index<count;++index) if(!slots[index].active && slots[index].available()) break;
 if(index==count) { if(pending>0) --pending; return false; }
 ref->ptr->handle=index;
 ref->ptr->type=2;
 StreamSlot006B7E70 *slot=&slots[index];
 if(slot->allocated) close(slot);
 Coord3D pos; bool valid;
 position(&pos,ref->ptr->event.ptr,&valid);
 if(!valid)return false;
 slot->stop=false; slot->started=false; slot->sample=sample;
 slot->event=ref->ptr->event;
 slot->offset=0; slot->playing=ref->ptr; slot->allocated=true;
 if(activeCount<=0 && timer!=-1) AIL_start_timer(timer);
 ++activeCount;
 if(!ref->ptr->file.ptr) return false;
 WaveInfo006B7E70 *info=ref->ptr->file.info();
 if(info->channels!=1) {
  if(_bfme_debugReportingEnabled()) {
   _bfme_debugRecordCallsite(1); reinterpret_cast<BfmeAwakenDebug *>(g_Rva00F36E5C)->v60();
   typedef BfmeAwakenLog* (__cdecl *Write)(BfmeAwakenLog*,const StringBase<char>&);
   BfmeAwakenLog *log=reinterpret_cast<BfmeAwakenDebug *>(g_Rva00F36E5C)->v6c(0,0);
   Event006B7E70 *event=ref->ptr->event.ptr;
   reinterpret_cast<Write>(j_00016f86)(log->v38("Stereo WAVE file listed for 3D sound "),event->name)->v4c(2);
  }
  ref->ptr->file.release(); return false;
 }
 slot->bits=info->bits; slot->rate=info->rate;
 attach(slot,&ref->ptr->file,2);
 ref->ptr->file.release();
 slot->size=(unsigned)(settings->bufferMilliseconds*slot->bits*slot->rate)/8000;
 if(slot->size<0xc400) slot->size=0xc400;
 unsigned remainder=slot->size&3;
 if(remainder) slot->size=slot->size-remainder+4;
 slot->data=new unsigned[(unsigned)slot->size/4];
 fill(slot,slot->size);
 WaveInfo006B7E70 sampleInfo=*info;
 sampleInfo.data=slot->data; sampleInfo.size=slot->size;
 AIL_set_3D_sample_info(sample,&sampleInfo);
 AIL_register_3D_EOS_callback(sample,0);
 configure(ref,&pos);
 AIL_set_3D_sample_loop_count(sample,0);
 if(ref->ptr->event.ptr->field28!=2 && ref->ptr->event.ptr->field28!=field604) ref->ptr->field3b=true;
 else ref->ptr->field3b=false;
 resume(ref);
 if(slot->started) AIL_start_3D_sample(sample);
 slot->active=true;
 return true;
}
