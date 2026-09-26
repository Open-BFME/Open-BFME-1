// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Lift the BfmeMouse setVisibility naked dump to clean C++.
//
// Retail keeps a pending cursor pair at +0x4DA3/+0x4DA4 and a dirty flag at
// +0x4DA5; when the flag is set it commits the pair down to +0x4DA1/+0x4DA2 and
// clears it, then hands the visibility flag and a pointer to the committed pair
// to the virtual at vtable +0x5C. The filler virtuals only place that call.

class BfmeMouse_setVisibility
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
	virtual void applyCursor(bool, const unsigned char *);	///< vtable +0x5C

	void setVisibility(bool);

private:
	unsigned char m_unreconstructed_04[0x4DA1 - 4];
	unsigned char m_cursor;						///< retail this+0x4DA1
	unsigned char m_cursorState;				///< retail this+0x4DA2
	unsigned char m_pendingCursor;				///< retail this+0x4DA3
	unsigned char m_pendingCursorState;			///< retail this+0x4DA4
	unsigned char m_cursorDirty;				///< retail this+0x4DA5
};

// ?setVisibility@BfmeMouse_setVisibility@@QAEX_N@Z
void BfmeMouse_setVisibility::setVisibility(bool visible)
{
	if (m_cursorDirty)
	{
		m_cursor = m_pendingCursor;
		m_cursorState = m_pendingCursorState;
		m_cursorDirty = 0;
	}

	applyCursor(visible, &m_cursorState);
}
