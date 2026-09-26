// ?d_00590480@@YAXXZ
// partial score=0.62 date=2026-09-17
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// Retail 0x00590480 (498 B).  The caller at 0x00598950 is the proven
// GameClient::update vtable slot and passes its GameClient this pointer in
// ECX.  The method name below remains address-qualified; only the owner and
// the fields used by the body are established by the caller and neighbours.

typedef int Int;
typedef bool Bool;

extern "C" long __ftol2( double value );
extern "C" __declspec(dllimport) void *__cdecl memmove(
	void *destination, const void *source, unsigned int bytes );

class Rva00589320PlayerHeader
{
private:
	char m_unmodelled00[ 0x118 ];

public:
	unsigned char m_field118;
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
	volatile Int m_points264;
	Int m_upper268;
	Int m_lower26C;
};

class Rva002EE330PlayerList
{
public:
	Rva00589320Player *getLocalPlayer( void );
};

#pragma comment( linker, "/alternatename:?getLocalPlayer@Rva002EE330PlayerList@@QAEPAVRva00589320Player@@XZ=?j_0000762b@@YAXXZ" )

#define RVA00590480_PLAYER_LIST (*(Rva002EE330PlayerList **)0x012ED748)

class Rva00564970
{
public:
	static void go( void );
};

class Rva004A0B20ControlBar
{
public:
	Bool classify( Rva00589320Player *player, Int index );
};

#pragma comment( linker, "/alternatename:?classify@Rva004A0B20ControlBar@@QAE_NPAVRva00589320Player@@H@Z=?j_00030ad0@@YAXXZ" )

#define RVA00590480_CONTROL_BAR (*(Rva004A0B20ControlBar **)0x012F33F8)

namespace _STL
{
struct random_access_iterator_tag
{
};

template <class Iterator, class Value>
Iterator __find( Iterator first, Iterator last, const Value &value,
	const random_access_iterator_tag &tag );

template <>
char *__find<char *, char>( char *first, char *last, const char &value,
	const random_access_iterator_tag &tag );
}

extern void Rva00564340( Bool on );
extern void Rva00564750( Bool on );
extern void Rva005642F0( Bool on );
extern char bfmeSetRankYX( Int rank );
extern void bfmeGoEACa( Int progress );

class Rva00590480GameClient
{
public:
	void rva00590480( void );

private:
	char m_unmodelled00[ 0x58 ];
	unsigned char m_flags58;
	char m_unmodelled59[ 3 ];
	Int m_rank5C;
	Int m_points60;
	Int m_progress64;
	char m_unmodelled68[ 0x450 ];
	unsigned char m_palantir4B8[ 0x0C ];
	unsigned char m_palantirReady4C4;
};

void Rva00590480GameClient::rva00590480( void )
{
	Rva00589320Player *player = RVA00590480_PLAYER_LIST->getLocalPlayer();
	Int playerRank = player->m_rank258;
	Int oldRank = m_rank5C;
	Int zero = 0;
	__asm xor ebx, ebx
	if ( playerRank != oldRank )
	{
		if ( oldRank >= zero && playerRank > oldRank )
			Rva00564970::go();
		m_rank5C = playerRank;
	}

	if ( (m_flags58 & 1) != 0 )
	{
		if ( player->m_points264 != m_points60 )
		{
			Int points = player->m_points264;
			if ( bfmeSetRankYX( points ) != 0 )
			{
				m_flags58 |= 1;
				m_points60 = player->m_points264;
			}
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
			progress = 1;
		else if ( raw > 100 )
			progress = 100;
		else
			progress = raw;
	}

	if ( progress != m_progress64 )
	{
		bfmeGoEACa( progress );
		m_progress64 = progress;
	}

	unsigned char buttonState[ 12 ];
	Int index = 0;
	for ( index = 0; index < 12; ++index )
		buttonState[ index ] = RVA00590480_CONTROL_BAR->classify( player, index );

	if ( m_palantirReady4C4 == (unsigned char)zero )
	{
		for ( index = 0; index < 12; ++index )
		{
			if ( buttonState[ index ] == (unsigned char)zero &&
				m_palantir4B8[ index ] == (unsigned char)zero )
			{
				m_palantirReady4C4 = 1;
				break;
			}
		}
	}
	else
	{
		unsigned char *spellStore = *(unsigned char **)0x012F4C38;
		if ( spellStore == (unsigned char *)zero ||
			spellStore[ 0x259 ] == (unsigned char)zero )
		{
			char searchValue = 1;
			_STL::random_access_iterator_tag tag;
			char *found = _STL::__find(
				(char *)buttonState, (char *)buttonState + 12,
				searchValue, tag );
			if ( found == (char *)buttonState )
				m_palantirReady4C4 = 0;
		}
		else
			m_palantirReady4C4 = 0;
	}

	memmove( m_palantir4B8, buttonState, 12 );
	unsigned char ready = m_palantirReady4C4;
	if ( ((m_flags58 >> 4) & 1) != ready )
	{
		Rva00564340( ready != 0 );
		m_flags58 = (unsigned char)((m_flags58 & 0xEF) | (ready << 4));
	}

	if ( player->m_field04 != (Rva00589320PlayerHeader *)zero )
	{
		unsigned char playerFlag = player->m_field04->m_field118;
		if ( (m_flags58 & 2) == 0 || ((m_flags58 >> 2) & 1) != playerFlag )
		{
			Rva00564750( playerFlag != 0 );
			m_flags58 = (unsigned char)((m_flags58 & 0xC3) |
				((playerFlag & 1) << 2) | 2);
		}
	}

	if ( (m_flags58 & 8) == 0 )
	{
		Rva005642F0( true );
		m_flags58 |= 8;
	}
}

#pragma comment( linker, "/alternatename:?rva00590480@Rva00590480GameClient@@QAEXXZ=?j_00590480@@YAXXZ" )
