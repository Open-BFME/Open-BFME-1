// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib
//
// Rva00518BF0LobbyView::apply, retail 0x00518BF0 (404 bytes).
// The secondary vtable at 0x01105A28 routes slot 3 through ILT 0x00015FF5.
// The body writes GameSlot::m_color, sends either serialized LAN state or
// Color=%d to the host, and stores the local color preference at +0x138.

#include "ascii_string.h"

// Four-byte UTF-16 result view with the retail inline-release lifetime.
// Canonical unicode_string.h produces a different out-of-line cleanup shape.
class Rva00518BF0Name
{
public:
    ~Rva00518BF0Name() { release(); }
    int compare(const Rva00518BF0Name &other) const throw();
private:
    void release();
    unsigned short *m_data;
};

class LANGameSlot;

class GameSlot
{
public:
	virtual void slot00();
	virtual LANGameSlot *slot01();

	int m_state;
	unsigned char m_accepted;
	unsigned char m_hasMap;
	unsigned char m_isMuted;
	unsigned char m_pad;
	int m_color;
	int m_startPos;
	int m_playerTemplate;

	int getColor() const { return m_color; }
	Rva00518BF0Name getName00518BF0() const;
};

class LANGameSlot : public GameSlot
{
public:
	bool isLocalPlayer() const;
};

class LANGameInfo
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual int getLocalSlotNum() const;
	virtual void resetAccepted();

	GameSlot *getSlot( int index );
};

struct TransportAddress
{
	TransportAddress() : m_ip( 0 ), m_port( 0 ) {}

	unsigned int m_ip;
	unsigned short m_port;
};

class LANAPI
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
	virtual void RequestGameOptions( AsciiString options, bool isPublic,
		const TransportAddress &address = TransportAddress() ) = 0;
	virtual void requestSerializedGameInfo( bool unused, void *destination ) = 0;
	virtual void slot22() = 0;
	virtual void slot23() = 0;
	virtual void slot24() = 0;
	virtual void slot25() = 0;
	virtual void slot26() = 0;
	virtual void slot27() = 0;
	virtual void slot28() = 0;
	virtual void slot29() = 0;
	virtual void slot30() = 0;
	virtual void slot31() = 0;
	virtual void slot32() = 0;
	virtual void slot33() = 0;
	virtual void slot34() = 0;
	virtual void slot35() = 0;
	virtual void slot36() = 0;
	virtual void slot37() = 0;
	virtual void slot38() = 0;
	virtual void slot39() = 0;
	virtual void slot40() = 0;
	virtual void slot41() = 0;
	virtual void slot42() = 0;
	virtual void slot43() = 0;
	virtual void slot44() = 0;
	virtual void slot45() = 0;
	virtual void slot46() = 0;
	virtual void slot47() = 0;
	virtual LANGameInfo *GetMyGame() = 0;
};

extern LANAPI *TheLAN;

class BfmeThing935B
{
public:
	char bfmeGo935B();
};

class Open2Option086F30
{
public:
	void store( int value );
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual bool write();
};

class Rva00518BF0LobbyView
{
public:
	bool apply( GameSlot *slot, int color );

private:
	unsigned char m_pad[ 0x138 ];
	Open2Option086F30 m_color;
};

// ?apply@Rva00518BF0LobbyView@@QAE_NPAVGameSlot@@H@Z
bool Rva00518BF0LobbyView::apply( GameSlot *slot, int color )
{
	if( !TheLAN )
		return false;
	LANGameInfo *game = TheLAN->GetMyGame();
	if( !game )
		return false;

	slot->m_color = color;
	if( ( (BfmeThing935B *)game )->bfmeGo935B() )
	{
		TransportAddress address;
		TheLAN->requestSerializedGameInfo( true, &address );
	}
	else
	{
		LANGameSlot *lanSlot = slot->slot01();
		if( !lanSlot )
			return false;
		if( !lanSlot->isLocalPlayer() )
			return false;

		AsciiString options;
		options.format( AsciiString( "Color=%d" ), slot->getColor() );
		TheLAN->RequestGameOptions( options, true );
	}

	if( slot->getName00518BF0().compare(
			game->getSlot( game->getLocalSlotNum() )->getName00518BF0() ) == 0 )
	{
		m_color.store( color );
		m_color.write();
	}
	return true;
}
