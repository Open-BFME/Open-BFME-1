typedef bool Bool;

class AptPalantir
{
public:
	void dismissAlert();
	void selectHero( int index );

	unsigned char m_unmodelled00[ 0x48 ];
	Bool m_alertVisible;
};

class PalantirUIState
{
public:
	virtual void unused0();
	virtual void unused1();
	virtual void unused2();
	virtual void unused3();
	virtual void setInteractive( Bool enabled );
	virtual void unused5();
	virtual void unused6();
	virtual void unused7();
	virtual void unused8();
	virtual void unused9();
	virtual void unused10();
	virtual void unused11();
	virtual void showSelection( int index, Bool show );
	unsigned char m_unmodelled04[ 4 ];
	Bool m_busy;
};

class WindowManager
{
public:
	void add( void *window, const char *name, int type, void *value,
		int unused0, int unused1, int unused2, int unused3 );
};

extern AptPalantir *TheAptPalantir;
// The client LivingWorld singleton cell at VA 0x012F7048, defined once by
// game/GameEngine/Source/GameClient/LivingWorld.cpp.  PalantirUIState above is
// this TU's local view of the same pointee, so cast at the use.
class Rva006092D0State;
extern Rva006092D0State *g_rva012F7048LivingWorld;
extern WindowManager *g_rva012F19E8WindowManager;
extern int g_aptPalantirWindow;
extern char g_aptPalantirHeroOne[];
extern char g_aptPalantirOne[];
extern char g_aptPalantirNumberFormat[];

extern "C" __declspec(dllimport) int __cdecl strncmp(
	const char *left, const char *right, unsigned int count );
extern "C" __declspec(dllimport) int __cdecl atoi( const char *text );
extern "C" __declspec(dllimport) int __cdecl sprintf(
	char *destination, const char *format, ... );

void setAptPalantirAlertVisible( int index, Bool visible );

// ?aptPalantirOnButtonAlert@@YAXPAD@Z
void aptPalantirOnButtonAlert( char *command )
{
	switch( *command )
	{
		case '1':
		{
			if( strncmp( g_aptPalantirHeroOne, "Hero", 4 ) == 0 )
				TheAptPalantir->selectHero( atoi( g_aptPalantirOne ) - 1 );

			char alertNumber[ 16 ] = "";
			sprintf( alertNumber, g_aptPalantirNumberFormat, 1 );
			g_rva012F19E8WindowManager->add( (void *)g_aptPalantirWindow,
				"HideAlert", 1, alertNumber, 0, 0, 0, 0 );
			break;
		}

		case '2':
			if( !((PalantirUIState *)g_rva012F7048LivingWorld)->m_busy )
			{
				if( TheAptPalantir->m_alertVisible )
					TheAptPalantir->dismissAlert();
				((PalantirUIState *)g_rva012F7048LivingWorld)->setInteractive( true );
				((PalantirUIState *)g_rva012F7048LivingWorld)->showSelection( 1, false );
				setAptPalantirAlertVisible( 2, false );
			}
			break;
	}
}
