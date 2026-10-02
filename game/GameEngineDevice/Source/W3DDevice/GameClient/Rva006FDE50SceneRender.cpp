// RVA 0x006FDE50: conditional scene rendering and camera interpolation.
// Owner identity unproved. Camera +0x70 and scene +0x74 agree with 0x00700030.
// All float globals retain their retail VA; +0xDB6 has no GlobalData name witness.
// 0x00035D69 routes to 0x006FCBD0. Retail supplies this in ECX and two stack args;
// the target ignores ECX and ends in ret 8. Preserve the observed caller ABI.
// cl: /DNDEBUG /MD /EHsc /O2 /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWDebug /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Include
#include "camera.h"
#include "scene.h"
#include "ww3d.h"
// BFME has one more Clear argument than the shared ZH header.
class DX8Wrapper { public: static void Clear(bool,bool,bool,const Vector3&,float,float,unsigned); };
class GlobalData; class GameLogic;
// The global at 0x012F706C is EA's `LivingWorldManager *TheLivingWorldManager`
// (data_rows.csv row ?TheLivingWorldManager@@3PAVLivingWorldManager@@A), defined
// once in LivingWorldManager.cpp; here it is only tested and passed on.
class LivingWorldManager;
extern LivingWorldManager *TheLivingWorldManager;
extern GlobalData* TheWritableGlobalData;
// The retail global at 0x012F0898 is EA's `GameLogic *TheGameLogic`, defined
// once in game/GameEngine/Source/GameLogic/System/GameLogic.cpp.
extern GameLogic* TheGameLogic;

extern unsigned char g_006fc8d0;
extern float g_Va012F8268[2],g_Va012F825C[2],g_Va012F8270,g_Va012F8264,g_Va012BAC4C,g_Va012F8274;
extern void j_00022c96(); extern void j_0000aadd(); extern void j_00014380();
float Rva00063E70Bezier(float,float,float,float); extern void j_00035d69(); extern void j_000460a1();
static bool paused(void* self) {
 struct Thunk { bool call(); }; typedef bool (Thunk::*F)();
 union { void (*raw)(); F member; } f; f.raw=j_00022c96;
 return (reinterpret_cast<Thunk*>(self)->*f.member)();
}
static void disable(void* self) {
 struct Thunk { void call(); }; typedef void (Thunk::*F)();
 union { void (*raw)(); F member; } f; f.raw=j_0000aadd;
 (reinterpret_cast<Thunk*>(self)->*f.member)();
}
static void enable(void* self) {
 struct Thunk { void call(); }; typedef void (Thunk::*F)();
 union { void (*raw)(); F member; } f; f.raw=j_00014380;
 (reinterpret_cast<Thunk*>(self)->*f.member)();
}
static void projection(void* self) {
 struct Thunk { void call(); }; typedef void (Thunk::*F)();
 union { void (*raw)(); F member; } f; f.raw=j_000460a1;
 (reinterpret_cast<Thunk*>(self)->*f.member)();
}
class Rva006FDE50SceneRender {
public:
 void render();
 char pad000[8]; bool field08; char pad009[0x67];
 CameraClass* camera70; SceneClass* scene74;
 char pad078[0x10]; float field88,field8c; Vector3 field90;
 char pad09c[0x48]; float fielde4,fielde8,fieldec;
 char pad0f0[0x4c]; void* object13c; void* object140; float field144;
};
void Rva006FDE50SceneRender::render() {
 struct ClampThunk { void call(void*,float); }; typedef void (ClampThunk::*ClampFunction)(void*,float);
 union { void (*raw)(); ClampFunction member; } clampFunction; clampFunction.raw=j_00035d69;

 if(scene74 && camera70 && field08) {
  g_006fc8d0=1;
  DX8Wrapper::Clear(true,true,true,Vector3(0,0,0),0.0f,1.0f,0);
  int index=0;
  if(TheWritableGlobalData && *(bool*)((char*)TheWritableGlobalData+0xdb6)) index=1;
  float a=g_Va012F8268[index];
  fieldec=(g_Va012F8270-a)*field144+a;
  float b=g_Va012F825C[index];
  field88=(g_Va012F8264-b)*field144+b;
  if(!paused(TheGameLogic)) fielde4+=fielde8;
  if(fielde4>g_Va012BAC4C && fielde8!=0.0f) {
   fielde4=g_Va012BAC4C; fielde8=0;
   if(TheLivingWorldManager) disable(TheLivingWorldManager);
  }
  if(fielde4<g_Va012F8274 && fielde8!=0.0f) {
   if(TheLivingWorldManager) enable(TheLivingWorldManager);
   fielde4=g_Va012F8274; fielde8=0;
  }
  if(object13c) {
   if(fielde8>0) {
    float t=Rva00063E70Bezier(0,0,1,fielde4);
    (reinterpret_cast<ClampThunk*>(this)->*clampFunction.member)(object13c,Rva00063E70Bezier(1,3,0,t));
   } else (reinterpret_cast<ClampThunk*>(this)->*clampFunction.member)(object13c,1.0f-fielde4);
  }
  if(object140) {float t=fielde4-0.5f;(reinterpret_cast<ClampThunk*>(this)->*clampFunction.member)(object140,t+t);}
  scene74->Set_Ambient_Light(field90);
  projection(this);
  WW3D::Render(scene74,camera70,false,false,Vector3(0,0,0));
 }
}
