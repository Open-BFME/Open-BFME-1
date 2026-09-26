// cl: /DNDEBUG /MD /EHsc
// Render2DClass::Add_Line(const Vector2&, const Vector2&, float, unsigned long)
// Retail body at RVA 0x006E7530, with the BFME vertex batch layout.

extern "C" void __cdecl _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class WWMath
{
public:
	static float __fastcall Inv_Sqrt(float a);
};

class Vector2
{
public:
	float X;
	float Y;

	float Length2() const
	{
		return (X * X + Y * Y);
	}

	void Normalize()
	{
		float len2 = Length2();
		if (len2 != 0.0f) {
			float oolen = WWMath::Inv_Sqrt(len2);
			X *= oolen;
			Y *= oolen;
		}
	}

	Vector2 &operator*=(float k)
	{
		X = (float)(X * k);
		Y = (float)(Y * k);
		return *this;
	}
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

public:
	void Add_Line(const Vector2 &a, const Vector2 &b, float width, BfmeUInt32 color);
	void Add_Line(const Vector2 &a, const Vector2 &b, float width, BfmeUInt32 color, BfmeUInt32 color2);
};

void Render2DClass::Add_Line(const Vector2 &a, const Vector2 &b, float width, BfmeUInt32 color)
{
	Vector2 corner_offset;
	corner_offset.X = a.Y - b.Y;
	corner_offset.Y = b.X - a.X;
	float len2 = corner_offset.Length2();
	BfmeUInt32 baseVertexPair;
	BfmeUInt32 *indices;
	BfmeRenderVertex *vertices;
	if (*(volatile const float *)0x01075350 == len2)
		return;

	float oolen = WWMath::Inv_Sqrt(len2);
	oolen *= width;
	oolen *= *(const float *)0x0107533c;
	corner_offset.X *= oolen;
	corner_offset.Y = (*(volatile float *)&corner_offset.Y) * oolen;

	vertices = allocateGeometry006e(4, 6, &indices, &baseVertexPair);

	convertPosition006e(vertices[0], a.X - corner_offset.X, a.Y - corner_offset.Y);
	vertices[0].z = g_BfmeRender2DZ;
	convertPosition006e(vertices[1], a.X + corner_offset.X, a.Y + corner_offset.Y);
	vertices[1].z = g_BfmeRender2DZ;
	convertPosition006e(vertices[2], b.X - corner_offset.X, b.Y - corner_offset.Y);
	vertices[2].z = g_BfmeRender2DZ;
	convertPosition006e(vertices[3], b.X + corner_offset.X, b.Y + corner_offset.Y);
	vertices[3].z = g_BfmeRender2DZ;

	vertices[0].u = vertices[1].u = vertices[0].v = vertices[2].v = 0.0f;
	vertices[3].v = 1.0f;
	_ReadWriteBarrier();
	vertices[2].u = vertices[3].u = vertices[1].v = 1.0f;

	vertices[0].color = vertices[1].color = vertices[2].color = vertices[3].color =
		g_BfmeColorConverter(color);

	indices[0] = baseVertexPair + 0x00010000;
	indices[1] = baseVertexPair + 0x00020002;
	indices[2] = baseVertexPair + 0x00030001;
}

// ?Add_Line@Render2DClass@@QAEXABVVector2@@0MKK@Z
// Retail 0x006E7750, the two-colour overload (render2d.h:141): identical to the
// one-colour body above except the a-end vertices take color and the b-end
// vertices color2, and it returns 0x14. Pinned as the W3DDisplay two-colour
// drawLine callee through ILT 0x004409E4.
void Render2DClass::Add_Line(const Vector2 &a, const Vector2 &b, float width, BfmeUInt32 color, BfmeUInt32 color2)
{
	Vector2 corner_offset;
	corner_offset.X = a.Y - b.Y;
	corner_offset.Y = b.X - a.X;
	float len2 = corner_offset.Length2();
	BfmeUInt32 baseVertexPair;
	BfmeUInt32 *indices;
	BfmeRenderVertex *vertices;
	if (*(volatile const float *)0x01075350 == len2)
		return;

	float oolen = WWMath::Inv_Sqrt(len2);
	oolen *= width;
	oolen *= *(const float *)0x0107533c;
	corner_offset.X *= oolen;
	corner_offset.Y = (*(volatile float *)&corner_offset.Y) * oolen;

	vertices = allocateGeometry006e(4, 6, &indices, &baseVertexPair);

	convertPosition006e(vertices[0], a.X - corner_offset.X, a.Y - corner_offset.Y);
	vertices[0].z = g_BfmeRender2DZ;
	convertPosition006e(vertices[1], a.X + corner_offset.X, a.Y + corner_offset.Y);
	vertices[1].z = g_BfmeRender2DZ;
	convertPosition006e(vertices[2], b.X - corner_offset.X, b.Y - corner_offset.Y);
	vertices[2].z = g_BfmeRender2DZ;
	convertPosition006e(vertices[3], b.X + corner_offset.X, b.Y + corner_offset.Y);
	vertices[3].z = g_BfmeRender2DZ;

	vertices[0].u = vertices[1].u = vertices[0].v = vertices[2].v = 0.0f;
	vertices[3].v = 1.0f;
	_ReadWriteBarrier();
	vertices[2].u = vertices[3].u = vertices[1].v = 1.0f;

	vertices[0].color = vertices[1].color = g_BfmeColorConverter(color);
	vertices[2].color = vertices[3].color = g_BfmeColorConverter(color2);

	indices[0] = baseVertexPair + 0x00010000;
	indices[1] = baseVertexPair + 0x00020002;
	indices[2] = baseVertexPair + 0x00030001;
}
