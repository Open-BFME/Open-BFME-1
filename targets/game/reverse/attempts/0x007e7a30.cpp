// ??0Matrix4D@@QAE@ABVCoord3D@@M@Z
// partial score=0.89 date=2026-09-27
// ??0Matrix4D@@QAE@ABVCoord3D@@M@Z
// cl: /DNDEBUG /Igame/Libraries/Source/WWVegas/WWMath
#include "matrix4d.h"

// Rodrigues axis-angle rotation about `v`. Byte target 0x007E7A30 len 247.
//
// Retail computes sine/cosine with a SINGLE x87 `fsincos` (D9 FB at +0x09)
// from one load of `angle`, and parks the two results in the two explicit
// stack slots [esp]=sine, [esp+4]=cosine. MSVC 7.1 has no route to that
// opcode from C++: `sincos` exists in this toolchain only as an x87 *mnemonic*
// in the c1/c1xx asm parsers and as an opcode name in c2, and 20 distinct
// sinf/cosf source shapes all emit a `fcos`+`fsin` pair with two loads of the
// argument (measured: 0/74 emitted functions contain D9 FB). So the five
// instructions below are the proven x87-shape exception, the same block
// game/Libraries/Source/WWVegas/WWMath/coord2d.cpp and
// game/GameEngine/Source/Common/SmallGaps/Rva008809E0Transform2D.cpp already
// carry. Everything after it is plain C++ and compiles to retail's bytes
// +0x00..+0xd0 exactly.
//
// The 26 bytes still missing are the five `values[11..15]` stores. Retail
// fills them into the x87 latency gaps of the `values[10]` diagonal --
// 1 after `fld [1.0]`, 3 after `fsub st(1)`, 1 after `fmul` -- while this
// toolchain emits the chain contiguously and appends the stores. The fill
// comes back the moment sine/cosine are `volatile` (or come from sinf/cosf),
// but then the single `fsub dword ptr [esp+4]` at +0x36 that retail relies on
// for the CSE of `1.0f - cosine` is lost, and the body diverges earlier. Both
// properties cannot be had at once from this compiler.
Matrix4D::Matrix4D(const Coord3D &v, float angle)
{
    float sine;
    float cosine;
    __asm {
        fld angle
        fsincos
        fstp cosine
        fstp sine
    }

    values[0] = v.x * v.x + cosine * (1.0f - v.x * v.x);
    values[1] = v.x * v.y * (1.0f - cosine) - v.z * sine;
    values[2] = v.z * (v.x * (1.0f - cosine)) + v.y * sine;
    values[3] = 0.0f;

    values[4] = v.x * v.y * (1.0f - cosine) + v.z * sine;
    values[5] = v.y * v.y + cosine * (1.0f - v.y * v.y);
    values[6] = v.z * (v.y * (1.0f - cosine)) - v.x * sine;
    values[7] = 0.0f;

    values[8] = v.z * (v.x * (1.0f - cosine)) - v.y * sine;
    values[9] = v.z * (v.y * (1.0f - cosine)) + v.x * sine;
    values[10] = v.z * v.z + cosine * (1.0f - v.z * v.z);
    values[11] = 0.0f;
    values[12] = 0.0f;
    values[13] = 0.0f;
    values[14] = 0.0f;
    values[15] = 1.0f;
}
