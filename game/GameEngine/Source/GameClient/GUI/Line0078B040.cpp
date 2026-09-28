// cl: /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath
#include "wwmath.h"
#pragma intrinsic(fabs)
struct LinePoint0078B040 { float x,y; };
struct LineVertex0078B040 { float x,y,z; unsigned color; float field10[4]; };
// Retail RVA 0x0078B040: six 32-byte vertices form the two triangles of a line.
// Caller 0x00785300 routes through ILT 0x00046105. No semantic owner is proved.
// Explicit volatile reads retain the witnessed x87 rounding/load order.
// ECX is unused. EDX carries the writable cursor; four stack arguments (RET16).
void __fastcall emitLine0078B040(void *, LineVertex0078B040 **cursor,
 const LinePoint0078B040 &a, const LinePoint0078B040 &b, float width, unsigned color)
{
 if (!*cursor) return;
 LinePoint0078B040 delta;
 delta.x=a.y-b.y;
 delta.y=b.x-a.x;
 float length=delta.x*delta.x+delta.y*delta.y;
 if ((float)fabs((float)(length<=0.0001f))!=0.0f) { delta.x=0.0f; delta.y=0.0f; }
 else { length=WWMath::Inv_Sqrt(length)*width*0.5f; delta.x=*(volatile float*)&delta.x*length; delta.y=*(volatile float*)&delta.y*length; }
 (*cursor)->x=a.x-delta.x; (*cursor)->y=a.y-delta.y; (*cursor)->z=0.0f; (*cursor)->color=color; ++*cursor;
 (*cursor)->x=a.x+delta.x; (*cursor)->y=a.y+delta.y; (*cursor)->z=0.0f; (*cursor)->color=color; ++*cursor;
 (*cursor)->x=b.x-delta.x; (*cursor)->y=b.y-delta.y; (*cursor)->z=0.0f; (*cursor)->color=color; ++*cursor;
 (*cursor)->x=b.x-delta.x; (*cursor)->y=b.y-delta.y; (*cursor)->z=0.0f; (*cursor)->color=color; ++*cursor;
 (*cursor)->x=a.x+delta.x; (*cursor)->y=a.y+delta.y; (*cursor)->z=0.0f; (*cursor)->color=color; ++*cursor;
 (*cursor)->x=b.x+delta.x; (*cursor)->y=b.y+delta.y; (*cursor)->z=0.0f; (*cursor)->color=color; ++*cursor;
}
