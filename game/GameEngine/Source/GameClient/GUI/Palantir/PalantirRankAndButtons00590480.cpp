// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// stlport
// Address-derived receiver view shared with the matched Rva00597FC0Client::update caller.

typedef int Int;
typedef bool Bool;

#include <algorithm>
#include <stl/_iterator_base.h>

extern "C" __declspec(dllimport) void *__cdecl memmove(
	void *destination, const void *source, unsigned int bytes );

class Rva00589320PlayerHeader
{
private:
	char m_unmodelled00[ 0x118 ];

public:
	Bool m_field118;
};

class Rva00589320Player
{
public:
	void *m_field00;
	Rva00589320PlayerHeader *m_field04;
	char m_unmodelled08[ 0x250 ];
	Int m_rank258;
	float m_progress25C;
	Int m_field260;
	Int m_points264;
	Int m_upper268;
	Int m_lower26C;
};

class Rva002EE330PlayerList
{
public:
	Rva00589320Player *getLocalPlayer( void );
};

// Retail 0x012ED748 is ?ThePlayerList@@3PAVPlayerList@@A (data_rows.csv,
// RTS/PlayerList.cpp); Rva002EE330ThePlayers was only a pin.
class PlayerList;
extern PlayerList *ThePlayerList;
#define Rva002EE330ThePlayers ( *(Rva002EE330PlayerList **)&ThePlayerList )
#define RVA00590480_PLAYER_LIST Rva002EE330ThePlayers

class Rva00564970
{
public:
	static void go( void );
};

class Player;
class ControlBar
{
public:
	Bool Rva004A0B20( Player *player, Int index );
};

class Rva004A0B20
{
public:
	// ?method@Rva004A0B20@@QAE_NPAVRva00589320Player@@H@Z absent-from-retail
	__forceinline Bool method( Rva00589320Player *player, Int index )
	{
		return ((ControlBar *)this)->Rva004A0B20( (Player *)player, index );
	}
};

extern ControlBar *TheControlBar;
#define RVA00590480_CONTROL_BAR ((Rva004A0B20 *)TheControlBar)

extern void *g_obj12F4C38;

extern void Rva00564340( Bool on );
extern void Rva00564750( Bool on );
extern void Rva005642F0( Bool on );
extern char bfmeSetRankYX( Int rank );
extern void bfmeGoEACa( Int progress );

struct Rva00590480Flags
{
	unsigned char b0:1, b1:1, b2:1, b3:1, b4:1, b5:1, b6:1, b7:1;
};

class Rva00590480GameClient
{
public:
	void rva00590480( void );

private:
	char m_unmodelled00[ 0x58 ];
	Rva00590480Flags m_flags58;
	char m_unmodelled59[ 3 ];
	Int m_rank5C;
	Int m_points60;
	Int m_progress64;
	char m_unmodelled68[ 0x450 ];
	Bool m_palantir4B8[ 0x0C ];
	Bool m_palantirReady4C4;
};

// ?rva00590480@Rva00590480GameClient@@QAEXXZ
void Rva00590480GameClient::rva00590480( void )
{
	Rva00589320Player *player = RVA00590480_PLAYER_LIST->getLocalPlayer();
	Int playerRank = player->m_rank258;
	Int oldRank = m_rank5C;
	Int zero = 0;
	if ( playerRank != oldRank )
	{
		if ( oldRank >= zero && playerRank > oldRank )
			Rva00564970::go();
		m_rank5C = playerRank;
	}

	if ( !m_flags58.b0 || player->m_points264 != m_points60 )
	{
		Int points = player->m_points264;
		if ( bfmeSetRankYX( points ) != 0 )
		{
			m_flags58.b0 = true;
			m_points60 = player->m_points264;
		}
	}

	Int lower = player->m_lower26C;
	Int delta = player->m_upper268 - lower;
	Int progress;
	if ( delta == zero )
		progress = 1;
	else
	{
		Int raw = (Int)( player->m_progress25C - lower );
		raw = raw * 100 / delta;
		if ( raw < 1 )
			raw = 1;
		if ( raw > 100 )
			raw = 100;
		progress = raw;
	}

	if ( progress != m_progress64 )
	{
		bfmeGoEACa( progress );
		m_progress64 = progress;
	}

	Bool buttonState[ 12 ];
	Int index = 0;
	for ( index = 0; index < 12; ++index )
		buttonState[ index ] = RVA00590480_CONTROL_BAR->method( player, index );

	if ( !m_palantirReady4C4 )
	{
		for ( index = 0; index < 12; ++index )
		{
			if ( buttonState[ index ] &&
				!m_palantir4B8[ index ] )
			{
				m_palantirReady4C4 = true;
				break;
			}
		}
	}
	else
	{
		unsigned char *spellStore = (unsigned char *)g_obj12F4C38;
		if ( spellStore == (unsigned char *)zero ||
			spellStore[ 0x259 ] == (unsigned char)zero )
		{
			Bool *found = _STL::find(buttonState, buttonState + 12, true);
			if ( found == buttonState + 12 )
				m_palantirReady4C4 = false;
		}
		else
			m_palantirReady4C4 = false;
	}

	memmove( m_palantir4B8, buttonState, 12 );
	if ( m_flags58.b4 != m_palantirReady4C4 )
	{
		Rva00564340( m_palantirReady4C4 );
		m_flags58.b4 = m_palantirReady4C4;
	}

	if ( player->m_field04 != (Rva00589320PlayerHeader *)zero )
	{
		Bool playerFlag = player->m_field04->m_field118;
		if ( !m_flags58.b1 || playerFlag != m_flags58.b2 )
		{
			Rva00564750( playerFlag );
			m_flags58.b2 = playerFlag;
			m_flags58.b1 = true;
			m_flags58.b3 = false;
			m_flags58.b4 = false;
			m_flags58.b5 = false;
		}
	}

	if ( !m_flags58.b3 )
	{
		Rva005642F0( true );
		m_flags58.b3 = true;
	}
}
