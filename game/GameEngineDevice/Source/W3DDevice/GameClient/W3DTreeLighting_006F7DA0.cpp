typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;

#define Rva006F7DA0ZeroRange (*(const Real *)0x01075350)
#define Rva006F7DA0One (*(const Real *)0x01075334)
#define Rva006F7DA0Uint32Scale (*(const Real *)0x01075358)
#define Rva006F7DA0OneOver255 (*(const Real *)0x0107C64C)
#define Rva006F7DA0OneDouble (*(const double *)0x0107C640)
#define Rva006F7DA0Scale255 (*(const Real *)0x01084068)

class Vector3;

class WWMath {
public:
    static Real __fastcall Inv_Sqrt(Real value);
};

extern "C" long __ftol2(double value);

class Vector3 {
public:
    Real X;
    Real Y;
    Real Z;

    Vector3(Real x, Real y, Real z) : X(x), Y(y), Z(z) {}

    void Normalize(void)
    {
        Real lengthSquared = X * X + Y * Y + Z * Z;

        if (lengthSquared != 0.0f) {
            Real inverseLength = WWMath::Inv_Sqrt(lengthSquared);
            X *= inverseLength;
            Y *= inverseLength;
            Z *= inverseLength;
        }
    }
};

namespace GlobalData {
struct TerrainLighting {
    struct RGBColor {
        Real red;
        Real green;
        Real blue;
    } ambient;
    RGBColor diffuse;
    struct Coord3D {
        Real x;
        Real y;
        Real z;
    } lightPos;
};
}

static Real Rva006F7DA0Fabs(Real value)
{
    union {
        Real realValue;
        UnsignedInt bits;
    } converted;

    converted.realValue = value;
    converted.bits &= 0x7FFFFFFF;
    return converted.realValue;
}

class Rva006F7DA0TreeBuffer {
public:
    static UnsignedInt __stdcall doLighting(const GlobalData::TerrainLighting *objectLighting,
                                             const Vector3 *emissive,
                                             UnsignedInt vertDiffuse,
                                             Real scale,
                                             UnsignedInt alpha);
};

// ?doLighting@W3DTreeBuffer@@SGIPBUTerrainLighting@GlobalData@@PBVVector3@@IMI@Z
// ?doLighting@Rva006F7DA0TreeBuffer@@SGIPBUTerrainLighting@GlobalData@@PBVVector3@@IMI@Z
UnsignedInt __stdcall Rva006F7DA0TreeBuffer::doLighting(
    const GlobalData::TerrainLighting *objectLighting,
    const Vector3 *emissive,
    UnsignedInt vertDiffuse,
    Real scale,
    UnsignedInt alpha)
{
    Real shadeR;
    Real shadeG;
    Real shadeB;
    Real shade;
    Int i;

    shadeR = objectLighting[0].ambient.red + emissive->X;
    shadeG = objectLighting[0].ambient.green + emissive->Y;
    shadeB = objectLighting[0].ambient.blue + emissive->Z;

    for (i = 0; i < 3; ++i) {
        Vector3 lightDirection(objectLighting[i].lightPos.x,
                               objectLighting[i].lightPos.y,
                               objectLighting[i].lightPos.z);
        lightDirection.Normalize();
        shade = Rva006F7DA0Fabs(-lightDirection.Z);

        if (shade > 1.0f) {
            shade = 1.0f;
        }

        shadeR += shade * objectLighting[i].diffuse.red;
        shadeG += shade * objectLighting[i].diffuse.green;
        shadeB += shade * objectLighting[i].diffuse.blue;
    }

    if (vertDiffuse != 0xFFFFFFFF) {
        shade = (Real)(vertDiffuse & 0xFF);
        shadeB *= shade / 255.0f;
        shade = (Real)((vertDiffuse >> 8) & 0xFF);
        shadeG *= shade / 255.0f;
        shade = (Real)((vertDiffuse >> 16) & 0xFF);
        shadeR *= shade / 255.0f;
    }

    shadeR *= scale;
    shadeG *= scale;
    shadeB *= scale;

    if (shadeR > 1.0) shadeR = 1.0;
    if (shadeR < 0.0f) shadeR = 0.0f;
    if (shadeG > 1.0) shadeG = 1.0;
    if (shadeG < 0.0f) shadeG = 0.0f;
    if (shadeB > 1.0) shadeB = 1.0;
    if (shadeB < 0.0f) shadeB = 0.0f;

    return (UnsignedInt)(shadeB * Rva006F7DA0Scale255)
        | ((UnsignedInt)(shadeG * Rva006F7DA0Scale255) << 8)
        | ((UnsignedInt)(shadeR * Rva006F7DA0Scale255) << 16)
        | (alpha << 24);
}
