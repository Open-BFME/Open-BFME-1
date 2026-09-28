// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/bfmeobjectlayout /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#include "PreRTS.h"
#include "GameLogic/Object.h"
#include "WWMath/matrix3d.h"
// The ZH GameLogic and ThingFactory headers have incompatible BFME call ABIs:
// findObjectByID takes int here (matched 0x0009A510), not ZH ObjectID;
// newObject takes BitFlags<86> plus a fourth unsigned argument (0x00138520).
// Keep these two declaration-only ABI views; Object, Weapon, Matrix3D,
// Coord3D and BitFlags come from the existing headers above.
class GameLogic { public: Object* findObjectByID(int); void destroyObject(Object*); };
class ThingFactory { public: Object* newObject(const ThingTemplate*,Team*,const BitFlags<86>&,unsigned); };
#include "GameLogic/Weapon.h"
class BfmeHostERT { public: char bfmeQueryERT(); };
extern GameLogic* TheGameLogic;
extern ThingFactory* TheThingFactory;
template<class T> __forceinline T& at(void* p,unsigned n) { return *(T*)((char*)p+n); }
class Rva002DE360Launch { public: virtual void launch(void*,void*,Object*,WeaponSlotType,int,void*,void*,Matrix3D*)=0; };
class Rva002DE360Module { public: virtual void slot0()=0;
 virtual void slot1()=0;
 virtual void slot2()=0;
 virtual void slot3()=0;
 virtual void slot4()=0;
 virtual void slot5()=0;
 virtual void slot6()=0;
 virtual void slot7()=0;
 virtual void slot8()=0;
 virtual void slot9()=0;
 virtual void slot10()=0;
 virtual void slot11()=0;
 virtual void slot12()=0;
 virtual void slot13()=0;
 virtual void slot14()=0;
 virtual void slot15()=0;
 virtual void slot16()=0;
 virtual Rva002DE360Launch* getProjectile()=0; };
class Rva002DE360Host { public: virtual void slot0()=0;
 virtual void slot1()=0;
 virtual void slot2()=0;
 virtual void slot3()=0;
 virtual void slot4()=0;
 virtual void slot5()=0;
 virtual void slot6()=0;
 virtual void slot7()=0;
 virtual void slot8()=0;
 virtual void slot9()=0;
 virtual void slot10()=0;
 virtual void slot11()=0;
 virtual void slot12()=0;
 virtual void slot13()=0;
 virtual void slot14()=0;
 virtual void slot15()=0;
 virtual void slot16()=0;
 virtual void slot17()=0;
 virtual void slot18()=0;
 virtual void slot19()=0;
 virtual void slot20()=0;
 virtual void slot21()=0;
 virtual void slot22()=0;
 virtual void slot23()=0;
 virtual void slot24()=0;
 virtual void slot25()=0;
 virtual void slot26()=0;
 virtual void slot27()=0;
 virtual void slot28()=0;
 virtual void slot29()=0;
 virtual void slot30()=0;
 virtual void slot31()=0;
 virtual void slot32()=0;
 virtual void slot33()=0;
 virtual void slot34()=0;
 virtual void slot35()=0;
 virtual void slot36()=0;
 virtual void slot37()=0;
 virtual void slot38()=0;
 virtual void slot39()=0;
 virtual void slot40()=0;
 virtual void slot41()=0;
 virtual void slot42()=0;
 virtual void slot43()=0;
 virtual void slot44()=0;
 virtual void slot45()=0;
 virtual void slot46()=0;
 virtual void slot47()=0;
 virtual void slot48()=0;
 virtual void slot49()=0;
 virtual void slot50()=0;
 virtual void slot51()=0;
 virtual void slot52()=0;
 virtual void slot53()=0;
 virtual void slot54()=0;
 virtual void slot55()=0;
 virtual void slot56()=0;
 virtual void slot57()=0;
 virtual void slot58()=0;
 virtual void slot59()=0;
 virtual void slot60()=0;
 virtual void slot61()=0;
 virtual void slot62()=0;
 virtual void slot63()=0;
 virtual void slot64()=0;
 virtual void slot65()=0;
 virtual void slot66()=0;
 virtual void slot67()=0;
 virtual void slot68()=0;
 virtual void slot69()=0;
 virtual void slot70()=0;
 virtual void slot71()=0;
 virtual void slot72()=0;
 virtual void slot73()=0;
 virtual Object* create(BfmeHostERT*)=0; };
// Identity: WeaponNuggetParse.cpp's ProjectileNugget parser constructs
// Made001E5E30 at 0x002DE700, installing vtable 0x010CF104. Its slots 5/6
// route through 0x00046D67/0x000178C8 to the two bodies below. Keep the
// established owner name and address-derived methods until method names
// are independently recovered. Boundaries: 371B each, both end in ret 8.
// The +0x1FC host callback uses slot +0x128 with one stack argument;
// the behavior interface at module+0x0C uses slot +0x44 then slot zero.
class Made001E5E30 { public: void rva002DE360(void*,void*); void rva002DE530(void*,void*); char m_pad[0x58]; void* m_58; ThingTemplate* m_5c; };
void Made001E5E30::rva002DE360(void* weapon,void* target) {
 Object* source=TheGameLogic->findObjectByID(at<int>(weapon,8));
 if(!source) return;
 Matrix3D transform;
 Coord3D pos;
 void* owner=at<void*>(weapon,4);
 Matrix3D* transformPtr=&transform;
 Object* projectile;
 if(at<BfmeHostERT>(owner,0x4e8).bfmeQueryERT() && at<void*>(source,0x1fc)) {
  Weapon::calcProjectileLaunchPosition(source,at<WeaponSlotType>(weapon,12),at<int>(weapon,0x38),transform,pos);
  Rva002DE360Host* host=at<Rva002DE360Host*>(source,0x1fc);
  void* owner2=at<void*>(weapon,4);
  projectile=host->create(&at<BfmeHostERT>(owner2,0x4e8));
 } else if(at<char>(at<void*>(weapon,4),0x4ec)) {
  Weapon::calcProjectileLaunchPosition(source,at<WeaponSlotType>(weapon,12),at<int>(weapon,0x38),transform,pos);
  projectile=source;
 } else {
  if(!m_5c) return;
  transformPtr=0;
  BitFlags<86> status;
  Team* team=at<Team*>(source->getControllingPlayer(),0x230);
  projectile=TheThingFactory->newObject(m_5c,team,status,0);
 }
 void** modules=at<void**>(projectile,0x1f0);
 for(;*modules;++modules) {
  Rva002DE360Module* module=(Rva002DE360Module*)((char*)*modules+12);
  Rva002DE360Launch* interface=module->getProjectile();
  if(interface) {
   projectile->setProducer(source);
   interface->launch(target,0,source,at<WeaponSlotType>(weapon,12),at<int>(weapon,0x38),weapon,m_58,transformPtr);
   return;
  }
 }
 TheGameLogic->destroyObject(projectile);
}


void Made001E5E30::rva002DE530(void* weapon,void* target) {
 Object* source=TheGameLogic->findObjectByID(at<int>(weapon,8));
 if(!source) return;
 Matrix3D transform;
 Coord3D pos;
 void* owner=at<void*>(weapon,4);
 Matrix3D* transformPtr=&transform;
 Object* projectile;
 if(at<BfmeHostERT>(owner,0x4e8).bfmeQueryERT() && at<void*>(source,0x1fc)) {
  Weapon::calcProjectileLaunchPosition(source,at<WeaponSlotType>(weapon,12),at<int>(weapon,0x38),transform,pos);
  Rva002DE360Host* host=at<Rva002DE360Host*>(source,0x1fc);
  void* owner2=at<void*>(weapon,4);
  projectile=host->create(&at<BfmeHostERT>(owner2,0x4e8));
 } else if(at<char>(at<void*>(weapon,4),0x4ec)) {
  Weapon::calcProjectileLaunchPosition(source,at<WeaponSlotType>(weapon,12),at<int>(weapon,0x38),transform,pos);
  projectile=source;
 } else {
  if(!m_5c) return;
  transformPtr=0;
  BitFlags<86> status;
  Team* team=at<Team*>(source->getControllingPlayer(),0x230);
  projectile=TheThingFactory->newObject(m_5c,team,status,0);
 }
 void** modules=at<void**>(projectile,0x1f0);
 for(;*modules;++modules) {
  Rva002DE360Module* module=(Rva002DE360Module*)((char*)*modules+12);
  Rva002DE360Launch* interface=module->getProjectile();
  if(interface) {
   projectile->setProducer(source);
   interface->launch(0,target,source,at<WeaponSlotType>(weapon,12),at<int>(weapon,0x38),weapon,m_58,transformPtr);
   return;
  }
 }
 TheGameLogic->destroyObject(projectile);
}

