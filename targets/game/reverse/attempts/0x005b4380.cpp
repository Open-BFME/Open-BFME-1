// ?method@Rva005B4380@@QAEHPAVGameMessage@@@Z
// partial score=0.891 date=2026-09-27
// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
// stlport
#include "PreRTS.h"
#include "Common/MessageStream.h"

// RVA-derived identities, offsets and control flow read from retail.
// Start: REL32 call RVA 0x0002F978; ret4 0x005B4A70;
// jump/index tables extend through 0x005B4B45, then int3 padding.
class GameLogicPortraitShim { public: bool isInMultiplayerOrSkirmishGame(); };
class BfmeGameLogicPause { public: bool isGamePaused(); };
class Rva003BDEC0 { public: bool allowed(); };
class Rva003BCA20 { public: void go(); };
class Gen_005B4260 { public: void bfmeAddMask(int); };
class Rva006092D0State { public: void rva00609360(void*); };
class BfmeGameCW { public: void rva0060D4C0(void*); };
class BfmeLivingWorldManager { public: void rva006159c0(); };
class LivingWorldRegion;
class LivingWorldLogic { public: bool rva003C3850(LivingWorldRegion*); };
struct Rva00615D50Object;
class Glo012F706CType { public: Rva00615D50Object *lookup(const ICoord2D*,int); };
class Glo012F1028Type { public: void rva003C4740(); __forceinline void position(const ICoord2D &); };
class Rva006140C0 { public: void method(Rva00615D50Object*,int); };
class Mouse { public: void _bfme_setEngineVisibility(bool); };
void setFPMode();
class Rva005B4380Mouse { public:
 __forceinline int kind() { return *(int*)((char*)this+0x4da8); }
 virtual void slot00();
 virtual void slot01();
 virtual void slot02();
 virtual void slot03();
 virtual void slot04();
 virtual void slot05();
 virtual void slot06();
 virtual void slot07();
 virtual void slot08();
 virtual void slot09();
 virtual void slot10();
 virtual void slot11();
 virtual void slot12();
 virtual void slot13();
 virtual void cursor(int);
};
class Rva005B4380Display { public:
 virtual void slot00();
 virtual void slot01();
 virtual void slot02();
 virtual void slot03();
 virtual void slot04();
 virtual void slot05();
 virtual void slot06();
 virtual void slot07();
 virtual void slot08();
 virtual void slot09();
 virtual void slot10();
 virtual unsigned width();
 virtual unsigned height();
};
class Rva005B4380State { public:
 virtual void slot00();
 virtual void slot01();
 virtual void slot02();
 virtual void slot03();
 virtual void slot04();
 virtual void slot05();
 virtual void slot06();
 virtual void slot07();
 virtual void slot08();
 virtual void slot09();
 virtual void slot10();
 virtual void slot11();
 virtual void call30(int,int);
};

extern char *g_005B4380Logic,*g_005B4380Owner,*g_005B4380Manager,*g_005B4380Settings,*g_005B4380Gate;
extern Rva005B4380Mouse *g_005B4380Mouse;
extern Rva005B4380Display *g_005B4380Display;
extern Rva005B4380State *g_005B4380State;
template<class T> __forceinline T &field(void *p,int offset) { return *(T*)((char*)p+offset); }
__forceinline void Glo012F1028Type::position(const ICoord2D &p) {
 if(this) { field<int>(g_005B4380Owner,0x20)=p.x; field<int>(g_005B4380Owner,0x24)=p.y;field<bool>(this,0x1c)=true; }
}
class Rva005B4380 {
public:
 int method(GameMessage *msg);
 void *f00; int mask; int f08;
 ICoord2D f0c,f14,f1c,f24;
 bool f2c;
 unsigned char keys[8];
 __forceinline void remove(int bit) {
  if(mask&bit) mask-=bit;
  if(mask<0) mask=0;
  if(mask==0) f2c=false;
 }
};
int Rva005B4380::method(GameMessage *msg) {
 union { int result; ICoord2D where; } out;
 out.result=0;
 if(((GameLogicPortraitShim*)g_005B4380Logic)->isInMultiplayerOrSkirmishGame()) return 0;
 int &fp=field<int>(g_005B4380Logic,0x1a0);
 if(fp==0) setFPMode();
 ++fp;
 if(!g_005B4380State) { --field<int>(g_005B4380Logic,0x1a0); return 0; }
 int type=(int)msg->getType();
 if(!field<bool>(g_005B4380State,8)) { --field<int>(g_005B4380Logic,0x1a0); return 0; }
 if(((BfmeGameLogicPause*)g_005B4380Logic)->isGamePaused()) { --field<int>(g_005B4380Logic,0x1a0); return 0; }
 switch(type) {
 case 14:
  if(g_005B4380State && ((Rva003BDEC0*)g_005B4380Owner)->allowed() && !field<bool>(g_005B4380Manager,0x288)) {
   f0c=msg->getArgument(0)->pixel; f14=msg->getArgument(0)->pixel;
   if(field<int>(g_005B4380Mouse,0x4da8)) ((Gen_005B4260*)this)->bfmeAddMask(1);
  }
  out.result=1;break;
 case 11:
  if(g_005B4380State && field<bool>(g_005B4380State,8) && ((Rva003BDEC0*)g_005B4380Owner)->allowed() && !field<bool>(g_005B4380Manager,0x288)) {
   if(field<int>(g_005B4380State,4)==1) {g_005B4380State->call30(0,0);((BfmeLivingWorldManager*)g_005B4380Manager)->rva006159c0();}
   out.result=1;
  }
  break;
 case 10:
  if(((Rva003BDEC0*)g_005B4380Owner)->allowed() && !field<bool>(g_005B4380Manager,0x288)) {
   f1c=msg->getArgument(0)->pixel; f24=msg->getArgument(0)->pixel;
   if(field<int>(g_005B4380Mouse,0x4da8)) ((Gen_005B4260*)this)->bfmeAddMask(2);
  }
  out.result=1;break;
 case 12: remove(2); out.result=1;break;
 case 3: {
  f14=msg->getArgument(0)->pixel;
  f24=msg->getArgument(0)->pixel;
  unsigned height=g_005B4380Display->height();
  unsigned width=g_005B4380Display->width();
  if(!field<bool>(g_005B4380State,8)) { mask=0;f2c=0;break; }
  ((Glo012F1028Type*)g_005B4380Owner)->position(f14);
  if(!field<bool>(g_005B4380Settings,0x29) && field<int>(g_005B4380Mouse,0x4da8)!=0) {
   if(mask&8) {
    if(mask==8 && f14.x>=3 && f14.y>=3 && (unsigned)f14.y<height-3 && (unsigned)f14.x<width-3) { mask=0;f2c=0; }
   } else {
    if(((Rva003BDEC0*)g_005B4380Owner)->allowed() && !field<bool>(g_005B4380Manager,0x288) &&
      (f14.x<3 || f14.y<3 || (unsigned)f14.y>=height-3 || (unsigned)f14.x>=width-3))
     ((Gen_005B4260*)this)->bfmeAddMask(8);
   }
  }
  out.result=1;break;
 }
 case 16: {bool special=g_005B4380Mouse->kind()==40;remove(1);if(special) g_005B4380Mouse->cursor(40);out.result=1;break;}
 case 21: case 22: {
  unsigned char key=msg->getArgument(0)->integer;
  bool up=(~msg->getArgument(1)->integer)&1;
  if(g_005B4380Gate && field<bool>(g_005B4380Gate,0x58)) break;
  switch(key) {
  case 0xc8: keys[0]=up;break;case 0xd0: keys[1]=up;break;
  case 0xcb: keys[2]=up;break;case 0xcd: keys[3]=up;break;
  case 0x4b: keys[4]=up;break;case 0x4d: keys[5]=up;break;
  case 0x48: keys[6]=up;break;case 0x50: keys[7]=up;break;
  }
  int count=0;if(keys[0])++count;if(keys[1])++count;if(keys[2])++count;if(keys[3])++count;
  if(count) ((Gen_005B4260*)this)->bfmeAddMask(4);else remove(4);
  out.result=1;break;
 }
 case 19: out.result=1;break;
 case 23: {
  if(g_005B4380State && ((Rva003BDEC0*)g_005B4380Owner)->allowed() && !field<bool>(g_005B4380Manager,0x288)) {
   out.where=msg->getArgument(0)->pixel;
   int cursor=field<int>(g_005B4380Mouse,0x4da8);
   if(cursor==41) {field<bool>(g_005B4380State,11)=false;g_005B4380Mouse->cursor(1);g_005B4380Mouse->cursor(1);out.result=1;break;}
   if(cursor==40) {
    if(field<int>(g_005B4380State,4)==1) g_005B4380Mouse->cursor(1);
    else {((Rva006092D0State*)g_005B4380State)->rva00609360(&out.where);g_005B4380Mouse->cursor(1);((Mouse*)g_005B4380Mouse)->_bfme_setEngineVisibility(false);}
    out.result=1;break;
   }
   if(cursor) {
    if(cursor==5) {((Glo012F1028Type*)g_005B4380Owner)->rva003C4740();((BfmeGameCW*)g_005B4380Manager)->rva0060D4C0(0);g_005B4380Mouse->cursor(1);((Rva003BCA20*)g_005B4380Owner)->go();g_005B4380Mouse->cursor(1);out.result=1;break;}
    if(!field<bool>(g_005B4380Settings,0x8e) && ((LivingWorldLogic*)g_005B4380Owner)->rva003C3850(field<LivingWorldRegion*>(field<void*>(g_005B4380Owner,0x28),8))==true) {out.result=1;break;}
    Rva00615D50Object *obj=((Glo012F706CType*)g_005B4380Manager)->lookup(&out.where,2);
    if(obj) {((Rva006140C0*)g_005B4380Manager)->method(obj,2);out.result=1;break;}
    obj=((Glo012F706CType*)g_005B4380Manager)->lookup(&out.where,1);
    if(obj) {((Rva006140C0*)g_005B4380Manager)->method(obj,1);out.result=1;break;}
    ((BfmeGameCW*)g_005B4380Manager)->rva0060D4C0(0);
   }
   g_005B4380Mouse->cursor(1);
  }
  out.result=1;break;
 }
 case 27:
  if(g_005B4380State && ((Rva003BDEC0*)g_005B4380Owner)->allowed() && !field<bool>(g_005B4380Manager,0x288)) msg->getArgument(0);
  out.result=1;break;
 case 0x44f:out.result=1;break;
 }
 --field<int>(g_005B4380Logic,0x1a0);
 return out.result;
}
