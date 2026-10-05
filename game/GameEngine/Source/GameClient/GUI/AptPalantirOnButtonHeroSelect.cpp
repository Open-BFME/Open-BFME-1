class AptPalantirHeroSelector
{
public:
	void selectHero( int index );
};

extern AptPalantirHeroSelector *g_bfmeW1027;
extern "C" __declspec(dllimport) int __cdecl strncmp( char *left, char *right, int count );
extern "C" __declspec(dllimport) int __cdecl atoi( char *text );

// ?aptPalantirOnButtonHeroSelect@@YAXPAD@Z
void aptPalantirOnButtonHeroSelect( char *hero )
{
	if( strncmp( hero, "Hero", 4 ) != 0 )
		return;

	g_bfmeW1027->selectHero( atoi( hero + 4 ) - 1 );
}
