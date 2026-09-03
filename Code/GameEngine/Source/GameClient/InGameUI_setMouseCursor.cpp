// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
typedef bool Bool;
typedef int Int;

class Mouse
{
public:
	enum MouseCursor { ARROW = 2, SCROLL = 3 };
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0C() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1C() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2C() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual void setCursor(MouseCursor cursor) = 0;
};

extern Mouse *TheMouse;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/InGameUI.h
class InGameUI
{
private:
	unsigned char m_beforeMouseState[0x820];
	Bool m_isScrolling;
	Bool m_isSelecting;
	unsigned char m_alignMouseMode[2];
	Int m_mouseMode;
	Int m_mouseModeCursor;

public:
	void setMouseCursor(Mouse::MouseCursor cursor);
};

// BFME suppresses cursor changes while selection or RMB scrolling is active.
void InGameUI::setMouseCursor(Mouse::MouseCursor cursor)
{
	if (m_isSelecting || m_isScrolling)
		return;

	if (TheMouse == 0)
		return;

	TheMouse->setCursor(cursor);

	if (m_mouseMode == 2 && cursor != Mouse::ARROW && cursor != Mouse::SCROLL)
		m_mouseModeCursor = cursor;
}
