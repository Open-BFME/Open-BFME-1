// ?build@Rva006FD990CameraCorners@@QAEXPAVVector3@@@Z
// partial score=0.9807073955 date=2026-09-28
// cl: /DNDEBUG /MD /EHsc /O2 /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWDebug /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Include
#include "camera.h"
class Rva006FD990CameraCorners {
public:
 void build(Vector3* output);
 char pad000[0x70]; CameraClass* camera70;
};
static __forceinline float groundX006FD990(const Vector3& origin,const Vector3& end) {
 float z=-origin.Z; return z*((end.X-origin.X)/(end.Z-origin.Z))+origin.X;
}
static __forceinline float groundY006FD990(const Vector3& origin,const Vector3& end) {
 float z=-origin.Z; return z*((end.Y-origin.Y)/(end.Z-origin.Z))+origin.Y;
}
void Rva006FD990CameraCorners::build(Vector3* output) {
 CameraClass* camera=camera70;
 Vector2 minimum,maximum;
 camera70->Get_View_Plane(minimum,maximum);
 Matrix3D transform(camera70->Get_Transform());
 Vector2 dimensions=maximum-minimum;
 double width=dimensions.X; double height=dimensions.Y;
 for(int i=0;i<4;++i) {
  int x,y;
  switch(i) {
   case 0: y=1; x=0; break;
   case 1: x=1; y=1; break;
   case 3: x=1; y=0; break;
   case 2: y=0; x=0; break;
   default: y=0; x=0; break;
  }
  Vector3 local; local.X=(x-0.5-camera->Get_Viewport().Min.X)*width; local.Y=(y-0.5-camera->Get_Viewport().Min.Y)*height; local.Z=-1.0f;
  Vector3 direction;
  Matrix3D::Rotate_Vector(transform,local,&direction);
  direction.Normalize();
  Vector3 end=direction+camera70->Get_Position();
  float groundX=groundX006FD990(camera70->Get_Position(),end);
  float groundY=groundY006FD990(camera70->Get_Position(),end);
  output[i].X=groundX; output[i].Y=groundY; output[i].Z=0.0f;
 }
}
