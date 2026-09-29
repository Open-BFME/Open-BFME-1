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
// THE STORED VALUES ARE THE VFTABLES dir32_addresses.csv NAMES AT THOSE
// ADDRESSES, reached through bfmeVft aliases declared below.  The base-slot
// values 0x0110F9E4, 0x0110F9E8, 0x0110FA14, 0x0107375C, 0x01073760 and
// 0x0110F978 are the second-base vftables V3InlineTwoBaseCopyCtors.cpp gives
// the V3Vt classes, and each per-row pair is the two vftables the table records
// for one class of the V3 copy-constructor files.  The FIRST of the two writes
// to a slot repeats across rows -- six distinct values over the eleven 32-byte
// rows -- while the SECOND is unique to every row, which is what a shared base
// and a per-class override look like.  The two per-row values are always four
// bytes apart and descending
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

// Vftables named in dir32_addresses.csv, reached through linker aliases.
extern "C" const void *bfmeVftV3Vt0110F978[];
#pragma comment(linker, "/alternatename:_bfmeVftV3Vt0110F978=??_7V3Vt0110F978@@6B@")
extern "C" const void *bfmeVftV3Vt01073760[];
#pragma comment(linker, "/alternatename:_bfmeVftV3Vt01073760=??_7V3Vt01073760@@6B@")
extern "C" const void *bfmeVftV3Vt0107375C[];
#pragma comment(linker, "/alternatename:_bfmeVftV3Vt0107375C=??_7V3Vt0107375C@@6B@")
extern "C" const void *bfmeVftV3Vt0110F9E4[];
#pragma comment(linker, "/alternatename:_bfmeVftV3Vt0110F9E4=??_7V3Vt0110F9E4@@6B@")
extern "C" const void *bfmeVftV3Vt0110FA14[];
#pragma comment(linker, "/alternatename:_bfmeVftV3Vt0110FA14=??_7V3Vt0110FA14@@6B@")
extern "C" const void *bfmeVftV3Vt0110F9E8[];
#pragma comment(linker, "/alternatename:_bfmeVftV3Vt0110F9E8=??_7V3Vt0110F9E8@@6B@")
extern "C" const void *bfmeVftV3Vt01111D90[];
#pragma comment(linker, "/alternatename:_bfmeVftV3Vt01111D90=??_7V3Vt01111D90@@6B@")
extern "C" const void *bfmeVftRva005EA430_V3Vt01111D90[];
#pragma comment(linker, "/alternatename:_bfmeVftRva005EA430_V3Vt01111D90=??_7Rva005EA430@@6BV3Vt01111D90@@@")
extern "C" const void *bfmeVftRva005EA430_V3Vt0110F978[];
#pragma comment(linker, "/alternatename:_bfmeVftRva005EA430_V3Vt0110F978=??_7Rva005EA430@@6BV3Vt0110F978@@@")
extern "C" const void *bfmeVftRva005EA400_V3Slot0N[];
#pragma comment(linker, "/alternatename:_bfmeVftRva005EA400_V3Slot0N=??_7Rva005EA400@@6BV3Slot0N@@@")
extern "C" const void *bfmeVftRva005EA400_V3Slot1[];
#pragma comment(linker, "/alternatename:_bfmeVftRva005EA400_V3Slot1=??_7Rva005EA400@@6BV3Slot1@@@")
extern "C" const void *bfmeVftRva005EA6F0_V3Vt01111D90[];
#pragma comment(linker, "/alternatename:_bfmeVftRva005EA6F0_V3Vt01111D90=??_7Rva005EA6F0@@6BV3Vt01111D90@@@")
extern "C" const void *bfmeVftRva005EA6F0_V3Vt01073760[];
#pragma comment(linker, "/alternatename:_bfmeVftRva005EA6F0_V3Vt01073760=??_7Rva005EA6F0@@6BV3Vt01073760@@@")
extern "C" const void *bfmeVftRva005EA6C0_V3Slot0N[];
#pragma comment(linker, "/alternatename:_bfmeVftRva005EA6C0_V3Slot0N=??_7Rva005EA6C0@@6BV3Slot0N@@@")
extern "C" const void *bfmeVftRva005EA6C0_V3Slot1[];
#pragma comment(linker, "/alternatename:_bfmeVftRva005EA6C0_V3Slot1=??_7Rva005EA6C0@@6BV3Slot1@@@")
extern "C" const void *bfmeVftRva005EB090_V3Vt01111D90[];
#pragma comment(linker, "/alternatename:_bfmeVftRva005EB090_V3Vt01111D90=??_7Rva005EB090@@6BV3Vt01111D90@@@")
extern "C" const void *bfmeVftRva005EB090_V3Vt0107375C[];
#pragma comment(linker, "/alternatename:_bfmeVftRva005EB090_V3Vt0107375C=??_7Rva005EB090@@6BV3Vt0107375C@@@")
extern "C" const void *bfmeVftRva005EA9B0_V3Vt01111D90[];
#pragma comment(linker, "/alternatename:_bfmeVftRva005EA9B0_V3Vt01111D90=??_7Rva005EA9B0@@6BV3Vt01111D90@@@")
extern "C" const void *bfmeVftRva005EA9B0_V3Vt0110F9E4[];
#pragma comment(linker, "/alternatename:_bfmeVftRva005EA9B0_V3Vt0110F9E4=??_7Rva005EA9B0@@6BV3Vt0110F9E4@@@")
extern "C" const void *bfmeVftRva005EA920_V3Slot0N[];
#pragma comment(linker, "/alternatename:_bfmeVftRva005EA920_V3Slot0N=??_7Rva005EA920@@6BV3Slot0N@@@")
extern "C" const void *bfmeVftRva005EA920_V3Slot1[];
#pragma comment(linker, "/alternatename:_bfmeVftRva005EA920_V3Slot1=??_7Rva005EA920@@6BV3Slot1@@@")
extern "C" const void *bfmeVftRva005EAE70_V3Vt01111D90[];
#pragma comment(linker, "/alternatename:_bfmeVftRva005EAE70_V3Vt01111D90=??_7Rva005EAE70@@6BV3Vt01111D90@@@")
extern "C" const void *bfmeVftRva005EAE70_V3Vt0110FA14[];
#pragma comment(linker, "/alternatename:_bfmeVftRva005EAE70_V3Vt0110FA14=??_7Rva005EAE70@@6BV3Vt0110FA14@@@")
extern "C" const void *bfmeVftRva005EADE0_V3Slot0N[];
#pragma comment(linker, "/alternatename:_bfmeVftRva005EADE0_V3Slot0N=??_7Rva005EADE0@@6BV3Slot0N@@@")
extern "C" const void *bfmeVftRva005EADE0_V3Slot1[];
#pragma comment(linker, "/alternatename:_bfmeVftRva005EADE0_V3Slot1=??_7Rva005EADE0@@6BV3Slot1@@@")
extern "C" const void *bfmeVftRva005EABB0_V3Vt01111D90[];
#pragma comment(linker, "/alternatename:_bfmeVftRva005EABB0_V3Vt01111D90=??_7Rva005EABB0@@6BV3Vt01111D90@@@")
extern "C" const void *bfmeVftRva005EABB0_V3Vt0110F9E8[];
#pragma comment(linker, "/alternatename:_bfmeVftRva005EABB0_V3Vt0110F9E8=??_7Rva005EABB0@@6BV3Vt0110F9E8@@@")
extern "C" const void *bfmeVftRva005EAB80_V3Slot0N[];
#pragma comment(linker, "/alternatename:_bfmeVftRva005EAB80_V3Slot0N=??_7Rva005EAB80@@6BV3Slot0N@@@")
extern "C" const void *bfmeVftRva005EAB80_V3Slot1[];
#pragma comment(linker, "/alternatename:_bfmeVftRva005EAB80_V3Slot1=??_7Rva005EAB80@@6BV3Slot1@@@")
extern "C" const void *bfmeVftRva005EB050_V3Vt01111D90[];
#pragma comment(linker, "/alternatename:_bfmeVftRva005EB050_V3Vt01111D90=??_7Rva005EB050@@6BV3Vt01111D90@@@")
extern "C" const void *bfmeVftRva005EB050_V3Vt0107375C[];
#pragma comment(linker, "/alternatename:_bfmeVftRva005EB050_V3Vt0107375C=??_7Rva005EB050@@6BV3Vt0107375C@@@")

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
		s[ 2 ] = (unsigned int)BASESLOT;                                   \
		s[ 0 ] = (unsigned int)OWN0;                                       \
		s[ 2 ] = (unsigned int)OWN8;                                       \
	}

T4_ARG_AT_4_DOUBLE_AT_8( Rva005EE820, bfmeVftV3Vt0110F978,
	bfmeVftRva005EA430_V3Vt01111D90, bfmeVftRva005EA430_V3Vt0110F978 )
T4_ARG_AT_4_DOUBLE_AT_8( Rva005EE850, bfmeVftV3Vt0110F978,
	bfmeVftRva005EA400_V3Slot0N, bfmeVftRva005EA400_V3Slot1 )
T4_ARG_AT_4_DOUBLE_AT_8( Rva005EF580, bfmeVftV3Vt01073760,
	bfmeVftRva005EA6F0_V3Vt01111D90, bfmeVftRva005EA6F0_V3Vt01073760 )
T4_ARG_AT_4_DOUBLE_AT_8( Rva005EFAC0, bfmeVftV3Vt01073760,
	bfmeVftRva005EA6C0_V3Slot0N, bfmeVftRva005EA6C0_V3Slot1 )
T4_ARG_AT_4_DOUBLE_AT_8( Rva005FC3B0, bfmeVftV3Vt0107375C,
	bfmeVftRva005EB090_V3Vt01111D90, bfmeVftRva005EB090_V3Vt0107375C )
T4_ARG_AT_4_DOUBLE_AT_8( Rva005FD9B0, bfmeVftV3Vt0110F9E4,
	bfmeVftRva005EA9B0_V3Vt01111D90, bfmeVftRva005EA9B0_V3Vt0110F9E4 )
T4_ARG_AT_4_DOUBLE_AT_8( Rva005FDC20, bfmeVftV3Vt0110F9E4,
	bfmeVftRva005EA920_V3Slot0N, bfmeVftRva005EA920_V3Slot1 )
T4_ARG_AT_4_DOUBLE_AT_8( Rva005FE690, bfmeVftV3Vt0110FA14,
	bfmeVftRva005EAE70_V3Vt01111D90, bfmeVftRva005EAE70_V3Vt0110FA14 )
T4_ARG_AT_4_DOUBLE_AT_8( Rva005FE9A0, bfmeVftV3Vt0110FA14,
	bfmeVftRva005EADE0_V3Slot0N, bfmeVftRva005EADE0_V3Slot1 )
T4_ARG_AT_4_DOUBLE_AT_8( Rva005FFA40, bfmeVftV3Vt0110F9E8,
	bfmeVftRva005EABB0_V3Vt01111D90, bfmeVftRva005EABB0_V3Vt0110F9E8 )
T4_ARG_AT_4_DOUBLE_AT_8( Rva005FFA70, bfmeVftV3Vt0110F9E8,
	bfmeVftRva005EAB80_V3Slot0N, bfmeVftRva005EAB80_V3Slot1 )

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
	s[ 2 ] = (unsigned int)bfmeVftV3Vt0107375C;
	*( (volatile unsigned char *)this + 0x0c ) = 1;
	s[ 0 ] = (unsigned int)bfmeVftRva005EB050_V3Vt01111D90;
	s[ 2 ] = (unsigned int)bfmeVftRva005EB050_V3Vt0107375C;
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
	s[ 0 ] = (unsigned int)bfmeVftV3Vt01111D90;
	s[ 1 ] = a;
}
