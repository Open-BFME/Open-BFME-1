extern "C" __declspec(dllimport) int __cdecl strncmp(
	const char *left, const char *right, unsigned int count );
extern "C" __declspec(dllimport) int __cdecl atoi( const char *text );

// Retail calls ILT 0x1EDDA -> 0x00589700, matched as BfmeThingAAB::bfmeGoAAB
// (BfmeThreeHundredEightyOne.cpp).
class BfmeThingAAB
{
public:
	void bfmeGoAAB( int index );
};

class AptPalantir
{
public:
	__forceinline void selectSpell( int index )
	{
		reinterpret_cast<BfmeThingAAB *>( this )->bfmeGoAAB( index );
	}
};

extern AptPalantir *TheAptPalantir;

// ?aptPalantirOnButtonSpell@@YAXPAD@Z
void aptPalantirOnButtonSpell( char *spell )
{
	if( spell == 0 )
		return;

	if( strncmp( spell, "Spell", 5 ) != 0 )
		return;

	TheAptPalantir->selectSpell( atoi( spell + 5 ) - 1 );
}
