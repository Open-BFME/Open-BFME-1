// ??0Rva008809E0Transform2D@@QAE@PBURva008809E0Vec2@@MHH@Z
// partial score=0.85 date=2026-09-06
#include <math.h>
struct Rva008809E0Vec2 { float x; float y; };
struct Rva008809E0Transform2D {
	float m_x; float m_y;
	float m_cos; float m_sin;
	float m_negSin; float m_cos2;
	int m_a; int m_b;
	Rva008809E0Transform2D(const Rva008809E0Vec2* pos, float angle, int a, int b);
};
Rva008809E0Transform2D::Rva008809E0Transform2D(const Rva008809E0Vec2* pos, float angle, int a, int b)
{
	m_x = pos->x;
	m_y = pos->y;
	double rad = angle;
	float c = (float)cos(rad);
	angle = (float)sin(rad);
	m_negSin = -angle;
	m_a = a;
	m_b = b;
	m_cos = c;
	m_sin = angle;
	m_cos2 = c;
}
