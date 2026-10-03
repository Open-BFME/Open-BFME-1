// ?rva00776AC0@Rva00776AC0Owner@@QAEXPAVXfer@@@Z
// partial score=0.9935 date=2026-10-03
// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib /Igame/GameEngine/Source/Common/System /Igame/Libraries/Source/WWVegas/WWMath
// stlport
// BANK ONLY: complete 3390-byte body, 22 non-relocation bytes differ.
// Callable declarations below are unbound ABI views, not new identity pins.
// See identity_evidence/00776ac0-model-transfer-bank.md before integration.
#include <vector>
#include <string>
#include "ascii_string.h"
#include "xfer.h"
#include "coord3d.h"
#include <string.h>

struct Rva00776AC0Record24 {
    AsciiString at00;
    bool at04;
    float at08, at0c, at10, at14;
};
class Rva00776AC0Render;
struct Rva00776AC0Coord : Coord3DBase {
 Rva00776AC0Coord() {}
 Rva00776AC0Coord(const Rva00776AC0Coord& o) { x=o.x; y=o.y; z=o.z; }
};
struct Rva00776AC0Record32 {
    Rva00776AC0Render *at00;
    std::string at04;
    Rva00776AC0Coord at10;
    int at1c;
    Rva00776AC0Record32() {}
    Rva00776AC0Record32(const Rva00776AC0Record32& o) : at00(o.at00),at04(o.at04),at10(o.at10),at1c(o.at1c) {
    }
};
namespace _STL {
template<> void vector<Rva00776AC0Record24>::reserve(unsigned int);
template<> Rva00776AC0Record24* vector<Rva00776AC0Record24>::erase(Rva00776AC0Record24*,Rva00776AC0Record24*);
template<> void vector<Rva00776AC0Record24>::_M_insert_overflow(Rva00776AC0Record24*,const Rva00776AC0Record24&,const __false_type&,unsigned int,bool);
template<> void vector<Rva00776AC0Record32>::_M_insert_overflow(Rva00776AC0Record32*,const Rva00776AC0Record32&,const __false_type&,unsigned int,bool);
}
void Open2Construct768D20(Rva00776AC0Record24*,const Rva00776AC0Record24&);
struct Rva00776AC0Vec24 : std::vector<Rva00776AC0Record24> {
 void overflow(const Rva00776AC0Record24& r) { _STL::__false_type tag; _M_insert_overflow(_M_finish,r,tag,1,true); }
 void firstAppend(const Rva00776AC0Record24& r) { if(_M_finish!=_M_end_of_storage._M_data) { Open2Construct768D20(_M_finish,r); ++_M_finish; } else { _STL::__false_type tag; _M_insert_overflow(_M_finish,r,tag,1,true); } }
 void append(const Rva00776AC0Record24& r) { if(_M_finish!=_M_end_of_storage._M_data) { _STL::_Construct(_M_finish,r); ++_M_finish; } else overflow(r); }
};
struct Rva00776AC0Vec32 : std::vector<Rva00776AC0Record32> {
 void append(const Rva00776AC0Record32& r) { if(_M_finish!=_M_end_of_storage._M_data) { _STL::_Construct(_M_finish,r); ++_M_finish; } else { _STL::__false_type tag; _M_insert_overflow(_M_finish,r,tag,1,true); } }
};
void Open2Construct768D20(Rva00776AC0Record24*,const Rva00776AC0Record24&);
class Rva00776AC0Anim {
public:
 virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
 virtual int s4();
};
class Rva00776AC0Render { public:
 virtual void s0();
 virtual void s1();
 virtual void s2();
 virtual int s3();
 virtual void s4();
 virtual void s5();
 virtual const char* s6();
 virtual void s7();
 virtual void s8();
 virtual void s9();
 virtual void s10();
 virtual void s11();
 virtual void s12();
 virtual void s13();
 virtual void s14();
 virtual void s15();
 virtual void s16();
 virtual void s17();
 virtual void s18();
 virtual void s19();
 virtual void s20();
 virtual void s21();
 virtual void s22();
 virtual void s23();
 virtual void s24();
 virtual void s25();
 virtual void s26();
 virtual void s27();
 virtual void s28();
 virtual void s29();
 virtual void s30();
 virtual void s31();
 virtual void s32();
 virtual void s33();
 virtual void s34();
 virtual void s35();
 virtual void s36();
 virtual void s37();
 virtual void s38();
 virtual void s39();
 virtual void s40();
 virtual void s41();
 virtual void s42();
 virtual void s43();
 virtual void s44(Rva00776AC0Anim*,float,int);
 virtual void s45();
 virtual Rva00776AC0Anim* s46();
 virtual void s47();
 virtual void s48();
 virtual void s49();
 virtual void s50();
 virtual void s51();
 virtual void s52();
 virtual void s53();
 virtual void s54();
 virtual void s55();
 virtual void s56();
 virtual void s57();
 virtual void s58();
 virtual void s59();
 virtual void s60();
 virtual void s61();
 virtual void s62();
 virtual void s63();
 virtual void s64();
 virtual void s65();
 virtual void s66();
 virtual void s67();
 virtual void s68();
 virtual void s69();
 virtual void s70();
 virtual void s71();
 virtual void s72();
 virtual void s73();
 virtual void s74();
 virtual void s75();
 virtual void s76();
 virtual void s77();
 virtual void s78();
 virtual void s79();
 virtual void s80();
 virtual void s81();
 virtual void s82();
 virtual void s83();
 virtual void s84();
 virtual void s85();
 virtual void s86();
 virtual void s87();
 virtual void s88();
 virtual void s89();
 virtual void s90();
 virtual void s91();
 virtual void s92();
 virtual void s93();
 virtual void s94();
 virtual void s95();
 virtual void s96();
 virtual void s97();
 virtual void s98();
 virtual void s99();
 virtual void s100();
 virtual void s101();
 virtual void s102();
 virtual void s103();
 virtual void s104();
 virtual void s105();
 virtual void s106();
 virtual void s107();
 virtual void s108();
 virtual void s109();
 virtual void s110();
 virtual void s111();
 virtual void s112();
 virtual void s113();
 virtual void s114();
 virtual void s115();
 virtual void s116();
 virtual void s117();
 virtual void s118();
 virtual void s119();
 virtual void s120();
 virtual void s121();
 virtual void s122();
 virtual void s123();
 virtual void s124();
 virtual void s125();
 virtual void s126();
 virtual void s127();
 virtual void s128();
 virtual void s129();
 virtual void s130();
 virtual Rva00776AC0Anim* s131(float&,int&,int&,float&);
};
class Rva00776AC0Owner { public:
 virtual void s0();
 virtual void s1();
 virtual void s2();
 virtual void s3();
 virtual void s4();
 virtual void s5();
 virtual void s6();
 virtual void s7();
 virtual void s8();
 virtual void s9();
 virtual void s10();
 virtual void s11();
 virtual void s12();
 virtual void s13();
 virtual void s14();
 virtual void s15();
 virtual void s16();
 virtual void s17();
 virtual void s18();
 virtual void s19();
 virtual void s20();
 virtual void s21();
 virtual void s22();
 virtual void s23();
 virtual void s24();
 virtual void s25();
 virtual void s26();
 virtual void s27();
 virtual void s28();
 virtual void s29();
 virtual void s30();
 virtual void s31();
 virtual void s32(bool);
 virtual void s33();
 char gap004[12];
 void* m010;
 void* m014;
 char gap018[12];
 int m024;
 int m028;
 bool m02c;
 bool m02d;
 bool m02e;
 bool m02f;
 bool m030;
 char gap031[3];
 Rva00776AC0Render* m034;
 AsciiString m038;
 char gap03c[16];
 Rva00776AC0Vec24 m04c;
 Rva00776AC0Vec24 m058;
 bool m064;
 bool m065;
 char gap066[2];
 int m068;
 int m06c;
 float m070;
 char gap074[8];
 float m07c;
 float m080;
 bool m084;
 char gap085[3];
 int m088;
 int m08c;
 char gap090[8];
 AsciiString m098;
 char gap09c[4];
 int m0a0;
 int m0a4;
 char gap0a8[136];
 Rva00776AC0Vec32 m130;
 char gap13c[52];
 bool m170;
 bool m171;
 bool m172;
 bool m173;
 char gap174[68];
 int m1b8;
 char gap1bc[64];
 bool m1fc;
 char gap1fd[3];
 AsciiString m200;
 AsciiString m204;
 AsciiString m208;
 float m20c;
 bool m210;
 char gap211[3];
 unsigned m214;
 unsigned m218;
 unsigned m21c;
 int m220;
 char gap224[12];
 bool m230;
 bool m231;
 char gap232[58];
 float m26c;
 float m270;
 float m274;
 float m278;
 void rva00776AC0(Xfer*);
 void rva001139A0(Xfer*);
 void rva00765FB0(void*,float,bool,bool,bool);
 template<class T> T& at(unsigned n) { return *(T*)((char*)this+n); }
};
class Rva00776AC0Scene { public: virtual void s0(); virtual void s1(); virtual void s2(Rva00776AC0Render*); };
extern Rva00776AC0Scene *Rva012F8058;
Rva00776AC0Render *Create_Render_Obj(const char*);
class Rva00776AC0Sub148 { public: void rva001CB270(Xfer*); };
void Rva0010C3E0(Xfer*,void*);
Xfer* rva0076AEA0ParticleSystemIdSetXfer(Xfer*,void*);
void bfmeHandOver_00001A50(Xfer*,void*);
static void setString(AsciiString& s,const char* p) { s.StringBase<char>::set(p,p?(int)strlen(p):0); }
static void transfer24(Xfer* x,Rva00776AC0Record24& r) {
 *x==r.at00; *x==r.at04; *x==r.at08; *x==r.at0c; *x==r.at10; *x==r.at14;
}
struct Rva00776AC0Version : Xfer::Version {
 Rva00776AC0Version(unsigned char current) { data[0]=1; data[1]=current; }
};
void Rva00776AC0Owner::rva00776AC0(Xfer* x) {
 rva001139A0(x);
 if(x->IsLightCRC()) return;
 Rva00776AC0Version version(4); *x==version;
 float percent=0.0f;
 bool restored=false;
 if(x->IsStoring()) {
  if(m034 && m034->s3()==25 && m010) {
   int mode,frames; float frame,dummy;
   Rva00776AC0Anim* anim=m034->s131(frame,frames,mode,dummy);
   bool present=anim!=0; *x==present;
   if(anim) { *x==mode; percent=frame/(float)(anim->s4()-1); *x==percent; }
  } else { bool present=false; *x==present; }
 } else {
  bool present; *x==present;
  if(present) {
   {int mode; *x==mode;}
   *x==percent;
   if(m034 && m034->s3()==25) {
    Rva00776AC0Render* render=m034;
    Rva00776AC0Anim* anim=render->s46();
    if(anim) {
     float frame=(float)(anim->s4()-1)*percent;
     float dummy1,dummy2; int mode,dummy3;
     render->s131(dummy1,dummy3,mode,dummy2);
     render->s44(anim,frame,mode); restored=true;
    }
   }
  }
 }
 *x==m084;
 Rva0010C3E0(x,&m088);
 rva0076AEA0ParticleSystemIdSetXfer(x,&m08c);
 *x==m098; *x==m0a0; *x==m0a4;
 at<Rva00776AC0Sub148>(0x148).rva001CB270(x);
 *x==m1b8;
 if(x->IsLoading()) {
  int count=0;
#define a m04c
#define b m058
  a.erase(a.begin(),a.end()); b.erase(b.begin(),b.end());
  Rva00776AC0Record24 r;
  *x==count; a.reserve(count);
  for(int i=0;i<count;++i) {
   transfer24(x,r);
   // First append's placement constructor is independently out of line.
   a.firstAppend(r);
  }
  *x==count; b.reserve(count);
  for(int j=0;j<count;++j) { transfer24(x,r); b.append(r);
 }
 #undef a
 #undef b
 } else if(x->IsStoring()) {
  int count=(int)m04c.size(); *x==count;
  for(int i=0;i<count;++i) transfer24(x,m04c[i]);
  count=(int)m058.size(); *x==count;
  for(int j=0;j<count;++j) transfer24(x,m058[j]);
 }
 if(x->IsLoading()) {
  s33();
  int count; *x==count;
  for(int i=0;i<count;++i) {
   Rva00776AC0Record32 r;
   AsciiString a(""),b("");
   *x==a; *x==b; *x==r.at10; *x==r.at1c;
   r.at00=Create_Render_Obj(a.str()); r.at04=b.str();
   if(r.at00) { Rva012F8058->s2(r.at00); m130.append(r); }
  }
 } else if(x->IsStoring()) {
  int count=(int)m130.size(); *x==count;
  for(int i=0;i<count;++i) {
   Rva00776AC0Record32 r=m130[i];
   AsciiString a(""),b("");
   if(r.at00) setString(a,r.at00->s6());
   if(!r.at04.empty()) setString(b,r.at04.c_str());
   *x==a; *x==b; *x==r.at10; *x==r.at1c;
  }
 }
 *x==m230; *x==m231; *x==m210;
 bool at2d=m02d; *x==at2d;
 *x==m172; *x==m064; *x==m173;
 bool at2c=m02c; *x==m02c; m02c=at2c;
 *x==m065; *x==m171; *x==m02e; *x==m170; *x==m02f; *x==m1fc;
 *x==m024; if(version.data[1]<2) *x==m028;
 *x==m038; *x==m068; if(version.data[1]<2) *x==m06c;
 *x==m070; *x==m07c; *x==m080; *x==m20c; *x==m210;
 *x==m214; *x==m218; *x==m21c;
 bfmeHandOver_00001A50(x,&m220);
 *x==m200;
 for(int i=0;i<2;++i) *x==at<AsciiString>(0x204+i*4);
 if(version.data[1]>=3) *x==m030;
 if(version.data[1]>=4) { *x==m26c; *x==m270; *x==m274; *x==m278; }
 if(restored && m014) { m230=false; rva00765FB0(m014,percent,false,true,true); }
 if(x->IsLoading()) { s32(at2d); ((Rva00776AC0Owner*)((char*)this+0xc))->s28(); }
}
