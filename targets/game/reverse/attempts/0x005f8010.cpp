// ?d_005f8010@@YAXXZ
// partial score=0.9959016393 date=2026-09-26
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WW3D2
#include "vector3.h"
#include "vector4.h"
#include "shader.h"
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
 char pad00[8]; int shader08; char pad0C[4]; char *name10;
 char pad14[0x7c-0x14]; int priority7C; bool ground80; char pad81[0xa0-0x81]; Particle005F8010 *firstA0;
};
template<class T> struct Buffer005F8010 { char pad00[0xc]; T *array0C; T *Get_Array() const { return array0C; } };
extern Buffer005F8010<Vector3> *positionBuffer005F8010;
extern Buffer005F8010<Vector4> *rgbaBuffer005F8010;
extern Buffer005F8010<float> *sizeBuffer005F8010;
extern Buffer005F8010<unsigned char> *angleBuffer005F8010;
extern ShaderClass shader012D6E2C,shader012D6E30,shader012D6E34,shader012D6E48,shader012D6E60,shader012D6E24,shader012D6E28;
class TextureClass;
class BFMEWaterTrackTexture { public: void Release_Ref(); };
class BFMEWaterTrackTextureHandle {
public:
 TextureClass *m_texture;
 ~BFMEWaterTrackTextureHandle() { if(m_texture) ((BFMEWaterTrackTexture*)m_texture)->Release_Ref(); }
};
BFMEWaterTrackTextureHandle BFMEGetWaterTrackTexture(char*,int,int);
class BfmeThingDUC { public: void bfmeGoDUC(); };
class StreakLineClass { public: void Set_Texture(TextureClass*); };
class Rva00918DA0 { public: void set(int); };
class BfmeStreakUGB { public: void bfmeSetUGB(unsigned,void*,void*,void*,int); };
class Rva005F8010Slots {
public:
#define S(n) virtual void s##n();
 S(0) S(1) S(2) S(3) S(4) S(5) S(6) S(7) S(8) S(9) S(10) S(11)
#undef S
 virtual void render(void*);

};
extern Rva005F8010Slots *renderTarget005F8010;
struct Bounds005F8010 { Vector3 center,extent; };
class Rva005F8010 {
public:
 int render(void*,const Bounds005F8010*,int*);
 System005F8010 *system() const { return !system04 ? ((System005F8010*(*)())j_00001b18)() : system04; }
 char pad00[4]; System005F8010 *system04;
};
int Rva005F8010::render(void *renderInfo,const Bounds005F8010 *bounds,int *fieldCount)
{
 int count=0;
 Vector3 *posArray=positionBuffer005F8010->Get_Array();
 float *sizeArray=sizeBuffer005F8010->Get_Array();
 Vector4 *rgbaArray=rgbaBuffer005F8010->Get_Array();
 unsigned char *angleArray=angleBuffer005F8010->Get_Array();
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
  *fieldCount+=(system()->priority7C==11 && system()->ground80);
  personalities[count]=p->personality58;
  posArray[count].X=pos->X; posArray[count].Y=pos->Y; posArray[count].Z=pos->Z;
  sizeArray[count]=psize;
  const Vector3 *color=invoke005F8010<const Vector3*>(p,j_00037308);
  if(color) { rgbaArray[count].X=color->X; rgbaArray[count].Y=color->Y; rgbaArray[count].Z=color->Z; }
  else { rgbaArray[count].X=0.0f; rgbaArray[count].Y=0.0f; rgbaArray[count].Z=0.0f; }
  rgbaArray[count].W=invoke005F8010<float>(p,j_0001153b);
  angleArray[count]=(unsigned char)(invoke005F8010<float>(p,j_00022796)*(255.0f/(2.0f*WWMATH_PI)));
  if(++count==512) break;
 }
 if(renderTarget005F8010 && count>=2) {
  char *name=system()->name10;
  BFMEWaterTrackTextureHandle texture=BFMEGetWaterTrackTexture(name ? name+8 : "",0,0);
  ((BfmeThingDUC*)renderTarget005F8010)->bfmeGoDUC();
  ((StreakLineClass*)renderTarget005F8010)->Set_Texture((TextureClass*)&texture);
  union { void(Rva00918DA0::*raw)(int); void(Rva00918DA0::*typed)(ShaderClass); } shaderCall;
  shaderCall.raw=&Rva00918DA0::set;
  switch(system()->shader08) {
  case 1: (((Rva00918DA0*)renderTarget005F8010)->*shaderCall.typed)(shader012D6E2C); break;
  case 2: (((Rva00918DA0*)renderTarget005F8010)->*shaderCall.typed)(shader012D6E30); break;
  case 3: (((Rva00918DA0*)renderTarget005F8010)->*shaderCall.typed)(shader012D6E34); break;
  case 4: (((Rva00918DA0*)renderTarget005F8010)->*shaderCall.typed)(shader012D6E48); break;
  case 5: (((Rva00918DA0*)renderTarget005F8010)->*shaderCall.typed)(shader012D6E60); break;
  case 6: (((Rva00918DA0*)renderTarget005F8010)->*shaderCall.typed)(shader012D6E24); break;
  case 7: (((Rva00918DA0*)renderTarget005F8010)->*shaderCall.typed)(shader012D6E28); break;
  }
  ((BfmeStreakUGB*)renderTarget005F8010)->bfmeSetUGB(count,positionBuffer005F8010->Get_Array(),sizeBuffer005F8010->Get_Array(),rgbaBuffer005F8010->Get_Array(),(int)personalities);
  rgbaArray[0].X=0;rgbaArray[0].Y=0;rgbaArray[0].Z=0;rgbaArray[0].W=0;
  renderTarget005F8010->render(renderInfo);
 }
 return count;
}

