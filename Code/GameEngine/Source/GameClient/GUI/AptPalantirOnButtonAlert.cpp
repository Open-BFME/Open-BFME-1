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
extern PalantirUIState *g_aptPalantirUIState;
extern WindowManager *g_theWindowManager;
extern int g_aptPalantirWindow;
extern char g_aptPalantirHeroPrefix[];
extern char g_aptPalantirHeroOne[];
extern char g_aptPalantirOne[];
extern char g_aptPalantirNumberFormat[];
extern char g_aptPalantirHideAlert[];

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
			if( strncmp( g_aptPalantirHeroOne, g_aptPalantirHeroPrefix, 4 ) == 0 )
				TheAptPalantir->selectHero( atoi( g_aptPalantirOne ) - 1 );

			char alertNumber[ 16 ] = "";
			sprintf( alertNumber, g_aptPalantirNumberFormat, 1 );
			g_theWindowManager->add( (void *)g_aptPalantirWindow,
				g_aptPalantirHideAlert, 1, alertNumber, 0, 0, 0, 0 );
			break;
		}

		case '2':
			if( !g_aptPalantirUIState->m_busy )
			{
				if( TheAptPalantir->m_alertVisible )
					TheAptPalantir->dismissAlert();
				g_aptPalantirUIState->setInteractive( true );
				g_aptPalantirUIState->showSelection( 1, false );
				setAptPalantirAlertVisible( 2, false );
			}
			break;
	}
}
