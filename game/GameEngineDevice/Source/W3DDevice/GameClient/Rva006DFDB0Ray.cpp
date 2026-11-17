// cl: /Igame/Libraries/Source/WWVegas/WWLib /O2 /DNDEBUG /MD /EHsc-

typedef float Real;
typedef int Int;



#include "../../../../Libraries/Include/Lib/ICoord2D.h"

#include "../../../../Libraries/Source/WWVegas/WWMath/vector2.h"

#include "../../../../Libraries/Source/WWVegas/WWMath/vector3.h"

class RenderObjClass
{
public:
    Vector3 Get_Position() const;
};

class CameraClass : public RenderObjClass
{
public:
    void Un_Project(Vector3 &destination, const Vector2 &viewPoint) const;
};

class Rva006DFDB0View
{
public:
    unsigned char padding[0xbc];
    Int width;
    Int height;
    Int originX;
    Int originY;
    CameraClass *camera;
};

extern void __cdecl PixelScreenToW3DLogicalScreen(
    Int screenX, Int screenY, Real *logX, Real *logY, Int screenWidth, Int screenHeight);

// ?Rva006DFDB0Ray@@YGXPBUICoord2D@@PAVVector3@@1PAVRva006DFDB0View@@@Z
void __stdcall Rva006DFDB0Ray(
    const ICoord2D *screen, Vector3 *rayStart, Vector3 *rayEnd, Rva006DFDB0View *view)
{
    Real logX;
    Real logY;
    PixelScreenToW3DLogicalScreen(
        screen->x - view->originX,
        screen->y - view->originY,
        &logX,
        &logY,
        view->width,
        view->height);
    *rayStart = view->camera->Get_Position();
    view->camera->Un_Project(*rayEnd, Vector2(logX, logY));
    *rayEnd -= *rayStart;
    rayEnd->Normalize();
    Real depth = *(const Real *)((const unsigned char *)view->camera + 0xf4);
    *rayEnd *= depth;
    *rayEnd += *rayStart;
}
