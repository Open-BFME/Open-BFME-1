// cl: /DNDEBUG /MD /EHsc

// FILE: ControlBarConstructionText.cpp ///////////////////////////////////////
//
// ControlBar::updateConstructionTextDisplay, retail 0x004AF520.
//
// No port of ControlBarUnderConstruction.cpp exists under Code/.  Found by the
// literal it pushes: "ControlBar.wnd:UnderConstructionDesc" appears in exactly
// one reference source and inside exactly one function there.  The body is Zero
// Hour's, minus the DEBUG_ASSERTCRASH that NDEBUG removes from both trees.
//
// Everything the stand-in asserts is read out of the bytes:
//
//   Object::getConstructionPercent() inlines to a Real at +0x220
//   ControlBar::m_displayedConstructPercent is at +0x68
//   GameWindowManager::winGetWindowFromId is virtual, at slot 0xdc
//   GameText::fetch is virtual, at slot 0x28
//   NameKeyGenerator::nameToKey takes a const char * here, not an AsciiString:
//     retail pushes the literal straight through and builds no temporary
//
// The intervening vtable slots are anonymous -- this body says where these
// three landed and nothing about what is above them.
//
///////////////////////////////////////////////////////////////////////////////

typedef float Real;
typedef unsigned int UnsignedInt;
typedef int NameKeyType;
typedef bool Bool;

template <class Type>
class StringBase
{
private:
	StringBase(const char *s);
	StringBase(const StringBase &that);
	friend class UnicodeString;
	friend class AsciiString;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/UnicodeString.h
class UnicodeString
{
public:

	UnicodeString() { m_text = 0; }

	// Visible delegation, so the by-value temporary is scheduled retail's way.
	UnicodeString(const UnicodeString &that)
	{
		((StringBase<unsigned short> *)this)->StringBase<unsigned short>::StringBase(
			*(const StringBase<unsigned short> *)&that);
	}

	~UnicodeString();

	// Variadic member: MSVC compiles these __cdecl with this pushed first, and
	// the format string is a UnicodeString BY VALUE.
	void __cdecl format(UnicodeString fmt, ...);

private:

	void *m_text;

};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString
{
public:

	AsciiString(const char *s)
	{
		((StringBase<char> *)this)->StringBase<char>::StringBase(s);
	}

	AsciiString(const AsciiString &that);
	~AsciiString();

private:

	void *m_text;

};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindow.h
class GameWindow
{
public:
	void winSetStatus( UnsignedInt status );
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
	Real getConstructionPercent( void ) const
	{
		return *(const Real *)((const char *)this + 0x220);
	}
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/GameWindowManager.h
class GameWindowManager
{
public:
	virtual void slot000() = 0;
	virtual void slot004() = 0;
	virtual void slot008() = 0;
	virtual void slot00C() = 0;
	virtual void slot010() = 0;
	virtual void slot014() = 0;
	virtual void slot018() = 0;
	virtual void slot01C() = 0;
	virtual void slot020() = 0;
	virtual void slot024() = 0;
	virtual void slot028() = 0;
	virtual void slot02C() = 0;
	virtual void slot030() = 0;
	virtual void slot034() = 0;
	virtual void slot038() = 0;
	virtual void slot03C() = 0;
	virtual void slot040() = 0;
	virtual void slot044() = 0;
	virtual void slot048() = 0;
	virtual void slot04C() = 0;
	virtual void slot050() = 0;
	virtual void slot054() = 0;
	virtual void slot058() = 0;
	virtual void slot05C() = 0;
	virtual void slot060() = 0;
	virtual void slot064() = 0;
	virtual void slot068() = 0;
	virtual void slot06C() = 0;
	virtual void slot070() = 0;
	virtual void slot074() = 0;
	virtual void slot078() = 0;
	virtual void slot07C() = 0;
	virtual void slot080() = 0;
	virtual void slot084() = 0;
	virtual void slot088() = 0;
	virtual void slot08C() = 0;
	virtual void slot090() = 0;
	virtual void slot094() = 0;
	virtual void slot098() = 0;
	virtual void slot09C() = 0;
	virtual void slot0A0() = 0;
	virtual void slot0A4() = 0;
	virtual void slot0A8() = 0;
	virtual void slot0AC() = 0;
	virtual void slot0B0() = 0;
	virtual void slot0B4() = 0;
	virtual void slot0B8() = 0;
	virtual void slot0BC() = 0;
	virtual void slot0C0() = 0;
	virtual void slot0C4() = 0;
	virtual void slot0C8() = 0;
	virtual void slot0CC() = 0;
	virtual void slot0D0() = 0;
	virtual void slot0D4() = 0;
	virtual void slot0D8() = 0;
	virtual GameWindow *winGetWindowFromId( GameWindow *window, NameKeyType id ) = 0;	// @0xdc
};

class GameText
{
public:
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
	virtual UnicodeString fetch( const char *label, Bool *exists = 0 ) = 0;	// @0x28
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/NameKeyGenerator.h
class NameKeyGenerator
{
public:
	NameKeyType nameToKey( const char *name );
};

extern NameKeyGenerator *TheNameKeyGenerator;
extern GameWindowManager *TheWindowManager;
extern GameText *TheGameText;

void GadgetStaticTextSetText( GameWindow *window, UnicodeString text );

class CommandButton;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameClient/ControlBar.h
class ControlBar
{
public:

	void updateConstructionTextDisplay( Object *obj );
	void populateOCLTimer( Object *creatorObject );

private:

	const CommandButton *findCommandButton( const AsciiString &name );
	void setControlCommand( GameWindow *button, const CommandButton *commandButton );
	void updateContextOCLTimer( void );
	void setPortraitByObject( Object *obj );

	char m_bfmeHead[0x54];
	GameWindow *m_bfmeContextParentOclTimer;		// @0x54, m_contextParent[CP_OCL_TIMER]
	char m_bfmeMiddle[0x68 - 0x58];
	Real m_displayedConstructPercent;						// @0x68

};

void ControlBar::updateConstructionTextDisplay( Object *obj )
{
	UnicodeString text;
	static UnsignedInt descID = TheNameKeyGenerator->nameToKey( "ControlBar.wnd:UnderConstructionDesc" );
	GameWindow *descWindow = TheWindowManager->winGetWindowFromId( 0, descID );

	// format the message
	text.format( TheGameText->fetch( "CONTROLBAR:UnderConstructionDesc" ),
							 obj->getConstructionPercent() );
	GadgetStaticTextSetText( descWindow, text );

	// record this as the last percentage displayed
	m_displayedConstructPercent = obj->getConstructionPercent();

}  // end updateConstructionTextDisplay

// Retail 0x004AAA70.  BFME dropped the two KINDOF branches Zero Hour has --
// there is no isKindOf call in these 182 bytes at all -- and always sets the
// sell button.  The order is the reference's only up to a point: retail builds
// and destroys the findCommandButton temporary BEFORE calling nameToKey, so
// that statement comes first here.
void ControlBar::populateOCLTimer( Object *creatorObject )
{

	// sanity
	if( creatorObject == 0 )
		return;

	// get our parent window
	GameWindow *parent = m_bfmeContextParentOclTimer;

	const CommandButton *commandButton = findCommandButton( "Command_Sell" );
	NameKeyType id = TheNameKeyGenerator->nameToKey( "ControlBar.wnd:OCLTimerSellButton" );
	GameWindow *win = TheWindowManager->winGetWindowFromId( parent, id );

	setControlCommand( win, commandButton );
	win->winSetStatus( 0x200000 );								// WIN_STATUS_USE_OVERLAY_STATES

	// set the text percent and bar of our timer we are displaying
	updateContextOCLTimer( );

	// set the portrait for the thing being constructed
	setPortraitByObject( creatorObject );

}  // end populateOCLTimer
