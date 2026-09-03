// cl: /DNDEBUG /MD /EHsc /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/shims/sweep
// Clean reconstruction of the retail AABoxClass point-array constructor at
// 0x007A0DF0.  The body is the shipped WWMath AABoxClass::Init(Vector3*,int)
// inlined into the constructor.

#include "vector3.h"

class AABoxClass
{
public:
	AABoxClass(Vector3 *points, int num);

	Vector3 Center;
	Vector3 Extent;
};

AABoxClass::AABoxClass(Vector3 *points, int num)
{
	Vector3 Min = points[0];
	Vector3 Max = points[0];

	for (int i = 1; i < num; ++i) {
		if (Min.X > points[i].X) Min.X = points[i].X;
		if (Min.Y > points[i].Y) Min.Y = points[i].Y;
		if (Min.Z > points[i].Z) Min.Z = points[i].Z;

		if (Max.X < points[i].X) Max.X = points[i].X;
		if (Max.Y < points[i].Y) Max.Y = points[i].Y;
		if (Max.Z < points[i].Z) Max.Z = points[i].Z;
	}

	Center = (Max + Min) * 0.5f;
	Extent = (Max - Min) * 0.5f;
}
