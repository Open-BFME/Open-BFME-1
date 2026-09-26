extern "C" __declspec(dllimport) int __cdecl strncmp(
	const char *left, const char *right, unsigned int count );
extern "C" __declspec(dllimport) int __cdecl atoi( const char *text );

class AptPalantir
{
public:
	void selectSpell( int index );
};

extern AptPalantir *TheAptPalantir;
extern char g_aptPalantirSpellPrefix[];

// ?aptPalantirOnButtonSpell@@YAXPAD@Z
void aptPalantirOnButtonSpell( char *spell )
{
	if( spell == 0 )
		return;

	if( strncmp( spell, g_aptPalantirSpellPrefix, 5 ) != 0 )
		return;

	TheAptPalantir->selectSpell( atoi( spell + 5 ) - 1 );
}
