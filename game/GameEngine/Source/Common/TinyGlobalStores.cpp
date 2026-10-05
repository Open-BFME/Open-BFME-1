// Sixteen 10-byte __cdecl bodies of the single shape
//
//     mov eax,[esp+4] / mov ds:<DIR32>,eax / ret
//
// WHAT THE BYTES SHOW.  The single dword argument is loaded off the stack and
// written to a fixed absolute address, and `ret` pops nothing: a __cdecl (or
// static-member) setter of a module-level variable, `void set(T v) { g = v; }`.
// A __thiscall or __stdcall spelling is excluded -- the former would take the
// value in ecx, the latter would `ret 4`.
//
// ONE AXIS: the address of the global.  It rides a DIR32 relocation, whose four
// bytes are verified against retail. The initialized scalar owners have
// data rows; all sixteen addresses are distinct.
//
// IDENTITY IS NOT RECOVERED.  Every class name is derived from the retail RVA.

#define BFME_GLOBAL_STORE( NAME )                                         \
	class NAME                                                             \
	{                                                                      \
	public:                                                                \
		static void store( int value );                                     \
		static int s_value;                                                 \
	};                                                                     \
	void NAME::store( int value )                                          \
	{                                                                      \
		s_value = value;                                                    \
	}

BFME_GLOBAL_STORE( Rva0085A850 )
BFME_GLOBAL_STORE( Rva00882F80 )
BFME_GLOBAL_STORE( Rva00892340 )
BFME_GLOBAL_STORE( Rva00892360 )
BFME_GLOBAL_STORE( Rva008FE150 )
BFME_GLOBAL_STORE( Rva00937140 )
BFME_GLOBAL_STORE( Rva00956A70 )
BFME_GLOBAL_STORE( Rva009A58C0 )
BFME_GLOBAL_STORE( Rva001A1A30 )
BFME_GLOBAL_STORE( Rva006C5730 )
BFME_GLOBAL_STORE( Rva006E1BD0 )
BFME_GLOBAL_STORE( Rva006E7040 )
BFME_GLOBAL_STORE( Rva0075B2F0 )
BFME_GLOBAL_STORE( Rva00782DF0 )
BFME_GLOBAL_STORE( Rva00782E00 )
BFME_GLOBAL_STORE( Rva00782E10 )

int Rva0085A850::s_value;
int Rva00882F80::s_value;
int Rva00892340::s_value;
int Rva00892360::s_value;
int Rva008FE150::s_value;
int Rva00937140::s_value;
int Rva00956A70::s_value;
int Rva009A58C0::s_value;
int Rva006C5730::s_value;
int Rva006E1BD0::s_value = 2;
int Rva006E7040::s_value;
int Rva00782DF0::s_value;
int Rva00782E00::s_value;
int Rva00782E10::s_value;
