// ?method@Rva00733000@@QAEDPAXVVector3@@PBVMatrix3D@@@Z
// Full retail 0x00733000..0x0073318D (397 bytes), including RET 0x14.
// Caller BfmeOwnKD::bfmeFwdKD at 0x006C87B0 uses ILT 0x0003FE77.
// Opaque identity: no original semantic method name is asserted.
// Matched destructor 0x00736590 witnesses 12000 E8-byte records and 64 5C-byte types.
// Center scaling consumes a local value; Radius rereads the record field,
// preserving the source aliasing semantics and the retail x87 reload.
// The caller proves a void* key, a 12-byte by-value value, and a trailing
// pointer with RET 0x14.  The value/pointer are the native Vector3 and
// Matrix3D used by this tree-position update; bounds use native SphereClass.
//
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims
#include "matrix3d.h"
#include "sphere.h"

typedef int Int;
typedef float Real;

struct Rva00733000Record
{
    Vector3 position;
    Real scale;
    Matrix3D transform;
    Int type;
    unsigned char reserved44[4];
    SphereClass bounds;
    void *key;
    unsigned char reserved5c[0x8c];
};

struct Rva00733000Type
{
    unsigned char reserved00[0x10];
    SphereClass bounds;
    unsigned char reserved20[0x3c];
};

class Rva00733000
{
public:
    char method(void *key, Vector3 position, const Matrix3D *transform);

private:
    unsigned char reserved000[0x1b0];
    Rva00733000Record records[12000];
    Int count;
    unsigned char changed;
    unsigned char reserved2a7cb5[7];
    Rva00733000Type types[64];
};

char Rva00733000::method(void *key, Vector3 position,
    const Matrix3D *transform)
{
    for (Int index = 0; index < count; ++index)
    {
        if (records[index].key == key)
        {
            records[index].position = position;
            records[index].transform = *transform;

            Rva00733000Type *type = types + records[index].type;
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
