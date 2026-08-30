// cl: /DNDEBUG /MD /EHsc

typedef unsigned long UnsignedInt;

struct ICoord2D
{
	int x;
	int y;
};

struct IRegion2D
{
	ICoord2D lo;
	ICoord2D hi;
};

extern bool ClipLine2D(ICoord2D *p1, ICoord2D *p2, ICoord2D *c1,
	ICoord2D *c2, IRegion2D *clipRegion);

class Vector2
{
public:
	Vector2(float x, float y) : X(x), Y(y) {}

	float X;
	float Y;
};

class Render2DClass
{
private:
	unsigned char m_unmodelled_00[0x54];
	unsigned char m_texturingEnabled;

public:
	void Add_Line(const Vector2 &a, const Vector2 &b, float width,
		UnsignedInt color, UnsignedInt color2);
	void disableTexturing()
	{
		m_texturingEnabled = 0;
	}
};

class W3DDisplay
{
private:
	unsigned char m_unmodelled_04[0x160];
	Render2DClass *m_render2D;
	IRegion2D m_clipRegion;
	unsigned char m_clippingEnabled;

public:
	virtual void drawLine(float startX, float startY, float endX, float endY,
		float lineWidth, UnsignedInt lineColor1, UnsignedInt lineColor2);
};

// ?drawLine@W3DDisplay@@UAEXMMMMMKK@Z
void W3DDisplay::drawLine(float startX, float startY, float endX, float endY,
	float lineWidth, UnsignedInt lineColor1, UnsignedInt lineColor2)
{
	m_render2D->disableTexturing();

	if (m_clippingEnabled) {
		ICoord2D start, end, returnStart, returnEnd;
		start.x = (int)startX;
		start.y = (int)startY;
		end.x = (int)endX;
		end.y = (int)endY;
		if (ClipLine2D(&start, &end, &returnStart, &returnEnd, &m_clipRegion)) {
			m_render2D->Add_Line(Vector2(returnStart.x, returnStart.y),
				Vector2(returnEnd.x, returnEnd.y), lineWidth, lineColor1, lineColor2);
		}
	} else {
		m_render2D->Add_Line(Vector2(startX, startY), Vector2(endX, endY),
			lineWidth, lineColor1, lineColor2);
	}
}
