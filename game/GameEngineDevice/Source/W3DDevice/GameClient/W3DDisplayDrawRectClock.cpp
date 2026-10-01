// ?drawRectClock@W3DDisplay@@UAEXMMMMMK@Z
// Retail RVA 0x006EBF20; vtable entry VA 0x0111EE98 -> ILT RVA 0x299C4.
// Matched wrapper RVA 0x00793C70 calls slot +0xC8 at 0x00793C9D.
// Adjacent matched drawOpenRect / drawFillRect entries establish Display ownership.
// Original W3DDisplay.cpp drawRectClock geometry; BFME takes float coordinates.
// Keep product parentheses: MSVC 7.1 uses them to constrain x87 reassociation.
// Retail helper ILTs 0x19D67 -> 0x6E73C0 (rect), 0x24BCC -> 0x6EB070 (tri).
// cl: /DNDEBUG /MD /EHsc

typedef unsigned long UnsignedInt;

class Vector2
{
public:
	Vector2(float x, float y) : X(x), Y(y) {}
	float X;
	float Y;
};

typedef Vector2 BfmeVector2;

class RectClass
{
public:
	RectClass(float left, float top, float right, float bottom)
		: Left(left), Top(top), Right(right), Bottom(bottom) {}
	float Left;
	float Top;
	float Right;
	float Bottom;
};

class Render2DClass
{
private:
	unsigned char m_unmodelled_00[0x54];
	unsigned char m_texturingEnabled;

public:
	void disableTexturing() { m_texturingEnabled = 0; }
	void Add_Quad(const RectClass &rect, unsigned long color);
	void Add_Tri(const Vector2 &v0, const Vector2 &v1,
		const Vector2 &v2, const Vector2 &uv0,
		const Vector2 &uv1, const Vector2 &uv2, unsigned long color);
};

class W3DDisplay
{
private:
	unsigned char m_unmodelled_04[0x160];
	Render2DClass *m_render2D;

public:
	virtual void drawRectClock(float startX, float startY, float width,
		float height, float percent, UnsignedInt color);
};

// ?drawRectClock@W3DDisplay@@UAEXMMMMMK@Z
void W3DDisplay::drawRectClock(float startX, float startY, float width,
	float height, float percent, UnsignedInt color)
{
	if (percent < 1.0f || percent > 100.0f)
		return;

	m_render2D->disableTexturing();

	if (percent == 100.0f) {
		m_render2D->Add_Quad(RectClass(startX, startY,
			startX + width, startY + height), color);
	} else if (percent > 75.0f) {
		m_render2D->Add_Quad(RectClass(startX + width / 2.0f, startY,
			startX + width, startY + height), color);
		m_render2D->Add_Quad(RectClass(startX, startY + height / 2.0f,
			startX + width / 2.0f, startY + height), color);
		float remain = percent - 75.0f;
		if (remain > 12.0f) {
			m_render2D->Add_Tri(Vector2(startX, startY),
				BfmeVector2(startX, startY + height / 2.0f),
				BfmeVector2(startX + width / 2.0f, startY + height / 2.0f),
				BfmeVector2(0, 0), BfmeVector2(0, 0), BfmeVector2(0, 0), color);
			float percentDraw = (remain - 12.0f) / 13.0f;
			m_render2D->Add_Tri(BfmeVector2(startX, startY),
				BfmeVector2(startX + width / 2.0f, startY + height / 2.0f),
				BfmeVector2(startX + (width / 2.0f * percentDraw), startY),
				BfmeVector2(0, 0), BfmeVector2(0, 0), BfmeVector2(0, 0), color);
		} else {
			float percentDraw = remain / 12.0f;
			m_render2D->Add_Tri(BfmeVector2(startX,
				startY + height / 2.0f - (height / 2.0f * percentDraw)),
				BfmeVector2(startX, startY + height / 2.0f),
				BfmeVector2(startX + width / 2.0f, startY + height / 2.0f),
				BfmeVector2(0, 0), BfmeVector2(0, 0), BfmeVector2(0, 0), color);
		}
	} else if (percent > 50.0f) {
		m_render2D->Add_Quad(RectClass(startX + width / 2.0f, startY,
			startX + width, startY + height), color);
		float remain = percent - 50.0f;
		if (remain > 12.0f) {
			m_render2D->Add_Tri(BfmeVector2(startX + width / 2.0f, startY + height / 2.0f),
				BfmeVector2(startX, startY + height),
				BfmeVector2(startX + width / 2.0f, startY + height),
				BfmeVector2(0, 0), BfmeVector2(0, 0), BfmeVector2(0, 0), color);
			float percentDraw = (remain - 12.0f) / 13.0f;
			m_render2D->Add_Tri(BfmeVector2(startX,
				startY + height - (height / 2.0f * percentDraw)),
				BfmeVector2(startX, startY + height),
				BfmeVector2(startX + width / 2.0f, startY + height / 2.0f),
				BfmeVector2(0, 0), BfmeVector2(0, 0), BfmeVector2(0, 0), color);
		} else {
			float percentDraw = remain / 12.0f;
			m_render2D->Add_Tri(BfmeVector2(startX + width / 2.0f, startY + height),
				BfmeVector2(startX + width / 2.0f, startY + height / 2.0f),
				BfmeVector2(startX + width / 2.0f - (width / 2.0f * percentDraw),
					startY + height),
				BfmeVector2(0, 0), BfmeVector2(0, 0), BfmeVector2(0, 0), color);
		}
	} else if (percent > 25.0f) {
		m_render2D->Add_Quad(RectClass(startX + width / 2.0f, startY,
			startX + width, startY + height / 2.0f), color);
		float remain = percent - 25.0f;
		if (remain > 12.0f) {
			m_render2D->Add_Tri(BfmeVector2(startX + width / 2.0f, startY + height / 2.0f),
				BfmeVector2(startX + width, startY + height),
				BfmeVector2(startX + width, startY + height / 2.0f),
				BfmeVector2(0, 0), BfmeVector2(0, 0), BfmeVector2(0, 0), color);
			float percentDraw = (remain - 12.0f) / 13.0f;
			m_render2D->Add_Tri(BfmeVector2(startX + width / 2.0f, startY + height / 2.0f),
				BfmeVector2(startX + width - (width / 2.0f * percentDraw), startY + height),
				BfmeVector2(startX + width, startY + height),
				BfmeVector2(0, 0), BfmeVector2(0, 0), BfmeVector2(0, 0), color);
		} else {
			float percentDraw = remain / 12.0f;
			m_render2D->Add_Tri(BfmeVector2(startX + width, startY + height / 2.0f),
				BfmeVector2(startX + width / 2.0f, startY + height / 2.0f),
				BfmeVector2(startX + width,
					startY + height / 2.0f + (height / 2.0f * percentDraw)),
				BfmeVector2(0, 0), BfmeVector2(0, 0), BfmeVector2(0, 0), color);
		}
	} else {
		if (percent > 12) {
			m_render2D->Add_Tri(BfmeVector2(startX + width / 2, startY),
				BfmeVector2(startX + width / 2, startY + height / 2),
				BfmeVector2(startX + width, startY),
				BfmeVector2(0, 0), BfmeVector2(0, 0), BfmeVector2(0, 0), color);
			float percentDraw = (percent - 12) / 13;
			m_render2D->Add_Tri(BfmeVector2(startX + width, startY),
				BfmeVector2(startX + width / 2, startY + height / 2),
				BfmeVector2(startX + width, startY + (height / 2 * percentDraw)),
				BfmeVector2(0, 0), BfmeVector2(0, 0), BfmeVector2(0, 0), color);
		} else {
			float percentDraw = percent / 12;
			m_render2D->Add_Tri(BfmeVector2(startX + width / 2, startY),
				BfmeVector2(startX + width / 2, startY + height / 2),
				BfmeVector2(startX + width / 2 + (width / 2 * percentDraw), startY),
				BfmeVector2(0, 0), BfmeVector2(0, 0), BfmeVector2(0, 0), color);
		}
	}
}
