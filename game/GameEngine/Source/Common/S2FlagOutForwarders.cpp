// Six __cdecl two-argument functions that declare a one-byte local, forward
// both arguments plus the address of that local to a three-argument __cdecl
// callee, and return whatever it returns:
//
//     push ecx / mov ecx,[esp+0Ch] / mov edx,[esp+8] / lea eax,[esp+3]
//     push eax / push ecx / push edx / call <REL32> / add esp,10h / ret
//
// WHAT THE BYTES SHOW.  `push ecx` is MSVC's four-byte local allocation, and
// `add esp,10h` pops twelve bytes of arguments plus that slot, so the callee is
// __cdecl with exactly three arguments.  The `lea` takes the address of the
// LAST byte of the slot, which is where MSVC 7.1 puts a lone one-byte local, so
// the third argument is an out-parameter pointing at a char-sized object the
// caller never reads afterwards.  eax is left untouched between the call and
// the `ret`, so the callee's return value is this function's.
//
// THREE CALLEES, TWO SITES EACH: 0x000247E9 (body 0x000BB5D0), 0x000336C2
// (body 0x0069CE20) and 0x000096FB (body 0x0069F100).  Members sharing a callee
// are byte-identical apart from the REL32 displacement.
//
// IDENTITY IS NOT RECOVERED.  Names are address-derived, and the two forwarded
// arguments are typed as opaque pointers only because they are dword-sized --
// the bytes cannot tell a pointer from an int here.

class GenArgA { public: int m_x; };
class GenArgB { public: int m_y; };

#define BFME_FLAG_OUT_CALLEE( ADDR )                                      \
	int Gen##ADDR( GenArgA *a, GenArgB *b, bool *flag );

#define BFME_FLAG_OUT_FORWARDER( NAME, CALLEE )                           \
	int NAME( GenArgA *a, GenArgB *b )                                    \
	{                                                                     \
		bool flag;                                                        \
		return CALLEE( a, b, &flag );                                     \
	}

BFME_FLAG_OUT_CALLEE( 000247E9 )
BFME_FLAG_OUT_CALLEE( 000336C2 )
BFME_FLAG_OUT_CALLEE( 000096FB )

// @?Rva000BB8F0@@YAHPAVGenArgA@@PAVGenArgB@@@Z 0x000BB8F0
BFME_FLAG_OUT_FORWARDER( Rva000BB8F0, Gen000247E9 )
// @?Rva000BC440@@YAHPAVGenArgA@@PAVGenArgB@@@Z 0x000BC440
BFME_FLAG_OUT_FORWARDER( Rva000BC440, Gen000247E9 )
// @?Rva0069F020@@YAHPAVGenArgA@@PAVGenArgB@@@Z 0x0069F020
BFME_FLAG_OUT_FORWARDER( Rva0069F020, Gen000336C2 )
// @?Rva006A12B0@@YAHPAVGenArgA@@PAVGenArgB@@@Z 0x006A12B0
BFME_FLAG_OUT_FORWARDER( Rva006A12B0, Gen000336C2 )
// @?Rva006A1420@@YAHPAVGenArgA@@PAVGenArgB@@@Z 0x006A1420
BFME_FLAG_OUT_FORWARDER( Rva006A1420, Gen000096FB )
// @?Rva006A4BE0@@YAHPAVGenArgA@@PAVGenArgB@@@Z 0x006A4BE0
BFME_FLAG_OUT_FORWARDER( Rva006A4BE0, Gen000096FB )
