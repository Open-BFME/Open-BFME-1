// cl: /DNDEBUG /D__PLACEMENT_VEC_NEW_INLINE /Iinputs/reference/shims/stringbaseascii /Igame/Libraries/Source/WWVegas/WWLib /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/ini /Iinputs/reference/shims/iniexception /Iinputs/reference/shims/ini_noinline /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
// Retail 0x002D5980 has a complete 685-byte extent: RET at 0x002D5C2C,
// then INT3 padding. GeometryUpgrade ctor 0x002D5790 installs vtable
// 0x010CCC48 at complete+0x10; slot 9 routes through ILT 0x0002A784 here.
// The entry receives that adjusted UpgradeMux interface: module data at
// this-0x0C and Object at this-8. Keep the source owner address-derived until
// the inherited C++ override/adjustment identity has independent review.
// ModuleData field parser fixes ShowGeometry/+70, HideGeometry/+7C,
// WallBoundsMesh/+88 and RampMesh1/2 at +8C/+90. Matched module-data ctor
// and dtor corroborate two 12-byte vectors and three 4-byte AsciiStrings.
// Geometry storage is Object+0xAC: 36-byte entries, range at +0x2C/+0x30;
// entry name/+1C and flag/+20 are witnessed by the two called helpers.
// Drawable dispatch reads Object virtual slot 10 and then the list getter
// at 0x00411580. Wall helper 0x002B26C0 is independently __thiscall void().
// Caller source sequences the player getter before taking the mask address;
// combining those expressions changes VC7.1's push/load schedule.
#include "Common/AsciiString.h"
#include "Common/BitFlags.h"
#include <vector>
class Rva002D5980Owner;
class Rva002D9F30Owner { public: void setCondition(); };
class BfmeR1094 { public: char pad[0x8c]; BitFlags<192> flags; };
class BfmeK1094 { public: BfmeR1094 *bfmeCur1094(); };
class BfmeHostCL { public: void bfmeResetCL(char); };
class BfmeItemBP {
public:
 virtual void unused00(); virtual void unused01(); virtual void unused02(); virtual void unused03();
 virtual void unused04(); virtual void unused05(); virtual void unused06(); virtual void unused07();
 virtual void unused08(); virtual void unused09(); virtual void unused10(); virtual void unused11();
 virtual void unused12(); virtual void unused13(); virtual void unused14(); virtual void unused15();
 virtual void unused16(); virtual void unused17(); virtual void unused18(); virtual void unused19();
 virtual void unused20(); virtual void unused21(); virtual void unused22(); virtual void unused23();
 virtual void unused24(); virtual void unused25(); virtual void unused26(); virtual void unused27();
 virtual void unused28(); virtual void unused29(); virtual void unused30(); virtual void unused31();
 virtual void unused32(); virtual void unused33(); virtual void unused34(); virtual void unused35();
 virtual void unused36(); virtual void unused37(); virtual void unused38(); virtual void unused39();
 virtual void unused40(); virtual void unused41(); virtual void unused42(); virtual void unused43();
 virtual void unused44(); virtual void unused45(); virtual void unused46(); virtual void unused47();
 virtual void slot48(const char*); virtual void slot49(const char*,bool);
};
class BfmeBBP { public: BfmeItemBP **bfmeListBP(); };
struct BfmeShapeE15 { char pad[0x1c]; AsciiString name; bool flag; char align[3]; };
class BfmeObjE15 { public: BfmeShapeE15 *bfmeAtE15(int); };
class BfmeStrF9;
class BfmeObjF9 { public: void setFlag(const BfmeStrF9&,char); };
class Module;
class Object;
Module *rva002B21E0FindWallUpgradeUpdate(const Object *);
class Rva002B26C0Owner { public: void method(); };
struct Rva002D5980Data {
 char pad[0x70]; _STL::vector<AsciiString> show; _STL::vector<AsciiString> hide;
 AsciiString wall; AsciiString ramp1; AsciiString ramp2;
};
struct Rva002D5980Geometry { char pad[0x2c]; BfmeShapeE15 *start; BfmeShapeE15 *finish; };
class Rva002D5980Object {
public:
 virtual void u00(); virtual void u01(); virtual void u02(); virtual void u03(); virtual void u04();
 virtual void u05(); virtual void u06(); virtual void u07(); virtual void u08(); virtual void u09();
 virtual BfmeBBP *slot10();
 char pad[0xac-4]; Rva002D5980Geometry geometry;
 char rest[0x224-0xac-sizeof(Rva002D5980Geometry)]; BitFlags<192> upgrades;
};
class Rva002D5980Owner {
public:
 virtual void unused00();virtual void unused01();virtual void unused02();virtual void unused03();virtual void unused04();
 virtual void unused05();virtual void unused06();virtual void unused07();virtual void unused08();virtual void unused09();
 virtual void flags(BitFlags<192>&,BitFlags<192>&);
 void method();
};
void Rva002D5980Owner::method()
{
 BitFlags<192> activation;
 BitFlags<192> conflicting;
 Rva002D5980Owner *self=this;
 flags(activation,conflicting);
 Rva002D5980Object *object=*(Rva002D5980Object**)((char*)this-8);
 if(object->upgrades.testForAny(conflicting)) return;
 BfmeR1094 *player=((BfmeK1094*)object)->bfmeCur1094();
 if(player->flags.testForAny(conflicting)) return;
 ((Rva002D9F30Owner*)((char*)this-16))->setCondition();
 const Rva002D5980Data *data=*(Rva002D5980Data**)((char*)this-12);
 bool wall=data->wall.getLength()>0;
 bool ramp1=data->ramp1.getLength()>0;
 bool ramp2=data->ramp2.getLength()>0;
 if(wall||ramp1||ramp2){
  const char *wallName=wall?data->wall.str():0;
  const char *ramp1Name=ramp1?data->ramp1.str():0;
  const char *ramp2Name=ramp2?data->ramp2.str():0;
  BfmeBBP *drawOwner=object->slot10();
  BfmeItemBP **draw=drawOwner->bfmeListBP();
  for(;*draw;++draw){
   if(wallName)(*draw)->slot48(wallName);
   if(ramp1Name)(*draw)->slot49(ramp1Name,false);
   if(ramp2Name)(*draw)->slot49(ramp2Name,true);
  }
 }
 if(wall||ramp1||ramp2||data->hide.size()>0||data->show.size()>0){
  Rva002D5980Geometry *geometry=&object->geometry;
  int count=geometry->finish-geometry->start;
  for(int i=0;i<count;++i){
   BfmeShapeE15 *shape=((BfmeObjE15*)geometry)->bfmeAtE15(i);
   if(shape->flag)((AsciiString*)((char*)self+12))->set(shape->name);
  }
  for(_STL::vector<AsciiString>::const_iterator hide=data->hide.begin();hide!=data->hide.end();++hide)
   ((BfmeObjF9*)geometry)->setFlag(*(const BfmeStrF9*)&*hide,0);
  for(_STL::vector<AsciiString>::const_iterator show=data->show.begin();show!=data->show.end();++show)
   ((BfmeObjF9*)geometry)->setFlag(*(const BfmeStrF9*)&*show,1);
  ((BfmeHostCL*)object)->bfmeResetCL(1);
  Module *wallUpdate=rva002B21E0FindWallUpgradeUpdate((const Object*)object);
  if(wallUpdate)((Rva002B26C0Owner*)wallUpdate)->method();
 }
}
