// ?Add_Line@Render2DClass@@QAEXABVVector2@@0MK@Z
// partial score=0.71 date=2026-09-04
// cl: /DNDEBUG /MD /EHsc
// Render2DClass::Add_Line(const Vector2&, const Vector2&, float, unsigned long)
// retail 0x006E7530 / 435B. Inlined BFME Add_Quad with UV (0,0)-(1,1).
// Dump sibling of six-color Add_Quad at 0x006E7210 in Code/gen_asm/d_006e0580.asm.
// upstream: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/render2d.cpp

class Vector2
{
public:
	float X;
	float Y;
};

class WWMath
{
public:
	static float __fastcall Inv_Sqrt(float a);
};

typedef unsigned long BfmeUInt32;

struct BfmeRenderVertex
{
	float x;
	float y;
	float z;
	unsigned char m_unmodelled_0C[0x0C];
	BfmeUInt32 color;
	float u;
	float v;
	unsigned char m_unmodelled_24[0x08];
};

typedef BfmeUInt32 (__cdecl *BfmeColorConverter)(BfmeUInt32 color);

extern "C" float g_BfmeRender2DZ;
extern "C" BfmeColorConverter g_BfmeColorConverter;

class Render2DClass
{
public:
	void Add_Line(const Vector2 &a, const Vector2 &b, float width, BfmeUInt32 color);

private:
	unsigned char m_unmodelled_00[0x04];
	float m_coordinateScaleX;
	float m_coordinateScaleY;
	float m_biasedCoordinateOffsetX;
	float m_biasedCoordinateOffsetY;

	BfmeRenderVertex *allocateGeometry006e(
		unsigned int vertexCount,
		unsigned int indexCount,
		BfmeUInt32 **indices,
		BfmeUInt32 *baseVertexPair);

	void convertPosition006e(BfmeRenderVertex &vertex, float x, float y)
	{
		vertex.x = x * m_coordinateScaleX + m_biasedCoordinateOffsetX;
		vertex.y = y * m_coordinateScaleY + m_biasedCoordinateOffsetY;
	}
};

void Render2DClass::Add_Line(const Vector2 &a, const Vector2 &b, float width, BfmeUInt32 color)
{
	float offsetX = a.Y - b.Y;
	float offsetY = b.X - a.X;
	float len2 = offsetX * offsetX + offsetY * offsetY;
	if (len2 != 0.0f) {
		float scale = WWMath::Inv_Sqrt(len2) * (width * 0.5f);
		offsetX *= scale;
		offsetY *= scale;
	}

	BfmeUInt32 baseVertexPair;
	BfmeUInt32 *indices;
	BfmeRenderVertex *vertices = allocateGeometry006e(4, 6, &indices, &baseVertexPair);

	convertPosition006e(vertices[0], a.X - offsetX, a.Y - offsetY);
	vertices[0].z = g_BfmeRender2DZ;
	convertPosition006e(vertices[1], a.X + offsetX, a.Y + offsetY);
	vertices[1].z = g_BfmeRender2DZ;
	convertPosition006e(vertices[2], b.X - offsetX, b.Y - offsetY);
	vertices[2].z = g_BfmeRender2DZ;
	convertPosition006e(vertices[3], b.X + offsetX, b.Y + offsetY);
	vertices[3].z = g_BfmeRender2DZ;

	vertices[0].v = vertices[2].v = 0.0f;
	vertices[1].v = vertices[3].v = 1.0f;
	vertices[0].u = vertices[1].u = 0.0f;
	vertices[2].u = vertices[3].u = 1.0f;

	vertices[0].color = vertices[1].color = vertices[2].color = vertices[3].color =
		g_BfmeColorConverter(color);

	indices[0] = baseVertexPair + 0x00010000;
	indices[1] = baseVertexPair + 0x00020002;
	indices[2] = baseVertexPair + 0x00030001;
}
