// cl: /DNDEBUG /MD /G6 /EHsc
// BFME's two-array matrix transform helper at retail 0x009244F0.

class Vector3
{
public:
	float X;
	float Y;
	float Z;
};

class Vector4
{
public:
	float X;
	float Y;
	float Z;
	float W;
};

class Matrix3D
{
public:
	void Transform_Vector(const Vector3 *in0, const Matrix3D &matrix,
		const Vector3 *in1, Vector3 *out, int count) const;

	Vector4 Row[3];
};

void Matrix3D::Transform_Vector(const Vector3 *in0, const Matrix3D &matrix,
	const Vector3 *in1, Vector3 *out, int count) const
{
	while (count--)
	{
		out->X = Row[0].X * in0->X + Row[0].Y * in0->Y + Row[0].Z * in0->Z
			+ matrix.Row[0].X * in1->X + matrix.Row[0].Y * in1->Y + matrix.Row[0].Z * in1->Z;
		out->Y = Row[1].X * in0->X + Row[1].Y * in0->Y + Row[1].Z * in0->Z
			+ matrix.Row[1].X * in1->X + matrix.Row[1].Y * in1->Y + matrix.Row[1].Z * in1->Z;
		out->Z = Row[2].X * in0->X + Row[2].Y * in0->Y + Row[2].Z * in0->Z
			+ matrix.Row[2].X * in1->X + matrix.Row[2].Y * in1->Y + matrix.Row[2].Z * in1->Z;
		++in0;
		++in1;
		++out;
	}
}
