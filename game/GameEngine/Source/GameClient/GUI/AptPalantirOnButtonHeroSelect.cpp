class AptPalantirHeroSelector
{
public:
	void selectHero( int index );
};

// Retail 0x012F4B98: use the existing data owner; retain the local pointee view.
extern class AptPalantir *TheAptPalantir;
extern "C" __declspec(dllimport) int __cdecl strncmp( char *left, char *right, int count );
extern "C" __declspec(dllimport) int __cdecl atoi( char *text );

// ?aptPalantirOnButtonHeroSelect@@YAXPAD@Z
void aptPalantirOnButtonHeroSelect( char *hero )
{
	if( strncmp( hero, "Hero", 4 ) != 0 )
		return;

	reinterpret_cast<AptPalantirHeroSelector *>(TheAptPalantir)->selectHero( atoi( hero + 4 ) - 1 );
}
