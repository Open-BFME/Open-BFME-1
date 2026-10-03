// cl: /DNDEBUG /MD /EHsc /Igame/Libraries/Source/WWVegas/WWLib

#include "ascii_string.h"

class Rva0058C100CommandManager
{
public:
	void *find( const AsciiString *name );
	void execute( int value, void *command );
};

extern void j_0003b59d( void );
extern void j_0003bccd( void );

typedef void *(Rva0058C100CommandManager::*Rva0058C100FindMethod)(const AsciiString *);
typedef void (Rva0058C100CommandManager::*Rva0058C100ExecuteMethod)(int, void *);

// Retail global 0x012F33F8; the canonical mangled spelling is
// ?TheControlBar@@3PAVControlBar@@A, so the pointee must be the real
// ControlBar and only the calls need the TU-local view of it.
class ControlBar;
extern ControlBar *TheControlBar;

void __stdcall rva0058C100ObserveNext( void * )
{
	void *command;
	{
		AsciiString name( "NonCommand_ObserveNextPlayer" );
		union { void (*raw)(void); Rva0058C100FindMethod method; } find;
		find.raw = j_0003b59d;
		command = (((Rva0058C100CommandManager *)TheControlBar)->*find.method)( &name );
	}
	if( command )
	{
		union { void (*raw)(void); Rva0058C100ExecuteMethod method; } execute;
		execute.raw = j_0003bccd;
		(((Rva0058C100CommandManager *)TheControlBar)->*execute.method)( 0, command );
	}
}

void __stdcall rva0058C1A0ObservePrior( void * )
{
	void *command;
	{
		AsciiString name( "NonCommand_ObservePriorPlayer" );
		union { void (*raw)(void); Rva0058C100FindMethod method; } find;
		find.raw = j_0003b59d;
		command = (((Rva0058C100CommandManager *)TheControlBar)->*find.method)( &name );
	}
	if( command )
	{
		union { void (*raw)(void); Rva0058C100ExecuteMethod method; } execute;
		execute.raw = j_0003bccd;
		(((Rva0058C100CommandManager *)TheControlBar)->*execute.method)( 0, command );
	}
}
