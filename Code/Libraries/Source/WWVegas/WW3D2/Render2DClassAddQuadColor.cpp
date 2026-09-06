// cl: /DNDEBUG /MD /EHsc
// readable body of ?Add_Quad@Render2DClass@@QAEXABVRectClass@@K@Z: Code/Libraries/Source/WWVegas/WW3D2/render2d.cpp
// BFME Render2DClass single-color rectangle overload, retail 0x006E73C0.
// Hardcoded UV (0,0)-(1,1); sibling of the six-color body in Render2DClassAddQuad.cpp.
//
// upstream: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/render2d.cpp
//   void Render2DClass::Add_Quad(const RectClass &screen, unsigned long color)

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
	void Add_Quad(const RectClass &screen, BfmeUInt32 color);
};

void Render2DClass::Add_Quad(const RectClass &screen, BfmeUInt32 color)
{
	BfmeUInt32 baseVertexPair;
	BfmeUInt32 *indices;
	BfmeRenderVertex *vertices = allocateGeometry006e(4, 6, &indices, &baseVertexPair);

	convertPosition006e(vertices[0], screen.Left, screen.Top);
	vertices[0].z = g_BfmeRender2DZ;
	convertPosition006e(vertices[1], screen.Left, screen.Bottom);
	vertices[1].z = g_BfmeRender2DZ;
	convertPosition006e(vertices[2], screen.Right, screen.Top);
	vertices[2].z = g_BfmeRender2DZ;
	convertPosition006e(vertices[3], screen.Right, screen.Bottom);
	vertices[3].z = g_BfmeRender2DZ;

	vertices[0].u = vertices[1].u = vertices[0].v = vertices[2].v = 0.0f;
	vertices[2].u = vertices[3].u = vertices[1].v = vertices[3].v = 1.0f;

	vertices[0].color = vertices[1].color = vertices[2].color = vertices[3].color =
		g_BfmeColorConverter(color);

	indices[0] = baseVertexPair + 0x00010000;
	indices[1] = baseVertexPair + 0x00020002;
	indices[2] = baseVertexPair + 0x00030001;
}
