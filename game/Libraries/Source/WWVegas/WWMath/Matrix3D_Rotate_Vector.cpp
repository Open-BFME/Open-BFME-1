// cl: /DNDEBUG /MD /G6 /EHsc
// BFME's matrix rotation array helper at retail 0x00924480.

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
	void Rotate_Vector(const Vector3 *in,
		Vector3 *out, int count) const;

	Vector4 Row[3];
};

void Matrix3D::Rotate_Vector(const Vector3 *in,
	Vector3 *out, int count) const
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
