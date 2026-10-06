// Open-BFME5 conversions.

struct BfmeV1207
{
	int m_bfme00;
	int m_bfme04;
};

class BfmeA1207;

// ILT 0x00024BCC -> 0x006EB070, the matched Render2DClass::Add_Tri
// (Render2DClassAddTri.cpp; six const Vector2 references and an unsigned
// long colour, ret 0x1C). Retail copies each point into a temporary as two
// dwords before the call, so this TU's Vector2 view is two ints.
class Vector2
{
public:
	int m_bfme00;
	int m_bfme04;
};

class Render2DClass
{
public:
	void Add_Tri(const Vector2 &v0, const Vector2 &v1, const Vector2 &v2,
		const Vector2 &uv0, const Vector2 &uv1, const Vector2 &uv2,
		unsigned long color);
};

void bfmeGo1207(BfmeA1207 *o, const BfmeV1207 *a1, const BfmeV1207 *a2, const BfmeV1207 *a3,
	const BfmeV1207 *a4, const BfmeV1207 *a5, const BfmeV1207 *a6)
{
	((Render2DClass *)o)->Add_Tri(Vector2(*(const Vector2 *)a1), Vector2(*(const Vector2 *)a2),
		Vector2(*(const Vector2 *)a3), Vector2(*(const Vector2 *)a4),
		Vector2(*(const Vector2 *)a5), Vector2(*(const Vector2 *)a6), 0xFFFFFFFF);
}
