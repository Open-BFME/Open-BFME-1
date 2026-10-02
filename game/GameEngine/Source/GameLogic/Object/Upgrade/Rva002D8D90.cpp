// cl: /DNDEBUG /D_STLP_USE_STATIC_LIB /Oi /D__PLACEMENT_VEC_NEW_INLINE /Iinputs/reference/shims/stringbaseascii /Igame/Libraries/Source/WWVegas/WWLib /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/ini /Iinputs/reference/shims/iniexception /Iinputs/reference/shims/ini_noinline /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
// Native BFME SubObjectsUpgrade upgrade implementation at 0x002D8D90.
// RET 0x002D91F1 followed by INT3 fixes the full 1122-byte extent.
// Identity evidence: targets/game/reverse/identity_evidence/
// 002d8d90-subobjectsupgrade-upgradeimplementation.md. The ctor installs
// UpgradeMux table VA 0x010CDEB0 at complete+0x10; slot 9 routes here.
// Entry ECX is the adjusted interface: module data at this-12, Object at
// this-8. The address-derived source view preserves this entry contract.
// BFME adds fade durations, UpgradeTexture records and house-recolor exclusion
// handling to the Zero Hour show/hide loops. Record type/12-byte layout is
// independently witnessed by native parseUpgradeTexture at 0x002D8C10.
// The texture helper at 0x008FF6A0 takes four cdecl stack arguments and
// recursively forwards all four: RenderObjClass*, two STLport strings,
// and a texture index. Its two temporary strings construct right to left.
// Native static STLport with exceptions suppressed inside its allocator
// reproduces retail allocation, memmove and outer temporary EH cleanups.
// The fade dispatcher at 0x004135C0 forwards a name, two 32-bit controls,
// and two float bit patterns through native module slots; all five slots
// are callee-popped. The address-derived helper at 0x00418200 forwards the exclusion-list
// address as one word. These local call adapters retain address identities.
#define _STLP_NO_EXCEPTIONS 1
#include <string>
#include <vector>
#include <bitset>
#include "Common/AsciiString.h"
#include "Common/BitFlags.h"
#include <vector>
class RenderObjClass;
class BfmeR1094 { public: char pad[0x8c]; BitFlags<192> flags; };
class BfmeK1094 { public: BfmeR1094 *bfmeCur1094(); };
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
 virtual void unused44(); virtual void unused45();
 virtual RenderObjClass *slot46();
};
class BfmeBBP { public: BfmeItemBP **bfmeListBP(); };

#include <string>
class S4Sink004135C0 { public: void finish(); void invoke(const AsciiString&,int,int,int,int); };
// Both signatures carry five native words, with identical thiscall callee pop.
// Cast transports float bits without numeric conversion or a second callee identity.
typedef void (S4Sink004135C0::*Rva002D8D90FadeCall)(const AsciiString&,int,int,float,float);
struct BfmeStrAE;
class BfmeOwnerAE { public: char bfmeSetAE(BfmeStrAE*,char); };
// One-word argument is &moduleData.ExcludeSubobjects, proven by FieldParse.
// The callee forwards it opaquely; no color interpretation is asserted.
class Rva00418200Owner { public: void method(unsigned); };
void Rva008FEB90(RenderObjClass*);
void Rva008FF6A0(RenderObjClass*,const _STL::string&,const _STL::string&,int);
struct Rva002D8C10Record { AsciiString first,second; int number; };
struct Rva002D8D90Data {
 char pad[0x70]; _STL::vector<AsciiString> m_showSubObjectNames; _STL::vector<AsciiString> m_hideSubObjectNames;
 _STL::vector<AsciiString> field0088; _STL::vector<Rva002D8C10Record*> textures;
 float field00a0; float field00a4; bool flag00a8; bool flag00a9;
 // FieldParse VA010CE0A8: Show70, Hide7C, Exclude88, Texture94, FadeA0, WaitA4, RecolorA8, SkipA9.
};
class Rva002D8D90Object {
public:
 virtual void s00();virtual void s01();virtual void s02();virtual void s03();virtual void s04();
 virtual void s05();virtual void s06();virtual void s07();virtual void s08();virtual void s09();
 virtual BfmeBBP *slot10();
 char pad[0x78-4]; int field78;
 char rest[0x224-0x7c]; BitFlags<192> upgrades;
};
class GameLogic;
extern GameLogic *TheGameLogic;
struct Rva002D8D90GameFrame { char pad[0x3c]; unsigned field003c; unsigned getField003C() const { return field003c; } };
class Rva002D8D90Owner {
public:
 virtual void s00();virtual void s01();virtual void s02();virtual void s03();virtual void s04();
 virtual void s05();virtual void s06();virtual void s07();virtual void s08();virtual void s09();
 virtual void masks(BitFlags<192>&,BitFlags<192>&);
 char pad4[8]; unsigned field0c; bool field10;
 void method();
};
void Rva002D8D90Owner::method()
{
 const Rva002D8D90Data *data=*(const Rva002D8D90Data**)((char*)this-12);
 BitFlags<192> activation,conflicting;
 masks(activation,conflicting);
 Rva002D8D90Object *object=*(Rva002D8D90Object**)((char*)this-8);
 if(object->upgrades.testForAny(conflicting))return;
 BfmeR1094 *player=((BfmeK1094*)object)->bfmeCur1094();
 if(player->flags.testForAny(conflicting))return;
 field10=true;
 float field00a0=0,field00a4=0;
 if(!data->flag00a9 && (object->field78 || ((Rva002D8D90GameFrame*)TheGameLogic)->getField003C()>=field0c+3)){
  if(data->field00a0!=0)field00a0=(1.0f/data->field00a0)*(1.0f/30.0f);else field00a0=0.07f;
  if(data->field00a4!=0)field00a4=(1.0f/data->field00a4)*(1.0f/30.0f);
 }
 BfmeBBP *draw=object->slot10();
 if(draw){
  bool changed=false;
  for(_STL::vector<AsciiString>::const_iterator n=data->m_hideSubObjectNames.begin();n!=data->m_hideSubObjectNames.end();++n){
   if(!((BfmeOwnerAE*)draw)->bfmeSetAE((BfmeStrAE*)&*n,0)){
    (((S4Sink004135C0*)draw)->*static_cast<Rva002D8D90FadeCall>(reinterpret_cast<Rva002D8D90FadeCall>(&S4Sink004135C0::invoke)))(*n,0,1,-field00a0,field00a4);changed=true;
   }
  }
  for(_STL::vector<AsciiString>::const_iterator n=data->m_showSubObjectNames.begin();n!=data->m_showSubObjectNames.end();++n){
   ((BfmeOwnerAE*)draw)->bfmeSetAE((BfmeStrAE*)&*n,1);
   (((S4Sink004135C0*)draw)->*static_cast<Rva002D8D90FadeCall>(reinterpret_cast<Rva002D8D90FadeCall>(&S4Sink004135C0::invoke)))(*n,1,1,field00a0,field00a4);changed=true;
  }
  const Rva002D8D90Data *textureData=*(const Rva002D8D90Data**)((char*)this-12);
  for(_STL::vector<Rva002D8C10Record*>::const_iterator t=textureData->textures.begin();t!=textureData->textures.end();++t){
   Rva002D8C10Record *record=*t;
   BfmeItemBP **items=draw->bfmeListBP();
   for(;*items;++items){
    RenderObjClass *render=(*items)->slot46();
    if(render){
     Rva008FEB90(render);
     Rva008FF6A0(render,record->first.str(),record->second.str(),record->number);
    }
   }
  }
  if(changed)((S4Sink004135C0*)draw)->finish();
  if(data->flag00a8)((Rva00418200Owner*)draw)->method((unsigned)&data->field0088);
 }
}
