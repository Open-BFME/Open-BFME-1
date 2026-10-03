// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// _Rva0051D2A0ForwardEnabled / _Rva0051D2C0ForwardDisabled
//
// Both forwarders push their two arguments plus a mode word and call retail
// 0x0003EA45, the incremental-link thunk that jumps to the body at 0x0051D1E0:
// ?Rva0051D1E0Shutdown@@YAH_NPAX0@Z, matched in Rva0051D1E0Shutdown.cpp. That
// is the name the reference must carry.
//
// Its third parameter is declared bool there (the `0` in the decorated name is
// MSVC's back-reference to argument 0), and passing a void * straight into that
// bool makes the compiler emit the pointer-to-bool test/setne pair retail does
// not have. Calling through a pointer to the same symbol, typed to the argument
// list retail actually pushes, keeps the cdecl pushes and the callee name.
typedef bool Bool;

int Rva0051D1E0Shutdown( Bool mode, void *unused, Bool enabled );

typedef void ( *ForwardCall )( int, void *, void * );

extern "C" void Rva0051D2A0ForwardEnabled( void *first, void *second )
{
	union { int ( *asShutdown )( Bool, void *, Bool ); ForwardCall asTyped; } callee;
	callee.asShutdown = Rva0051D1E0Shutdown;
	callee.asTyped( 1, first, second );
}

extern "C" void Rva0051D2C0ForwardDisabled( void *first, void *second )
{
	union { int ( *asShutdown )( Bool, void *, Bool ); ForwardCall asTyped; } callee;
	callee.asShutdown = Rva0051D1E0Shutdown;
	callee.asTyped( 0, first, second );
}