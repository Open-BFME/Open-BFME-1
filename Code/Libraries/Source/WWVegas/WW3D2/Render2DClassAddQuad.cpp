// cl: /DNDEBUG /MD /EHsc
// readable body of ?Add_Quad@Render2DClass@@: Code/Libraries/Source/WWVegas/WW3D2/render2d.cpp
// BFME Render2DClass six-color rectangle overload, retail 0x006E7210.
//
// BFME's renderer stores a 0x2c-byte vertex in its active batch.  The
// vendored Render2DClass declaration describes the later vector-based
// renderer, so this TU keeps the older layout local while preserving the
// public Render2DClass symbol and call signature.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath/rect.h
class RectClass
{
	public:
	float Left;
	float Top;
	float Right;
	float Bottom;
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/render2d.h
class Render2DClass
{
private:
	unsigned char m_unmodelled_00[0x04];
	float m_coordinateScaleX;
	float m_coordinateScaleY;
	float m_biasedCoordinateOffsetX;
	float m_biasedCoordinateOffsetY;
	unsigned char m_unmodelled_14[0x40];
	unsigned char m_texturingEnabled;

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
	void Add_Quad(const RectClass &screen, const RectClass &uv,
		BfmeUInt32 color0, BfmeUInt32 color1,
		BfmeUInt32 color2, BfmeUInt32 color3);
};

// ?Add_Quad@Render2DClass@@QAEXABVRectClass@@0KKKK@Z
void Render2DClass::Add_Quad(const RectClass &screen, const RectClass &uv,
	BfmeUInt32 color0, BfmeUInt32 color1,
	BfmeUInt32 color2, BfmeUInt32 color3)
{
	BfmeUInt32 baseVertexPair;
	BfmeUInt32 *indices;
	BfmeRenderVertex *vertices = allocateGeometry006e(
		4, 6, &indices, &baseVertexPair);

	convertPosition006e(vertices[0], screen.Left, screen.Top);
	vertices[0].z = g_BfmeRender2DZ;
	convertPosition006e(vertices[1], screen.Left, screen.Bottom);
	vertices[1].z = g_BfmeRender2DZ;
	convertPosition006e(vertices[2], screen.Right, screen.Top);
	vertices[2].z = g_BfmeRender2DZ;
	convertPosition006e(vertices[3], screen.Right, screen.Bottom);
	vertices[3].z = g_BfmeRender2DZ;

	vertices[0].u = vertices[1].u = uv.Left;
	vertices[2].u = vertices[3].u = uv.Right;
	vertices[0].v = vertices[2].v = uv.Top;
	vertices[1].v = vertices[3].v = uv.Bottom;

	vertices[0].color = g_BfmeColorConverter(color0);
	vertices[1].color = g_BfmeColorConverter(color2);
	vertices[2].color = g_BfmeColorConverter(color1);
	vertices[3].color = g_BfmeColorConverter(color3);

	indices[0] = baseVertexPair + 0x00010000;
	indices[1] = baseVertexPair + 0x00020002;
	indices[2] = baseVertexPair + 0x00030001;
}
