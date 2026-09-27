// RVA 0x006FDCB0: camera projection/transform update; owner identity unproved.
// Camera at +0x70 is witnessed by Rva00700030::initialize and retail calls.
// The ILT at 0x0000B0AF reaches 0x006FD700: thiscall (Matrix3D*, float, float).
// cl: /DNDEBUG /MD /EHsc /O2 /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWDebug /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Include
#include "camera.h"
#include <math.h>
extern void j_0000b0af();
class Rva006FDCB0CameraProjection {
public:
 void update();
 char pad000[0x70]; CameraClass* camera70;
 char pad074[0x14]; float field88,field8c;
 char pad090[0x54]; float fielde4, fielde8, fieldec;
};
static void transform(void* self,Matrix3D* m,float a,float b) {
 struct Thunk { void call(Matrix3D*,float,float); };
 typedef void (Thunk::*Function)(Matrix3D*,float,float);
 union { void (*raw)(); Function member; } f;
 f.raw=j_0000b0af;
 (reinterpret_cast<Thunk*>(self)->*f.member)(m,a,b);
}
void Rva006FDCB0CameraProjection::update() {
 float t=fielde4;
 float end=fieldec;
 // Preserve retail's multiply then independent member reload; MSVC otherwise factors this.
 float u=(fielde4*fielde4+*(const volatile float*)&fielde4)*0.5f;
 float uu=u*u;
 float start=field88;
 float distance=(field8c-start)*((sqrt(u)-uu)*u+uu)+start;
 float tt=t*t;
 Matrix3D m(true);
 if(camera70) {
  camera70->Set_Clip_Planes(10.0f,distance*1.5f+2000.0f);
  camera70->Set_View_Plane(0.8726646304130554f,-1.0f);
  float zero=0.0f;
  transform(this,&m,distance,(zero-end)*((sqrt(t)-tt)*t+tt)+end);
  camera70->Set_Transform(m);
 }
}
