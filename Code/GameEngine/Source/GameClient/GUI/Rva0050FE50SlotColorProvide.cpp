// cl: /O2
// thiscall @ 0x0050FE50, 82 bytes, ret 0xC.  This is the compact APT
// provider which turns a GameInfo slot's apparent colour into the decimal
// colour value expected by the movie.

class GameSlot
{
public:
	int getApparentColor( void ) const;
};

class GameInfo
{
public:
	const GameSlot *getConstSlot( int index ) const;
};

class MultiplayerColorDefinition
{
public:
	char m_pad[ 0x10 ];
	int m_color;
};

class MultiplayerSettings
{
public:
	MultiplayerColorDefinition *getColor( int which );
};

extern MultiplayerSettings *TheMultiplayerSettings;

extern "C" __declspec( dllimport ) int __cdecl sprintf(
	char *destination, const char *format, ... );

class Rva0050FE50Host
{
public:
	void bfmeProvide( int index, char *output, bool setting );

private:
	char m_pad[ 0x34 ];
	GameInfo *m_game;
};

void Rva0050FE50Host::bfmeProvide( int index, char *output, bool setting )
{
	if ( setting )
		return;

	*(unsigned short *)output = (unsigned short)'0';
	if ( index < 0 || index >= 8 )
		return;

	const GameSlot *slot = m_game->getConstSlot( index );
	MultiplayerColorDefinition *color =
		TheMultiplayerSettings->getColor( slot->getApparentColor() );
	sprintf( output, "%d", color->m_color );
}
