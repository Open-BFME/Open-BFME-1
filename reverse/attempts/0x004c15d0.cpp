// ?d_004c15d0@@YAXXZ
// partial score=0.317109 date=2026-09-25
// cl: /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE
#include <list>
#include "PreRTS.h"
#include "GameClient/AnimateWindowManager.h"

class Rva004C1150AdapterBase { public: virtual ~Rva004C1150AdapterBase(); };
class Rva004C1AE0Handle {
public:
 ~Rva004C1AE0Handle() { delete m_ptr; }
 Rva004C1150AdapterBase *release() { Rva004C1150AdapterBase *p=m_ptr;m_ptr=0;return p; }
 Rva004C1150AdapterBase *m_ptr;
};
class Rva004C1510Handle {
public:
 Rva004C1510Handle(Rva004C1150AdapterBase *p=0):m_ptr(p) {}
 Rva004C1510Handle(Rva004C1510Handle &o):m_ptr(o.release()) {}
 Rva004C1510Handle(Rva004C1AE0Handle &o):m_ptr(o.release()) {}
 ~Rva004C1510Handle(){delete m_ptr;}
 Rva004C1150AdapterBase *release(){Rva004C1150AdapterBase *p=m_ptr;m_ptr=0;return p;}
 Rva004C1510Handle &operator=(Rva004C1510Handle);
private: Rva004C1150AdapterBase *m_ptr;
};
class Rva004C15D0Arg {
public:
 virtual void slot0();
 virtual Rva004C1AE0Handle clone(); // retail slot +4, hidden return
 virtual unsigned delay();         // retail slot +8
};
class InGameUI { public: virtual Bool slot0(); virtual Bool slot1(); virtual Bool slot2(); virtual Bool slot3(); virtual Bool slot4(); virtual Bool slot5(); virtual Bool slot6(); virtual Bool slot7(); virtual Bool slot8(); virtual Bool slot9(); virtual Bool slot10(); virtual Bool slot11(); virtual Bool slot12(); virtual Bool slot13(); virtual Bool slot14(); virtual Bool slot15(); virtual Bool slot16(); virtual Bool slot17(); virtual Bool slot18(); virtual Bool slot19(); virtual Bool slot20(); virtual Bool slot21(); virtual Bool slot22(); virtual Bool slot23(); virtual Bool slot24(); virtual Bool slot25(); virtual Bool slot26(); virtual Bool slot27(); virtual Bool slot28(); virtual Bool slot29(); virtual Bool slot30(); virtual Bool slot31(); virtual Bool slot32(); virtual Bool slot33(); virtual Bool slot34(); virtual Bool slot35(); virtual Bool slot36(); virtual Bool slot37(); virtual Bool slot38(); virtual Bool slot39(); virtual Bool slot40(); virtual Bool slot41(); virtual Bool slot42(); virtual Bool slot43(); virtual Bool slot44(); virtual Bool slot45(); virtual Bool slot46(); virtual Bool slot47(); virtual Bool slot48(); virtual Bool slot49(); virtual Bool slot50(); virtual Bool slot51(); virtual Bool slot52(); virtual Bool slot53(); virtual Bool slot54(); virtual Bool slot55(); virtual Bool slot56(); virtual Bool slot57(); virtual Bool slot58(); virtual Bool slot59(); virtual Bool slot60(); virtual Bool slot61(); virtual Bool slot62(); virtual Bool slot63(); virtual Bool slot64(); virtual Bool slot65(); virtual Bool slot66(); virtual Bool slot67(); virtual Bool slot68(); virtual Bool slot69(); virtual Bool slot70(); virtual Bool slot71(); virtual Bool slot72(); virtual Bool slot73(); virtual Bool slot74(); virtual Bool slot75(); virtual Bool slot76(); virtual Bool slot77(); virtual Bool slot78(); virtual Bool slot79(); virtual Bool slot80(); virtual Bool slot81(); virtual Bool slot82(); virtual Bool slot83(); virtual Bool slot84(); virtual Bool slot85(); virtual Bool slot86(); virtual Bool slot87(); virtual Bool slot88(); virtual Bool slot89(); virtual Bool slot90(); virtual Bool slot91(); virtual Bool slot92(); virtual Bool slot93(); virtual Bool slot94(); virtual Bool slot95(); virtual Bool slot96(); virtual Bool slot97(); virtual Bool slot98(); virtual Bool slot99(); virtual Bool slot100(); virtual Bool slot101(); };
class Rva004C15D0Layout { public: virtual void s0(); virtual void s4(); virtual void s8(); virtual void sC(); virtual void show(bool); };
// BFME animate-windows switch is at +0xBC4, unlike the reference layout.
static inline bool animateWindowsEnabled(const GlobalData *data)
{ return *(const bool *)((const char *)data + 0xBC4); }
class ControlBar {
 char pad0[0x278]; Rva004C15D0Layout *layout; char pad280[0x78]; public: Rva004C1510Handle handle; private:
 char pad2FC[0x74];
public: void doRepopulateBuildTooltipLayout(); void rva004C15D0(Rva004C15D0Arg*);
};
extern InGameUI *TheInGameUI; // 012F148C
extern void *TheScriptEngine;
extern GlobalData *TheWritableGlobalData;
extern Bool g_bfmeReadyPT;
extern bool Rva004C15D0Shown;
extern void *TheDisconnectMenu;
class BfmeThingGX;
extern int bfmeSameGX(BfmeThingGX*,BfmeThingGX*);
extern void *operator new(unsigned int);
class Rva005929E0 { public: void release(); };

extern AnimateWindowManager *Glo012F368C;
extern void *Glo012F4B98;
void ControlBar::rva004C15D0(Rva004C15D0Arg *arg)
{
 if(TheInGameUI->slot101()) return;
 if(*(int*)((char*)TheScriptEngine+0x17080)>=0) return;
 static unsigned begin=(unsigned)timeGetTime();
 void *ownerHandle=*(void**)((char*)this+0x2f4);
 if(ownerHandle && ((bool (__cdecl *)(void *, void *))bfmeSameGX)(arg,ownerHandle)) {
  *(Bool*)((char*)this+0x27c)=1;
  unsigned d=arg->delay();
  if(Rva004C15D0Shown || begin+d>= (unsigned)timeGetTime()) return;
  Rva004C15D0Shown=1;
  if(TheInGameUI->slot85() || TheDisconnectMenu) return;
  *(Bool*)((char*)this+0x27c)=1;
  doRepopulateBuildTooltipLayout();
  layout->show(false);
  if(!g_bfmeReadyPT || !animateWindowsEnabled(TheWritableGlobalData)) return;
  Glo012F368C=new AnimateWindowManager;
  Glo012F368C->update();
  Glo012F368C->registerGameWindow(*(GameWindow **)((char*)layout+8),(AnimTypes)2,true,200,0);
  return;
 }
 if(!*(Bool*)((char*)layout+0x14)) {
  if(g_bfmeReadyPT && animateWindowsEnabled(TheWritableGlobalData) && !*(Bool*)((char*)Glo012F368C+0x11)) {
   Glo012F368C->reverseAnimateWindow(); return;
  }
  if(g_bfmeReadyPT && animateWindowsEnabled(TheWritableGlobalData) && *(Bool*)((char*)Glo012F368C+0x11)) return;
  layout->show(true);
  Rva004C1150AdapterBase *p=(Rva004C1150AdapterBase*)*(void**)((char*)this+0x2f4);
  delete p;
  *(void**)((char*)this+0x2f4)=0;
  if(Glo012F4B98) ((Rva005929E0*)((char*)Glo012F4B98+0x488))->release();
  return;
 }
 handle=arg->clone();
 begin=(unsigned)timeGetTime();
 Rva004C15D0Shown=0;
}
