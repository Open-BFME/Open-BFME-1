// cl: /DNDEBUG /MD /EHsc

typedef bool Bool;
typedef int Int;
typedef unsigned short WideChar;
typedef unsigned int UnsignedInt;
typedef int Color;
typedef float Real;

#define TRUE true
#define FALSE false

template <typename Char>
class StringBase
{
public:
	void set( const StringBase<Char> &source );

protected:
	StringBase() : m_data( 0 ) {}
	StringBase( const Char *source );
	StringBase( const StringBase<Char> &source );
	friend class UnicodeString;

private:
	void releaseBuffer();

	void *m_data;
};

class AsciiString : private StringBase<char>
{
public:
	AsciiString( const AsciiString &source ) : StringBase<char>( source ) {}
};

class UnicodeString : private StringBase<WideChar>
{
public:
	UnicodeString() : StringBase<WideChar>() {}
	UnicodeString( const UnicodeString &source ) : StringBase<WideChar>( source ) {}
	~UnicodeString() { releaseBuffer(); }

	UnicodeString &operator=( const UnicodeString &source )
	{
		set( source );
		return *this;
	}
};

class BfmePopupWindowLayout
{
public:
	virtual void runInit( void *userData ) = 0;
};

class PopupMessageData
{
public:
	PopupMessageData() {}
	virtual ~PopupMessageData();

	UnicodeString message;
	Int x;
	Int y;
	Int width;
	Color textColor;
	Bool pause;
	Bool pauseMusic;
	unsigned char _padding[2];
	BfmePopupWindowLayout *layout;
};

class BfmeGameText
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual UnicodeString fetch( AsciiString label, Bool *exists = 0 ) = 0;
};

class BfmeDisplay
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual UnsignedInt getWidth() = 0;
	virtual UnsignedInt getHeight() = 0;
};

class BfmeGameLogicPause
{
public:
	void setGamePaused( Bool pause, Int pauseInput, Bool pauseMusic );
};

class BFMERetailAsciiString : private StringBase<char>
{
public:
	BFMERetailAsciiString( const char *text ) : StringBase<char>( text ) {}
	~BFMERetailAsciiString() {}
};

class BfmeWindowManager
{
public:
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
	virtual void slot15() = 0;
	virtual void slot16() = 0;
	virtual void slot17() = 0;
	virtual void slot18() = 0;
	virtual void slot19() = 0;
	virtual void slot20() = 0;
	virtual void slot21() = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual BfmePopupWindowLayout *winCreateLayout( BFMERetailAsciiString filename ) = 0;
};

class GameTextInterface;
extern GameTextInterface *TheGameText;
// Retail 0x012F1270 is EA's `Display *TheDisplay`, defined once in
// game/GameEngine/Source/GameClient/Display.cpp. This TU only reads the
// width/height vtable slots, so the reference carries the canonical spelling
// and the observed vtable slice stays a TU-local view cast at each use.
class Display;
extern Display *TheDisplay;
class GameWindowManager;
extern GameWindowManager *TheWindowManager;

class GameLogic;
extern GameLogic *TheGameLogic;
static inline BfmeGameLogicPause *TheBfmeGameLogicView() { return (BfmeGameLogicPause *)TheGameLogic; }

void UpdateDiplomacyBriefingText( const AsciiString &newText, Bool clear );

class InGameUI
{
public:
	virtual void popupMessage( const AsciiString &, Int, Int, Int, Color, Bool, Bool );
	void clearPopupMessageData();
};

struct BfmeInGameUIPopup
{
	unsigned char _padding[0x12A8];
	PopupMessageData *m_popupMessageData;
};

// ?popupMessage@InGameUI@@UAEXABVAsciiString@@HHHH_N1@Z
void InGameUI::popupMessage( const AsciiString &identifier, Int x, Int y,
	Int width, Color textColor, Bool pause, Bool pauseMusic )
{
	BfmeInGameUIPopup *self = (BfmeInGameUIPopup *)this;
	if( self->m_popupMessageData )
		clearPopupMessageData();

	UpdateDiplomacyBriefingText( identifier, false );

	UnicodeString message = reinterpret_cast<BfmeGameText *>(TheGameText)->fetch( identifier );
	self->m_popupMessageData = new PopupMessageData;
	self->m_popupMessageData->message = message;
	if( x > 100 )
		x = 100;
	else if( x < 0 )
		x = 0;
	if( y > 100 )
		y = 100;
	else if( y < 0 )
		y = 0;

	self->m_popupMessageData->x = ((BfmeDisplay *)TheDisplay)->getWidth() *
		( (Real)x * 0.01f );
	self->m_popupMessageData->y = ((BfmeDisplay *)TheDisplay)->getHeight() *
		( (Real)y * 0.01f );
	if( width < 50 )
		width = 50;
	self->m_popupMessageData->width = width;
	self->m_popupMessageData->textColor = textColor;
	self->m_popupMessageData->pause = pause;
	self->m_popupMessageData->pauseMusic = pauseMusic;

	if( pause )
		TheBfmeGameLogicView()->setGamePaused( TRUE, pauseMusic == FALSE, TRUE );

	self->m_popupMessageData->layout =
		reinterpret_cast<BfmeWindowManager *>(TheWindowManager)->winCreateLayout( BFMERetailAsciiString( "InGamePopupMessage.wnd" ) );
	self->m_popupMessageData->layout->runInit( 0 );
}
