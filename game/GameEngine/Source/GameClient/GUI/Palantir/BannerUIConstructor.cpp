// ??0BannerUI@@QAE@XZ
// Retail 0x005849A0 (521 bytes): the constructor of the BannerUI subsystem, the
// client banner block Zero Hour has no equivalent for.  It names the singleton
// through AsciiString("TheBannerUI"), initialises the two trailing members,
// then binds nine window callbacks through WindowManager::bfmeBindRva004650F0
// and a refcounted functor holder: for each of the two locations the
// AvailableBttn, the WaitingBttn and the Background gadget under
// BannerUI/~Location%d/Banner/.
//
// Identity: the body stores the named vftable at 0x0110B828, recorded in
// dir32_addresses.csv as ??_7BannerUI@@6B@, which names the class independently
// of this body, and the string at 0x0110B8F8 names the singleton; the member
// layout stays a private view of the class BannerUI.cpp already owns.
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
class BannerUI;
class FunctorWrapperHead {
public: FunctorWrapperHead():m_refCount(0) {} virtual ~FunctorWrapperHead(); int m_refCount;
};
class Rva00582470FunctorSingleWrapper:public FunctorWrapperHead {
 BannerUI *owner; unsigned index;
public: Rva00582470FunctorSingleWrapper(BannerUI *p,unsigned i):owner(p),index(i) {} virtual ~Rva00582470FunctorSingleWrapper(); virtual void invoke();
};
class Rva0050F8B0FunctorHolder {
public:
 __forceinline Rva0050F8B0FunctorHolder(BannerUI *owner,unsigned i) { m_ptr=new Rva00582470FunctorSingleWrapper(owner,i); if(m_ptr)++m_ptr->m_refCount; }
 Rva0050F8B0FunctorHolder(const Rva0050F8B0FunctorHolder &other):m_ptr(other.m_ptr) { if(m_ptr)++m_ptr->m_refCount; }
 ~Rva0050F8B0FunctorHolder() { FunctorWrapperHead *p=m_ptr; if(p && (p->m_refCount=p->m_refCount-1)<=0)delete p; }
 FunctorWrapperHead *m_ptr;
};
class WindowManager { public: void bfmeBindRva004650F0(const AsciiString&,Rva0050F8B0FunctorHolder); };
// Retail 0x012F19E8 is ?g_rva012F19E8WindowManager@@3PAVWindowManager@@A
// (data_rows.csv, GUI/WindowManager.cpp); g_theWindowManager was only a pin.
extern WindowManager *g_rva012F19E8WindowManager;
#define g_theWindowManager g_rva012F19E8WindowManager
class BannerUI:public SubsystemInterface {
 std::hash_map<int,Gen_p12cd> at08;
 Gen003A0410 at1c;
 std::vector<Rva005849A0Entry12> at20;
 int at2c;
 std::vector<Gen_p28pod> at30;
 bool at3c;
 int at40;
public:
 BannerUI(); virtual ~BannerUI(); virtual void init(); virtual void reset(); virtual void update();
};
BannerUI::BannerUI():at2c(0),at3c(false),at40(-1) {
 m_name=AsciiString("TheBannerUI");
 for(unsigned i=0;i<2;++i) {
  AsciiString name;
  name.format("BannerUI/~Location%d/Banner/AvailableBttn/",i);
  g_theWindowManager->bfmeBindRva004650F0(name,Rva0050F8B0FunctorHolder(this,i));
  name.format("BannerUI/~Location%d/Banner/WaitingBttn/",i);
  g_theWindowManager->bfmeBindRva004650F0(name,Rva0050F8B0FunctorHolder(this,i));
  name.format("BannerUI/~Location%d/Banner/Background",i);
  g_theWindowManager->bfmeBindRva004650F0(name,Rva0050F8B0FunctorHolder(this,i));
 }
}
