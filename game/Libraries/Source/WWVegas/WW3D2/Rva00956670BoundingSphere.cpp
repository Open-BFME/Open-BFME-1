// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/Wwutil /Igame/Libraries/Source/WWVegas/WWDownload /Igame/Libraries/Source/Compression /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims/sweep
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
