// Lift the Mouse engine-visibility setter to clean C++.
//
// This is the engine-lock twin of BfmeMouse_setVisibility::setVisibility.  It
// commits the pending cursor pair to +0x4DA1/+0x4DA2 and passes the committed
// cursor byte (+0x4DA1) to the same virtual apply method at +0x5C.

class Mouse
{
public:
	virtual void unused00();
	virtual void unused01();
	virtual void unused02();
	virtual void unused03();
	virtual void unused04();
	virtual void unused05();
	virtual void unused06();
	virtual void unused07();
	virtual void unused08();
	virtual void unused09();
	virtual void unused10();
	virtual void unused11();
	virtual void unused12();
	virtual void unused13();
	virtual void unused14();
	virtual void unused15();
	virtual void unused16();
	virtual void unused17();
	virtual void unused18();
	virtual void unused19();
	virtual void unused20();
	virtual void unused21();
	virtual void unused22();
	virtual void applyCursor(bool, const unsigned char *); // vtable +0x5C

	void _bfme_setEngineVisibility(bool);

private:
	unsigned char m_unreconstructed_04[0x4DA1 - 4];
	unsigned char m_cursor;                  // +0x4DA1
	unsigned char m_cursorState;             // +0x4DA2
	unsigned char m_pendingCursor;           // +0x4DA3
	unsigned char m_pendingCursorState;      // +0x4DA4
	unsigned char m_cursorDirty;             // +0x4DA5
};

// ?_bfme_setEngineVisibility@Mouse@@QAEX_N@Z
void Mouse::_bfme_setEngineVisibility(bool visible)
{
	if (m_cursorDirty)
	{
		m_cursor = m_pendingCursor;
		m_cursorState = m_pendingCursorState;
		m_cursorDirty = 0;
	}

	applyCursor(visible, &m_cursor);
}
