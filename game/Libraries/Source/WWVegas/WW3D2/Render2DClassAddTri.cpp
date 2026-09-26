// cl: /DNDEBUG /MD /EHsc
// readable body of ?Add_Tri@Render2DClass@@: game/Libraries/Source/WWVegas/WW3D2/render2d.cpp
// BFME Render2DClass triangle overload, retail 0x006EB070.
//
// Sibling of Render2DClassAddQuad.cpp (Add_Quad, retail 0x006E7210): same
// active-batch vertex layout, allocateGeometry006e helper, coordinate
// conversion and color-converter global, just for three vertices instead of
// four, one shared color instead of per-vertex colors, and 16-bit indices
// written individually instead of packed as dword pairs.

class Vector2
{
public:
	float X;
	float Y;
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

typedef BfmeUInt32(__cdecl *BfmeColorConverter)(BfmeUInt32 color);

extern "C" float g_BfmeRender2DZ;
extern "C" BfmeColorConverter g_BfmeColorConverter;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/render2d.h
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

	void convertPosition006e(BfmeRenderVertex &vertex, const Vector2 &v)
	{
		vertex.x = v.X * m_coordinateScaleX + m_biasedCoordinateOffsetX;
		vertex.y = v.Y * m_coordinateScaleY + m_biasedCoordinateOffsetY;
	}

public:
	void Add_Tri(const Vector2 &v0, const Vector2 &v1, const Vector2 &v2,
		const Vector2 &uv0, const Vector2 &uv1, const Vector2 &uv2,
		BfmeUInt32 color);
};

// ?Add_Tri@Render2DClass@@QAEXABVVector2@@00000K@Z
void Render2DClass::Add_Tri(const Vector2 &v0, const Vector2 &v1, const Vector2 &v2,
	const Vector2 &uv0, const Vector2 &uv1, const Vector2 &uv2,
	BfmeUInt32 color)
{
	BfmeUInt32 baseVertexPair;
	BfmeUInt32 *indices;
	BfmeRenderVertex *vertices = allocateGeometry006e(
		3, 3, &indices, &baseVertexPair);

	convertPosition006e(vertices[0], v0);
	vertices[0].z = g_BfmeRender2DZ;
	convertPosition006e(vertices[1], v1);
	vertices[1].z = g_BfmeRender2DZ;
	convertPosition006e(vertices[2], v2);
	vertices[2].z = g_BfmeRender2DZ;

	vertices[0].u = uv0.X;
	vertices[0].v = uv0.Y;
	vertices[1].u = uv1.X;
	vertices[1].v = uv1.Y;
	vertices[2].u = uv2.X;
	vertices[2].v = uv2.Y;

	BfmeUInt32 convertedColor = g_BfmeColorConverter(color);
	vertices[2].color = convertedColor;
	vertices[1].color = convertedColor;
	vertices[0].color = convertedColor;

	reinterpret_cast<unsigned short *>(indices)[0] = (unsigned short)baseVertexPair;
	reinterpret_cast<unsigned short *>(indices)[1] = (unsigned short)baseVertexPair + 1;
	reinterpret_cast<unsigned short *>(indices)[2] = (unsigned short)baseVertexPair + 2;
}
