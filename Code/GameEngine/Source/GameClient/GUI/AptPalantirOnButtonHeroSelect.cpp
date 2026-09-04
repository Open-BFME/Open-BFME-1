class AptPalantirHeroSelector
{
public:
	void selectHero( int index );
};

extern AptPalantirHeroSelector *g_bfmeW1027;
extern char g_bfmeKey1027[];
__declspec(dllimport) int __cdecl bfmeCmp1027( char *left, char *right, int count );
__declspec(dllimport) int __cdecl bfmeAtoi1027( char *text );

// ?aptPalantirOnButtonHeroSelect@@YAXPAD@Z
void aptPalantirOnButtonHeroSelect( char *hero )
{
	if( bfmeCmp1027( hero, g_bfmeKey1027, 4 ) != 0 )
		return;

	g_bfmeW1027->selectHero( bfmeAtoi1027( hero + 4 ) - 1 );
}
