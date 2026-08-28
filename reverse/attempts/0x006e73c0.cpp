// ?addRect006e@BfmeRender2D@@QAEXABUBfmeFloatRect@@H@Z
// partial score=0.98 date=2026-08-28
// cl: /DNDEBUG /MD /EHsc

struct BfmeFloatRect
{
	void set(float newLeft, float newTop, float newRight, float newBottom)
	{
		left = newLeft;
		top = newTop;
		right = newRight;
		bottom = newBottom;
	}

	float left;
	float top;
	float right;
	float bottom;
};

typedef unsigned int BfmeUInt32;

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

class BfmeRender2D
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
	void disableTexturing()
	{
		m_texturingEnabled = 0;
	}

	void addRect006e(const BfmeFloatRect &rect, int color);
};

// ?addRect006e@BfmeRender2D@@QAEXABUBfmeFloatRect@@H@Z
void BfmeRender2D::addRect006e(const BfmeFloatRect &rect, int color)
{
	BfmeUInt32 baseVertexPair;
	BfmeUInt32 *indices;
	BfmeRenderVertex *vertices = allocateGeometry006e(4, 6, &indices, &baseVertexPair);

	convertPosition006e(vertices[0], rect.left, rect.top);
	vertices[0].z = g_BfmeRender2DZ;
	convertPosition006e(vertices[1], rect.left, rect.bottom);
	vertices[1].z = g_BfmeRender2DZ;
	convertPosition006e(vertices[2], rect.right, rect.top);
	vertices[2].z = g_BfmeRender2DZ;
	convertPosition006e(vertices[3], rect.right, rect.bottom);
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

struct BfmeClipRegion
{
	int left;
	int top;
	int right;
	int bottom;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DDisplay.h
class W3DDisplay
{
private:
	unsigned char m_unmodelled_04[0x160];
	BfmeRender2D *m_render2D;
	BfmeClipRegion m_clipRegion;
	unsigned char m_clippingEnabled;

public:
	virtual void drawFillRect(float x, float y, float width, float height, int color);
};

// ?drawFillRect@W3DDisplay@@UAEXMMMMH@Z
void W3DDisplay::drawFillRect(float x, float y, float width, float height, int color)
{
	m_render2D->disableTexturing();

	BfmeFloatRect rect;
	float right;
	float bottom;
	if (m_clippingEnabled) {
		right = x + width - 1.0f;
		bottom = y + height - 1.0f;
		if (x < m_clipRegion.left) {
			x = static_cast<float>(m_clipRegion.left);
		}
		if (y < m_clipRegion.top) {
			y = static_cast<float>(m_clipRegion.top);
		}
		if (right > m_clipRegion.right) {
			right = static_cast<float>(m_clipRegion.right);
		}
		if (bottom > m_clipRegion.bottom) {
			bottom = static_cast<float>(m_clipRegion.bottom);
		}
		if (x > right || y > bottom) {
			return;
		}
		rect.set(x, y, right, bottom);
	} else {
		rect.set(x, y, x + width, y + height);
	}

	m_render2D->addRect006e(rect, color);
}
