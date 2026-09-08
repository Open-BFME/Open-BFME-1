// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// Retail RVA 0x00956760, full 494 bytes. This is the independent ray body
// immediately after the 0x9566D0 child constructor. Its field layout is the
// Streak-like child: SimpleDynVec<Vector3> at +0xC8, SimpleDynVec<float> at
// +0xD8, and a nontrivial 0x24-byte renderer tail at +0xE8. Historical owner identity is
// unresolved; retain the address-qualified child and its proven layout.

#include "rendobj.h"
#include <stddef.h>
#include "ww3d.h"
#include "w3d_file.h"
#include "simplevec.h"
#include "coltest.h"

// The constructor at 0x009566D0 proves only a nontrivial 0x24-byte tail
// member at +0xE8. The ray body reads its width at member offset +8; keep
// that ABI view local and address-qualified instead of importing the larger
// ZH SegLineRendererClass definition.
class Rva00956760WidthView
{
public:
    unsigned char Prefix[8];
    float Width;
    unsigned char Tail[0x18];

    float Get_Width(void) const { return Width; }
};

typedef char Rva00956760WidthViewSizeGuard
    [(sizeof(Rva00956760WidthView) == 0x24) ? 1 : -1];
typedef char Rva00956760WidthViewWidthGuard
    [(offsetof(Rva00956760WidthView, Width) == 0x08) ? 1 : -1];

class Rva00956760 : public RenderObjClass
{
public:
    virtual bool Cast_Ray(RayCollisionTestClass &raytest);

private:
    SimpleDynVecClass<Vector3> PointLocations;
    SimpleDynVecClass<float> PointWidths;
    Rva00956760WidthView LineRenderer;
};

// ?Cast_Ray@Rva00956760@@UAE_NAAVRayCollisionTestClass@@@Z
bool Rva00956760::Cast_Ray(RayCollisionTestClass &raytest)
{
    if ((Get_Collision_Type() & raytest.CollisionType) == 0) return false;

    bool retval = false;
    float fraction = 1.0F;
    for (uint32 index = 1; index < (unsigned int)PointLocations.Count(); index ++) {
        Vector3 curr[2];
        Transform.mulVector3Array(&PointLocations[index-1], curr, 2);
        LineSegClass line_seg(curr[0], curr[1]);

        Vector3 p0;
        Vector3 p1;
        if (raytest.Ray.Find_Intersection(line_seg, &p0, &fraction, &p1, NULL)) {
            float dist = (p0 - p1).Length();
            if (dist <= LineRenderer.Get_Width() && fraction >= 0 && fraction < raytest.Result->Fraction) {
                retval = true;
                break;
            }
        }
    }

    if (retval) {
        raytest.Result->Fraction = fraction;
        raytest.Result->SurfaceType = SURFACE_TYPE_DEFAULT;
        raytest.CollidedRenderObj = this;
    }

    return retval;
}
