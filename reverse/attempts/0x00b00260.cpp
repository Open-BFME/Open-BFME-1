// ?rva00B00260RotateVec3Array@@YAXPAVVector3@@PBV1@ABVMatrix3D@@H@Z
// partial score=0.96 date=2026-09-04
// cl: /DNDEBUG /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WW3D2 /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWSaveLoad /ICode/Libraries/Source/WWVegas/Wwutil /ICode/Libraries/Source/WWVegas/WWDownload /ICode/Libraries/Source/Compression /ICode/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep

#include "vector3.h"
#include "matrix3d.h"

class Rva00B00260MatrixView : public Matrix3D
{
public:
	static __forceinline void rotateArray(Vector3 *out, const Vector3 *in,
		const Matrix3D &matrix, int count)
	{
		const Rva00B00260MatrixView &m =
			(const Rva00B00260MatrixView &)matrix;
		while (count--)
		{
			float row0z = m.Row[0][2] * in->Z;
			out->X = row0z + m.Row[0][1] * in->Y + m.Row[0][0] * in->X;
			out->Y = (m.Row[1][0] * in->X + m.Row[1][1] * in->Y + m.Row[1][2] * in->Z);
			out->Z = (m.Row[2][0] * in->X + m.Row[2][1] * in->Y + m.Row[2][2] * in->Z);
			++in;
			++out;
		}
	}
};

void rva00B00260RotateVec3Array(Vector3 *out, const Vector3 *in,
	const Matrix3D &mtx, int count)
{
	int n = count;
	Vector3 *d = out;
	const Vector3 *s = in;

	if (n <= 0)
		return;

	Rva00B00260MatrixView::rotateArray(d, s, mtx, n);
}
