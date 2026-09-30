// cl: /DNDEBUG /DWIN32 /MD /EHs-c- /O2 /Ob1 /Iinputs/reference/shims/sweep /Iinputs/reference/shims/locomotor /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
// Retail 0x00416660, 356B. Flags at +11C/+120 drive TintEnvelope state.
// Global color +2C, durations +38/+3C, scale +48 and mode +A8 are retail witnesses.
#define Matrix4x4 Matrix4
#define __PLACEMENT_VEC_NEW_INLINE
#include "PreRTS.h"
#include "GameClient/Drawable.h"
#include "../Common/Rva00412140Ctor.cpp"
struct Rva00416660EnvelopeView { char head[0x38]; unsigned char mode; };
struct Rva00416660Global { char head[0x2C]; RGBColor color; int first,second; char pad40[8]; float scale; char pad4C[0xA8-0x4C]; int mode; };
class BfmeGlobCC0;
extern BfmeGlobCC0 *g_bfmeGlobCC0;
class Rva00416660Owner { public: void update(); char head[0x8C]; Rva00412140 *envelope; char pad90[0x11C-0x90]; unsigned current,previous; };
void Rva00416660Owner::update() {
 if(previous!=current) {
  if(!envelope) envelope=new Rva00412140;
  Rva00416660Global *global=reinterpret_cast<Rva00416660Global *>(g_bfmeGlobCC0);
  bool scaled=global->mode==3 || global->mode==4;
  if(current&4) {
   int first=global->first;
   int second=global->second;
   RGBColor color=global->color;
   if(scaled) { const double scale=global->scale; first=(int)((double)first*scale); second=(int)((double)second*scale); }
   reinterpret_cast<TintEnvelope *>(envelope)->play(&color,first,second,-2);
  } else if(current&8) reinterpret_cast<Rva00416660EnvelopeView *>(envelope)->mode=2;
  else if(current&1) reinterpret_cast<Rva00416660EnvelopeView *>(envelope)->mode=2;
  else if(current&2) {
   int second;
   int first;
   first=global->first;
   second=global->second;
   RGBColor color=global->color;
   if(scaled) { const double scale=global->scale; first=(int)((double)first*scale); second=(int)((double)second*scale); }
   reinterpret_cast<TintEnvelope *>(envelope)->play(&color,first,second,-2);
  }
 }
 previous=current;
}