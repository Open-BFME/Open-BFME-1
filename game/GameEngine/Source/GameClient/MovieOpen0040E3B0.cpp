// Retail RVAs 0x0040E3B0 (573 bytes), 0x0040E680 (616 bytes) and 0x0040F780 (834 bytes).
// Address-derived ABI view: movie stream at +0x34, transition state at +0x50,
// and the virtual slots below are independently read from both retail bodies.
// These declarations do not construct objects or assert an original class name.
// Volatile on +0x38 and +0x59 preserves the observed reloads/store ordering;
// this is an executable view of retail, not a claim about original qualifiers.
// The scoped transition guard uses the established 0x00382960 constructor
// and counter helpers at 0x004893E0/0x00489410. Parameter-owned AsciiString
// cleanup is emitted by the real StringBase-based header.
// cl: /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
class VideoPlayerInterface;
extern VideoPlayerInterface *TheVideoPlayer;

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
class Rva004893C0ByteSetter {public: void set();};
extern GameWindowTransitionsHandler *Transitions0040E3B0;
class Rva00382960 {
public:
 Rva00382960() { if(Transitions0040E3B0) ((Glo00EF3330*)Transitions0040E3B0)->h004893E0(); }
 ~Rva00382960() { if(Transitions0040E3B0) ((Glo00EF3330*)Transitions0040E3B0)->h00489410(); }
};
extern "C" unsigned __stdcall bfme_timeGetTime();
struct MovieStream0040E3B0 {
 virtual void v00();
 virtual void v01();
 virtual void v02();
 virtual void v03();
 virtual void v04();
 virtual void v05();
 virtual unsigned advance(int);
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
 virtual bool startMovie(AsciiString,int,int,int);
 virtual void v3a();
 virtual void close();
 virtual void extra3c();
 virtual void extra3d();
 virtual void extra3e();
 virtual void extra3f();
 virtual void extra40();
 virtual void extra41();
 virtual void extra42();
 virtual void extra43();
 virtual void extra44();
 virtual void extra45();
 virtual void extra46();
 virtual void extra47();
 virtual void extra48();
 virtual void extra49();
 virtual void extra4a();
 virtual void extra4b();
 virtual void extra4c();
 virtual void extra4d();
 virtual void extra4e();
 virtual void extra4f();
 virtual void extra50();
 virtual void extra51();
 virtual void extra52();
 virtual void extra53();
 virtual void extra54();
 virtual void extra55();
 virtual void extra56();
 virtual void extra57();
 virtual void extra58();
 virtual void render(bool);
 char bytes04[0x30]; MovieStream0040E3B0 *stream34; volatile int flags38;
 char bytes3c[0x14]; int field50,field54; bool field58; volatile bool field59; char bytes5a[6]; bool field60; char bytes61[0x6b];
 AsciiString namecc; char bytesd0[0xc]; int fielddc,fielde0; unsigned fielde4;
 char bytese8[0x20]; bool field108; char bytes109[3]; int field10c;
 bool open(AsciiString name,int flags,int a,int b);
 bool update0040E680(bool);
 bool play0040F780(AsciiString,bool,int);
};
class DebugStream00409E20
{
public:
	virtual DebugStream00409E20 *Put_Unsigned(unsigned value);
	virtual void Slot04();
	virtual void Slot08();
	virtual void Slot0C();
	virtual void Slot10();
	virtual void Slot14();
	virtual void Slot18();
	virtual void Slot1C();
	virtual void Slot20();
	virtual void Slot24();
	virtual void Slot28();
	virtual void Slot2C();
	virtual void Slot30();
	virtual void Slot34();
	virtual DebugStream00409E20 *Put_String(const char *text);
	virtual void Slot3C();
	virtual void Slot40();
	virtual void Slot44();
	virtual void Slot48();
	virtual DebugStream00409E20 *Finish(int report);
};

class DebugView00409E20
{
public:
	virtual void Slot00(); virtual void Slot04(); virtual void Slot08(); virtual void Slot0C();
	virtual void Slot10(); virtual void Slot14(); virtual void Slot18(); virtual void Slot1C();
	virtual void Slot20(); virtual void Slot24(); virtual void Slot28(); virtual void Slot2C();
	virtual void Slot30(); virtual void Slot34(); virtual void Slot38(); virtual void Slot3C();
	virtual void Slot40(); virtual void Slot44(); virtual void Slot48(); virtual void Slot4C();
	virtual void Slot50(); virtual void Slot54(); virtual void Slot58(); virtual void Slot5C();
	virtual void Begin_Report();
	virtual void Slot64(); virtual void Slot68();
	virtual DebugStream00409E20 *Get_Stream(void *owner, void *context);
};

extern DebugView00409E20 *DebugGlobal00409E20;
extern void _bfme_debugRecordCallsite(int kind);
bool __cdecl _bfme_debugReportingEnabled(void);



extern "C" __declspec(dllimport) long __stdcall SendMessageA(void*,unsigned,unsigned,long);
extern "C" __declspec(dllimport) void *__stdcall GetCurrentThread();
extern "C" __declspec(dllimport) int __stdcall SetThreadPriority(void*,int);
extern void *Window0040F780;
extern __int64 Counter0040F780;
extern double Interval0040F780;
class GameLogic;
extern GameLogic *TheGameLogic;
class BfmeGameLogicPause {public: void setGamePaused(bool,int,bool);};
bool bfmeGoEMEa(void*);
void Rva009EBC00(int);
void Rva009EBBE0(int);
void setFPMode();
// Retail's writable-global pointer (0x012ED5C8), defined once in
// Common/GlobalData.cpp.  The canonical spelling is what links; the local view
// below is only how this TU reads field1278 at +0x1278, so it is cast at use.
class GlobalData;
extern GlobalData *TheWritableGlobalData;
struct Settings0040F780 {char bytes00[0x1278];bool field1278;};
class Mouse {public: void _bfme_setEngineVisibility(bool);};
extern Mouse *TheMouse;
class BfmeObjDC {public:void bfmeGoDC();};
class Display {public:void bfmeStopMovie();};
class Watchdog {public:void update();};
extern Watchdog *Watchdog0040F780;
struct Audio0040F780 {
 virtual void audio00();
 virtual void audio01();
 virtual void audio02();
 virtual void audio03();
 virtual void audio04();
 virtual void audio05();
 virtual void audio06();
 virtual void audio07();
 virtual void audio08();
 virtual void audio09();
 virtual void audio0a();
 virtual void audio0b();
 virtual void audio0c();
 virtual void audio0d();
 virtual void audio0e();
 virtual void audio0f();
 virtual void audio10();
 virtual void audio11();
 virtual void audio12();
 virtual void audio13();
 virtual void audio14();
 virtual void audio15();
 virtual void audio16();
 virtual void audio17();
 virtual void audio18();
 virtual void audio19();
 virtual void audio1a();
 virtual void audio1b();
 virtual void audio1c();
 virtual void audio1d();
 virtual void audio1e();
 virtual void audio1f();
 virtual void audio20();
 virtual void audio21();
 virtual void audio22();
 virtual void audio23();
 virtual void audio24();
 virtual void audio25();
 virtual void audio26();
 virtual void audio27();
 virtual void audio28();
 virtual void audio29();
 virtual void audio2a();
 virtual void audio2b();
 virtual void audio2c();
 virtual void audio2d();
 virtual void audio2e();
 virtual void audio2f();
 virtual void audio30();
 virtual void audio31();
 virtual void audio32();
 virtual void audio33();
 virtual void audio34();
 virtual void audio35();
 virtual void audio36();
 virtual void audio37();
 virtual void audio38();
 virtual void audio39();
 virtual void audio3a();
 virtual void audio3b();
 virtual void audio3c();
 virtual void audio3d();
 virtual void audio3e();
 virtual void suspend();
 virtual void resume();
 virtual void update();
};
class AudioManager;
extern AudioManager *TheAudio;
struct MovieControl0040F780 { virtual void v00(); virtual void v04();virtual void v08();virtual void v0c();virtual void v10();virtual void update();};
class GameWindowManager;
extern GameWindowManager *TheWindowManager;
struct Renderer0040F780 {
 virtual void renderer00();
 virtual void renderer01();
 virtual void renderer02();
 virtual void renderer03();
 virtual void renderer04();
 virtual void renderer05();
 virtual void renderer06();
 virtual void renderer07();
 virtual void renderer08();
 virtual void renderer09();
 virtual void renderer0a();
 virtual void renderer0b();
 virtual void renderer0c();
 virtual void renderer0d();
 virtual void renderer0e();
 virtual void renderer0f();
 virtual void update();
};
class GameEngine;
extern GameEngine *TheGameEngine;

struct KeyEvent0040F780 {unsigned char type,byte01,flags,bytes03[5];};
struct Keyboard0040F780:MovieControl0040F780 {char bytes04[8];KeyEvent0040F780 *first,*last;};
class Keyboard;
extern Keyboard *TheKeyboard;
__forceinline void priorityFailure0040F780() {
 _bfme_debugRecordCallsite(1);
 DebugGlobal00409E20->Begin_Report();
 DebugGlobal00409E20->Get_Stream(0,0)->Put_String("Could not set Main Thread Priority")->Finish(1);
}
bool MovieOpen0040E3B0::open(AsciiString name,int flags,int a,int b) {
 close();
 bool special=false;
 field59=true; field58=false;
 if(flags&0x40) special=true;
 stream34=((MovieFactory0040E3B0 *&)TheVideoPlayer)->open(name,flags);
 if(!stream34) return false;
 if(!stream34->start(buffer(special))) {close();return false;}
 field59=false;
 namecc=name; fielddc=a; fielde0=b; fielde4=bfme_timeGetTime(); flags38=flags;
 if(flags38&0x400000) stream34->rate(0.05f);
 else if(flags38&0x10) {
  Rva00382960 guard;
  Transitions0040E3B0->reset();
  Transitions0040E3B0->reverse(AsciiString("FadeInGameMovie"));
  field50=0;
 } else if(flags38&0x100) {
  Rva00382960 guard;
  Transitions0040E3B0->reset();
  Transitions0040E3B0->reverse(AsciiString("FadeScreenToWhite"));
  field50=0;
 } else {Transitions0040E3B0->reset(); field50=1;}
 unsigned count=stream34->frames();
 if(flags38&0x200000) {
  field10c=10;
  if(flags38&0x80) field54=count; else field54=count-20;
 } else if(flags38&0x20) field54=count-Transitions0040E3B0->bfmeGetGroupTotalFrames(AsciiString("FadeInGameMovie"));
 else if(flags38&0x200) field54=count-Transitions0040E3B0->bfmeGetGroupTotalFrames(AsciiString("FadeScreenToWhite"));
 else field54=stream34->frames();
 return true;
}

bool MovieOpen0040E3B0::update0040E680(bool skip) {
 if(!stream34) return true;
 bool done=false;
 switch(field50) {
 case 0:
  if(flags38&0x400000) {
   float rate=stream34->getRate()+0.05f;
   if(rate>1.0f) {rate=1.0f; field50=1;}
   stream34->rate(rate);
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
    reinterpret_cast<MovieControl0040F780 *>(TheWindowManager)->update();
   } else if(flags38&0x200) {
    field50=2;
    Transitions0040E3B0->setGroup(AsciiString("FadeScreenToWhite"),false);
    ((Rva004893C0ByteSetter*)Transitions0040E3B0)->set();
    reinterpret_cast<MovieControl0040F780 *>(TheWindowManager)->update();
   } else if(skip) done=true;
  }
  break;
 case 2: {
  bool finished=false;
  if(flags38&0x200000) {
   if(field10c<=0) {
    float rate=stream34->getRate()-0.05f;
    if(rate<0.0f) {rate=0.0f;finished=true;}
    stream34->rate(rate);
   } else {--field10c; break;}
  } else if(Transitions0040E3B0->isFinished()) finished=true;
  if(finished) { if(skip || finished0040E680(stream34)) done=true; }
  break;
 }
 default: done=skip; break;
 }
 return done;
}

bool MovieOpen0040E3B0::play0040F780(AsciiString name,bool allowSkip,int flags) {
 SendMessageA(Window0040F780,15,0,0);
 Interval0040F780=(1.0/30.0)/(double)Counter0040F780*1000.0;
 ((BfmeGameLogicPause *)TheGameLogic)->setGamePaused(true,0,false);
 bool active=bfmeGoEMEa(0);
 if(!((Settings0040F780 *)TheWritableGlobalData)->field1278 && active) Rva009EBC00(0);
 void *thread=GetCurrentThread();
 if(!SetThreadPriority(thread,2)) priorityFailure0040F780();
 if(TheAudio) ((Audio0040F780 *)TheAudio)->suspend();
 if(startMovie(name,flags|8,-1,-1)) {
  field108=true;
  unsigned pending=0;
  bool skipRequested=false;
  bool drawFrame=false;
  reinterpret_cast<MovieControl0040F780 *>(TheWindowManager)->update();
  TheMouse->_bfme_setEngineVisibility(false);
  bool alternateAudio=false;
  bool done;
  do {
   reinterpret_cast<Keyboard0040F780 *>(TheKeyboard)->update();
   KeyEvent0040F780 *end=reinterpret_cast<Keyboard0040F780 *>(TheKeyboard)->last;
   for(KeyEvent0040F780 *k=reinterpret_cast<Keyboard0040F780 *>(TheKeyboard)->first;k!=end;++k) {
    if(k->type==1 && (k->flags&1) && allowSkip) {skipRequested=true;break;}
   }
   done=update0040E680(skipRequested);
   if(stream34 && !(pending&2)) {
    pending|=stream34->advance(0);
    drawFrame=(pending&1)!=0;
   } else done=true;
   if(drawFrame) {
    drawFrame=false;pending&=~1U;
    ((BfmeObjDC*)this)->bfmeGoDC();
    render(true);
    ((MovieControl0040F780*)Transitions0040E3B0)->update();
    (*reinterpret_cast<Renderer0040F780 **>(&TheGameEngine))->update();
    if(alternateAudio) {((Audio0040F780 *)TheAudio)->update();alternateAudio=false;}
    else alternateAudio=true;
    setFPMode();
   }
   if(Watchdog0040F780) Watchdog0040F780->update();
  } while(!done);
  close();field60=false;
  ((Display*)this)->bfmeStopMovie();
  reinterpret_cast<Keyboard0040F780 *>(TheKeyboard)->update();
 }
 if(TheAudio) ((Audio0040F780 *)TheAudio)->resume();
 if(!SetThreadPriority(thread,0)) priorityFailure0040F780();
 if(!((Settings0040F780 *)TheWritableGlobalData)->field1278 && active) Rva009EBBE0(0);
 ((BfmeGameLogicPause *)TheGameLogic)->setGamePaused(false,0,false);
 if(flags&0x100000) {Transitions0040E3B0->reset(); TheMouse->_bfme_setEngineVisibility(true);}
 reinterpret_cast<MovieControl0040F780 *>(TheWindowManager)->update();
 return true;
}
