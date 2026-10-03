// ??0Rva00592640Owner@@QAE@XZ
// partial score=1.0 date=2026-10-03
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /MD /EHsc /DBFME_STLP_NODE_ALLOC /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/shims/zhcanonascii /Iinputs/reference/shims/displaystringmanager /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
#define __PLACEMENT_VEC_NEW_INLINE
#include "PreRTS.h"
#include "GameClient/DisplayStringManager.h"
#include "GameClient/Image.h"
class __single_inheritance Rva00592640Owner;
class Gen0003FA7B;
class Rva00590790 {
public:
 Rva00590790():m_held(0) {}
 ~Rva00590790();
 Gen0003FA7B* m_held;
};
class Rva00592640Counted {
public:
 Rva00592640Counted():m_refs(0) {}
 virtual ~Rva00592640Counted();
 virtual void invoke();
 int m_refs;
};
struct Rva00592640Binding {
 typedef void (Rva00592640Owner::*Method)(void*,void*,void*,void*);
 Rva00592640Binding(Rva00592640Owner* p,Method f):m_owner(p),m_method(f) {}
 Rva00592640Owner* m_owner;
 Method m_method;
};
class Rva00592640Callback : public Rva00592640Counted {
public:
 Rva00592640Callback(const Rva00592640Binding& b):m_binding(b) {}
 virtual ~Rva00592640Callback();
 virtual void invoke();
 Rva00592640Binding m_binding;
};
class AptMapPreviewFunctorHolder {
public:
 AptMapPreviewFunctorHolder(Rva00592640Binding b) {
  m_ptr=new Rva00592640Callback(b); if(m_ptr) ++m_ptr->m_refs;
 }
 AptMapPreviewFunctorHolder(const AptMapPreviewFunctorHolder&);
 ~AptMapPreviewFunctorHolder();
 Rva00592640Callback* m_ptr;
};
class WindowManager {
public: void registerAptCallback(const AsciiString&,AptMapPreviewFunctorHolder);
};
extern WindowManager* g_theWindowManager;
class Rva00592640Owner {
public:
 Rva00592640Owner();
 void rva0058E390(void*,void*,void*,void*);
 bool at00,at01,at02;
 int at04;
 Rva00590790 at08,at0c;
 int at10;
 DisplayString *at14,*at18,*at1c,*at20,*at24;
 const Image* at28;
 int at2c;
};
Rva00592640Owner::Rva00592640Owner():at00(false),at01(false),at02(false),at04(-1),at10(0) {
 at14=TheDisplayStringManager->newDisplayString();
 at18=TheDisplayStringManager->newDisplayString();
 at1c=TheDisplayStringManager->newDisplayString();
 at20=TheDisplayStringManager->newDisplayString();
 at24=TheDisplayStringManager->newDisplayString();
 at28=TheMappedImageCollection->findImageByName(AsciiString("Resource_Icon"));
 at2c=0;
 { AsciiString text("HelpBoxText");
 g_theWindowManager->registerAptCallback(text,AptMapPreviewFunctorHolder(Rva00592640Binding(this,&Rva00592640Owner::rva0058E390))); }
 if(at28 && (at28->getImageWidth()<=0 || at28->getImageHeight()<=0)) at28=0;
}
