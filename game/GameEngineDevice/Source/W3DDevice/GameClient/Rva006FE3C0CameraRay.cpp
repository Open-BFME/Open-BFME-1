// RVA 0x006FE3C0 (340 B, ret 12): vtable 0x011207C0 slot 7 builds a unit pick ray from a screen point
// through the camera at +0x70 and returns the camera position as the ray origin; owner identity unproved.
// The view-plane point (x, y, -1) is rotated by the camera transform, like Zero Hour's intersec.inl pick ray.
// cl: /DNDEBUG /MD /EHsc /O2 /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWDebug /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Include
#include "camera.h"
#include <math.h>
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
// ?sqr@@YAMM@Z absent-from-retail
inline float sqr(float value) { return value*value; }
void Rva006FE3C0CameraRay::build(const Rva006FE3C0ScreenPoint* screen, Vector3* origin, Vector3* direction) {
 const Matrix3D& transform=camera70->Get_Transform();
 Vector2 minimum, maximum;
 camera70->Get_View_Plane(minimum,maximum);
 float width=maximum.X-minimum.X;
 float height=maximum.Y-minimum.Y;
 float displayWidth=TheDisplay->getWidth();
 float displayHeight=TheDisplay->getHeight();
 float viewX=(screen->x/displayWidth-0.5f)*width;
 float viewY=-((screen->y/displayHeight-0.5f)*height);
 float viewZ=-1.0f;
 float x=viewX*transform[0][0]+viewY*transform[0][1]+transform[0][2]*viewZ;
 float y=viewX*transform[1][0]+viewY*transform[1][1]+transform[1][2]*viewZ;
 float z=viewX*transform[2][0]+viewY*transform[2][1]+transform[2][2]*viewZ;
 direction->Set(x,y,z);
 float inverse=1.0f/sqrt(sqr(direction->X)+sqr(direction->Y)+sqr(direction->Z));
 direction->X*=inverse; direction->Y*=inverse; direction->Z*=inverse;
 Vector3 position=camera70->Get_Position();
 origin->X=position.X; origin->Y=position.Y; origin->Z=position.Z;
}
