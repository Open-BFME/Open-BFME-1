// Full retail 0x007331F0..0x007333AC (444 bytes), including all RET 12 tails.
// Address-derived owner; retail proves (key, direction, float speed), with
// a type-data pointer at +0x20 in each 0x5C-byte type record. The old bank
// treated the third argument and that pointer incorrectly.
// The force-application sequence follows the ZH applyTopplingForce twin,
// with BFME's owner lookup, terrain override, extra guard and changed byte.
// Native inline lookup plus separate failure guards preserves retail tails.
//
// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims
#include "matrix3d.h"

typedef bool Bool;
typedef int Int;
typedef float Real;

struct Coord3D
{
    Real x;
    Real y;
    Real z;

    void set(Real px, Real py, Real pz)
    {
        x = px;
        y = py;
        z = pz;
    }

    void normalize(void);
};

class FXList
{
public:
    Bool bfmeIsBlocked(void);
    void doFXPos(const Coord3D *position, const Matrix3D *transform,
        Real speed, const Coord3D *secondary) const;
};

struct Rva003FD060TerrainLogic;
extern Rva003FD060TerrainLogic *TheTerrainLogic;
extern const Real BfmeZeroRange;

struct Rva007331F0TypeData
{
    unsigned char pad00[0x20];
    FXList *fx;
    unsigned char pad24[8];
    Real factor2c;
    Real factor30;
    unsigned char pad34[4];
    Real defaultHeight;
    unsigned char pad3c[0x20];
};

struct Rva007331F0Type
{
    unsigned char pad00[0x20];
    Rva007331F0TypeData *data;
    unsigned char pad24[0x38];
};

struct Rva007331F0Record
{
    Vector3 location;
    unsigned char pad0c[0x34];
    Int type;
    unsigned char pad44[0x14];
    void *key;
    unsigned char pad5c[0x10];
    Real height6c;
    Real height70;
    Coord3D direction;
    Int guard80;
    Int field84;
    Int field88;
    Int field8c;
    Matrix3D matrix;
    unsigned char padc0[8];
    void *guardc8;
    unsigned char padcc[0x1c];
};

class Rva007331F0
{
public:
    Bool method(void *key, const Coord3D *direction, Real height);

    __forceinline Rva007331F0Record *find(void *key)
    {
        for (Int i = 0; i < count; ++i)
        {
            if (records[i].key == key)
                return records + i;
        }
        return 0;
    }

private:
    unsigned char pad000[0x1b0];
    Rva007331F0Record records[12000];
    Int count;
    unsigned char pad2a7cb4[1];
    unsigned char changed;
    unsigned char pad2a7cb6[6];
    Rva007331F0Type types[64];
};

Bool Rva007331F0::method(void *key, const Coord3D *direction, Real height)
{
    if (!key)
        return false;

    Rva007331F0Record *record = find(key);
    if (!record)
        return false;
    if (record->guard80)
        return false;
    if (record->guardc8)
        return false;

    const Rva007331F0TypeData *typeData = types[record->type].data;
    Real terrainHeight = *(Real *)((unsigned char *)TheTerrainLogic + 0x18f8);
    if (terrainHeight > BfmeZeroRange)
        height = terrainHeight;
    else if (height < typeData->defaultHeight)
        height = typeData->defaultHeight;

    record->direction = *direction;
    record->direction.normalize();
    record->field84 = 0;
    record->height6c = height * typeData->factor2c;
    record->height70 = height * typeData->factor30;
    record->guard80 = 1;
    record->field8c = 0;

    Coord3D position;
    position.set(record->location.X, record->location.Y, record->location.Z);
    FXList *fx = typeData->fx;
    if (fx && !fx->bfmeIsBlocked())
        fx->doFXPos(&position, 0, 0.0f, 0);

    changed = 1;
    record->matrix.Make_Identity();
    record->matrix.Set_Translation(record->location);
    return true;
}
