// ?build@Rva006FE3C0CameraRay@@QAEXPBURva006FE3C0ScreenPoint@@PAVVector3@@1@Z
// partial score=0.7970588235294118 date=2026-09-28
// cl: /DNDEBUG /MD /EHsc /O2 /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWDebug /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Include
#include "camera.h"
#include <math.h>
extern const float Rva00C75334One;
class Display {
public:
 virtual void slot00(); virtual void slot04(); virtual void slot08();
 virtual void slot0c(); virtual void slot10(); virtual void slot14();
 virtual void slot18(); virtual void slot1c(); virtual void slot20();
 virtual void slot24(); virtual void slot28();
 virtual unsigned getWidth(); virtual unsigned getHeight();
};
extern Display* TheDisplay;
struct Rva006FE3C0ScreenPoint { int x,y; };
class Rva006FE3C0CameraRay {
public:
 void build(const Rva006FE3C0ScreenPoint* screen, Vector3* origin, Vector3* direction);
 char pad000[0x70]; CameraClass* camera70;
};
void Rva006FE3C0CameraRay::build(const Rva006FE3C0ScreenPoint* screen, Vector3* origin, Vector3* direction) {
 const Matrix3D& transform=camera70->Get_Transform();
 Vector2 minimum, maximum;
 camera70->Get_View_Plane(minimum,maximum);
 float width=maximum.X-minimum.X;
 float height=maximum.Y-minimum.Y;
 float displayWidth=TheDisplay->getWidth();
 float displayHeight=TheDisplay->getHeight();
 float x=(screen->x/displayWidth-0.5f)*width;
 float y=-(screen->y/displayHeight-0.5f)*height;
 float vy=x*transform[1][0]+y*transform[1][1]-transform[1][2]*Rva00C75334One;
 float vz=x*transform[2][0]+y*transform[2][1]-transform[2][2]*Rva00C75334One;
 float vx=x*transform[0][0]+y*transform[0][1]-transform[0][2]*Rva00C75334One;
 float inverse=1.0f/sqrt(vx*vx+vz*vz+vy*vy);
 direction->X=vx*inverse; direction->Y=vy*inverse; direction->Z=vz*inverse;
 Vector3 position=camera70->Get_Position();
 origin->X=position.X; origin->Y=position.Y; origin->Z=position.Z;
}
