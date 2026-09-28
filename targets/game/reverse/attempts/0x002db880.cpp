// ?apply@BfmeOwnerXJApplyCall@@QAE_NPAXPAVBfmeThingXJ@@PAVDamageInfo@@@Z
// partial score=0.9709 date=2026-09-28
// cl: /O2 /Ob2 /DNDEBUG /DWIN32 /MD /EHs-c- /Igame/GameEngine/Source/GameLogic/Object /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include
// stlport
#include "Lib/BaseType.h"
#include <list>
#include <vector>
#include <algorithm>
#undef min
#include <math.h>
#pragma intrinsic(sqrt)
class Player;
#define OBJECT_TU_MEMBERS Player* getControllingPlayer() const; bool getAttributeModifierBonus(int,float*) const; bool getAttributeModifierMultiplier(int,float*) const;
#include "object.h"
class GameLogic { public: Object* findObjectByID(int); };
extern GameLogic* TheGameLogic;
class BfmeThingXJ;
class DamageInfo;
class BfmeRvaA760Object;
class BfmeRvaA760ProbeInterface { public: bool accepts(BfmeRvaA760Object*,int); };
struct Rva002DB880Scale { BfmeRvaA760ProbeInterface filter; float factor; };
class Rva002DB880Contain { public:
 virtual void slot0()=0;
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
 virtual const _STL::list<Object*>* members()=0;
};
template<class T> __forceinline T& at(void* p,unsigned n) { return *(T*)((char*)p+n); }
class BfmeOwnerXJApplyCall { public:
 bool apply(void*,BfmeThingXJ*,DamageInfo*);
 char m_pad[0x58]; float m_58; char m_5c[12]; bool m_68; char m_69[3]; unsigned m_6c; int m_70,m_74,m_78;
 _STL::vector<Rva002DB880Scale> m_7c; float m_88;
};
bool BfmeOwnerXJApplyCall::apply(void* weapon,BfmeThingXJ* thing,DamageInfo* damage) {
 Object* source=TheGameLogic->findObjectByID(at<int>(weapon,8));
 float multiplier;
 if(!source) return false;
 at<float>(damage,0x1c)=m_58;
 if(at<char>(at<void*>(weapon,4),0x508) && source->m_contain) {
  unsigned count=((Rva002DB880Contain*)source->m_contain)->members()->size();
  int maximum=at<unsigned char>(at<void*>(weapon,4),0x509);
  if(maximum>0) { float ratio=(float)count/maximum; const float& capped=_STL::min(ratio,1.0f); at<float>(damage,0x1c)*=capped; }
 }
 int count=m_7c.size();
 for(int i=0;i<count;++i) {
  if(m_7c[i].filter.accepts((BfmeRvaA760Object*)thing,(int)source->getControllingPlayer())) {
   at<float>(damage,0x1c)*=m_7c[i].factor; break;
  }
 }
 float bonus=0.0f;
 if(m_68 && at<float>(damage,0x1c)!=0.0f && source->getAttributeModifierBonus(2,&bonus))
  at<float>(damage,0x1c)+=bonus;
 {
  multiplier=1.0f;
  if(m_70==15) { if(source->getAttributeModifierMultiplier(10,&multiplier)) at<float>(damage,0x1c)*=multiplier; } else { if(source->getAttributeModifierMultiplier(3,&multiplier)) at<float>(damage,0x1c)*=multiplier; }
 }
 float delay=(float)m_6c;
 if(m_88>0.0f && thing) {
  Object* target=(Object*)thing;
  Coord3D v; v.set((const Coord3D*)target->m_cachedPos); v.sub((const Coord3D*)source->m_cachedPos);
  delay+=v.length()/m_88;
 }
 at<int>(damage,0x10)=m_70;
 at<int>(damage,0x14)=m_78;
 at<float>(damage,0x24)=delay;
 at<int>(damage,0x18)=m_74;
 at<int>(damage,8)=at<int>(weapon,8);
 at<unsigned short>(damage,12)=(unsigned short)(1<<at<int>(source->getControllingPlayer(),0x24));
 at<int>(damage,0x28)=at<int>(at<void*>(weapon,4),0x10);
 at<char>(damage,0x21)=at<char>(at<void*>(weapon,4),0x535);
 return true;
}
