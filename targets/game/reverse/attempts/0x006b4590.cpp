// ?method@Rva006B4590Owner@@QAEXPBVAudioEventRTS@@@Z
// partial score=0.2391 date=2026-10-03
// Draft only: address-qualified lifetime/call views are deliberately UNBOUND.
// Canonical AudioEventRTS needs BFME112B cutover; do not pin duplicate aliases.
// Current setAudioPriority callee identity at B23A0 needs independent audit.
// stlport
// cl: /O2 /MD /EHsc /D_STLP_USE_STATIC_LIB /I. /Iinputs/vendor/stlport /Iinputs/reference/shims/audio /Igame/Libraries/Source/WWVegas/WWLib /DNDEBUG /DWIN32 /Iinputs/reference/shims/zhcanonascii /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
#define _STLP_NO_EXCEPTIONS 1
typedef union { struct { unsigned long LowPart, HighPart; }; unsigned __int64 QuadPart; } ULARGE_INTEGER;
#include "PreRTS.h"
#include "Common/AudioEventRTS.h"
#include "mss.h"
typedef void *HAUDIO;
extern "C" __declspec(dllimport) HAUDIO __stdcall AIL_quick_load_and_play(const char *, int, int);
extern "C" __declspec(dllimport) void __stdcall AIL_quick_set_volume(HAUDIO, float, float);
class Rva006B4590Owner { public: void method(const AudioEventRTS *); };
#include <map>
#include <list>
// BFME AudioEventRTS is 112 bytes. This deliberately unbound lifetime view
// needs the canonical BFME header cutover before any production promotion.
struct Rva006B4590Event {
    Rva006B4590Event(const AudioEventRTS &);
    ~Rva006B4590Event();
    char bytes[0x70];
    AudioEventRTS *native() { return (AudioEventRTS *)this; }
    AsciiString &key() { return *(AsciiString *)(bytes+0x14); }
    int index() { return *(int *)(bytes+0x28); }
};
class Rva006B4590EventCalls {
public:
 unsigned getSoundClass() const;
 void bfmeGenerateFilename();
};
class Rva006B4590ManagerCalls {
public:
 void rva006B15A0(const AsciiString *);
 void rva006AF840();
};
class Rva006915E0 {
public:
 Rva006915E0(void *mutex) : m_held(false) { m_mutex=mutex; if(WaitForSingleObject(mutex,0xFFFFFFFF)!=0x102)m_held=true; }
 ~Rva006915E0() { release(); }
 void release() { if(m_held) {ReleaseMutex(m_mutex);m_held=false;} }
private:
 void *m_mutex; bool m_held;
};
namespace _STL { template<> struct less<AsciiString> { bool operator()(const AsciiString&a,const AsciiString&b)const{return a.compare(b)<0;} }; }
struct Rva005C7770Value { AsciiString m_key; };
struct Rva005C7770KeyOfValue { const AsciiString &operator()(const Rva005C7770Value &x)const{return x.m_key;} };
typedef _STL::_Rb_tree<AsciiString,Rva005C7770Value,Rva005C7770KeyOfValue,_STL::less<AsciiString>,_STL::allocator<Rva005C7770Value> > Rva006B4590Tree;
struct Rva006B4590Virtuals {
#define S(n) virtual void slot##n();
 S(0) S(1) S(2) S(3) S(4) S(5) S(6) S(7) S(8) S(9) S(10) S(11) S(12) S(13) S(14) S(15) S(16) S(17) S(18) S(19) S(20) S(21) S(22) S(23) S(24) S(25) S(26) S(27) S(28) S(29) S(30) S(31) S(32) S(33) S(34) S(35) S(36) S(37) S(38) S(39) S(40) S(41) S(42)
 virtual void slot43(const AudioEventRTS *);
 S(44) S(45)
 virtual bool slot46(unsigned);
};
void Rva006B4590Owner::method(const AudioEventRTS *eventToPlay)
{
 char *self=(char *)this;
 Rva006915E0 lock(*(void **)(self+0x95c));
 if(!*(void **)((char *)eventToPlay+8)) {
  ((Rva006B4590Virtuals *)this)->slot43(eventToPlay);
  if(!*(void **)((char *)eventToPlay+8))return;
 }
 if(!((Rva006B4590Virtuals *)this)->slot46(((const Rva006B4590EventCalls *)eventToPlay)->getSoundClass()))return;
 Rva006B4590Event event(*eventToPlay);
 ((Rva006B4590EventCalls *)&event)->bfmeGenerateFilename();
 event.native()->generatePlayInfo();
 Rva006B4590Tree *tree=(Rva006B4590Tree *)(self+0x270+event.index()*0x1c4);
 void *node=tree->find(event.key())._M_node;
 if(node!=*(void **)tree) {
  AudioPriority *value=(AudioPriority *)((char *)node+0x14);
  if(value)event.native()->setAudioPriority(*value);
 }
 AsciiString filename=event.native()->getFilename();
 HAUDIO audio=AIL_quick_load_and_play(filename.str(),1,0);
 if(audio) {
  ((Rva006B4590ManagerCalls *)this)->rva006B15A0(&filename);
  ((Rva006B4590ManagerCalls *)this)->rva006AF840();
  float volume=*(float *)(self+0x1ac+event.index()*0x1c4);
  AIL_quick_set_volume(audio,event.native()->getPitchShift()*volume,0.5f);
  ((std::list<HAUDIO> *)(self+0x9bc))->push_back(audio);
 }
}
