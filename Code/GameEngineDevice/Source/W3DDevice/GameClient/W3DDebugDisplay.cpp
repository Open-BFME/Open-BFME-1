// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: W3DDebugDisplay::~W3DDebugDisplay, retail 0x006E6C50,
// zh_sweep packet 006e6c50.
//
// The Zero Hour body unchanged:
//
//   if ( m_displayString )
//     TheDisplayStringManager->freeDisplayString( m_displayString );
//
// The reference tree's W3DDebugDisplay.cpp is not ported, so the two classes
// are spelled TU-locally at the offsets retail proves:
//
//  - m_displayString is [this+0x2C], which is exactly where the vendored
//    headers put it: DebugDisplay is a vptr plus m_textColor/m_xPos/m_yPos/
//    m_width/m_height/m_rightMargin/m_leftMargin (0x20 bytes), then
//    W3DDebugDisplay adds m_font/m_fontWidth/m_fontHeight before it. So the
//    layout did not drift; only the class hierarchy did.
//  - Retail's destructor emits two vptr stores, but the chain is three deep,
//    not two. The packet originally read "two stores, so two levels" and named
//    the base DebugDisplay; that is wrong, and it collided with the base the
//    DebugDisplay constructor stores. .rdata settles it: 0x0110F898 is twelve
//    slots of which 1..11 are all the same _purecall stub -- an all-abstract
//    interface -- while 0x0110F8D4 is thirteen distinct thunks with only the
//    last one _purecall, and 0x005BD1C0 (??0DebugDisplay@@QAE@XZ) stores
//    0x0110F8D4 and calls its own slot 3 absolutely at 0x0110F8E0. A
//    constructor stamps its own class, so 0x0110F8D4 is ??_7DebugDisplay@@6B@
//    and 0x0110F898 is ??_7DebugDisplayInterface@@6B@.
//    The middle level is still there: ~DebugDisplay's inline vptr store is
//    immediately overwritten by ~DebugDisplayInterface's with nothing in
//    between, so the compiler drops it as a dead store. Spelling all three
//    levels reproduces that -- two stores, and the surviving base reloc names
//    the interface.
//  - freeDisplayString is [vtbl+0x28] on TheDisplayStringManager, slot 10.

class DisplayString;
class GameFont;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/DisplayStringManager.h
class DisplayStringManager
{
public:
	// Only the one slot is named; the rest exist to place it.
	virtual void slot0( void ) = 0;
	virtual void slot1( void ) = 0;
	virtual void slot2( void ) = 0;
	virtual void slot3( void ) = 0;
	virtual void slot4( void ) = 0;
	virtual void slot5( void ) = 0;
	virtual void slot6( void ) = 0;
	virtual void slot7( void ) = 0;
	virtual void slot8( void ) = 0;
	virtual void slot9( void ) = 0;
	virtual void freeDisplayString( DisplayString *string ) = 0;	///< slot 10, [vtbl+0x28]
};

extern DisplayStringManager *TheDisplayStringManager;				///< retail 0x012F12CC

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/DebugDisplay.h
class DebugDisplayInterface
{
public:
	virtual ~DebugDisplayInterface() {}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/DebugDisplay.h
class DebugDisplay : public DebugDisplayInterface
{
public:
	virtual ~DebugDisplay() {}

protected:
	int m_textColor;					///< +0x04
	int m_xPos;							///< +0x08
	int m_yPos;							///< +0x0C
	int m_width;						///< +0x10
	int m_height;						///< +0x14
	int m_rightMargin;					///< +0x18
	int m_leftMargin;					///< +0x1C
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include/W3DDevice/GameClient/W3DDebugDisplay.h
class W3DDebugDisplay : public DebugDisplay
{
public:
	virtual ~W3DDebugDisplay();

protected:
	GameFont *m_font;					///< +0x20
	int m_fontWidth;					///< +0x24
	int m_fontHeight;					///< +0x28
	DisplayString *m_displayString;		///< +0x2C
};

//============================================================================
// W3DDebugDisplay::~W3DDebugDisplay
//============================================================================
// ??1W3DDebugDisplay@@UAE@XZ
W3DDebugDisplay::~W3DDebugDisplay()
{
	if ( m_displayString )
	{
		TheDisplayStringManager->freeDisplayString( m_displayString );
	}
}
