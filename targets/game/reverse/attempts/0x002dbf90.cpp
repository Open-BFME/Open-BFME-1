// ?bfmeDoneXJ@BfmeOwnerXJ@@UAEXPAXPAUBfmeSubXJ@@@Z
// partial score=0.9643268 date=2026-09-28
// cl: /DNDEBUG /DWIN32 /MD /EHsc /Iinputs/reference/shims/bfmeobjectlayout /Iinputs/reference/shims/sweep /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
#define _STLP_NO_EXCEPTIONS 1
#define _STLP_USE_STATIC_LIB 1
#define BFME_STLP_NODE_ALLOC 1
#define __PLACEMENT_VEC_NEW_INLINE
#include <vector>
#define cosf header_inline_cosf
#include "PreRTS.h"
#include "GameLogic/Object.h"
#include "Common/ThingTemplate.h"
#include "WWMath/vector3.h"
#include <math.h>
#pragma intrinsic(sqrt)
#undef cosf
extern "C" float __cdecl cosf(float);

class GameLogic {public: Object* findObjectByID(int);};
extern GameLogic* TheGameLogic;
class GlobalData;
extern GlobalData* TheWritableGlobalData;
class PartitionManager;
extern PartitionManager* ThePartitionManager;
struct BfmeIterEntry { Object* m_obj; void* m_extra; };
struct BfmeObjectIterator { std::vector<BfmeIterEntry> m_entries; BfmeIterEntry* m_cur; int m_refCount; };
struct BfmeWideResult {
 BfmeObjectIterator* m_value;
 BfmeWideResult(); BfmeWideResult(const BfmeWideResult&);
 __forceinline ~BfmeWideResult() { if(--m_value->m_refCount==0) delete m_value; }
 Object* next() { if(m_value->m_cur==m_value->m_entries.end()) return 0; return (m_value->m_cur++)->m_obj; }
};
class BfmeWideForwardA {public: BfmeWideResult bfmeForwardWideA(int,int,int,int);};
class BfmeThingXJ;
struct BfmeSubXJ;
class BfmeOwnerXJ {public:
 virtual void bfmeV0XJ();
 virtual bool bfmeTestXJ(void*,BfmeThingXJ*);
 virtual void bfmeV2XJ(); virtual void bfmeV3XJ(); virtual void bfmeV4XJ(); virtual void bfmeV5XJ();
 virtual void bfmeDoneXJ(void*,BfmeSubXJ*);
 unsigned char bfmeApplyXJ(void*,BfmeThingXJ*);
 unsigned char m_bfmeHeadXJ[0x58];
 float m_bfmeValueXJ;
 float m_60,m_64;
};
template<class T> __forceinline T& at(void* p,unsigned n) {return *(T*)((char*)p+n);}
void BfmeOwnerXJ::bfmeDoneXJ(void* weapon,BfmeSubXJ* sub) {
 float radius=m_bfmeValueXJ;
 if(radius<1.0f) radius=1.0f;
 int id=at<int>(weapon,8); Object* source=TheGameLogic->findObjectByID(id);
 int mode=3;
 if(radius>=10.0f) {
  const ThingTemplate* t=at<ThingTemplate*>(source,4);
  if(t) t=(const ThingTemplate*)t->getFinalOverride();
  if(!(at<unsigned>((void*)t,0xdc)&0x200) || !source->isKindOf((KindOfType)0x15) || !at<void*>(source,0x1fc)) mode=4;
 }
 const Vector3* center=(const Vector3*)sub;
 BfmeWideResult result=((BfmeWideForwardA*)ThePartitionManager)->bfmeForwardWideA((int)center,*(int*)&radius,mode,0);
 Object* target;
 while((target=result.next())!=0) {
  if(!bfmeTestXJ(weapon,(BfmeThingXJ*)target)) continue;
  if(m_60<3.1415927f) {
   Coord3D delta; delta.set(target->getPosition());
   delta.sub((const Coord3D*)center);
   Coord3D initial; initial.set((const Coord3D*)center);
   initial.sub(source->getPosition());
   Vector3 direction(initial.x,initial.y,initial.z);
   if(initial.length()==0.0f) direction=Vector3(at<float>(source,8),at<float>(source,0x18),at<float>(source,0x28));
   Vector3 normalized(delta.x,delta.y,delta.z);
   direction.Normalize();
   normalized.Normalize();
   if(Vector3::Dot_Product(direction,normalized)<cosf(m_60)) continue;
  }
  if(*(int*)&m_64!=int(0xbf800000)) { float sourceZ=at<float>(source,0x40); if(at<float>(target,0x40)-sourceZ>m_64) continue; }
  {
   if(bfmeApplyXJ(weapon,(BfmeThingXJ*)target)) { if(radius<=at<float>(TheWritableGlobalData,0xbdc)) break; }
  }
 }
}
