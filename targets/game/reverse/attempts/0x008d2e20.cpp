// ?bfmeApplyXS@BfmeThingXS@@QAEXPAX0@Z
// partial score=0.9 date=2026-09-28
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib /FAsc /Fabuild/luna4_008d2e20_order.cod
#include "vector2.h"

class BfmeThingXS
{
public:
	void bfmeApplyXS(void *, void *);
	void applyVector(const Vector2 &input, Vector2 &output) const
	{
		output.X = input.X * m_offset20.X + input.Y * m_offset28.X + m_offset30.X;
		output.Y = input.X * m_offset20.Y + input.Y * m_offset28.Y + m_offset30.Y;
	}

private:
	unsigned char m_pad000[0x20];
	Vector2 m_offset20;
	Vector2 m_offset28;
	Vector2 m_offset30;
};

void BfmeThingXS::bfmeApplyXS(void *what, void *sub)
{
	float *bounds = (float *)what;
	const float *input = (const float *)sub;
	Vector2 inputPoints[4];
	inputPoints[0].Set(input[0], input[1]);
	inputPoints[1].Set(input[2], input[1]);
	inputPoints[2].Set(input[2], input[3]);
	inputPoints[3].Set(input[0], input[3]);
	Vector2 points[4];
	applyVector(inputPoints[0], points[0]);
	applyVector(inputPoints[1], points[1]);
	applyVector(inputPoints[2], points[2]);
	applyVector(inputPoints[3], points[3]);

	if (points[0].X < bounds[0])
		bounds[0] = points[0].X;
	if (points[0].X > bounds[2])
		bounds[2] = points[0].X;
	if (points[0].Y < bounds[1])
		bounds[1] = points[0].Y;
	if (points[0].Y > bounds[3])
		bounds[3] = points[0].Y;
	if (points[1].X < bounds[0])
		bounds[0] = points[1].X;
	if (points[1].X > bounds[2])
		bounds[2] = points[1].X;
	if (points[1].Y < bounds[1])
		bounds[1] = points[1].Y;
	if (points[1].Y > bounds[3])
		bounds[3] = points[1].Y;
	if (points[2].X < bounds[0])
		bounds[0] = points[2].X;
	if (points[2].X > bounds[2])
		bounds[2] = points[2].X;
	if (points[2].Y < bounds[1])
		bounds[1] = points[2].Y;
	if (points[2].Y > bounds[3])
		bounds[3] = points[2].Y;
	if (points[3].X < bounds[0])
		bounds[0] = points[3].X;
	if (points[3].X > bounds[2])
		bounds[2] = points[3].X;
	if (points[3].Y < bounds[1])
		bounds[1] = points[3].Y;
	if (points[3].Y > bounds[3])
		bounds[3] = points[3].Y;
}
