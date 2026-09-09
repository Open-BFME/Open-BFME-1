// ?doLighting@W3DTreeBuffer@@QBEIPBUVector3@@000II@Z
// partial score=0.92 date=2026-09-08
// Retail 0x00732700 is the unused dynamic-lighting helper from W3DTreeBuffer.cpp.
// The body uses three precomputed light rays and their RGB values.

typedef float Real;
typedef unsigned int UnsignedInt;

struct Vector3
{
	Real X;
	Real Y;
	Real Z;

	static Real Dot_Product(const Vector3 &a, const Vector3 &b)
	{
		return a.X * b.X + a.Y * b.Y + a.Z * b.Z;
	}

};

#define g_bfmeScaleB3 (*(Real *)0x01084068)

class WWMath
{
	public:
	static Real Fabs(Real value)
	{
		int bits = *(int *)&value;
		bits &= 0x7fffffff;
		return *(Real *)&bits;
	}

	static int Float_To_Long(Real value)
	{
		int result;
		__asm {
			fld [value]
			fistp [result]
		}
		return result;
	}
};

class W3DTreeBuffer
{
public:
	UnsignedInt doLighting(const Vector3 *normal, const Vector3 *shade,
		const Vector3 *light, const Vector3 *diffuse,
		UnsignedInt vertexDiffuse, UnsignedInt alpha) const;
};

UnsignedInt W3DTreeBuffer::doLighting(const Vector3 *normal,
	const Vector3 *shade, const Vector3 *light, const Vector3 *diffuse,
	UnsignedInt vertexDiffuse, UnsignedInt alpha) const
{
	Vector3 shadeValue = *shade;
	Real lighting;

	lighting = Vector3::Dot_Product(light[0], *normal);
	lighting = WWMath::Fabs(lighting);
	shadeValue.X += lighting * diffuse[0].X;
	shadeValue.Y += lighting * diffuse[0].Y;
	shadeValue.Z += lighting * diffuse[0].Z;

	lighting = Vector3::Dot_Product(light[1], *normal);
	lighting = WWMath::Fabs(lighting);
	shadeValue.X += lighting * diffuse[1].X;
	shadeValue.Y += lighting * diffuse[1].Y;
	shadeValue.Z += lighting * diffuse[1].Z;

	lighting = Vector3::Dot_Product(light[2], *normal);
	lighting = WWMath::Fabs(lighting);
	shadeValue.X += lighting * diffuse[2].X;
	shadeValue.Y += lighting * diffuse[2].Y;
	shadeValue.Z += lighting * diffuse[2].Z;

	UnsignedInt red;
	UnsignedInt blue;
	UnsignedInt green;
	red = WWMath::Float_To_Long(shadeValue.X * g_bfmeScaleB3);
	green = WWMath::Float_To_Long(shadeValue.Y * g_bfmeScaleB3);
	blue = WWMath::Float_To_Long(shadeValue.Z * g_bfmeScaleB3);

	if (vertexDiffuse != 0xFFFFFFFF) {
		red = ((vertexDiffuse >> 16) & 0xFF) * red >> 8;
		green = ((vertexDiffuse >> 8) & 0xFF) * green >> 8;
		blue = (vertexDiffuse & 0xFF) * blue >> 8;
	}
	if (red > 0xFF) red = 0xFF;
	if (green > 0xFF) green = 0xFF;
	if (blue > 0xFF) blue = 0xFF;
	return (alpha << 24) | (red << 16) | (green << 8) | blue;
}
