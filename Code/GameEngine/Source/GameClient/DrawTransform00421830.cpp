// cl: /O2 /Ob2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /Ireference/shims/sweep /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug
// RVA 00421830: opaque Drawable draw path; 674 bytes, thiscall, unused arg, ret4.
// Evidence: docs/analysis/0x0077b3f0.md, NEIGHBOUR NOTES 00421830.
// Ported from GeneralsMD Drawable::draw; original BFME method identity unproved.
// The BitFlagsHFCountInverseIntersectionShim pin at this RVA is contradicted
// by the complete body and the hub's child-Drawable call; it is not used here.
#include "matrix3d.h"
#include "drawable.h"

class DrawTransform00421830;
class Drawable
{
    friend class DrawTransform00421830;
protected:
    void applyPhysicsXform(Matrix3D *);
};

// Reuse the independently landed callee contracts, including the legacy
// integer spelling for the EAX matrix address returned by 0041CEC0.
class BfmeCalc919G { public: int bfmeCalc919G(); };
struct BfmeMatETE;
class BfmeHostETE { public: BfmeMatETE *bfmeGetETE(); };

class DrawModule00421830
{
public:
    virtual void slot00(); virtual void slot04(); virtual void slot08();
    virtual void slot0C(); virtual void slot10(); virtual void slot14();
    virtual void slot18(); virtual void slot1C(); virtual void slot20();
    virtual void slot24(const Matrix3D *);
};

class DrawTransform00421830
{
    // Layout witnessed in the complete retail body. name_oracle reports no
    // semantic names for 114/150/2E4/3AD..3B0; m_object at FC is witnessed.
    unsigned char pad000[0xFC];
    char *m_object;
    unsigned char pad100[0x14];
    unsigned int field114;
    unsigned char pad118[0x38];
    DrawModule00421830 **field150;
    unsigned char pad154[0x190];
    float field2E4;
    unsigned char pad2E8[0xC5];
    bool field3AD, field3AE, field3AF, field3B0;
public:
    void draw(void *unused);
};

// Native Matrix3D::postMul, retaining retail's x87 accumulation order.
// A single sum permits VC7.1 to reassociate the products differently. Keep
// each original row alive until all four outputs have been calculated.
static __forceinline void compose00421830(Matrix3D &a, const Matrix3D &b)
{
    float v00 = a[0][0] * b[0][0];
    v00 = v00 + a[0][2] * b[2][0];
    v00 = v00 + a[0][1] * b[1][0];
    float v01 = a[0][1] * b[1][1];
    v01 = v01 + a[0][2] * b[2][1];
    v01 = v01 + a[0][0] * b[0][1];
    float v02 = a[0][2] * b[2][2];
    v02 = v02 + a[0][0] * b[0][2];
    v02 = v02 + a[0][1] * b[1][2];
    float v03 = a[0][1] * b[1][3];
    v03 = v03 + a[0][2] * b[2][3];
    v03 = v03 + a[0][0] * b[0][3];
    a[0][0] = v00;
    a[0][1] = v01;
    a[0][2] = v02;
    a[0][3] += v03;
    float v10 = a[1][2] * b[2][0];
    v10 = v10 + a[1][1] * b[1][0];
    v10 = v10 + a[1][0] * b[0][0];
    float v11 = a[1][0] * b[0][1];
    v11 = v11 + a[1][2] * b[2][1];
    v11 = v11 + a[1][1] * b[1][1];
    float v12 = a[1][0] * b[0][2];
    v12 = v12 + a[1][2] * b[2][2];
    v12 = v12 + a[1][1] * b[1][2];
    float v13 = a[1][0] * b[0][3];
    v13 = v13 + a[1][2] * b[2][3];
    v13 = v13 + a[1][1] * b[1][3];
    a[1][0] = v10;
    a[1][1] = v11;
    a[1][2] = v12;
    a[1][3] += v13;
    float v20 = a[2][2] * b[2][0];
    v20 = v20 + a[2][1] * b[1][0];
    v20 = v20 + a[2][0] * b[0][0];
    float v21 = a[2][0] * b[0][1];
    v21 = v21 + a[2][2] * b[2][1];
    v21 = v21 + a[2][1] * b[1][1];
    float v22 = a[2][0] * b[0][2];
    v22 = v22 + a[2][2] * b[2][2];
    v22 = v22 + a[2][1] * b[1][2];
    float v23 = a[2][0] * b[0][3];
    v23 = v23 + a[2][2] * b[2][3];
    v23 = v23 + a[2][1] * b[1][3];
    a[2][0] = v20;
    a[2][1] = v21;
    a[2][2] = v22;
    a[2][3] += v23;
}

void DrawTransform00421830::draw(void *unused)
{
    if ((field114 & 8) == 0)
    {
        char *object = m_object;
        if (object && (static_cast<unsigned char>(object[0x344]) & 1))
            field2E4 = 0.0f;
        else if (field2E4 > 0.001f)
            field2E4 *= 0.8f;
        else
            field2E4 = 0.0f;
    }

    if (field3AD || field3AE || field3B0)
        return;

    Matrix3D transform = *reinterpret_cast<const Matrix3D *>(
        reinterpret_cast<BfmeCalc919G *>(this)->bfmeCalc919G());
    if (!field3AF)
        compose00421830(transform, *reinterpret_cast<const Matrix3D *>(
            reinterpret_cast<BfmeHostETE *>(this)->bfmeGetETE()));

    reinterpret_cast<Drawable *>(this)->applyPhysicsXform(&transform);
    for (DrawModule00421830 **module = field150;
         *module; ++module)
        (*module)->slot24(&transform);
}
