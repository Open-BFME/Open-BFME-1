// cl: /EHs-c-
//
// Open-BFME: retail 0x0060D3E0, 34 bytes.
//
// The body clears the byte at this+0x288, selects cursor 0x28 through
// TheMouse's BFME-only vtable layout, then passes false to slot 0x40 of the
// global at 0x012F7048.  Mouse::setCursor is independently established at
// vtable+0x38 in LanGameOptionsMenu.cpp.  The second receiver's identity is
// not yet recovered, so its type and method retain address-derived names.

typedef bool Bool;

class Mouse;
extern Mouse *TheMouse;

class BfmeVirtualCursorMouse0060D3E0
{
public:
	virtual void slot00() = 0; virtual void slot04() = 0;
	virtual void slot08() = 0; virtual void slot0C() = 0;
	virtual void slot10() = 0; virtual void slot14() = 0;
	virtual void slot18() = 0; virtual void slot1C() = 0;
	virtual void slot20() = 0; virtual void slot24() = 0;
	virtual void slot28() = 0; virtual void slot2C() = 0;
	virtual void slot30() = 0; virtual void slot34() = 0;
	virtual void setCursor( int cursor ) = 0;
};

class Glo012F7048CursorGate
{
public:
	virtual void slot00() = 0; virtual void slot04() = 0;
	virtual void slot08() = 0; virtual void slot0C() = 0;
	virtual void slot10() = 0; virtual void slot14() = 0;
	virtual void slot18() = 0; virtual void slot1C() = 0;
	virtual void slot20() = 0; virtual void slot24() = 0;
	virtual void slot28() = 0; virtual void slot2C() = 0;
	virtual void slot30() = 0; virtual void slot34() = 0;
	virtual void slot38() = 0; virtual void slot3C() = 0;
	virtual void setEnabled( Bool enabled ) = 0;
};

extern Glo012F7048CursorGate *Glo012F7048;

class Rva0060D3E0CursorDisable
{
public:
	void apply( void );

private:
	unsigned char m_unmodelled00[ 0x288 ];
	Bool m_enabled;
};

void Rva0060D3E0CursorDisable::apply( void )
{
	m_enabled = false;
	((BfmeVirtualCursorMouse0060D3E0 *)TheMouse)->setCursor( 0x28 );
	Glo012F7048->setEnabled( false );
}
