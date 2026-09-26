// ?method@Rva0071C9C0@@QAEDHMMMPBVMatrix3D@@@Z
// Retail 0x0071C9C0, 397 bytes.  The caller proves a four-byte identifier,
// three scalar position arguments, and a trailing Matrix3D pointer.  The
// record and type extents/offsets are taken from the matched neighbours and
// this body's own stores; the semantic owner remains address-derived.
//
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims
#include "matrix3d.h"
#include "sphere.h"

typedef int Int;
typedef float Real;

struct Rva0071C9C0Record
{
    Vector3 position;
    Real scale;
    Matrix3D transform;
    Int type;
    unsigned char reserved44[4];
    SphereClass bounds;
    Real sortKey;
    Int key;
    unsigned char reserved60[0x44];
};

struct Rva0071C9C0Type
{
    SphereClass bounds;
    unsigned char reserved10[0x4c];
};

class Rva0071C9C0
{
public:
    char method(Int key, Real x, Real y, Real z, const Matrix3D *transform);

private:
    unsigned char reserved000[0x1548];
    Rva0071C9C0Record records[12000];
    Int count;
    unsigned char changed;
    unsigned char reserved1e1ccd[0x17];
    Rva0071C9C0Type types[64];
};

char Rva0071C9C0::method(Int key, Real x, Real y, Real z,
    const Matrix3D *transform)
{
    for (Int index = 0; index < count; ++index)
    {
        if (records[index].key == key)
        {
            records[index].position.Set(x, y, z);
            records[index].transform = *transform;

            Rva0071C9C0Type *type = types + records[index].type;
            records[index].bounds = type->bounds;
            Real scale = records[index].scale;
            records[index].bounds.Center *= scale;
            records[index].bounds.Radius *= records[index].scale;
            records[index].bounds.Center += records[index].position;

            changed = 1;
            return 1;
        }
    }
    return 0;
}
