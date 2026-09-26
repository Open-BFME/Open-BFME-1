// Level one of the constructor chain that runs from 0x005E9860 to 0x005EA1F0.
//
// The slice 0x005E97B0..0x005EA530 is a stack of constructors that call each
// other: the four leaves at 0x005E9890, 0x005E9AE0, 0x005E9D00 and 0x005E9F40
// are matched in T4VtableSetCtors.cpp, the four rows here call those, and
// further rows call these.  A callee named in the SAME translation unit gets
// inlined by MSVC 7.1, and retail keeps a `call` at every step, so each level
// of the chain has to live in its own translation unit; this file is level one
// and declares its bases without defining them.
//
// Retail, the 32-byte arity:
//
//     mov eax,[esp+4] / push esi / push eax / mov esi,ecx
//     call <LEAF>
//     mov [esi],  <V0>
//     mov [esi+4],<V4>
//     mov eax,esi / pop esi / ret 4
//
// WHAT THE BYTES SHOW.  One dword argument, re-pushed unchanged and never read,
// then `mov eax,esi` before `ret 4`: a constructor forwarding its parameter to
// a base and doing nothing else.  Two constant stores, at 0 and +4, each
// written once.  Following T1BaseForwardingCtors.cpp's reading -- MSVC 7.1
// elides only the PRIMARY base's own vptr store, so a secondary base's store
// survives -- zero surviving base stores means there is exactly ONE base here,
// and the two vftables are that base's own.  That is consistent with the leaf
// this row calls: each leaf writes two vptrs, at 0 and +4, and is itself the
// multiply-inheriting class.
//
// 0x005E9F00 (50 bytes) is the same forward plus one byte copy:
//
//     call 0x005E9F40
//     test edi,edi / je L / lea eax,[edi+8] / jmp M / L: xor eax,eax
//     M: mov al,[eax] / mov [esi+8],al
//     mov [esi],<V0> / mov [esi+4],<V4>
//
// The null-checked `+8` is MSVC's derived-to-base POINTER adjustment, the same
// shape WideSlotSetup.cpp measured: it appears for a NAMED base-pointer
// conversion and not for an ordinary inherited-member access.  So the argument
// is treated as a pointer to this very class and converted to a base of it at
// offset 8, and the byte read from that base's offset 0 is stored into this
// object's own subobject at +8.  POSITION DECIDES WHAT THAT BYTE IS: it lands
// BEFORE the two vptr stamps, and MSVC 7.1 orders a constructor as base
// subobjects, then vptrs, then members, so a store ahead of the stamps cannot
// be a member of this class -- it is a third base at +8, one byte wide, whose
// constructor is inlined because it has no body to call.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address.  The
// argument is spelled `unsigned int` because only its width is visible; it is
// forwarded unchanged, and where it is dereferenced it is cast rather than
// declared as a pointer, so nothing is asserted about the caller's type.

// ------------------------------------------------------- bases, declared only

#define T4_SECOND_BASE( VT )                                                  \
	class T4A2_##VT { public: virtual void s0(); };

#define T4_TWO_VPTR_LEAF( NAME, VT )                                          \
	class T4P0_##NAME { public: virtual void s0(); };                         \
	class NAME : public T4P0_##NAME, public T4A2_##VT                         \
	{                                                                         \
	public:                                                                   \
		NAME( unsigned int a );                                               \
	};

T4_SECOND_BASE( 0110F9E4 )
T4_SECOND_BASE( 0110F9E8 )
T4_SECOND_BASE( 0110FA14 )
T4_SECOND_BASE( 0107375C )

T4_TWO_VPTR_LEAF( Rva005E9890, 0110F9E4 )
T4_TWO_VPTR_LEAF( Rva005E9AE0, 0110F9E8 )
T4_TWO_VPTR_LEAF( Rva005E9D00, 0110FA14 )
T4_TWO_VPTR_LEAF( Rva005E9F40, 0107375C )

// ------------------------------------------------------- the plain forwarders

#define T4_CHAIN_FORWARD( ROW, BASE )                                         \
	class Rva##ROW : public BASE                                              \
	{                                                                         \
	public:                                                                   \
		Rva##ROW( unsigned int a );                                           \
	};                                                                        \
	Rva##ROW::Rva##ROW( unsigned int a ) : BASE( a )                          \
	{                                                                         \
	}

T4_CHAIN_FORWARD( 005E9860, Rva005E9890 )
T4_CHAIN_FORWARD( 005E9AB0, Rva005E9AE0 )
T4_CHAIN_FORWARD( 005E9CD0, Rva005E9D00 )

// ------------------------------------- the forwarder with a one-byte base copy

class Rva005E9F00;

class T4Flag005E9F00
{
public:
	T4Flag005E9F00( const T4Flag005E9F00 *source ) : m_flag( source->m_flag ) {}
	unsigned char m_flag;
};

class Rva005E9F00 : public Rva005E9F40, public T4Flag005E9F00
{
public:
	Rva005E9F00( unsigned int a );
};

Rva005E9F00::Rva005E9F00( unsigned int a )
	: Rva005E9F40( a ),
	  T4Flag005E9F00( (const T4Flag005E9F00 *)(const Rva005E9F00 *)a )
{
}
