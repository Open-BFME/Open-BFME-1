class AptPalantirCommandHandler
{
public:
	void selectCommand( int index );
};

// Retail 0x012F4B98: use the existing data owner; retain the local pointee view.
extern class AptPalantir *TheAptPalantir;
extern "C" __declspec(dllimport) int __cdecl strncmp( char *left, char *right, int count );

// ?aptPalantirOnButtonCommand@@YAXPAD@Z
void aptPalantirOnButtonCommand( char *command )
{
	if( command == 0 )
		return;

	if( strncmp( command, "Command", 7 ) != 0 )
		return;

	reinterpret_cast<AptPalantirCommandHandler *>(TheAptPalantir)->selectCommand( command[ 7 ] - '1' );
}
