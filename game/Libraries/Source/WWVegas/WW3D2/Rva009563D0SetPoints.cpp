// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WWMath /Iinputs/reference/shims/sweep
#include "vector3.h"
#include "simplevec.h"
// Retail 009563D0: two SimpleDynVec fields at C8 and D8, then a
// bounding-volume invalidation at 10. Owner identity remains unproven.
class Rva009563D0PointArrays {
 char pad_00[0x10];
 unsigned int field_10;
 char pad_14[0xb4];
 SimpleDynVecClass<Vector3> points_c8;
 SimpleDynVecClass<float> widths_d8;
public:
 void Set_Points(unsigned int count, Vector3 *points, float *widths);
};
void Rva009563D0PointArrays::Set_Points(unsigned int count, Vector3 *points, float *widths) {
 if (count < 2 || !points || !widths) return;
 points_c8.Delete_All();
 for (unsigned int i=0; i<count; ++i) points_c8.Add(points[i],count);
 widths_d8.Delete_All();
 for (unsigned int j=0; j<count; ++j) widths_d8.Add(widths[j],count);
 field_10 &= ~0x20000;
}
