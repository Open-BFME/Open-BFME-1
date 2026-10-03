// ?method@Rva00693B90@@QAE?AVRva006910F0Handle@@ABVAsciiString@@H@Z
// partial score=0.3333 date=2026-10-03
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Iinputs/reference/shims/stringinline /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWLib /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define _STLP_NO_EXCEPTIONS 1
#define _OPERATOR_NEW_DEFINED_
#include "StringInline.h"
#include <list>
inline bool AsciiString::isEmpty()const { return m_data==0 || *(const unsigned short*)&m_data->m_length==0; }
extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(void*,unsigned long);
extern "C" __declspec(dllimport) int __stdcall ReleaseMutex(void*);
class Gen0002857E;
class Gen_006910e0 { public: void *m(); };
extern void j_0003834d(); extern void j_00018971(); extern void j_0003cc81();
extern void j_00003071(); extern void j_0001cb7f(); extern void j_0001f3a2();
class Rva006BA130MaxField { public: void update(int); };
class Gen0002857EOwner { public: void Rva00693B00(Gen0002857E*); };
class Rva006910F0Handle { public:
 Rva006910F0Handle() { ((Gen_006910e0*)this)->m(); }
 Rva006910F0Handle(Gen0002857E*);
 Rva006910F0Handle(const Rva006910F0Handle &v) {
  typedef void (Rva006910F0Handle::*Fn)(const Rva006910F0Handle&);
  union { void(*raw)(); Fn member; } c; c.raw=j_0003834d; (this->*c.member)(v);
 }
 ~Rva006910F0Handle();
 Gen0002857E *ptr;
};
class Rva00693B90;
class Gen0002857E { public:
 Gen0002857E(Rva00693B90 *o,const AsciiString &name);
 char field00[0x34]; int field34; unsigned field38; int field3c; bool field40,field41,field42;
};
struct Rva00693B90Node { void *next; const AsciiString key; Gen0002857E *value; };
struct Rva00693B90Map {
 Rva00693B90Node *find(const AsciiString &s) const {
  typedef Rva00693B90Node *(Rva00693B90Map::*Fn)(const AsciiString&) const;
  union {void(*raw)();Fn member;}c;c.raw=j_0003cc81;return(this->*c.member)(s);
 }
 Gen0002857E *&index(const AsciiString &s) {
  typedef Gen0002857E *&(Rva00693B90Map::*Fn)(const AsciiString&);
  union {void(*raw)();Fn member;}c;c.raw=j_0001cb7f;return(this->*c.member)(s);
 }
 char storage[0x14];
};
struct Rva00693B90Set {
 void *find(const AsciiString &s)const {
  typedef void *(Rva00693B90Set::*Fn)(const AsciiString&)const;
  union {void(*raw)();Fn member;}c;c.raw=j_00003071;return(this->*c.member)(s);
 }
 void *sentinel;
};
struct Rva00693B90Lock {
 void *mutex; char acquired;
 Rva00693B90Lock(void *m) { acquired=0; mutex=m; if(WaitForSingleObject(m,0xffffffff)!=0x102)acquired=1; }
 ~Rva00693B90Lock(){if(acquired)ReleaseMutex(mutex);}
};
class Rva00693B90 { public:
 Rva006910F0Handle method(const AsciiString &name,int bucket);
 Rva00693B90Map field00; std::list<Gen0002857E*> field14[3];
 char field20[12]; Rva00693B90Set field2c; char field30[24]; void *field48;
};
void push(Rva00693B90 *o,int bucket,Gen0002857E *const &p) {
 typedef void (std::list<Gen0002857E*>::*Fn)(Gen0002857E *const&);
 union {void(*raw)();Fn member;}c;c.raw=j_0001f3a2; (o->field14[bucket].*c.member)(p);
}
Rva006910F0Handle Rva00693B90::method(const AsciiString &name,int bucket) {
 if(bucket<0) bucket=0; else if(bucket>=3) bucket=2;
 Rva00693B90Lock lock(field48);
 if(name.isEmpty())return Rva006910F0Handle();
 Rva00693B90Node *entry=field00.find(name);
 if(entry) {
  Gen0002857E *p=entry->value;
  if(p->field34==0)((Gen0002857EOwner*)this)->Rva00693B00(p);
  if(!p->field41 && p->field3c<bucket) {
   std::list<Gen0002857E*> &list=field14[p->field3c];
   for(std::list<Gen0002857E*>::iterator it=list.begin();it!=list.end();++it) {
    if(*it==p){list.erase(it);field14[bucket].push_back(p);break;}
   }
  }
  ((Rva006BA130MaxField*)p)->update(bucket);
  return Rva006910F0Handle(p);
 }
 void *end=field2c.sentinel;
 if(field2c.find(name)!=end)return Rva006910F0Handle();
 Gen0002857E *p=new Gen0002857E(this,name);
 Rva006910F0Handle handle(p);
 field00.index(name)=p;
 push(this,bucket,p);
 ((Rva006BA130MaxField*)p)->update(bucket);
 return handle;
}

// Retail extent525B: RET12 at00693D9A; INT3 at00693D9D.
// EH handlerC47214 -> FuncInfoVA01236CDC has FOUR states, not nine:
// 0 guarded return-handle cleanup (bit0 at[ebp-20], sret at[ebp+4]);
// 1 mutex guard at[ebp-1C], previous0, cleanup -> ILT1E961 ->6915E0;
// 2 failed allocation at[ebp+8], previous1, delete at881EB0;
// 3 local handle at[ebp-24], previous1, cleanup -> ILT298E8 ->691130.
// Independent helpers:6910E0 null ctor9B;6910F0 ptr ctor24B;
// 691110 copy ctor26B;691130 destructor12B. Both retain viaILT2857E;
// destructor releases through442B0. Constructor6BA2D0 is83B RET8 and
// initializes44B record. Native constructor declaration above still needs
// an independently reviewed ABI binding; old BfmeRecordBQ alias has wrong
// AsciiStringBQ type and is deliberately not used. No pins added.
// Candidate535B,330 masked positional differences, normalized shape.914.
// Mutex bool/char and constructor forms tried; out-of-line record constructor
// plus preloading set sentinel improves shape. Remaining: lock acquired flag
// cached inBL vs stack, bucketEBP vsEBX, frame14 vs18, extra loop compare.
// Native StringInline AsciiString and STLport list own their actual lifetimes;
// no inline-asm or naked reconstruction. Typed ILT adapters preserve existing
// ledger names; pin/callback binding remains unverified. Bank only.
