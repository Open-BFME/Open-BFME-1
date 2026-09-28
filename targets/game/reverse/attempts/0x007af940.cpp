// ?projectRangesRva007AF940@@YAXABVVector3@@0MMMMAAVVector2@@1@Z
// partial score=0.915 date=2026-09-28
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Iinputs/reference/shims/sweep /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas
// File-static helpers of BFME's W3DProjectedShadow.cpp TU (retail
// 0x007AF710 / 0x007AF940), the eventual home of the projected-shadow
// family (callers 0x007B23F0 and 0x007B4FE0). MSVC 7.1 gives a file-static
// function whose address is not taken a private register convention when its
// caller is in the same TU: 0x007AF710 takes four stack floats and returns a
// Vector2 through a hidden pointer in ECX; 0x007AF940 takes axisA in ECX,
// axisB in EAX, xr in EDI, yr in ESI plus four stack floats, and its caller
// pops the stack. Both conventions come out of the compiler by themselves
// here (docs/shape_levers.md, "Compiler-private ABI").
// Types: the callers pass two adjacent 12-byte vectors (Vector3, frame of
// six 12-byte objects at 0x48) and zero two adjacent 8-byte outputs (Vector2).
// The names keep the address: no caller, string or Zero Hour twin names them.
#include "vector2.h"
#include "vector3.h"

static Vector2 minMax4Rva007AF710(float a, float b, float c, float d)
{
	float lo, hi;
	if (a < b) {
		lo = a;
		hi = b;
	} else {
		lo = b;
		hi = a;
	}
	if (c < d) {
		if (c < lo)
			lo = c;
		if (d > hi)
			hi = d;
	} else {
		if (d < lo)
			lo = d;
		if (c > hi)
			hi = c;
	}
	return Vector2(lo, hi);
}

static void projectRangesRva007AF940(const Vector3 &axisA, const Vector3 &axisB, float sizeA, float sizeB,
	float offA, float offB, Vector2 &xr, Vector2 &yr)
{
	Vector3 a0 = axisA * -((offA + 0.5f) * sizeA);
	Vector3 a1 = axisA * ((0.5f - offA) * sizeA);
	Vector3 b0 = axisB * -((offB + 0.5f) * sizeB);
	Vector3 b1 = axisB * ((0.5f - offB) * sizeB);
	Vector3 c0 = b0 + a0;
	Vector3 c1 = b0 + a1;
	Vector3 c2 = b1 + a1;
	Vector3 c3 = b1 + a0;
	xr = minMax4Rva007AF710(c0.X, c1.X, c2.X, c3.X);
	yr = minMax4Rva007AF710(c0.Y, c1.Y, c2.Y, c3.Y);
}

void exp7AF940Caller(const Vector3 &a, const Vector3 &b, float s0, float s1, float s2, float s3,
	Vector2 *out)
{
	Vector2 xr(0, 0), yr(0, 0);
	projectRangesRva007AF940(a, b, s0, s1, s2, s3, xr, yr);
	projectRangesRva007AF940(b, a, s1, s0, s3, s2, out[0], out[1]);
	out[2] = xr;
	out[3] = yr;
}
