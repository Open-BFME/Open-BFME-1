// ?extrapolate@Rva003A1D00Owner@@QAEXXZ
// partial score=0.0826 date=2026-10-10
// cl: /DNDEBUG /MD /EHsc /Iinputs/toolchains/dx81/include /Iinputs/toolchains/vs2003/PROGRA~1/MICROS~1.NET/Vc7/PlatformSDK/Include /Igame/Libraries/Include /Igame/Libraries/Source/WWVegas /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWDebug
#include "vector3.h"
#include <math.h>

extern const float Rva00C75350Zero;
extern const float Rva00C75334One;

// A float view of the witnessed element; its nominal type is unknown.
struct Rva003A1D00Element
{
    char pad00[0xa4];
    Vector3 point;
    char padb0[8];
};

struct Rva003A1D00Range
{
    Rva003A1D00Element *first;
    Rva003A1D00Element *last;
    // ?size@Rva003A1D00Range@@QBEIXZ absent-from-retail
    unsigned int size() const { return (unsigned int)(last - first); }
    // ??ARva003A1D00Range@@QAEAAURva003A1D00Element@@I@Z absent-from-retail
    Rva003A1D00Element &operator[](unsigned int index) { return first[index]; }
};

class Rva003A1D00Owner
{
public:
    void extrapolate();
    char pad00[0x2c];
    Rva003A1D00Range entries;
};

// ?length003A1D00@@YAMABVVector3@@@Z absent-from-retail
static inline float length003A1D00(const Vector3 &value)
{
    return (float)sqrt(value.X * value.X + value.Y * value.Y + value.Z * value.Z);
}

// ?normalize003A1D00@@YAXAAVVector3@@@Z absent-from-retail
static inline void normalize003A1D00(Vector3 &value)
{
    float length = length003A1D00(value);
    if (length != Rva00C75350Zero)
        value *= Rva00C75334One / length;
}

// ?extrapolate@Rva003A1D00Owner@@QAEXXZ present-unmatched
void Rva003A1D00Owner::extrapolate()
{
    Vector3 nearPoint = entries[1].point;
    float distance = length003A1D00(nearPoint - entries[2].point);
    Vector3 direction = nearPoint - entries[0].point;
    normalize003A1D00(direction);
    entries[0].point = nearPoint - direction * distance;

    nearPoint = entries[entries.size() - 2].point;
    distance = length003A1D00(nearPoint - entries[entries.size() - 3].point);
    direction = nearPoint - entries[entries.size() - 1].point;
    normalize003A1D00(direction);
    entries[entries.size() - 1].point = nearPoint - direction * distance;
}
