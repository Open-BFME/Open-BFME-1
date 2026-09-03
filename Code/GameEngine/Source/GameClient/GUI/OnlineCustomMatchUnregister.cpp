// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// BfmeAptScreenOnlineCustomMatch gadget teardown, retail 0x00538E40, 150 bytes.
// Shuts down the +0x40 Gen_00525EE0 member, releases a GameSpyInfo object
// stored at +0x198, and unregisters AptOnlineCustomMatch::InitGadgets.

template <typename T> class StringBase
{
	friend class AsciiString;

private:
	StringBase( const T *text );
	~StringBase();

	void *m_data;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
class AsciiString : private StringBase<char>
{
public:
	AsciiString( const char *text ) : StringBase<char>( text ) {}
	~AsciiString() {}
};

class BfmeAptGameWindow
{
public:
	virtual ~BfmeAptGameWindow() {}

private:
	unsigned char m_unmodelled[ 0x38 ];
};

class BfmeAptScreenSecondary
{
public:
	virtual ~BfmeAptScreenSecondary() {}
};

class Gen_00525EE0
{
public:
	void bfmeShutdown();

private:
	unsigned char m_data[ 0x134 ];
};

#define GAMESPY_SLOT( n ) virtual void gamespySlot##n() = 0
class GameSpyInfo
{
public:
	GAMESPY_SLOT( 0 ); GAMESPY_SLOT( 1 ); GAMESPY_SLOT( 2 ); GAMESPY_SLOT( 3 );
	GAMESPY_SLOT( 4 ); GAMESPY_SLOT( 5 ); GAMESPY_SLOT( 6 ); GAMESPY_SLOT( 7 );
	GAMESPY_SLOT( 8 ); GAMESPY_SLOT( 9 ); GAMESPY_SLOT( 10 ); GAMESPY_SLOT( 11 );
	GAMESPY_SLOT( 12 ); GAMESPY_SLOT( 13 ); GAMESPY_SLOT( 14 ); GAMESPY_SLOT( 15 );
	GAMESPY_SLOT( 16 ); GAMESPY_SLOT( 17 ); GAMESPY_SLOT( 18 ); GAMESPY_SLOT( 19 );
	GAMESPY_SLOT( 20 ); GAMESPY_SLOT( 21 ); GAMESPY_SLOT( 22 ); GAMESPY_SLOT( 23 );
	GAMESPY_SLOT( 24 ); GAMESPY_SLOT( 25 ); GAMESPY_SLOT( 26 ); GAMESPY_SLOT( 27 );
	GAMESPY_SLOT( 28 ); GAMESPY_SLOT( 29 ); GAMESPY_SLOT( 30 ); GAMESPY_SLOT( 31 );
	GAMESPY_SLOT( 32 ); GAMESPY_SLOT( 33 ); GAMESPY_SLOT( 34 ); GAMESPY_SLOT( 35 );
	GAMESPY_SLOT( 36 ); GAMESPY_SLOT( 37 ); GAMESPY_SLOT( 38 ); GAMESPY_SLOT( 39 );
	GAMESPY_SLOT( 40 ); GAMESPY_SLOT( 41 ); GAMESPY_SLOT( 42 ); GAMESPY_SLOT( 43 );
	GAMESPY_SLOT( 44 ); GAMESPY_SLOT( 45 ); GAMESPY_SLOT( 46 ); GAMESPY_SLOT( 47 );
	GAMESPY_SLOT( 48 ); GAMESPY_SLOT( 49 ); GAMESPY_SLOT( 50 ); GAMESPY_SLOT( 51 );
	GAMESPY_SLOT( 52 ); GAMESPY_SLOT( 53 ); GAMESPY_SLOT( 54 ); GAMESPY_SLOT( 55 );
	GAMESPY_SLOT( 56 ); GAMESPY_SLOT( 57 );
	virtual void releaseStagingObject( void *object ) = 0;
};
#undef GAMESPY_SLOT

void _bfme_closeAptScreen( const AsciiString &name );

extern GameSpyInfo *TheGameSpyInfo;

class BfmeAptScreenOnlineCustomMatch : public BfmeAptGameWindow, public BfmeAptScreenSecondary
{
public:
	void unregisterInitGadgets();

private:
	Gen_00525EE0 m_setup;
	unsigned char m_prefsHead[ 0x24 ];
	void *m_stagingObject;
	unsigned char m_prefsMid[ 0x28 ];
	int m_clearedFlag;
};

void BfmeAptScreenOnlineCustomMatch::unregisterInitGadgets()
{
	m_setup.bfmeShutdown();
	void *staging = m_stagingObject;
	m_clearedFlag = 0;
	if( staging )
	{
		if( TheGameSpyInfo )
		{
			TheGameSpyInfo->releaseStagingObject( staging );
			m_stagingObject = 0;
		}
	}
	{
		AsciiString callback( "AptOnlineCustomMatch::InitGadgets" );
		_bfme_closeAptScreen( callback );
	}
}
