class AptPalantirCommandHandler
{
public:
	void selectCommand( int index );
};

extern AptPalantirCommandHandler *g_bfmeW1026;
extern char g_bfmeKey1026[];
__declspec(dllimport) int __cdecl bfmeCmp1026( char *left, char *right, int count );

// ?aptPalantirOnButtonCommand@@YAXPAD@Z
void aptPalantirOnButtonCommand( char *command )
{
	if( command == 0 )
		return;

	if( bfmeCmp1026( command, g_bfmeKey1026, 7 ) != 0 )
		return;

	g_bfmeW1026->selectCommand( command[ 7 ] - '1' );
}
