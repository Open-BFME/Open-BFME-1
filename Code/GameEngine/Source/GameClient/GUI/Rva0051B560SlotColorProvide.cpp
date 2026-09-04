// cl: /O2
// thiscall @ 0x0051B560, 114 bytes, ret 0xC. Apt-style provide: if the
// setting flag is clear, look up m_map[index] as a GameInfo slot, and
// sprintf the occupied slot's apparent MultiplayerColorDefinition::m_color
// as "%d". Same `*(unsigned short *)out = '0'` default as
// BfmeAptScreenScoreScreen::bfmeProvide. Callees are the landed GameInfo /
// GameSlot / MultiplayerSettings methods. Host name is address-derived.

class GameSlot
{
public:
	bool isOccupied( void ) const;
	int getApparentColor( void ) const;
};

class GameInfo
{
public:
	GameSlot *getSlot( int index );
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

class Rva0051B560Host
{
public:
	void bfmeProvide( int index, char *output, bool setting );

private:
	char m_lead[ 0x58 ];
	GameInfo *m_game;
	int m_gap;
	int m_map[ 8 ];
};

void Rva0051B560Host::bfmeProvide( int index, char *output, bool setting )
{
	if ( setting )
		return;
	if ( index >= 8 )
		return;
	int mapped = m_map[ index ];
	if ( mapped < 0 )
		return;
	if ( mapped >= 8 )
		return;
	*(unsigned short *)output = (unsigned short)'0';
	if ( !m_game )
		return;
	GameSlot *slot = m_game->getSlot( mapped );
	if ( !slot )
		return;
	if ( !slot->isOccupied() )
		return;
	MultiplayerColorDefinition *def =
		TheMultiplayerSettings->getColor( slot->getApparentColor() );
	sprintf( output, "%d", def->m_color );
}
