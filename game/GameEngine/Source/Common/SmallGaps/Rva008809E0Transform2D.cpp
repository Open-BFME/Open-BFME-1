// Retail 0x008809E0 uses fsincos; MSVC does not fuse separate sin/cos calls.
// The small x87 block is the proven codegen exception for this constructor.
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
	float c;
	float sine;
	__asm {
		fld angle
		fsincos
		fstp c
		fstp sine
	}
	m_negSin = -sine;
	m_a = a;
	m_b = b;
	m_cos = c;
	m_sin = sine;
	m_cos2 = c;
}
