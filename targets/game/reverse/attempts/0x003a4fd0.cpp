// ?update@Rva003A4FD0State@@QAEXPAX@Z
// partial score=0.8818 date=2026-09-30
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath
#include "ascii_string.h"
#include "coord3d.h"
class LivingWorldRegion;
class LivingWorldRegionManager {public:
 LivingWorldRegion *rva003C8160(Coord3DBase*);
 bool rva003CAE00(LivingWorldRegion*);
 void rva003C9CB0(void*,void*,void*,void*);
};
#pragma comment(linker,"/alternatename:?rva003CAE00@LivingWorldRegionManager@@QAE_NPAVLivingWorldRegion@@@Z=?j_00003611@@YAXXZ")
#pragma comment(linker,"/alternatename:?rva003C8160@LivingWorldRegionManager@@QAEPAVLivingWorldRegion@@PAUCoord3DBase@@@Z=?j_00046150@@YAXXZ")
class Glo012F1028Type {public: void rva003BE020(LivingWorldRegion*);char pad[0x28];LivingWorldRegionManager *manager;};
extern Glo012F1028Type *Glo012F1028;
class BfmeHostCB {public:char bfmePopCB();};
class Rva003A4FD0State {public:
 void update(void*);AsciiString stringAt003A4390();char pad[12];float x;volatile float y;char gap[8];unsigned char byte1C,byte1D,byte1E;
};
void Rva003A4FD0State::update(void* arg){
 if(((BfmeHostCB*)this)->bfmePopCB())return;
 if(byte1D && byte1E){
  LivingWorldRegionManager *manager=Glo012F1028->manager;
  Coord3DBase point;
  point.y=y;point.x=x;point.z=0;
  LivingWorldRegion *region=manager->rva003C8160(&point);
  if(region && manager->rva003CAE00(region)){
   AsciiString name=stringAt003A4390();
   manager->rva003C9CB0((char*)region+4,&name,0,arg);
   Glo012F1028->rva003BE020(region);
  }
 }
 byte1C=0;
}
