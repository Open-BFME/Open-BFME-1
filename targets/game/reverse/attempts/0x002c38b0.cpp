// ?method@Rva002C38B0@@QAEX_N@Z
// partial score=0.3495 date=2026-10-03
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /O2 /Ob2 /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath /Igame/GameEngine/Source /Iinputs/reference/shims/stlp_nodealloc /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include
// stlport
#define _STLP_NO_EXCEPTIONS 1
#define DEBUG_ASSERTCRASH(c,m) ((void)0)
#define DEBUG_CRASH(m) ((void)0)
#define __PLACEMENT_VEC_NEW_INLINE
#include "vector3.h"
#include "Lib/BaseType.h"
#include "Common/BitFlags.h"
typedef BitFlags<320> ModelConditionFlags;
#define BFME_HAVE_COORD3D
#define BFME_HAVE_MODELCONDITIONFLAGS
#include "GameLogic/Object/object.h"
class GameLogic;class TerrainLogic;
extern GameLogic *TheGameLogic;extern TerrainLogic *TheTerrainLogic;
extern void j_0002191d();extern void j_0001f253();extern void j_00015ae6();extern void j_00034e91();extern void j_00001bae();extern void j_0000314d();extern void j_0000795a();
extern char Rva00EF02D4[],Rva00EF02DC[];
class Rva002C38B0Calls {};
#define M(tag,ret,args) typedef ret(Rva002C38B0Calls::*M##tag)args; __forceinline M##tag m##tag(){union{void(*raw)();M##tag member;}p;p.raw=j_##tag;return p.member;}
M(0002191d,void,())
M(0001f253,Object*,(int))
M(00015ae6,bool,(Object*,Coord3D*,const Coord3D*,bool))
M(00034e91,bool,(Coord3D*,const Coord3D*,const char*,int,int,bool))
M(0000314d,void,(const Coord3D*))
M(0000795a,void,(void*,void*,void*,void*))
#define CALL(p,tag) (((Rva002C38B0Calls*)(p))->*m##tag())
class Rva002C38B0Terrain { public:virtual void s0()=0;virtual void s4()=0;virtual void s8()=0;virtual void sc()=0;virtual void s10()=0;virtual void s14()=0;virtual float s18(float,float,void*)=0;};
class Rva002C38B0 {public:
 char f00[0x1c];void *f1c;char f20[8];Coord3D f28;
 void method(bool force);
};
void Rva002C38B0::method(bool force)
{
 Object *object=*(Object**)((char*)f1c+0x10);
 AIUpdateInterface *ai=object->m_ai;
 if(object->m_modelConditionFlags.test(145)) {object->m_modelConditionFlags.set(145,0);CALL(object,0002191d)();}
 if(!ai) return;
 Object *target=CALL(TheGameLogic,0001f253)(*(int*)((char*)ai+0x3f8));
 if(!target) return;
 Coord3D delta,contact;
 const Coord3D *pos=&object->m_cachedPos;
 if(!CALL(ai,00015ae6)(target,&contact,pos,false)) {
  CALL(target,00034e91)(&contact,pos,0,1,((int(*)(int,int,char*,int))j_00001bae)(0,12345678,"F:\\bfme\\Code\\gameengine\\Source\\GameLogic\\Object\\Update\\AIUpdate\\GiantBirdAIUpdate.cpp",623),false);
 }
 delta=contact;delta.sub(&f28);
 float goalDistance=delta.length();
 delta=contact;delta.sub(pos);
 float distance=delta.length();
 if(distance<*(float*)((char*)ai+0x470)*4.0f && !object->m_modelConditionFlags.test(145)) {
  object->m_modelConditionFlags.set(145);CALL(object,0002191d)();
 }
 if(goalDistance>10.0f || force) {
  float threshold=*(float*)((char*)ai+0x470)*8.0f;
  if(distance<threshold || goalDistance>threshold || force) {
   f28=contact;
   if(!*(int*)((char*)ai+0x494)) {
    void *data=*(void**)((char*)ai+0x1cc);
    if(data) {
     f28.z=((Rva002C38B0Terrain*)TheTerrainLogic)->s18(f28.x,f28.y,0)+*(float*)((char*)data+0x44);
     CALL(f1c,0000314d)(&f28);
    }
   }
   if(!((*(unsigned*)((char*)ai+0x3f0)>>2)&1) && !((*(unsigned*)((char*)ai+0x3f0)>>3)&1)) {
    CALL(ai,0000795a)(&f28,Rva00EF02D4,0,0);return;
   }
   CALL(ai,0000795a)(&f28,Rva00EF02DC,0,0);
  }
 }
}
