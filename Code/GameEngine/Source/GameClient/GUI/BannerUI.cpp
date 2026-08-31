// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /Ireference/shims/stlp_nodealloc /Ireference/shims/sweep /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main
// stlport
//
// The BannerUI block -- BFME's unit banners, which Zero Hour has no equivalent
// for. One global settings object, parsed straight into.
//
// Several names here are ours rather than retail's, and it is worth being
// explicit about which. The block keyword "BannerUI" comes from the registry,
// so the settings class is named. The pointer at 0x012F4B70 is not: nothing in
// the image names it, and the only matched rows that touch it are InGameUI's
// constructor, destructor and update, which say where it is owned but not what
// it is called. The parser name follows the keyword. The callback at 0x00582C70
// is installed by BannerUI's selected-entry routine at 0x00583190, and its
// current-id global and removal member are likewise unnamed, so their names
// below describe that proven ownership and behavior rather than claiming a
// recovered retail spelling.
#define BFME_STLP_NODE_ALLOC 1
#include "PreRTS.h"
#include "Common/INI.h"
#include <algorithm>
#include <vector>

struct BannerMovieEntry
{
	int m_unmodelled;
	int m_id;
	unsigned char m_unmodelled_08[ 20 ];
};

class BannerMovieEntryMatches
{
public:
	BannerMovieEntryMatches( int id ) : m_id( id ) {}
	bool operator()( const BannerMovieEntry &entry ) const { return entry.m_id == m_id; }

private:
	int m_id;
};

namespace _STL
{
	void vectorLargeDeallocate( void *memory );
	void vectorSmallDeallocate( void *memory, unsigned int bytes );
}

class BannerMovieEntryVector
{
public:
	typedef BannerMovieEntry *iterator;
	iterator begin() { return m_start; }
	iterator end() { return m_finish; }
	void clear() { m_finish = std::copy( m_finish, m_finish, m_start ); }
	iterator erase( iterator entry )
	{
		if( entry + 1 != m_finish )
			std::copy( entry + 1, m_finish, entry );
		--m_finish;
		return entry;
	}
	__forceinline ~BannerMovieEntryVector()
	{
		if( m_start )
		{
			unsigned int bytes = ( m_capacity - m_start ) * sizeof( BannerMovieEntry );
			if( bytes > 128 )
				_STL::vectorLargeDeallocate( m_start );
			else
				_STL::vectorSmallDeallocate( m_start, bytes );
		}
	}

private:
	BannerMovieEntry *m_start;
	BannerMovieEntry *m_finish;
	BannerMovieEntry *m_capacity;
};

class BannerSubsystemBase
{
public:
	virtual ~BannerSubsystemBase();

private:
	void *m_name;
};

class BannerTypeStoreMember
{
public:
	~BannerTypeStoreMember();

private:
	unsigned char m_data[ 0x14 ];
};

class BannerStringMember
{
public:
	~BannerStringMember();

private:
	void *m_data;
};

class BannerTimerAsciiString
{
public:
	~BannerTimerAsciiString();

private:
	void *m_data;
};

struct BannerTimerEntry
{
	BannerTimerAsciiString m_first;
	BannerTimerAsciiString m_second;
	BannerStringMember m_third;
};

typedef _STL::vector<BannerTimerEntry> BannerTimerEntries;

class BannerTimerMember
{
public:
	__declspec( noinline ) ~BannerTimerMember();

private:
	BannerTimerEntries m_entries;
};

// ??1BannerTimerMember@@QAE@XZ
BannerTimerMember::~BannerTimerMember()
{
}

class BannerUI : public BannerSubsystemBase
{
public:
	static const FieldParse m_fieldParseTable[];
	virtual ~BannerUI();
	virtual void init();
	virtual void reset();
	void removeMovieBanner( int id );
	void removeCurrentBannerMovie();
	void hide( bool immediate );

private:
	BannerTypeStoreMember m_bannerTypes;
	BannerStringMember m_unmodelledString;
	BannerTimerMember m_bannerTimer;
	int m_windowIndex;
	BannerMovieEntryVector m_movieEntries;
	bool m_hidden;
	unsigned char m_unmodelled_3D[ 3 ];
	int m_currentLocation;
};

extern BannerUI *TheBannerUI;

class BfmeDisplayMovie
{
public:
	#define BFME_DISPLAY_SLOT( n ) virtual void bfmeDisplaySlot##n() = 0
	BFME_DISPLAY_SLOT( 0 ); BFME_DISPLAY_SLOT( 1 ); BFME_DISPLAY_SLOT( 2 );
	BFME_DISPLAY_SLOT( 3 ); BFME_DISPLAY_SLOT( 4 ); BFME_DISPLAY_SLOT( 5 );
	BFME_DISPLAY_SLOT( 6 ); BFME_DISPLAY_SLOT( 7 ); BFME_DISPLAY_SLOT( 8 );
	BFME_DISPLAY_SLOT( 9 ); BFME_DISPLAY_SLOT( 10 ); BFME_DISPLAY_SLOT( 11 );
	BFME_DISPLAY_SLOT( 12 ); BFME_DISPLAY_SLOT( 13 ); BFME_DISPLAY_SLOT( 14 );
	BFME_DISPLAY_SLOT( 15 ); BFME_DISPLAY_SLOT( 16 ); BFME_DISPLAY_SLOT( 17 );
	BFME_DISPLAY_SLOT( 18 ); BFME_DISPLAY_SLOT( 19 ); BFME_DISPLAY_SLOT( 20 );
	BFME_DISPLAY_SLOT( 21 ); BFME_DISPLAY_SLOT( 22 ); BFME_DISPLAY_SLOT( 23 );
	BFME_DISPLAY_SLOT( 24 ); BFME_DISPLAY_SLOT( 25 ); BFME_DISPLAY_SLOT( 26 );
	BFME_DISPLAY_SLOT( 27 ); BFME_DISPLAY_SLOT( 28 ); BFME_DISPLAY_SLOT( 29 );
	BFME_DISPLAY_SLOT( 30 ); BFME_DISPLAY_SLOT( 31 ); BFME_DISPLAY_SLOT( 32 );
	BFME_DISPLAY_SLOT( 33 ); BFME_DISPLAY_SLOT( 34 ); BFME_DISPLAY_SLOT( 35 );
	BFME_DISPLAY_SLOT( 36 ); BFME_DISPLAY_SLOT( 37 ); BFME_DISPLAY_SLOT( 38 );
	BFME_DISPLAY_SLOT( 39 ); BFME_DISPLAY_SLOT( 40 ); BFME_DISPLAY_SLOT( 41 );
	BFME_DISPLAY_SLOT( 42 ); BFME_DISPLAY_SLOT( 43 ); BFME_DISPLAY_SLOT( 44 );
	BFME_DISPLAY_SLOT( 45 ); BFME_DISPLAY_SLOT( 46 ); BFME_DISPLAY_SLOT( 47 );
	BFME_DISPLAY_SLOT( 48 ); BFME_DISPLAY_SLOT( 49 ); BFME_DISPLAY_SLOT( 50 );
	BFME_DISPLAY_SLOT( 51 ); BFME_DISPLAY_SLOT( 52 ); BFME_DISPLAY_SLOT( 53 );
	BFME_DISPLAY_SLOT( 54 ); BFME_DISPLAY_SLOT( 55 ); BFME_DISPLAY_SLOT( 56 );
	BFME_DISPLAY_SLOT( 57 ); BFME_DISPLAY_SLOT( 58 );
	#undef BFME_DISPLAY_SLOT
	virtual void stopMovie() = 0;
	virtual bool isMoviePlaying() = 0;
	virtual void bfmeDisplaySlot61() = 0;
	virtual bool bfmeMovieState() = 0;
};

class Display;
class GlobalData;

struct BfmeGlobalDataMovieState
{
	unsigned char m_unmodelled[ 0xA7D ];
	bool m_allowMovieExit;
};

extern Display *TheDisplay;
extern GlobalData *TheWritableGlobalData;
extern int TheCurrentBannerMovie;

template <typename T> class BannerStringBase
{
	friend class BFMERetailAsciiString;

private:
	BannerStringBase( const T *text );
};

class BFMERetailAsciiString
{
public:
	BFMERetailAsciiString() : m_data( 0 ) {}
	BFMERetailAsciiString( const char *text )
	{
		((BannerStringBase<char> *)this)->BannerStringBase<char>::BannerStringBase( text );
	}
	~BFMERetailAsciiString() { releaseBuffer(); }
	void __cdecl format( BFMERetailAsciiString format, ... );

private:
	void releaseBuffer();
	void *m_data;
};

class WindowManager
{
public:
	#define WINDOW_MANAGER_SLOT( n ) virtual void windowManagerSlot##n() = 0
	WINDOW_MANAGER_SLOT( 0 ); WINDOW_MANAGER_SLOT( 1 ); WINDOW_MANAGER_SLOT( 2 );
	WINDOW_MANAGER_SLOT( 3 ); WINDOW_MANAGER_SLOT( 4 ); WINDOW_MANAGER_SLOT( 5 );
	WINDOW_MANAGER_SLOT( 6 ); WINDOW_MANAGER_SLOT( 7 ); WINDOW_MANAGER_SLOT( 8 );
	WINDOW_MANAGER_SLOT( 9 ); WINDOW_MANAGER_SLOT( 10 ); WINDOW_MANAGER_SLOT( 11 );
	WINDOW_MANAGER_SLOT( 12 ); WINDOW_MANAGER_SLOT( 13 ); WINDOW_MANAGER_SLOT( 14 );
	#undef WINDOW_MANAGER_SLOT
	virtual int loadAptWindow( BFMERetailAsciiString directory, BFMERetailAsciiString file,
		int unknown1, int unknown2, int unknown3 ) = 0;
	void removeAptObject( const BFMERetailAsciiString &name );
	bool hideAptWindow( int index );
	bool showAptWindow( int index );
};

extern WindowManager *g_theWindowManager;
extern void DeleteBanner( int id );
extern void registerBannerAptCallbacks();

void parseBannerUI( INI *ini )
{
	ini->initFromINI( TheBannerUI, BannerUI::m_fieldParseTable );
}

int finishBannerMovie()
{
	int result = 0;

	if( !reinterpret_cast<BfmeDisplayMovie *>( TheDisplay )->isMoviePlaying() ||
		reinterpret_cast<BfmeDisplayMovie *>( TheDisplay )->bfmeMovieState() ||
		reinterpret_cast<BfmeGlobalDataMovieState *>( TheWritableGlobalData )->m_allowMovieExit )
	{
		if( TheCurrentBannerMovie != -1 )
		{
			int id = TheCurrentBannerMovie;
			TheCurrentBannerMovie = -1;
			TheBannerUI->removeMovieBanner( id );
		}

		reinterpret_cast<BfmeDisplayMovie *>( TheDisplay )->stopMovie();
		result = 2;
	}

	return result;
}

void BannerUI::removeCurrentBannerMovie()
{
	if( TheCurrentBannerMovie != -1 )
	{
		int id = TheCurrentBannerMovie;
		TheCurrentBannerMovie = -1;
		removeMovieBanner( id );
	}
}

void BannerUI::removeMovieBanner( int id )
{
	if( TheCurrentBannerMovie == id )
		return;

	BannerMovieEntryVector::iterator entry =
		std::find_if( m_movieEntries.begin(), m_movieEntries.end(), BannerMovieEntryMatches( id ) );
	if( entry != m_movieEntries.end() )
	{
		DeleteBanner( id );
		reinterpret_cast<std::vector<BannerMovieEntry> &>( m_movieEntries ).erase( entry );
	}
}

void BannerUI::hide( bool immediate )
{
	if( g_theWindowManager )
	{
		m_hidden = immediate;
		if( immediate )
		{
			g_theWindowManager->hideAptWindow( m_windowIndex );
			m_movieEntries.clear();
		}
		else
		{
			g_theWindowManager->showAptWindow( m_windowIndex );
		}
	}
}

void BannerUI::init()
{
	if( TheBannerUI )
	{
		m_windowIndex = g_theWindowManager->loadAptWindow(
			"Apt\\", "BannerUI.apt", 0, 0, -1 );
		registerBannerAptCallbacks();
	}
}

void BannerUI::reset()
{
	hide( true );
	m_movieEntries.clear();
}

BannerUI::~BannerUI()
{
	if( g_theWindowManager )
	{
		for( unsigned int location = 0; location < 2; ++location )
		{
			BFMERetailAsciiString name;
			name.format( "BannerUI/~Location%d/Banner/AvailableBttn/", location );
			g_theWindowManager->removeAptObject( name );
			name.format( "BannerUI/~Location%d/Banner/WaitingBttn/", location );
			g_theWindowManager->removeAptObject( name );
			name.format( "BannerUI/~Location%d/Banner/Background", location );
			g_theWindowManager->removeAptObject( name );
		}
	}
}

template void std::vector<BannerMovieEntry>::push_back( const BannerMovieEntry &entry );
