// cl: /O2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /Igame/Libraries/Source/WWVegas/WWLib
// Retail 0x006B4090: start a mono 3D sample from the nullable file record.
// The +0xB44 table and PlayingAudio-shaped fields agree with the adjacent
// matched configure3D and resume3D helpers. The owner remains address-qualified.
// A shared final resume call lets MSVC duplicate the two return paths as retail
// does; spelling those calls twice changes the callee-saved register assignment.
#include "ascii_string.h"
#define Rva01336E50EmptyString AsciiString::TheEmptyString
struct Coord3D { float x,y,z; };
struct SampleFile006B4090 { char pad00[8]; char format[0x14]; int channels; char pad20[12]; void *data; };
struct Event006B4090 { char pad00[0x14]; AsciiString name; char pad18[0x10]; int field28; char pad2c[0x1c]; bool field48; };
struct Playing006B4090 { char pad00[8]; unsigned handle; int type; char pad10[4]; Event006B4090 *event; SampleFile006B4090 *file; char pad1c[0x1f]; bool field3b;
 const void *fileName() const { return file ? (void*)file : (const void*)&Rva01336E50EmptyString; }
 const char *fileFormat() const { return file ? (char*)file+8 : 0; }
 void *fileData() const { return file ? file->data : 0; }
 };
struct PlayingRef006B4090 { Playing006B4090 *ptr; };
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
extern void *g_Rva00F36E5C;
#define TheBfmeAwakenDebug (static_cast<BfmeAwakenDebug *>(g_Rva00F36E5C))
extern bool _bfme_debugReportingEnabled();
extern void _bfme_debugRecordCallsite(int);
extern void j_00001ece(); extern void j_00021ff3(); extern void j_00016f86();
extern void j_00047519(); extern void j_0002e668(); extern void j_0003bd6d();
extern "C" __declspec(dllimport) int __stdcall AIL_set_3D_sample_file(unsigned,void*);
extern "C" __declspec(dllimport) void* __stdcall AIL_register_3D_EOS_callback(unsigned,void (*)());
extern "C" __declspec(dllimport) void __stdcall AIL_set_3D_sample_loop_count(unsigned,int);
extern "C" __declspec(dllimport) void __stdcall AIL_start_3D_sample(unsigned);
template<class M> inline M member006B4090(void (*fn)()) { union { void(*f)(); M m; } u; u.f=fn; return u.m; }
class SampleStarter006B4090 {
public:
 bool start3D(PlayingRef006B4090 *ref);
 Coord3D *position(Coord3D *out,Event006B4090 *event,bool *valid) { typedef Coord3D* (SampleStarter006B4090::*Fn)(Coord3D*,Event006B4090*,bool*); return (this->*member006B4090<Fn>(j_00001ece))(out,event,valid); }
 void touch(const void *p) { typedef void (SampleStarter006B4090::*Fn)(const void*); (this->*member006B4090<Fn>(j_00021ff3))(p); }
 void configure(PlayingRef006B4090 *r,const Coord3D *p) { typedef void (SampleStarter006B4090::*Fn)(PlayingRef006B4090*,const Coord3D*); (this->*member006B4090<Fn>(j_00047519))(r,p); }
 void resume(PlayingRef006B4090 *r) { typedef void (SampleStarter006B4090::*Fn)(PlayingRef006B4090*); (this->*member006B4090<Fn>(j_0002e668))(r); }

 char pad00[0x604]; int field604; char pad608[0x53c]; char *table;
};

bool SampleStarter006B4090::start3D(PlayingRef006B4090 *ref) {
 Playing006B4090 *playing=ref->ptr;
 unsigned sample;
 switch(playing->type) { case 1: sample=playing->handle; break; case 2: sample=*(unsigned*)(table+playing->handle*64+4); break; default: sample=0; }
 bool valid;
 typedef Coord3D* (SampleStarter006B4090::*GetPos)(Coord3D*,Event006B4090*,bool*);
 Coord3D pos; position(&pos,playing->event,&valid);
 if(!valid) return false;
 if(!ref->ptr->file) return false;
 typedef void (SampleStarter006B4090::*Touch)(const void*);
 touch(ref->ptr->fileName());
 if(*(int*)((ref->ptr->fileFormat())+0x14)!=1) {
  if(_bfme_debugReportingEnabled()) {
   _bfme_debugRecordCallsite(1); TheBfmeAwakenDebug->v60();
   BfmeAwakenLog *log=TheBfmeAwakenDebug->v6c(0,0);
   typedef BfmeAwakenLog* (__cdecl *Write)(BfmeAwakenLog*,const StringBase<char>&);
   Event006B4090 *event=playing->event;
   reinterpret_cast<Write>(j_00016f86)(log->v38("Stereo WAVE file listed for 3D sound "),event->name)->v4c(2);
  }
  return false;
 }
 AIL_set_3D_sample_file(sample,ref->ptr->fileData());
 AIL_register_3D_EOS_callback(sample,j_0003bd6d);
 typedef void (SampleStarter006B4090::*Configure)(PlayingRef006B4090*,const Coord3D*);
 configure(ref,&pos);
 AIL_set_3D_sample_loop_count(sample,1); AIL_start_3D_sample(sample);
 playing->event->field48=true;
 typedef void (SampleStarter006B4090::*Resume)(PlayingRef006B4090*);
 if(ref->ptr->event->field28!=2 && ref->ptr->event->field28!=field604) {
  ref->ptr->field3b=true;
 } else ref->ptr->field3b=false;
 resume(ref); return true;
}


