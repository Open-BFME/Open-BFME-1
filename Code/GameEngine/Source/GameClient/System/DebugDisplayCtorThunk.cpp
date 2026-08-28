// cl: /DNDEBUG /MD /EHsc
// readable body of ??0DebugDisplay@@: Code/GameEngine/Source/GameClient/System/DebugDisplay.cpp
// readable body of ?reset@DebugDisplay@@: Code/GameEngine/Source/GameClient/System/DebugDisplay.cpp
// Open-BFME5: DebugDisplay::DebugDisplay, retail 0x005BD1C0, converted out of a
// machine byte dump. The reference constructor is one initialiser list and a
// call to reset(); reset() is inlined here, so all four of its calls are in
// these 104 bytes and each one pins a vtable slot.
//
//   +0x0C  setCursorPos      called with (0, 0)
//   +0x18  getWidth          no argument, result feeds the next call
//   +0x20  setTextColor      called with 0, so WHITE is 0
//   +0x24  setRightMargin    called with 0
//   +0x28  setLeftMargin     called with getWidth()
//
// Those offsets place setCursorPos at slot 3, which puts two slots ahead of
// printf and fixes the base as contributing a vptr and nothing else. Reading
// the declaration order back from there gives the ten virtuals below.
//
// The data side is fixed by the only two stores: m_width at +0x10 and
// m_height at +0x14, which leaves exactly room for m_textColor, m_xPos and
// m_yPos between the vptr and them.
//
// setCursorPos is reached as `call dword ptr [0x0110F8E0]` -- an absolute call
// through the vtable's own slot 3 rather than through this object's vptr,
// because inside a constructor the dynamic type is known. Spelling reset() out
// by hand would emit a vptr load instead and lose those bytes.

typedef int Int;
typedef char Char;
typedef unsigned int Color;

enum { WHITE = 0 };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/DebugDisplay.h
class DebugDisplayInterface
{
public:
	virtual ~DebugDisplayInterface();
	virtual void bfmeRetailSlot01( void ) = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/DebugDisplay.h
class DebugDisplay : public DebugDisplayInterface
{

	public:

		DebugDisplay();
		virtual ~DebugDisplay() {};

		virtual void	printf( Char *format, ...);			///< Print formatted text at current cursor position
		virtual void	setCursorPos( Int x, Int y );		///< Set new cursor position
		virtual Int		getCursorXPos( void );					///< Get current X position of cursor
		virtual Int		getCursorYPos( void );					///< Get current Y position of cursor
		virtual Int		getWidth( void );								///< Get character width of display
		virtual Int		getHeight( void );							///< Get character height of display
		virtual void	setTextColor( Color color );		///< set text color
		virtual void	setRightMargin( Int rightPos );	///< set right margin position
		virtual void	setLeftMargin( Int leftPos );		///< set left margin position
		virtual void	reset( void );									///< Reset back to default settings

	protected:

		Color m_textColor;	///< +0x04, Color to render text in
		Int		m_xPos;				///< +0x08, Current X position of cursor
		Int		m_yPos;				///< +0x0C, Current Y position of cursor
		Int		m_width;			///< +0x10, Character width of display
		Int		m_height;			///< +0x14, Character height of display
		Int		m_rightMargin;///< +0x18, Right margin position
		Int		m_leftMargin;	///< +0x1C, Left margin position

};

//============================================================================
// DebugDisplay::DebugDisplay
//============================================================================
// ??0DebugDisplay@@QAE@XZ
DebugDisplay::DebugDisplay()
: m_width(0),
	m_height(0)
{
	reset();
}

//============================================================================
// DebugDisplay::reset
//============================================================================

void DebugDisplay::reset( void )
{
	setCursorPos( 0, 0 );
	setTextColor( WHITE );
	setRightMargin( 0 );
	setLeftMargin( getWidth() );
}
