// ?rva0056FD90@Rva56E070StateOwner@@QAEHXZ
// partial score=1.0 date=2026-10-03
// BANK ONLY: callback-holder cleanup identities remain UNBOUND at51E6E0/4C5790.
// Full control flow and six-state outgoing-argument EH choreography are reconstructed.
// cl: /O2 /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /Igame/GameEngine/Source/GameClient
#include "unicode_string.h"
#include "game_window.h"
// Same inline destructor as the canonical implementation; no duplicate type.
inline UnicodeString::~UnicodeString() { ((StringBase<unsigned short> *)this)->releaseBuffer(); }
class BfmeH1065;
int bfmeAptLevel00465CE0(BfmeH1065 *);
class BfmeLevelAN { public: char *bfmeBuildAN(unsigned,int,int,int,int,int,int,int); };
class WindowManager; extern WindowManager *g_rva012F19E8WindowManager;
class BfmeThingME { public: void apply(); };
class Rva56E070StateOwner : public BfmeThingME {
public:
 char pad0[0x258]; int state; int direction; char pad260[4];
 GameWindow *arg264,*arg268,*context26c;
 void finishCurrent(); void rva0056D070(); int rva0056FD90();
};
class __multiple_inheritance FunctorTarget;
typedef void (FunctorTarget::*FunctorMethod)();
struct FunctorBinding { FunctorTarget *target; unsigned refCount; FunctorMethod method; };
class Rva0056DB00FunctorHolder {
public: Rva0056DB00FunctorHolder(FunctorBinding); Rva0056DB00FunctorHolder(const Rva0056DB00FunctorHolder &); ~Rva0056DB00FunctorHolder(); void *ptr;
}; // dtor UNBOUND: retail cleanup51E6E0, pointer at outgoing-argument address
class Rva0056FD90NullHolder { public: Rva0056FD90NullHolder():ptr(0){} Rva0056FD90NullHolder(const Rva0056FD90NullHolder &); ~Rva0056FD90NullHolder(); void *ptr; };
// null-holder dtor UNBOUND: retail cleanup4C5790.
class UnicodeStringYX; struct Rva522990RefPtr;
void Rva00522990ConfigureMessageBox(int,const UnicodeStringYX&,const UnicodeStringYX&,Rva522990RefPtr,Rva522990RefPtr);
typedef void (__cdecl *Rva0056FD90MessageCall)(int,const UnicodeString&,const UnicodeString&,Rva0056FD90NullHolder,Rva0056DB00FunctorHolder);
class Rva0056FD90Text {
public:
 virtual void slot0();
 virtual void slot1();
 virtual void slot2();
 virtual void slot3();
 virtual void slot4();
 virtual void slot5();
 virtual void slot6();
 virtual void slot7();
 virtual void slot8();
 virtual void slot9();
 virtual UnicodeString slot10(const char *,bool *);
};
class GameTextInterface; extern GameTextInterface *TheGameText;
void j_00020d15(); // existing5-byte address identity; routes to dispatchState56A940
static __forceinline FunctorBinding bind56FD90(Rva56E070StateOwner *owner) {
 FunctorBinding b; b.target=(FunctorTarget *)owner;
 union { FunctorMethod method; struct {unsigned code;int delta;} words; } bits;
 bits.words.code=(unsigned)&j_00020d15; bits.words.delta=0; b.method=bits.method;
 return b; // refCount is deliberately unspecified, matching the native binding family.
}
int Rva56E070StateOwner::rva0056FD90() {
 if(state==1) {apply();state=0;}
 else if(state==2) {finishCurrent();state=0;}
 else if(state==10 || state==11 || state==12 || state==13) {
  if(context26c)context26c->winEnable(false);
  if(arg264)arg264->winEnable(false);
  if(arg268)arg268->winEnable(false);
  if(state==10) {((BfmeLevelAN *)g_rva012F19E8WindowManager)->bfmeBuildAN(bfmeAptLevel00465CE0((BfmeH1065 *)this),(int)"showMessageBox",1,(int)"Load",0,0,0,0);state=14;}
  else if(state==11) {((BfmeLevelAN *)g_rva012F19E8WindowManager)->bfmeBuildAN(bfmeAptLevel00465CE0((BfmeH1065 *)this),(int)"showMessageBox",1,(int)"Save",0,0,0,0);state=15;}
  else if(state==12) {((BfmeLevelAN *)g_rva012F19E8WindowManager)->bfmeBuildAN(bfmeAptLevel00465CE0((BfmeH1065 *)this),(int)"showMessageBox",1,(int)"Delete",0,0,0,0);state=16;}
  else if(state==13) {((BfmeLevelAN *)g_rva012F19E8WindowManager)->bfmeBuildAN(bfmeAptLevel00465CE0((BfmeH1065 *)this),(int)"showMessageBox",1,(int)"ReplayVersionMismatch",0,0,0,0);state=17;}
 }
 else if(state==3) {((BfmeLevelAN *)g_rva012F19E8WindowManager)->bfmeBuildAN(bfmeAptLevel00465CE0((BfmeH1065 *)this),(int)"closeDelayed",1,(int)"OnClosed",0,0,0,0);state=5;}
 else if(state==4) {
  ((Rva0056FD90MessageCall)&Rva00522990ConfigureMessageBox)(3,
    ((Rva0056FD90Text *)TheGameText)->slot10("APT:SaveGameProgress",0),
    ((Rva0056FD90Text *)TheGameText)->slot10("APT:SavingWait",0),
    Rva0056FD90NullHolder(),Rva0056DB00FunctorHolder(bind56FD90(this)));
  state=7;
 }
 else if(state==6)rva0056D070();
 return 1;
}
