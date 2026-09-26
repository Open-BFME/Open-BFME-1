// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/Wwutil /Igame/Libraries/Source/WWVegas/WWDownload /Igame/Libraries/Source/Compression /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims/sweep
// Retail RVA 0x009566D0, complete 143-byte constructor.
// W3DStreakDraw constructs this segmented-line-family RenderObj child.
// Complete primary/secondary tables contain 130/1 entries; all 17 child
// overrides and the four-state constructor cleanup are independently audited.
// The matched W3DStreakDraw caller and its configuration methods identify the
// constructed object as BfmeStreakObject.
// This TU uses the complete reconciled RenderObj interface and declares the
// 17 raw target replacements (including its compiler-generated deleting dtor).
#include "vector3.h"
#include "rendobj.h"
#include "simplevec.h"

// The terminal member is a proven nontrivial 0x24-byte value: its first field
// is a TextureRef whose retail destructor is out of line at RVA 0x00975010.
class TextureRef
{
public:
    TextureRef() : m_ptr(0) {}
    ~TextureRef();
private:
    void *m_ptr;
};

class Rva00974F80
{
public:
    Rva00974F80();
private:
    TextureRef m_tex;
    char m_storage[0x20];
};

class BfmeStreakObject : public RenderObjClass
{
public:
    BfmeStreakObject();

    // Target primary slots 1, 2, 3, 10, 12, 59, 66, 67, 71, 73-80.
    // Signatures are taken directly from the reconciled RenderObjClass header.
    virtual RenderObjClass *Clone(void) const;
    virtual int Class_ID(void) const;
    virtual int Get_Num_Polys(void) const;
    virtual void Render(RenderInfoClass &rinfo);
    virtual bool Cast_Ray(RayCollisionTestClass &raytest);
    virtual void Get_Obj_Space_Bounding_Sphere(SphereClass &sphere) const;
    virtual void Get_Obj_Space_Bounding_Box(AABoxClass &box) const;
    virtual void Prepare_LOD(CameraClass &camera);
    virtual void Increment_LOD(void);
    virtual void Decrement_LOD(void);
    virtual float Get_Cost(void) const;
    virtual float Get_Value(void) const;
    virtual float Get_Post_Increment_Value(void) const;
    virtual void Set_LOD_Level(int lod);
    virtual int Get_LOD_Level(void) const;
    virtual int Get_LOD_Count(void) const;

private:
    SimpleDynVecClass<Vector3> m_points;
    SimpleDynVecClass<float> m_widths;
    Rva00974F80 m_renderer;
};

// ??0BfmeStreakObject@@QAE@XZ
BfmeStreakObject::BfmeStreakObject()
    : m_points(0),
      m_widths(0),
      m_renderer()
{}
