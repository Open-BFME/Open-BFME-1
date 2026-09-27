// ?d_006fd700@@YAXXZ
// partial score=0.963740458 date=2026-09-27
// cl: /DNDEBUG /MD /EHsc /O2 /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWDebug /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Include
#include "camera.h"
#include <math.h>
class Rva006FD700CameraTransform {
public:
 void build(Matrix3D* result,float distance,float angle);
 char pad000[0xc]; float field0c,field10;
 char pad014[0x94]; Vector3 fielda8,fieldb4,fieldc0;
 float fieldcc;
 char pad0d0[0x14]; float fielde4;
 char pad0e8[0x50]; RenderObjClass* object138;
 char pad13c[8]; float field144;
};
void Rva006FD700CameraTransform::build(Matrix3D* result,float distance,float angle) {
 Vector3 position(0.0f,-sin(angle)*distance,cos(angle)*distance);
 if(position.Y==0.0f) position.Y=-0.5f;
 float t=fielde4;
 float tt=t*t;
 float blend=(sqrt(t)-tt)*t+tt;
 Vector3::Lerp(fielda8,fieldb4,blend,&fieldc0);
 float x=fieldc0.X;
 fieldc0.X=(field0c-x)*field144+x;
 float y=fieldc0.Y;
 fieldc0.Y=(field10-y)*field144+y;
 position+=fieldc0;
 if(object138) {
  Matrix3D m(true);
  m.Set_Translation(Vector3(192.43f,569.88f,(distance+distance)*blend));
  object138->Set_Transform(m);
 }
 position-=fieldc0;
 float initialTurn=fieldcc;
 float turn=(0.0f-initialTurn)*blend+initialTurn;
 turn=(0.0f-turn)*field144+turn;
 position.Rotate_Z(turn);
 position+=fieldc0;
 result->Make_Identity();
 result->Look_At(position,fieldc0,0.0f);
}
