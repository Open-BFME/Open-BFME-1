class AptPalantirCommandHandler
{
public:
	void selectCommand( int index );
};

extern AptPalantirCommandHandler *g_bfmeW1026;
extern "C" __declspec(dllimport) int __cdecl strncmp( char *left, char *right, int count );

// ?aptPalantirOnButtonCommand@@YAXPAD@Z
void aptPalantirOnButtonCommand( char *command )
{
	if( command == 0 )
		return;

	if( strncmp( command, "Command", 7 ) != 0 )
		return;

	g_bfmeW1026->selectCommand( command[ 7 ] - '1' );
}
