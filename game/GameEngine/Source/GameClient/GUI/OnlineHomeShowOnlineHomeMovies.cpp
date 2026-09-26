// cl: /O2 /Ob2 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// OnlineHome's ShowOnlineHomeMovies value provider, retail 0x00547090.
// The constructor at 0x005484E0 binds the callback through ILT 0x000385E1.

extern "C" __declspec( dllimport ) char * __cdecl _itoa(
	int value, char *buffer, int radix );
extern "C" char * __cdecl strcpy( char *destination, const char *source );

class PSPlayerStats
{
public:
	PSPlayerStats( const PSPlayerStats &other );
	~PSPlayerStats();

	int m_id;
	char m_beforeLastSide[ 0x178 - 4 ];
	int m_lastSide;
	char m_afterLastSide[ 0x1C4 - 0x17C ];
};

typedef char PSPlayerStatsSizeCheck[ sizeof( PSPlayerStats ) == 0x1C4 ? 1 : -1 ];

class GameSpyInfo
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4C();
	virtual void slot50();
	virtual void slot54();
	virtual void slot58();
	virtual void slot5C();
	virtual void slot60();
	virtual void slot64();
	virtual void slot68();
	virtual void slot6C();
	virtual void slot70();
	virtual void slot74();
	virtual void slot78();
	virtual void slot7C();
	virtual void slot80();
	virtual void slot84();
	virtual void slot88();
	virtual void setCachedLocalPlayerStats( PSPlayerStats stats );
	virtual PSPlayerStats getCachedLocalPlayerStats( void );
};

class BfmeAptScreenOnlineHome
{
public:
	void showOnlineHomeMovies( const char *selector, void *value, bool setting );
};

// ?showOnlineHomeMovies@BfmeAptScreenOnlineHome@@QAEXPBDPAX_N@Z
void BfmeAptScreenOnlineHome::showOnlineHomeMovies(
	const char *selector, void *value, bool setting )
{
	char *output = (char *)value;
	if( !setting )
		output[ 0 ] = '\0';

	if( selector || setting )
		return;

	char buffer[ 16 ];
	GameSpyInfo *info = *(GameSpyInfo **)0x012F7194;
	PSPlayerStats stats = info->getCachedLocalPlayerStats();
	int side = stats.m_lastSide;
	switch( side )
	{
	case 0:
		_itoa( 0, buffer, 10 );
		break;
	case 2:
		_itoa( 2, buffer, 10 );
		break;
	case 3:
		_itoa( 3, buffer, 10 );
		break;
	default:
		_itoa( 1, buffer, 10 );
		break;
	}
	strcpy( output, buffer );
}
