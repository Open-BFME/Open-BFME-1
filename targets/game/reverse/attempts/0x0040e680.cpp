// ?update0040E680@MovieOpen0040E3B0@@QAE_N_N@Z
// partial score=0.939 date=2026-09-28
// cl: /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
#include "ascii_string.h"
class Glo00EF3330 { public: void h004893E0(); void h00489410(); };
class GameWindowTransitionsHandler {
public:
 virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void reset();
 void reverse(AsciiString);
 int bfmeGetGroupTotalFrames(AsciiString);
 bool isFinished();
 void setGroup(AsciiString,bool);
};
extern GameWindowTransitionsHandler *Transitions0040E3B0;
class Rva00382960 {
public:
 Rva00382960() { if(Transitions0040E3B0) ((Glo00EF3330*)Transitions0040E3B0)->h004893E0(); }
 ~Rva00382960() { if(Transitions0040E3B0) ((Glo00EF3330*)Transitions0040E3B0)->h00489410(); }
};
extern "C" unsigned __stdcall bfme_timeGetTime();
class Rva004893C0ByteSetter {public: void set();};
struct MovieControl0040E680 {virtual void v00();virtual void v04();virtual void v08();virtual void v0c();virtual void v10();virtual void update();};
extern MovieControl0040E680 *Control0040E680;
struct MovieStream0040E3B0 {
 virtual void v00();
 virtual void v01();
 virtual void v02();
 virtual void v03();
 virtual void v04();
 virtual void v05();
 virtual void v06();
 virtual void v07();
 virtual int current();
 virtual int frames();
 virtual void v0a();
 virtual void v0b();
 virtual void v0c();
 virtual void v0d();
 virtual bool start(void*);
 virtual void v0f();
 virtual void v10();
 virtual void rate(float);
 virtual float getRate();
 
};
__forceinline bool finished0040E680(MovieStream0040E3B0 *const &stream) {return stream->current()>=stream->frames()-1;}
struct MovieFactory0040E3B0 {
 virtual void v00();
 virtual void v01();
 virtual void v02();
 virtual void v03();
 virtual void v04();
 virtual void v05();
 virtual void v06();
 virtual void v07();
 virtual void v08();
 virtual void v09();
 virtual void v0a();
 virtual void v0b();
 virtual MovieStream0040E3B0 *open(AsciiString,int);
};
extern MovieFactory0040E3B0 *MovieFactoryGlobal0040E3B0;
struct MovieOpen0040E3B0 {
 virtual void v00();
 virtual void v01();
 virtual void v02();
 virtual void v03();
 virtual void v04();
 virtual void v05();
 virtual void v06();
 virtual void v07();
 virtual void v08();
 virtual void v09();
 virtual void v0a();
 virtual void v0b();
 virtual void v0c();
 virtual void v0d();
 virtual void v0e();
 virtual void v0f();
 virtual void v10();
 virtual void v11();
 virtual void v12();
 virtual void v13();
 virtual void v14();
 virtual void v15();
 virtual void v16();
 virtual void v17();
 virtual void v18();
 virtual void v19();
 virtual void v1a();
 virtual void v1b();
 virtual void v1c();
 virtual void v1d();
 virtual void v1e();
 virtual void v1f();
 virtual void v20();
 virtual void *buffer(bool);
 virtual void v22();
 virtual void v23();
 virtual void v24();
 virtual void v25();
 virtual void v26();
 virtual void v27();
 virtual void v28();
 virtual void v29();
 virtual void v2a();
 virtual void v2b();
 virtual void v2c();
 virtual void v2d();
 virtual void v2e();
 virtual void v2f();
 virtual void v30();
 virtual void v31();
 virtual void v32();
 virtual void v33();
 virtual void v34();
 virtual void v35();
 virtual void v36();
 virtual void v37();
 virtual void v38();
 virtual void v39();
 virtual void v3a();
 virtual void close();
 char bytes04[0x30]; MovieStream0040E3B0 *stream34; volatile int flags38;
 char bytes3c[0x14]; int field50,field54; bool field58; volatile bool field59; char bytes5a[0x72];
 AsciiString namecc; char bytesd0[0xc]; int fielddc,fielde0; unsigned fielde4;
 char bytese8[0x24]; int field10c;
 bool open(AsciiString name,int flags,int a,int b);
 bool update0040E680(bool skip);
void setRate0040E680(float r) {stream34->rate(r);}
};
bool MovieOpen0040E3B0::update0040E680(bool skip) {
 if(!stream34) return true;
 bool done=false;
 switch(field50) {
 case 0:
  if(flags38&0x400000) {
   float rate=stream34->getRate()+0.05f;
   if(rate>1.0f) {rate=1.0f; field50=1;}
   setRate0040E680(rate);
  } else if(Transitions0040E3B0->isFinished()) {
   field50=1;
   Transitions0040E3B0->reset();
  }
  break;
 case 1:
  if((unsigned)stream34->current()>=(unsigned)field54 || skip) {
   field50=3;
   if(flags38&0x200000) {field50=2;}
   else if(flags38&0x20) {
    field50=2;
    Transitions0040E3B0->setGroup(AsciiString("FadeInGameMovie"),false);
    ((Rva004893C0ByteSetter*)Transitions0040E3B0)->set();
    Control0040E680->update();
   } else if(flags38&0x200) {
    field50=2;
    Transitions0040E3B0->setGroup(AsciiString("FadeScreenToWhite"),false);
    ((Rva004893C0ByteSetter*)Transitions0040E3B0)->set();
    Control0040E680->update();
   } else if(skip) done=true;
  }
  break;
 case 2: {
 bool finished=false;
 float rate;
 if(flags38&0x200000) {if(field10c<=0) {rate=stream34->getRate()-0.05f;
    if(rate<0.0f) {rate=0.0f;finished=true;}
    setRate0040E680(rate);
} else --field10c;}
else finished=Transitions0040E3B0->isFinished();
if(finished) { if(skip || finished0040E680(stream34)) done=true; }
 break;
 }
 default: done=skip; break;
 }
 return done;
}
