// cl: /DNDEBUG /Igame/Libraries/Source/WWVegas/WWLib /Igame/Libraries/Source/WWVegas/WW3D2 /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWSaveLoad /Igame/Libraries/Source/WWVegas/Wwutil /Igame/Libraries/Source/WWVegas/WWDownload /Igame/Libraries/Source/Compression /Igame/Libraries/Source/WWVegas/WWDebug /Iinputs/reference/shims/sweep

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
