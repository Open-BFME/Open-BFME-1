// Six __cdecl one-argument functions that convert their argument with the CRT
// `atoi` and hand the result, plus a per-function constant, to one __thiscall
// member of a global object:
//
//     mov eax,[esp+4] / push <0..5> / push eax
//     call dword ptr [__imp__atoi] / mov ecx,[<GLOBAL>] / add esp,4
//     push eax / call <REL32> / ret
//
// WHAT THE BYTES SHOW.  The stack accounting is what decides the shape.  The
// import is __cdecl and takes ONE argument, which is why only four bytes are
// popped after it; the `push <0..5>` that precedes it is therefore not its
// argument at all but the SECOND argument of the member call, pushed first
// because arguments go out right-to-left and the first one has to be computed.
// The member call then pops eight, which makes it __thiscall with two stack
// arguments, and the whole function balances.  0x01359384 is MSVCR71's `atoi`
// slot, read out of the import directory.
//
// ONE CALLEE, ONE GLOBAL, SIX CONSTANTS.  All six call the same thunk
// (0x00039FEF, body 0x00587600) on the same global at 0x012F4B78 and differ in
// nothing but the immediate 0, 1, 2, 3, 4, 5 -- a hand-written run of adjacent
// entry points, laid out consecutively at 0x0051A700..0x0051A7F0.
//
// IDENTITY IS NOT RECOVERED.  Names are address-derived.  Nothing in the bytes
// says the constant is an enum rather than an int, and the return value of the
// member call is discarded, so this function's own return type is unobservable.

extern "C" __declspec(dllimport) int __cdecl atoi( const char * );

class Gen00587600
{
public:
	void apply( int value, int which );
	void applySingle( int value );
	void notify( void );
};

extern Gen00587600 *TheGen00587600;
extern unsigned char g_Va012F499D;

// @?Rva0051A6E0@@YAXXZ 0x0051A6E0
void Rva0051A6E0( void )
{
	Gen00587600 *object = TheGen00587600;
	g_Va012F499D = 1;
	if ( object )
		object->notify();
}

#define BFME_ATOI_MEMBER_CALL( NAME, WHICH )                              \
	void NAME( const char *text )                                         \
	{                                                                     \
		TheGen00587600->apply( atoi( text ), WHICH );                     \
	}

// @?Rva0051A700@@YAXPBD@Z 0x0051A700
BFME_ATOI_MEMBER_CALL( Rva0051A700, 0 )
// @?Rva0051A730@@YAXPBD@Z 0x0051A730
BFME_ATOI_MEMBER_CALL( Rva0051A730, 1 )
// @?Rva0051A760@@YAXPBD@Z 0x0051A760
BFME_ATOI_MEMBER_CALL( Rva0051A760, 2 )
// @?Rva0051A790@@YAXPBD@Z 0x0051A790
BFME_ATOI_MEMBER_CALL( Rva0051A790, 3 )
// @?Rva0051A7C0@@YAXPBD@Z 0x0051A7C0
BFME_ATOI_MEMBER_CALL( Rva0051A7C0, 4 )
// @?Rva0051A7F0@@YAXPBD@Z 0x0051A7F0
BFME_ATOI_MEMBER_CALL( Rva0051A7F0, 5 )

// @?Rva0051A820@@YAXPBD@Z 0x0051A820
void Rva0051A820( const char *text )
{
	TheGen00587600->applySingle( atoi( text ) );
}
