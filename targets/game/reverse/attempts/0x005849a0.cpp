// ??0Rva005849A0@@QAE@XZ
// partial score=1.0 date=2026-10-03
// cl: /O2 /Ob2 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Igame/Libraries/Source/WWVegas/WWLib /Igame/GameEngine/Source/Common/System
// stlport
typedef bool Bool;
#include "subsystem_interface.h"
#include <hash_map>
#include <vector>
struct Gen_p12cd { int a[3]; Gen_p12cd(); Gen_p12cd(const Gen_p12cd&); ~Gen_p12cd(); };
class Gen003A0410 { public: Gen003A0410(); ~Gen003A0410(); unsigned value; };
struct Rva005849A0Entry12 { unsigned words[3]; ~Rva005849A0Entry12(); };
struct Gen_p28pod { unsigned words[7]; };
class Rva005849A0;
class FunctorWrapperHead {
public: FunctorWrapperHead():m_refCount(0) {} virtual ~FunctorWrapperHead(); int m_refCount;
};
class Rva0110B724Callback:public FunctorWrapperHead {
 Rva005849A0 *owner; unsigned index;
public: Rva0110B724Callback(Rva005849A0 *p,unsigned i):owner(p),index(i) {} virtual ~Rva0110B724Callback(); virtual void invoke();
};
class Rva0050F8B0FunctorHolder {
public:
 __forceinline Rva0050F8B0FunctorHolder(Rva005849A0 *owner,unsigned i) { m_ptr=new Rva0110B724Callback(owner,i); if(m_ptr)++m_ptr->m_refCount; }
 Rva0050F8B0FunctorHolder(const Rva0050F8B0FunctorHolder &other):m_ptr(other.m_ptr) { if(m_ptr)++m_ptr->m_refCount; }
 ~Rva0050F8B0FunctorHolder() { FunctorWrapperHead *p=m_ptr; if(p && (p->m_refCount=p->m_refCount-1)<=0)delete p; }
 FunctorWrapperHead *m_ptr;
};
class WindowManager { public: void bfmeBindRva004650F0(const AsciiString&,Rva0050F8B0FunctorHolder); };
extern WindowManager *TheWindowManager;
class Rva005849A0:public SubsystemInterface {
 std::hash_map<int,Gen_p12cd> at08;
 Gen003A0410 at1c;
 std::vector<Rva005849A0Entry12> at20;
 int at2c;
 std::vector<Gen_p28pod> at30;
 bool at3c;
 int at40;
public:
 Rva005849A0(); virtual ~Rva005849A0(); virtual void init(); virtual void reset(); virtual void update();
};
Rva005849A0::Rva005849A0():at2c(0),at3c(false),at40(-1) {
 m_name=AsciiString("TheBannerUI");
 for(unsigned i=0;i<2;++i) {
  AsciiString name;
  name.format("BannerUI/~Location%d/Banner/AvailableBttn/",i);
  TheWindowManager->bfmeBindRva004650F0(name,Rva0050F8B0FunctorHolder(this,i));
  name.format("BannerUI/~Location%d/Banner/WaitingBttn/",i);
  TheWindowManager->bfmeBindRva004650F0(name,Rva0050F8B0FunctorHolder(this,i));
  name.format("BannerUI/~Location%d/Banner/Background",i);
  TheWindowManager->bfmeBindRva004650F0(name,Rva0050F8B0FunctorHolder(this,i));
 }
}
