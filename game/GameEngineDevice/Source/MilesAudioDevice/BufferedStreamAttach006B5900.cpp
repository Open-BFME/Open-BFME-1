// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /Igame/Libraries/Source/WWVegas/WWLib 
// ?attach@BufferedStreamStarter006B7E70@@QAEXPAUStreamSlot006B7E70@@PAVFileRef006B7E70@@H@Z
// Evidence: targets/game/reverse/identity_evidence/006b5900-inline-accessors.md
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
extern void j_0000268a(); extern void j_0001079e(); extern void j_00021ff3();
extern void j_000298e8(); extern void j_0003aa6c(); extern void j_0004066f(); extern void j_00046a33();
template<class M> inline M member006B7E70(void (*fn)()) { union { void(*f)(); M m; } u; u.f=fn; return u.m; }
#include "../../../Libraries/Include/Lib/Coord3D.h"
struct WaveInfo006B7E70 { int format; void *data; unsigned size; int rate,bits,channels; unsigned extra[3]; };
struct SampleFile006B7E70 { char pad00[8]; WaveInfo006B7E70 info; int m_rva006B5900Word2c; };
extern AsciiString Rva01336E50EmptyString;
class FileRef006B7E70 {
public:
 SampleFile006B7E70 *ptr;
 // ?offset006B5900@FileRef006B7E70@@QBEHXZ absent-from-retail
 int offset006B5900() const { return ptr ? ptr->m_rva006B5900Word2c : 0; }
 WaveInfo006B7E70 *info() const { return ptr ? &ptr->info : 0; }
 void release() { typedef void (FileRef006B7E70::*Fn)(); (this->*member006B7E70<Fn>(j_000311bf))(); }
 FileRef006B7E70 &operator=(const FileRef006B7E70 &other) { typedef FileRef006B7E70 &(FileRef006B7E70::*Fn)(const FileRef006B7E70 &); return (this->*member006B7E70<Fn>(j_0000268a))(other); }
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
 char pad04[0x10]; AsciiString name; char pad18[0x10]; int field28; char pad2c[0x1c]; bool m_flag48; char pad49[0x17]; int m_rva006B5900Portion60; char pad64[0x0c];
 // ?flag006B5900@EventBase006B7E70@@QAEX_N@Z absent-from-retail
 void flag006B5900(bool value) { m_flag48=value; }
 const AsciiString &getName() const { return name; }
 void advanceNextPlayPortion() { typedef void (EventBase006B7E70::*Fn)(); (this->*member006B7E70<Fn>(j_0001079e))(); }
 void bfmeGenerateFilename() { typedef void (EventBase006B7E70::*Fn)(); (this->*member006B7E70<Fn>(j_00046a33))(); }
};
class Event006B7E70 : public EventBase006B7E70, public Counted006B7E70 {};
class EventRef006B7E70 {
public:
 Event006B7E70 *ptr;
 EventRef006B7E70 &operator=(const EventRef006B7E70 &o) { if(this!=&o) { if(o.ptr)o.ptr->addRef(); if(ptr)ptr->release(); ptr=o.ptr; } return *this; }
};
inline int rva006B5900Portion(Event006B7E70 *event) { return *(volatile int *)((char *)event+0x60); }
struct Playing006B7E70 { char pad00[8]; unsigned handle; int type; char pad10[4]; EventRef006B7E70 event; FileRef006B7E70 file; char pad1c[0x1f]; bool field3b; };
struct PlayingRef006B7E70 { Playing006B7E70 *ptr; };
class Gen0002857E;
class Rva00691140Handle {
public:
 Gen0002857E *m_rva006B5900Pointer;
 Rva00691140Handle &operator=(const Rva00691140Handle &other); // retail 0x00691140 (Rva00690FF0Handle.cpp) via ILT 0x0004066F
};
class Rva006910F0Handle : public Rva00691140Handle {
public:
 ~Rva006910F0Handle(); // retail 0x00691130 (R1GuardedPointerTailCalls.cpp)
};
class AudioEventRTS;
class AudioEventRef { public: AudioEventRTS *ptr; };
class Rva00694710AudioWorker {
public:
 Rva006910F0Handle rva00694130(const AudioEventRef &event,int value);
 Rva006910F0Handle rva00693B90(const AsciiString &filename,int value);
};
class Rva006B5900Worker {
public:
 Rva006910F0Handle openForEvent(const EventRef006B7E70 &event,int mode) { typedef Rva006910F0Handle (Rva006B5900Worker::*Fn)(const EventRef006B7E70 &,int); return (this->*member006B7E70<Fn>(j_0003aa6c))(event,mode); }
};
struct StreamSlot006B7E70 {
 bool active,stop; char pad02[2]; unsigned sample; EventRef006B7E70 event; bool allocated; char pad0d[3]; Playing006B7E70 *playing;
 unsigned *data; int size; FileRef006B7E70 m_rva006B5900Field1c; Rva00691140Handle m_rva006B5900Field20; Rva00691140Handle m_rva006B5900Field24; int m_rva006B5900Field28; int m_rva006B5900Field2c; unsigned offset; int rate,bits; bool started; char pad3d[3];
 bool available() const { if(sample==0)return true; return AIL_3D_sample_status(sample)!=4; }
};
struct Settings006B7E70 { char pad00[0x50]; int bufferMilliseconds; };
class BufferedStreamStarter006B7E70 {
public:
 char pad00[12]; Settings006B7E70 *settings; char pad10[0x5f4]; int field604; char pad608[12]; unsigned pending;
 char pad618[0x4e8]; Rva006B5900Worker *m_rva006B5900PointerB00; char padb04[0x40]; StreamSlot006B7E70 *slots; int count,timer,activeCount;
 bool start(PlayingRef006B7E70 *ref,unsigned sample);
 void close(StreamSlot006B7E70 *s) { typedef void (BufferedStreamStarter006B7E70::*Fn)(StreamSlot006B7E70*); (this->*member006B7E70<Fn>(j_0003b741))(s); }
 Coord3D *position(Coord3D *out,Event006B7E70 *e,bool *valid) { typedef Coord3D* (BufferedStreamStarter006B7E70::*Fn)(Coord3D*,Event006B7E70*,bool*); return (this->*member006B7E70<Fn>(j_00001ece))(out,e,valid); }
 __declspec(noinline) void attach(StreamSlot006B7E70 *s,FileRef006B7E70 *f,int mode);
 void fill(StreamSlot006B7E70 *s,unsigned end) { typedef void (BufferedStreamStarter006B7E70::*Fn)(StreamSlot006B7E70*,unsigned); (this->*member006B7E70<Fn>(j_00029910))(s,end); }
 void configure(PlayingRef006B7E70 *r,const Coord3D *p) { typedef void (BufferedStreamStarter006B7E70::*Fn)(PlayingRef006B7E70*,const Coord3D*); (this->*member006B7E70<Fn>(j_00047519))(r,p); }
 void resume(PlayingRef006B7E70 *r) { typedef void (BufferedStreamStarter006B7E70::*Fn)(PlayingRef006B7E70*); (this->*member006B7E70<Fn>(j_0002e668))(r); }
};
// ?attach@BufferedStreamStarter006B7E70@@QAEXPAUStreamSlot006B7E70@@PAVFileRef006B7E70@@H@Z
void BufferedStreamStarter006B7E70::attach(StreamSlot006B7E70 *slot,FileRef006B7E70 *file,int mode) {
	int one=1;
	int zero=0;
	slot->event.ptr->flag006B5900(one);
	if(rva006B5900Portion(slot->event.ptr)!=2 || mode==one) slot->event.ptr->advanceNextPlayPortion();
	slot->event.ptr->bfmeGenerateFilename();
	if(rva006B5900Portion(slot->event.ptr)==2) {
  if(!slot->m_rva006B5900Field24.m_rva006B5900Pointer) { Rva00694710AudioWorker *worker=reinterpret_cast<Rva00694710AudioWorker *>(m_rva006B5900PointerB00); slot->m_rva006B5900Field24=worker->rva00694130(reinterpret_cast<const AudioEventRef &>(slot->event),0); }
	} else if(rva006B5900Portion(slot->event.ptr)!=3) {
  slot->m_rva006B5900Field20=reinterpret_cast<Rva00694710AudioWorker *>(m_rva006B5900PointerB00)->rva00694130(reinterpret_cast<const AudioEventRef &>(slot->event),0);
	}
	FileRef006B7E70 *copyFrom=file; FileRef006B7E70 *copyTo=&slot->m_rva006B5900Field1c;
	*copyTo=*copyFrom;
	SampleFile006B7E70 *sample=file->ptr;
	if(sample==(SampleFile006B7E70 *)zero) {
		slot->m_rva006B5900Field2c=zero;
		slot->m_rva006B5900Field28=zero;
		return;
	}
	int base=slot->m_rva006B5900Field1c.offset006B5900();
	slot->m_rva006B5900Field2c=(unsigned int)sample->info.data-base;
	slot->m_rva006B5900Field28=sample->info.size+slot->m_rva006B5900Field2c;
	const AsciiString *value = file->ptr ? reinterpret_cast<const AsciiString *>(file->ptr) : &Rva01336E50EmptyString;
	typedef void (BufferedStreamStarter006B7E70::*Fn)(const AsciiString &);
	(this->*member006B7E70<Fn>(j_00021ff3))(*value);
}
