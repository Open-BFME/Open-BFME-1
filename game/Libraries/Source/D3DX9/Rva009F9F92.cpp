// cl: /O2 /MD /Oi
// Original d3dxmath.obj code COMDATs independently delimit all four bodies.
// See identity_evidence/009f9f92-native-float-helpers.md.
#include <math.h>
#pragma intrinsic(atan2, fabs, sin, sqrt)
float __stdcall Rva009F9F92(float y, float x) { return (float)atan2(y, x); }
float __stdcall Rva009F9FB6(float x) { return (float)fabs(x); }
float __stdcall Rva009F9FD2(float x) { return (float)sin(x); }
float __stdcall Rva009F9FEC(float x) { return (float)sqrt(x); }
