// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WW3D2
// Retail 0x005F8010, 976 bytes (RET12 at +0x3AE, then alignment and the
// seven-entry shader switch table). FXParticleSystem streak draw pass: culls
// the system's particles into the four shared point buffers (at most 512),
// then feeds the streak line g_rva005F7FA0Resource (texture, shader by type,
// points), clears the first colour and renders it. Zero Hour's
// W3DParticleSystemManager::doParticles streak branch and Open-BFME-2's
// StreakDrawModule::doParticles (0x0055FD6B) are the structural leads; the
// owner class keeps an address-derived name.
// Handoff: targets/game/reverse/attempt_support/20261110-005f8010-priority-accessor.md
//
// Shape note: the in-loop priority test reads the system through an inline
// getPriority() accessor (Zero Hour: sys->getPriority() == AREA_EFFECT).
// Reading the field directly left the loop-exit reloads of EBP (colour base)
// and EDI (this) at +0x23B/+0x23F in the opposite order (4 bytes).
#include "vector3.h"
#include "vector4.h"
#include "shader.h"
#include "sharebuf.h"
#include "ascii_string.h"
#include "texture.h"
extern void j_00001b18();
extern void j_00038a5f();
extern void j_000309f9();
extern void j_00037308();
extern void j_0001153b();
extern void j_00022796();
class Receiver005F8010 {};
template<class R> inline R invoke005F8010(void*obj,void(*entry)()) {
 typedef R (Receiver005F8010::*Method)();
 union { void(*raw)(); Method typed; } f; f.raw=entry;
 return (((Receiver005F8010*)obj)->*f.typed)();
}
struct Particle005F8010 {
 char pad00[0x1c]; Vector3 position1C; char pad28[0x3c-0x28];
 Particle005F8010 *next3C; char pad40[0x58-0x40]; unsigned personality58;
};
struct System005F8010 {
 char pad00[8]; int shader08; char pad0C[4]; AsciiString name10;
 char pad14[0x7c-0x14]; int priority7C; bool ground80; char pad81[0xa0-0x81]; Particle005F8010 *firstA0;
 int getPriority() const { return priority7C; }
};
extern ShareBufferClass<Vector3> *g_vector3Buffer;
extern ShareBufferClass<Vector4> *g_vector4Buffer;
extern ShareBufferClass<float> *g_floatBuffer;
extern ShareBufferClass<unsigned char> *g_byteBuffer;
extern const float g_Va011135A8;
extern ShaderClass g_Va012D6E24;
extern ShaderClass g_Va012D6E28;
extern ShaderClass g_Va012D6E30;
extern ShaderClass g_Va012D6E48;
class BFMEWaterTrackTextureHandle {
public:
 TextureClass *m_texture;
 ~BFMEWaterTrackTextureHandle() { if(m_texture) m_texture->Release_Ref(); }
};
BFMEWaterTrackTextureHandle BFMEGetWaterTrackTexture(char*,int,int);
class BfmeThingDUC { public: void bfmeGoDUC(); };
class Rva00918DA0 { public: void set(int); };
class BfmeStreakUGB { public: void bfmeSetUGB(unsigned,void*,void*,void*,int); };
class RenderInfoClass;
class StreakLineClass {
public:
#define S(n) virtual void s##n();
 S(0) S(1) S(2) S(3) S(4) S(5) S(6) S(7) S(8) S(9) S(10) S(11)
#undef S
 virtual void Render(RenderInfoClass&);
 void Set_Texture(TextureClass*);
};
extern StreakLineClass *g_rva005F7FA0Resource;
struct Bounds005F8010 { Vector3 center,extent; };
class Rva005F8010 {
public:
 int render(RenderInfoClass&,const Bounds005F8010*,int*);
 System005F8010 *system() const { return !system04 ? ((System005F8010*(*)())j_00001b18)() : system04; }
 char pad00[4]; System005F8010 *system04;
};
int Rva005F8010::render(RenderInfoClass &renderInfo,const Bounds005F8010 *bounds,int *fieldCount)
{
 int count=0;
 Vector3 *posArray=g_vector3Buffer->Get_Array();
 float *sizeArray=g_floatBuffer->Get_Array();
 Vector4 *rgbaArray=g_vector4Buffer->Get_Array();
 unsigned char *angleArray=g_byteBuffer->Get_Array();
 float bcX=bounds->center.X,bcY=bounds->center.Y,bcZ=bounds->center.Z;
 float beX=bounds->extent.X,beY=bounds->extent.Y,beZ=bounds->extent.Z;
 unsigned personalities[512];
 for(Particle005F8010 *p=system()->firstA0;p;p=p->next3C) {
  if(invoke005F8010<bool>(p,j_00038a5f)) continue;
  const Vector3 *pos=&p->position1C;
  float psize=invoke005F8010<float>(p,j_000309f9);
  if(WWMath::Fabs(pos->X-bcX)>(beX+psize)) continue;
  if(WWMath::Fabs(pos->Y-bcY)>(beY+psize)) continue;
  if(WWMath::Fabs(pos->Z-bcZ)>(beZ+psize)) continue;
  *fieldCount+=(system()->getPriority()==11 && system()->ground80);
  personalities[count]=p->personality58;
  posArray[count].X=pos->X; posArray[count].Y=pos->Y; posArray[count].Z=pos->Z;
  sizeArray[count]=psize;
  const Vector3 *color=invoke005F8010<const Vector3*>(p,j_00037308);
  if(color) { rgbaArray[count].X=color->X; rgbaArray[count].Y=color->Y; rgbaArray[count].Z=color->Z; }
  else { rgbaArray[count].X=0.0f; rgbaArray[count].Y=0.0f; rgbaArray[count].Z=0.0f; }
  rgbaArray[count].W=invoke005F8010<float>(p,j_0001153b);
  angleArray[count]=(unsigned char)(invoke005F8010<float>(p,j_00022796)*g_Va011135A8);
  if(++count==512) break;
 }
 if(g_rva005F7FA0Resource && count>=2) {
  BFMEWaterTrackTextureHandle texture=BFMEGetWaterTrackTexture(const_cast<char*>(system()->name10.str()),0,0);
  ((BfmeThingDUC*)g_rva005F7FA0Resource)->bfmeGoDUC();
  g_rva005F7FA0Resource->Set_Texture((TextureClass*)&texture);
  union { void(Rva00918DA0::*raw)(int); void(Rva00918DA0::*typed)(ShaderClass); } shaderCall;
  shaderCall.raw=&Rva00918DA0::set;
  switch(system()->shader08) {
  case 1: (((Rva00918DA0*)g_rva005F7FA0Resource)->*shaderCall.typed)(ShaderClass::_PresetAdditiveSpriteShader); break;
  case 2: (((Rva00918DA0*)g_rva005F7FA0Resource)->*shaderCall.typed)(g_Va012D6E30); break;
  case 3: (((Rva00918DA0*)g_rva005F7FA0Resource)->*shaderCall.typed)(ShaderClass::_PresetAlphaSpriteShader); break;
  case 4: (((Rva00918DA0*)g_rva005F7FA0Resource)->*shaderCall.typed)(g_Va012D6E48); break;
  case 5: (((Rva00918DA0*)g_rva005F7FA0Resource)->*shaderCall.typed)(ShaderClass::_PresetMultiplicativeSpriteShader); break;
  case 6: (((Rva00918DA0*)g_rva005F7FA0Resource)->*shaderCall.typed)(g_Va012D6E24); break;
  case 7: (((Rva00918DA0*)g_rva005F7FA0Resource)->*shaderCall.typed)(g_Va012D6E28); break;
  }
  ((BfmeStreakUGB*)g_rva005F7FA0Resource)->bfmeSetUGB(count,g_vector3Buffer->Get_Array(),g_floatBuffer->Get_Array(),g_vector4Buffer->Get_Array(),(int)personalities);
  rgbaArray[0].X=0;rgbaArray[0].Y=0;rgbaArray[0].Z=0;rgbaArray[0].W=0;
  g_rva005F7FA0Resource->Render(renderInfo);
 }
 return count;
}

