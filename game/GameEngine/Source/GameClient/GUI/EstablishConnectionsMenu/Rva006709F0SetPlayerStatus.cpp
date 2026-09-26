// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib
//
// Retail 0x00538700, 373 bytes: slot 5 (vtable+0x14) of VA 0x0111A394, the
// vtable the derived-menu constructor 0x006709F0 installs after calling the
// EstablishConnectionsMenu base constructor 0x004B2C80 (base vtable VA
// 0x010FD79C, whose slot 5 is EstablishConnectionsMenu::setPlayerStatus at
// 0x004B2DC0). NAT::setConnectionState 0x00670DC0 calls this slot with
// (slot, state). The GUI: labels are the Zero Hour setPlayerStatus set; this
// override writes the text through setConnectingPlayerStatus 0x00538490 and
// maps NATCONNECTIONSTATE_NOSTATE to a single space.

typedef char Bool;
typedef unsigned short WideChar;

#include "string_base.h"

// Retail inlines the UnicodeString default constructor, destructor and
// copy assignment into StringBase<unsigned short> calls; unicode_string.h
// declares them out of line, so this TU keeps the inline forwarders.
class UnicodeString
{
public:
	UnicodeString() { m_data = 0; }
	~UnicodeString()
	{
		( (StringBase<WideChar> *)this )->releaseBuffer();
	}
	UnicodeString &operator=( const UnicodeString &that )
	{
		( (StringBase<WideChar> *)this )->set( *(const StringBase<WideChar> *)&that );
		return *this;
	}
	UnicodeString &operator=( const WideChar *text );

private:
	WideChar *m_data;
};

class GameTextInterface
{
public:
	virtual void slot00() = 0; virtual void slot01() = 0; virtual void slot02() = 0;
	virtual void slot03() = 0; virtual void slot04() = 0; virtual void slot05() = 0;
	virtual void slot06() = 0; virtual void slot07() = 0; virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual UnicodeString fetch( const char *label, Bool *exists = 0 ) = 0;	// slot 10, vtable+0x28
};

extern GameTextInterface *TheGameText;

enum NATConnectionState
{
	NATCONNECTIONSTATE_NOSTATE,
	NATCONNECTIONSTATE_WAITINGTOBEGIN,
	NATCONNECTIONSTATE_WAITINGFORMANGLERRESPONSE,
	NATCONNECTIONSTATE_WAITINGFORMANGLEDPORT,
	NATCONNECTIONSTATE_WAITINGFORRESPONSE,
	NATCONNECTIONSTATE_DONE,
	NATCONNECTIONSTATE_FAILED
};

void setConnectingPlayerStatus( int index, const UnicodeString &text );

class EstablishConnectionsMenu
{
public:
	virtual ~EstablishConnectionsMenu();
	virtual void initMenu();
	virtual void endMenu();
	virtual void abortGame();
	virtual void setPlayerName( int slot, UnicodeString name );
	virtual void setPlayerStatus( int slot, NATConnectionState state );
};

class Rva006709F0 : public EstablishConnectionsMenu
{
public:
	virtual void setPlayerStatus( int slot, NATConnectionState state );
};

void Rva006709F0::setPlayerStatus( int slot, NATConnectionState state )
{
	UnicodeString text;
	if ( state == NATCONNECTIONSTATE_WAITINGFORMANGLERRESPONSE ) {
		text = TheGameText->fetch( "GUI:WaitingForManglerResponse" );
	} else if ( state == NATCONNECTIONSTATE_WAITINGFORMANGLEDPORT ) {
		text = TheGameText->fetch( "GUI:WaitingForMangledPort" );
	} else if ( state == NATCONNECTIONSTATE_WAITINGFORRESPONSE ) {
		text = TheGameText->fetch( "GUI:WaitingForResponse" );
	} else if ( state == NATCONNECTIONSTATE_DONE ) {
		text = TheGameText->fetch( "GUI:ConnectionDone" );
	} else if ( state == NATCONNECTIONSTATE_FAILED ) {
		text = TheGameText->fetch( "GUI:ConnectionFailed" );
	} else if ( state == NATCONNECTIONSTATE_WAITINGTOBEGIN ) {
		text = TheGameText->fetch( "GUI:WaitingToBeginConnection" );
	} else if ( state == NATCONNECTIONSTATE_NOSTATE ) {
		text = L" ";
	} else {
		text = TheGameText->fetch( "GUI:UnknownConnectionState" );
	}
	setConnectingPlayerStatus( slot, text );
}
