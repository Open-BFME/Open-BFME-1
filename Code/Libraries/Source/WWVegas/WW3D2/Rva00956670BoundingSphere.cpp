// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// Retail full93B RVA956670. Address-qualified child of the independently
// established RenderObj base; sphere slot108 calls virtual box slot10C.
#include "rendobj.h"

class Rva00956670 : public RenderObjClass
{
public:
    virtual void Get_Obj_Space_Bounding_Sphere(SphereClass &sphere) const;
};

// ?Get_Obj_Space_Bounding_Sphere@Rva00956670@@UBEXAAVSphereClass@@@Z
void Rva00956670::Get_Obj_Space_Bounding_Sphere(SphereClass &sphere) const
{
    AABoxClass box;
    Get_Obj_Space_Bounding_Box(box);
    sphere.Center = box.Center;
    sphere.Radius = box.Extent.Length();
}
