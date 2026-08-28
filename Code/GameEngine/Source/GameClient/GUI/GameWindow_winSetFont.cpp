// cl: /DNDEBUG /MD /EHsc
// readable body of ?winSetFont@GameWindow@@UAEXPAVGameFont@@@Z: Code/GameEngine/Source/GameClient/GUI/GameWindow.cpp
// Open-BFME: GameWindow::winSetFont, retail 0x00478550, 131 bytes.
//
// The reference's body, plus one BFME line: after whichever branch ran, a hook
// at this+0x04 is handed the font through its vtable slot +0x10.  Every branch
// joins there, so it is written after the if/else chain rather than inside it.
//
// The style word is read once into a register and the four tests come out of
// it: 0x20 listbox, 0x8000 combo box (the sign test on ah), 0x40 entry field,
// 0x80 static text (the sign test on al) -- the reference's own GWS values.
//
// Offsets: the style at this+0x3C, the font at this+0x1B4 and the text and
// tooltip display strings at this+0x1CC and this+0x1D0, whose setFont is vtable
// slot +0x18.

class GameFont;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/DisplayString.h
class DisplayString
{
public:
	virtual void unusedSlot00();
	virtual void unusedSlot01();
	virtual void unusedSlot02();
	virtual void unusedSlot03();
	virtual void unusedSlot04();
	virtual void unusedSlot05();
	virtual void setFont(GameFont *font);			// vtable +0x18
};

// Shape only: whatever sits at GameWindow+0x04, it takes the font through its
// own vtable slot +0x10 every time the font changes.
class BfmeWindowFontSink
{
public:
	virtual void unusedSlot00();
	virtual void unusedSlot01();
	virtual void unusedSlot02();
	virtual void unusedSlot03();
	virtual void setFont(GameFont *font);			// vtable +0x10
};

class GameWindow;

void GadgetListBoxSetFont(GameWindow *g, GameFont *font);	// ILT 0x000013CF
void GadgetComboBoxSetFont(GameWindow *g, GameFont *font);	// ILT 0x00009CD2
void GadgetTextEntrySetFont(GameWindow *g, GameFont *font);	// ILT 0x0003CBCD
void GadgetStaticTextSetFont(GameWindow *g, GameFont *font);	// ILT 0x00044904

enum
{
	GWS_SCROLL_LISTBOX	= 0x00000020,
	GWS_ENTRY_FIELD		= 0x00000040,
	GWS_STATIC_TEXT		= 0x00000080,
	GWS_COMBO_BOX		= 0x00008000
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
class GameWindow
{
public:
	virtual void winSetFont(GameFont *font);		// the window's own vtable sits at this+0x00

private:
	BfmeWindowFontSink *m_bfmeFontSink;			// this+0x04
	unsigned char m_unmodelled_008[0x3C - 0x08];
	unsigned int m_style;					// this+0x3C
	unsigned char m_unmodelled_040[0x1B4 - 0x40];
	GameFont *m_font;					// this+0x1B4
	unsigned char m_unmodelled_1b8[0x1CC - 0x1B8];
	DisplayString *m_text;					// this+0x1CC
	DisplayString *m_tooltip;				// this+0x1D0
};

void GameWindow::winSetFont( GameFont *font )
{

	// set font in window member
	m_font = font;

	// set font for other display strings in special gadget window controls
	if( m_style & GWS_SCROLL_LISTBOX )
		GadgetListBoxSetFont( this, font );
	else if( m_style & GWS_COMBO_BOX )
		GadgetComboBoxSetFont( this, font );
	else if( m_style & GWS_ENTRY_FIELD )
		GadgetTextEntrySetFont( this, font );
	else if( m_style & GWS_STATIC_TEXT )
		GadgetStaticTextSetFont( this, font );
	else
	{
		DisplayString *dString;

		// set the font for the display strings all windows have
		dString = m_text;
		if( dString )
			dString->setFont( font );
		dString = m_tooltip;
		if( dString )
			dString->setFont( font );

	}  // end else

	if( m_bfmeFontSink )
		m_bfmeFontSink->setFont( font );

}  // end WinSetFont
