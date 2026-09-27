// ?d_006b1690@@YAXXZ
// partial score=0.995 date=2026-09-27
// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib
// stlport
#define _STLP_NO_EXCEPTIONS 1
#include <set>
#include "string_base.h"
template<> inline const char *StringBase<char>::str() const { return m_data ? m_data->data : ""; }
#include "ascii_string.h"
extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(volatile long*);
extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(volatile long*);
extern "C" __declspec(dllimport) void* __stdcall AIL_open_stream(void*,const char*,int);
extern void j_00021c1f();
extern void j_000273a9();
extern void j_0000b7d5();
extern void j_00021ff3();
extern void j_000046ab();
extern void j_0002c5cf();
extern void j_0004acaa();
extern void j_00016f86();
template<class M> inline M member006B1690(void (*fn)()) { union { void(*f)(); M m; } u; u.f=fn; return u.m; }
class AudioEventRTS { public: AsciiString getFilename(); };
class Counted006B1690 {
public:
 virtual ~Counted006B1690(); long refs;
 void addRef() { InterlockedIncrement(&refs); }
 void release() { if(InterlockedDecrement(&refs)<=0) delete this; }
};
class EventBase006B1690 {
public:
 virtual ~EventBase006B1690();
 char pad04[0x24]; int field28; char pad2c[0x38]; int field64; char pad68[8];
 int get28() const { return field28; }
 int get64() const { return field64; }
 AsciiString filename() { typedef AsciiString (EventBase006B1690::*Fn)(); return (this->*member006B1690<Fn>(j_0000b7d5))(); }
 bool fading() { typedef bool (EventBase006B1690::*Fn)(); return (this->*member006B1690<Fn>(j_000046ab))(); }
 void setFade(bool v) { typedef void (EventBase006B1690::*Fn)(bool); (this->*member006B1690<Fn>(j_0002c5cf))(v); }
};
class Event006B1690 : public EventBase006B1690, public Counted006B1690 {};
class EventRef006B1690 {
public:
 Event006B1690 *ptr;
 EventRef006B1690 &operator=(const EventRef006B1690 &o) { if(this!=&o) { if(o.ptr)o.ptr->addRef(); if(ptr)ptr->release(); ptr=o.ptr; } return *this; }
};
class Playing006B1690 : public Counted006B1690 {
public:
 void *stream; int type; int field10; EventRef006B1690 event;
 char pad18[0x10]; float fade; char pad2c[9]; bool fading;
};
class PlayingRef006B1690 {
public:
 Playing006B1690 *ptr;
 PlayingRef006B1690() : ptr(0) {}
 PlayingRef006B1690(const PlayingRef006B1690 &o):ptr(o.ptr) { if(ptr)ptr->addRef(); }
 ~PlayingRef006B1690() { if(ptr)ptr->release(); }
 Playing006B1690 *operator->() const { return ptr; }
};
struct Request006B1690 { int action; EventRef006B1690 event; char pad08[8]; bool field10; };
struct Settings006B1690 { char pad00[0x3c]; int duration; };
class MusicStreamStarter006B1690 {
public:
 char pad00[12]; Settings006B1690 *settings; char pad10[0x950]; void *driver; char pad964[0x160]; int indices[3];
 void start(Request006B1690 *request);
 void stop(int kind,int flag) { typedef void (MusicStreamStarter006B1690::*Fn)(int,int); (this->*member006B1690<Fn>(j_00021c1f))(kind,flag); }
 PlayingRef006B1690 allocate() { typedef PlayingRef006B1690 (MusicStreamStarter006B1690::*Fn)(); return (this->*member006B1690<Fn>(j_000273a9))(); }
 void touch(const AsciiString &s) { typedef void (MusicStreamStarter006B1690::*Fn)(const AsciiString&); (this->*member006B1690<Fn>(j_00021ff3))(s); }
 void play(const PlayingRef006B1690 &r,float f) { typedef void (MusicStreamStarter006B1690::*Fn)(const PlayingRef006B1690&,float); (this->*member006B1690<Fn>(j_0004acaa))(r,f); }
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
extern BfmeAwakenDebug *TheBfmeAwakenDebug;
extern bool _bfme_debugReportingEnabled();
extern void _bfme_debugRecordCallsite(int);
void MusicStreamStarter006B1690::start(Request006B1690 *request) {
 int kind=request->event.ptr->field28;
 int index=request->event.ptr->field64;
 if(index>indices[kind]) { stop(kind,!request->field10); indices[kind]=index; }
 PlayingRef006B1690 audio=allocate();
 audio->event=request->event;
 AsciiString filename=((AudioEventRTS*)audio->event.ptr)->getFilename();
 audio->stream=AIL_open_stream(driver,filename.str(),0);
 if(!audio->stream) {
  static _STL::set<AsciiString> failures;
  _STL::set<AsciiString>::iterator found=failures.find(filename);
  if(found==failures.end()) {
   if(_bfme_debugReportingEnabled()) {
    _bfme_debugRecordCallsite(1); TheBfmeAwakenDebug->v60();
    typedef BfmeAwakenLog* (__cdecl *Write)(BfmeAwakenLog*,const StringBase<char>&);
    reinterpret_cast<Write>(j_00016f86)(TheBfmeAwakenDebug->v6c(0,0)->v38("Attempt to open streaming music file "),filename)->v38(" failed ")->v4c(2);
   }
   failures.insert(filename);
  }
 } else touch(filename);
 audio->type=3;
 if(index==indices[kind]) {
  stop(kind,!request->field10);
  if(audio->event.ptr->fading()) { audio->fading=true; audio->fade=(float)settings->duration; audio->event.ptr->setFade(false); }
 }
 if(audio->stream) play(audio,-1.0f);
}
