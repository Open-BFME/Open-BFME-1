// ?drawRectClock@W3DDisplay@@UAEXMMMMMK@Z
// partial score=0.89 date=2026-09-02
// cl: /DNDEBUG /MD /EHsc

typedef unsigned long UnsignedInt;

struct BfmeV1207
{
	BfmeV1207(float x, float y) : X(x), Y(y) {}
	float X;
	float Y;
};

typedef BfmeV1207 BfmeVector2;

struct BfmeFloatRect
{
	BfmeFloatRect(float left, float top, float right, float bottom)
		: Left(left), Top(top), Right(right), Bottom(bottom) {}
	float Left;
	float Top;
	float Right;
	float Bottom;
};

class BfmeRender2D
{
private:
	unsigned char m_unmodelled_00[0x54];
	unsigned char m_texturingEnabled;

public:
	void disableTexturing() { m_texturingEnabled = 0; }
	void addRect006e(const BfmeFloatRect &rect, int color);
};

class BfmeA1207 : public BfmeRender2D
{
public:
	void bfmeDo1207(const BfmeV1207 &a1, const BfmeV1207 &a2,
		const BfmeV1207 &a3, const BfmeV1207 &a4,
		const BfmeV1207 &a5, const BfmeV1207 &a6, int color);
};

class W3DDisplay
{
private:
	unsigned char m_unmodelled_04[0x160];
	BfmeA1207 *m_render2D;

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
		m_render2D->addRect006e(BfmeFloatRect(startX, startY,
			startX + width, startY + height), color);
	} else if (percent > 75.0f) {
		m_render2D->addRect006e(BfmeFloatRect(startX + width / 2.0f, startY,
			startX + width, startY + height), color);
		m_render2D->addRect006e(BfmeFloatRect(startX, startY + height / 2.0f,
			startX + width / 2.0f, startY + height), color);
		float remain = percent - 75.0f;
		if (remain > 12.0f) {
			m_render2D->bfmeDo1207(BfmeV1207(startX, startY),
				BfmeVector2(startX, startY + height / 2.0f),
				BfmeVector2(startX + width / 2.0f, startY + height / 2.0f),
				BfmeVector2(0, 0), BfmeVector2(0, 0), BfmeVector2(0, 0), color);
			float percentDraw = (remain - 12.0f) / 13.0f;
			m_render2D->bfmeDo1207(BfmeVector2(startX, startY),
				BfmeVector2(startX + width / 2.0f, startY + height / 2.0f),
				BfmeVector2(startX + width / 2.0f * percentDraw, startY),
				BfmeVector2(0, 0), BfmeVector2(0, 0), BfmeVector2(0, 0), color);
		} else {
			float percentDraw = remain / 12.0f;
			m_render2D->bfmeDo1207(BfmeVector2(startX,
				startY + height / 2.0f - height / 2.0f * percentDraw),
				BfmeVector2(startX, startY + height / 2.0f),
				BfmeVector2(startX + width / 2.0f, startY + height / 2.0f),
				BfmeVector2(0, 0), BfmeVector2(0, 0), BfmeVector2(0, 0), color);
		}
	} else if (percent > 50.0f) {
		m_render2D->addRect006e(BfmeFloatRect(startX + width / 2.0f, startY,
			startX + width, startY + height), color);
		float remain = percent - 50.0f;
		if (remain > 12.0f) {
			m_render2D->bfmeDo1207(BfmeVector2(startX + width / 2.0f, startY + height / 2.0f),
				BfmeVector2(startX, startY + height),
				BfmeVector2(startX + width / 2.0f, startY + height),
				BfmeVector2(0, 0), BfmeVector2(0, 0), BfmeVector2(0, 0), color);
			float percentDraw = (remain - 12.0f) / 13.0f;
			m_render2D->bfmeDo1207(BfmeVector2(startX,
				startY + height - height / 2.0f * percentDraw),
				BfmeVector2(startX, startY + height),
				BfmeVector2(startX + width / 2.0f, startY + height / 2.0f),
				BfmeVector2(0, 0), BfmeVector2(0, 0), BfmeVector2(0, 0), color);
		} else {
			float percentDraw = remain / 12.0f;
			m_render2D->bfmeDo1207(BfmeVector2(startX + width / 2.0f, startY + height),
				BfmeVector2(startX + width / 2.0f, startY + height / 2.0f),
				BfmeVector2(startX + width / 2.0f - width / 2.0f * percentDraw,
					startY + height),
				BfmeVector2(0, 0), BfmeVector2(0, 0), BfmeVector2(0, 0), color);
		}
	} else if (percent > 25.0f) {
		m_render2D->addRect006e(BfmeFloatRect(startX + width / 2.0f, startY,
			startX + width, startY + height / 2.0f), color);
		float remain = percent - 25.0f;
		if (remain > 12.0f) {
			m_render2D->bfmeDo1207(BfmeVector2(startX + width / 2.0f, startY + height / 2.0f),
				BfmeVector2(startX + width, startY + height),
				BfmeVector2(startX + width, startY + height / 2.0f),
				BfmeVector2(0, 0), BfmeVector2(0, 0), BfmeVector2(0, 0), color);
			float percentDraw = (remain - 12.0f) / 13.0f;
			m_render2D->bfmeDo1207(BfmeVector2(startX + width / 2.0f, startY + height / 2.0f),
				BfmeVector2(startX + width - width / 2.0f * percentDraw, startY + height),
				BfmeVector2(startX + width, startY + height),
				BfmeVector2(0, 0), BfmeVector2(0, 0), BfmeVector2(0, 0), color);
		} else {
			float percentDraw = remain / 12.0f;
			m_render2D->bfmeDo1207(BfmeVector2(startX + width, startY + height / 2.0f),
				BfmeVector2(startX + width / 2.0f, startY + height / 2.0f),
				BfmeVector2(startX + width,
					startY + height / 2.0f + height / 2.0f * percentDraw),
				BfmeVector2(0, 0), BfmeVector2(0, 0), BfmeVector2(0, 0), color);
		}
	} else {
		if (percent > 12) {
			m_render2D->bfmeDo1207(BfmeVector2(startX + width / 2, startY),
				BfmeVector2(startX + width / 2, startY + height / 2),
				BfmeVector2(startX + width, startY),
				BfmeVector2(0, 0), BfmeVector2(0, 0), BfmeVector2(0, 0), color);
			float percentDraw = (percent - 12) / 13;
			m_render2D->bfmeDo1207(BfmeVector2(startX + width, startY),
				BfmeVector2(startX + width / 2, startY + height / 2),
				BfmeVector2(startX + width, startY + height / 2 * percentDraw),
				BfmeVector2(0, 0), BfmeVector2(0, 0), BfmeVector2(0, 0), color);
		} else {
			float percentDraw = percent / 12;
			m_render2D->bfmeDo1207(BfmeVector2(startX + width / 2, startY),
				BfmeVector2(startX + width / 2, startY + height / 2),
				BfmeVector2(startX + width / 2 + width / 2 * percentDraw, startY),
				BfmeVector2(0, 0), BfmeVector2(0, 0), BfmeVector2(0, 0), color);
		}
	}
}
