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
// bytes the gate takes from retail, so which global each body writes is not
// evidence and is not reconstructed; all sixteen addresses are distinct.
//
// IDENTITY IS NOT RECOVERED.  Every class name is derived from the retail RVA.

#define BFME_GLOBAL_STORE( NAME )                                         \
	class NAME                                                             \
	{                                                                      \
	public:                                                                \
		static void store( int value );                                     \
		static int s_value;                                                 \
	};                                                                     \
	int NAME::s_value;                                                     \
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
