// cl: /DNDEBUG /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep

#include "vector3.h"
#include "matrix3d.h"

class Rva00B00260MatrixView : public Matrix3D
{
public:
	__forceinline void rotateArray(const Vector3 *in, Vector3 *out, int count) const
	{
		while (count--)
		{
			out->X = (Row[0].X * in->X + Row[0].Y * in->Y + Row[0].Z * in->Z);
			out->Y = (Row[1].X * in->X + Row[1].Y * in->Y + Row[1].Z * in->Z);
			out->Z = (Row[2].X * in->X + Row[2].Y * in->Y + Row[2].Z * in->Z);
			++in;
			++out;
		}
	}
};

void rva00B00260RotateVec3Array(Vector3 *out, const Vector3 *in,
	const Matrix3D &mtx, int count)
{
	if (count <= 0)
		return;

	((const Rva00B00260MatrixView &)mtx).rotateArray(in, out, count);
}
