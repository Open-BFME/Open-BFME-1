// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWMath
#include "coord3d.h"

// Drawable::Drawable at 0x00418DA0 passes this+0x31C at +0x2D2 and calls
// this constructor through ILT 0x0003B700 at +0x313; the next field starts
// at +0x3AC, proving this subobject's 0x90-byte extent. Its semantic class
// is not established, so the owner name retains this body's address.
// The 16-byte row constructor at ILT 0x00045561 is also used by the
// SpawnPointProductionExitUpdate matrix-array constructor. This declaration
// retains its existing pinned name and layout without asserting this owner's
// semantic class.
class SpawnBoneRow
{
public:
    SpawnBoneRow();
    float X, Y, Z, W;
};

struct Rva00413400Matrix
{
    SpawnBoneRow rows[3];
};

struct Rva00413400Owner
{
    Rva00413400Owner();
    Rva00413400Matrix matrices[2];
    Coord3D points[4];
};

Rva00413400Owner::Rva00413400Owner() {}
