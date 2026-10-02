// cl: /DNDEBUG /MD /EHsc

class RectClass
{
public:
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

class Render2DClass
{
private:
	unsigned char m_unmodelled_00[0x54];
	unsigned char m_texturingEnabled;

public:
	void disableTexturing()
	{
		m_texturingEnabled = 0;
	}

	void Add_Quad(const RectClass &rect, unsigned long color);
};

struct BfmeClipRegion
{
	int left;
	int top;
	int right;
	int bottom;
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DDisplay.h
class W3DDisplay
{
private:
	unsigned char m_unmodelled_04[0x160];
	Render2DClass *m_render2D;
	BfmeClipRegion m_clipRegion;
	unsigned char m_clippingEnabled;

public:
	virtual void drawFillRect(float x, float y, float width, float height, int color);
};

// ?drawFillRect@W3DDisplay@@UAEXMMMMH@Z
void W3DDisplay::drawFillRect(float x, float y, float width, float height, int color)
{
	m_render2D->disableTexturing();

	RectClass rect;
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

	m_render2D->Add_Quad(rect, color);
}
