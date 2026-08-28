// cl: /DNDEBUG /MD /EHsc-

typedef bool Bool;

class Mouse
{
public:
	enum MouseCursor
	{
		NONE = 0,
		NORMAL = 1,
		ARROW = 2,
		SCROLL = 3
	};

	virtual void slot00(void) = 0;
	virtual void slot01(void) = 0;
	virtual void slot02(void) = 0;
	virtual void slot03(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot05(void) = 0;
	virtual void slot06(void) = 0;
	virtual void slot07(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot09(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot11(void) = 0;
	virtual void slot12(void) = 0;
	virtual void slot13(void) = 0;
	virtual void setCursor(MouseCursor cursor) = 0;
	virtual void capture(void) = 0;
	virtual void releaseCapture(void) = 0;
};

extern Mouse *TheMouse;

class InGameUI
{
public:
	virtual void setScrolling(Bool isScrolling);

private:
	void setMouseCursor(Mouse::MouseCursor cursor)
	{
		if (!TheMouse)
			return;

		TheMouse->setCursor(cursor);
	}

	char m_beforeIsScrolling[0x81C];
	Bool m_isScrolling;
};

// BFME's implementation omits the two TacticalView camera-unlock calls in
// the later Zero Hour source. The adjacent getter confirms this field at
// +0x820, while the Mouse vtable calls identify capture and cursor handling.
// ?setScrolling@InGameUI@@UAEX_N@Z
void InGameUI::setScrolling(Bool isScrolling)
{
	if (m_isScrolling == isScrolling)
		return;

	if (isScrolling)
	{
		TheMouse->capture();
		setMouseCursor(Mouse::SCROLL);
	}
	else
	{
		setMouseCursor(Mouse::ARROW);
		TheMouse->releaseCapture();
	}

	m_isScrolling = isScrolling;
}
