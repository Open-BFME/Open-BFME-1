// cl: /DNDEBUG /MD /EHsc

typedef unsigned long UnsignedInt;

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
		UnsignedInt color);
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

public:
	virtual void drawLine(float startX, float startY, float endX, float endY,
		float lineWidth, UnsignedInt lineColor);
};

// ?drawLine@W3DDisplay@@UAEXMMMMMK@Z
void W3DDisplay::drawLine(float startX, float startY, float endX, float endY,
	float lineWidth, UnsignedInt lineColor)
{
	m_render2D->disableTexturing();
	m_render2D->Add_Line(Vector2(startX, startY), Vector2(endX, endY),
		lineWidth, lineColor);
}
