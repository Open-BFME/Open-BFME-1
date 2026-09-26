// cl: /EHs-c-
//
// Seventeen __thiscall constructors from the 0x005E97B0..0x0060D680 slice that do
// nothing but write a fixed set of absolute dwords into the fresh object and,
// in two of the three shapes, park one incoming pointer in a field.
//
// WHAT THE BYTES SHOW.  Every body opens with `mov eax,ecx` and closes with
// `ret 4` / `ret 8`, so each is __thiscall, returns the receiver, and pops its
// own arguments -- a constructor.  No call is made, so nothing here is an
// out-of-line base construction; the whole body is straight-line stores of
// immediates.
//
// The stores are REDUNDANT and that redundancy is the evidence.  In the 32-byte
// shape the same slot at +0x08 is written twice, first with one absolute dword
// and then with another, with no read in between; the 25-byte shape does the
// same to +0x04.  A plain assignment pair would be dead-store eliminated, so
// the retail sequence can only come from writes the compiler is not allowed to
// drop.  That is exactly the modelling this repository already uses for the
// same construct in
// game/GameEngine/Source/GameClient/System/FXParticleSystem/fx_particle_system_bulk.cpp
// (see PointEmissionVolumeTemplateAllocation and its siblings): volatile dword
// stores through `this`.  The double write is MSVC's own MI constructor
// sequence -- an inlined base constructor installs its vftable pointer, the
// most-derived class then overwrites that slot with its own -- but nothing in
// these bodies names the base, so the source is written as the store sequence
// and not as a hierarchy that would assert one.
//
// THE STORE ORDER IS SOURCE ORDER.  MSVC 7.1 does not reorder straight-line
// constant stores, and with `volatile` it may not merge or drop them either, so
// the sequence transcribed below is the sequence retail executes: the argument
// field first where there is one, then the base slot, then offset 0, then the
// base slot again.
//
// THE STORED VALUES ARE NOT ASSERTED.  They are written as integer literals,
// not as `&SomeVftable`, precisely so that no identity is claimed for them: an
// extern would have to resolve to one consistent address and would turn a guess
// into a ledger fact.  What they are is legible from the image -- 0x0110F9E4,
// 0x0110F9E8, 0x0110FA14, 0x0107375C, 0x01073760 and 0x0110F978 are each the
// head of a short table of code addresses, mostly the shared stub at 0x00C8C500,
// and each such table is followed a few dwords later by a class-name string
// ("WindModuleInfo" after 0x0110F9E4's group, "FXParticleSystemInfo" after
// 0x0107375C's).  The FIRST of the two writes to a slot repeats across rows --
// six distinct values over the eleven 32-byte rows -- while the SECOND is
// unique to every row, which is what a shared base and a per-class override
// look like.  The two per-row values are always four bytes apart and descending
// (0x01112B28 / 0x01112B24), the adjacency MSVC gives the two vftables it emits
// for one multiply-inheriting class.
//
// IDENTITY IS NOT RECOVERED.  Every class is named after its constructor's RVA.
// The storage array is a size floor derived from the highest slot written, not
// a layout claim, and the argument is spelled `unsigned int` because only its
// width is visible.  The second argument of the `ret 8` shapes is never read;
// it is present because the callee pops eight bytes.
//
// Built with exception handling off: these bodies carry no unwind frame, and
// the project default `-EHsc-` is parsed by cl as EHs ON, hence the directive.

// ---------------------------------------------------------------------------
// 32 bytes, __thiscall(two args), first argument stored at +0x04, doubled
// write at +0x08.
// ---------------------------------------------------------------------------
#define T4_ARG_AT_4_DOUBLE_AT_8( NAME, BASESLOT, OWN0, OWN8 )              \
	class NAME                                                             \
	{                                                                      \
	public:                                                                \
		NAME( unsigned int a, unsigned int b );                            \
	private:                                                               \
		unsigned char m_storage[ 0x0c ];                                   \
	};                                                                     \
	NAME::NAME( unsigned int a, unsigned int b )                           \
	{                                                                      \
		volatile unsigned int *s = (unsigned int *)this;                   \
		s[ 1 ] = a;                                                        \
		s[ 2 ] = BASESLOT;                                                 \
		s[ 0 ] = OWN0;                                                     \
		s[ 2 ] = OWN8;                                                     \
	}

T4_ARG_AT_4_DOUBLE_AT_8( Rva005EE820, 0x0110f978, 0x01112b28, 0x01112b24 )
T4_ARG_AT_4_DOUBLE_AT_8( Rva005EE850, 0x0110f978, 0x01112b08, 0x01112b04 )
T4_ARG_AT_4_DOUBLE_AT_8( Rva005EF580, 0x01073760, 0x01112b94, 0x01112b90 )
T4_ARG_AT_4_DOUBLE_AT_8( Rva005EFAC0, 0x01073760, 0x01112b74, 0x01112b70 )
T4_ARG_AT_4_DOUBLE_AT_8( Rva005FC3B0, 0x0107375c, 0x01112d44, 0x01112d40 )
T4_ARG_AT_4_DOUBLE_AT_8( Rva005FD9B0, 0x0110f9e4, 0x01112bf0, 0x01112bec )
T4_ARG_AT_4_DOUBLE_AT_8( Rva005FDC20, 0x0110f9e4, 0x01112bd8, 0x01112bd4 )
T4_ARG_AT_4_DOUBLE_AT_8( Rva005FE690, 0x0110fa14, 0x01112ce8, 0x01112ce4 )
T4_ARG_AT_4_DOUBLE_AT_8( Rva005FE9A0, 0x0110fa14, 0x01112cd0, 0x01112ccc )
T4_ARG_AT_4_DOUBLE_AT_8( Rva005FFA40, 0x0110f9e8, 0x01112c8c, 0x01112c88 )
T4_ARG_AT_4_DOUBLE_AT_8( Rva005FFA70, 0x0110f9e8, 0x01112c54, 0x01112c50 )

// The same shape with one extra byte set true at +0x0C, written between the two
// stores to +0x08 -- that is, after the inlined base constructor and before the
// most-derived stamps, which is where a further base subobject's own
// initialisation goes.
class Rva005FC6E0
{
public:
	Rva005FC6E0( unsigned int a, unsigned int b );
private:
	unsigned char m_storage[ 0x10 ];
};

Rva005FC6E0::Rva005FC6E0( unsigned int a, unsigned int b )
{
	volatile unsigned int *s = (unsigned int *)this;
	s[ 1 ] = a;
	s[ 2 ] = 0x0107375c;
	*( (volatile unsigned char *)this + 0x0c ) = 1;
	s[ 0 ] = 0x01112d2c;
	s[ 2 ] = 0x01112d28;
}

// ---------------------------------------------------------------------------
// 25 bytes, __thiscall(one unread arg), doubled write at +0x04.  These four are
// NOT written as store sequences: they are the roots of a constructor chain
// (0x005E9860, 0x005E9AB0, 0x005E9CD0 and 0x005E9F00 each `call` one of them,
// and further rows call those), so they are spelled as the classes the chain
// needs, in the modelling T1BaseForwardingCtors.cpp established -- a primary
// base whose own vptr store MSVC elides, a bare-vptr secondary base at +0x04
// whose store survives, and the derived class stamping both slots afterwards.
// The secondary base is named after the address retail stores through it, one
// class per distinct address, shared with this lane's other files.
//
// The single argument is never read.  It is spelled `unsigned int` rather than
// a reference because nothing here shows its type -- only that it is one dword
// wide and that every caller forwards its own incoming dword unchanged and
// unadjusted.  Spelling it as a reference would assert a copy constructor that
// the bytes do not.
// ---------------------------------------------------------------------------
#define T4_SECOND_BASE( VT )                                                \
	class T4A2_##VT { public: virtual void s0(); };

#define T4_TWO_VPTR_LEAF( NAME, VT )                                        \
	class T4P0_##NAME { public: virtual void s0(); };                       \
	class NAME : public T4P0_##NAME, public T4A2_##VT                       \
	{                                                                       \
	public:                                                                 \
		NAME( unsigned int a );                                             \
	};                                                                      \
	NAME::NAME( unsigned int a )                                            \
	{                                                                       \
	}

T4_SECOND_BASE( 0110F9E4 )
T4_SECOND_BASE( 0110F9E8 )
T4_SECOND_BASE( 0110FA14 )
T4_SECOND_BASE( 0107375C )

T4_TWO_VPTR_LEAF( Rva005E9890, 0110F9E4 )
T4_TWO_VPTR_LEAF( Rva005E9AE0, 0110F9E8 )
T4_TWO_VPTR_LEAF( Rva005E9D00, 0110FA14 )
T4_TWO_VPTR_LEAF( Rva005E9F40, 0107375C )

// ---------------------------------------------------------------------------
// 18 bytes, __thiscall(two args): one slot written at +0x00, first argument
// parked at +0x04.  No doubled write, so nothing here says there is a base at
// all -- only that the object begins with a table pointer and a saved pointer.
// ---------------------------------------------------------------------------
class Rva005EE340
{
public:
	Rva005EE340( unsigned int a, unsigned int b );
private:
	unsigned char m_storage[ 0x08 ];
};

Rva005EE340::Rva005EE340( unsigned int a, unsigned int b )
{
	volatile unsigned int *s = (unsigned int *)this;
	s[ 0 ] = 0x01111d90;
	s[ 1 ] = a;
}
