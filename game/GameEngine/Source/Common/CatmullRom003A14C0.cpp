// cl: /DNDEBUG /MD /EHsc /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug
#include "vector3.h"
// Retail 0x003A14C0, 829 bytes, cdecl with seven arguments. The original
// function name is unproved; keep the address in this behavioral name.
// Vector3's three-float layout and inline arithmetic reproduce every retail
// operation. Each polynomial term must be a separate local to retain the
// original x87 expression evaluation order and 0x78-byte frame.
//
// Preserve the existing callee pin below, including its legacy spelling.
// Despite that spelling, it is the Catmull-Rom import route: RVA 0x009FA11F
// jumps through VA 0x012DBEC0, initially VA 0x00DFA0F5, whose 42-byte body is
// the vendored d3dx9 init_D3DXVec3CatmullRom and ends in ret 0x18. This proves
// stdcall with six stack arguments; the inference-only cdecl hint is wrong.
// The opaque pointer types below are used solely for that established ABI.
struct BfmeVector3;
struct Coord3D;
extern BfmeVector3 *__stdcall bfmeVec3Hermite(BfmeVector3 *, const Coord3D *, const Coord3D *, const Coord3D *, const Coord3D *, float);
void catmullRom003A14C0(Vector3 *out, const Vector3 *p0, const Vector3 *p1, const Vector3 *p2, const Vector3 *p3, float t, bool imported)
{
    if (imported) {
        bfmeVec3Hermite((BfmeVector3*)out, (const Coord3D*)p0, (const Coord3D*)p1, (const Coord3D*)p2, (const Coord3D*)p3, t);
        return;
    }
    float t2 = t*t;
    float t3 = t*t2;
    Vector3 a = *p0, b = *p1, c = *p2, d = *p3;
    Vector3 q0 = 2.0f*b;
    Vector3 q1 = (c-a)*t;
    Vector3 q2 = (2.0f*a-5.0f*b+4.0f*c-d)*t2;
    Vector3 q3 = (3.0f*b-a-3.0f*c+d)*t3;
    *out = (q0+q1+q2+q3)*0.5f;
}
