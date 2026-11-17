class AptPalantirCommandHandler
{
};

// Retail calls ILT 0x0002B706 (tail thunk 0x005896F0), not a named member body;
// spell the call through the ledgered ?j_0002b706 thunk as a member-pointer call.
extern void j_0002b706();
typedef void (AptPalantirCommandHandler::*SelectCommandFn)( int );

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

	union { void (*fn)(); SelectCommandFn call; } target = { j_0002b706 };
	( reinterpret_cast<AptPalantirCommandHandler *>(TheAptPalantir)->*target.call )( command[ 7 ] - '1' );
}
