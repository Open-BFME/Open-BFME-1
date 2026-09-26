// cl: /EHs-c- /Igame/GameEngine/Source/Common/System /Igame/GameEngine/Include/Common /Igame/Libraries/Source/WWVegas/WWMath /Igame/Libraries/Source/WWVegas/WWLib
//
// Five copy constructors from game/gen_asm/d_005e6700.asm, 69 to 89 bytes, and
// the reason they live in FXParticleSystem instead of Common: THEIR SECOND BASE
// IS A NAMED FXParticleSystem MODULE-INFO CLASS.  Each body's second `call` is a
// REL32 that follows its incremental-link thunk to a matched ledger row:
//
//     0x005EC8B0 -> 0x005D81C0  FXParticleSystem::DefaultUpdateModuleInfo
//     0x005ECFA0 -> 0x005D92C0  FXParticleSystem::RenderObjectUpdateModuleInfo
//     0x005ECAF0 -> 0x005BD970  FXParticleSystem::WindModuleInfo
//     0x005ED2B0 -> 0x005D6DA0  FXParticleSystem::OrthoEmissionVelocityInfo
//
// all four of them that class's COPY constructor, all four already declared in
// fx_particle_system.h, which is why this file includes that header and uses the
// real types rather than inventing four more address-derived ones.  That fixes
// the family: these are composites that inherit one of the ParticleSystem info
// aggregates AND one module-info class, and copy both.
//
// THE FIRST BASE IS ALWAYS A ROW OF THIS SAME gen_asm FILE, already landed:
// 0x005EC930 and 0x005ECB80 (V3HeadNodeCopyCtors.cpp), 0x005ED310 (same), and
// 0x005ED870 (V3CopyCtorForwarders.cpp).  They are re-declared here only as far
// as these bodies observe them -- the offsets of their vptr slots and their
// total width -- because that is all the call needs; the members those files
// recovered are not restated.
//
// TWO OF THE FIVE HAVE AN EXTRA VPTR BLOCK between the first call and the
// second, at the same offsets, with different vftable addresses.  A caller
// cannot stamp another class's vptrs, so those stores belong to a class BETWEEN
// the landed first base and the row's own class, whose copy constructor was
// inlined while the one below it was not.  0x005EC8B0 and 0x005ECFA0 stamp the
// SAME intermediate triple (0x01113190 / 0x0111318C / 0x01113188) over the same
// first base, so they share that intermediate; 0x005ED2B0's is its own.
// 0x005ECAF0 and 0x005ED810 have no such block and derive directly.
//
// 0x005ED810's SECOND BASE IS INLINE, not called: it stamps that base's own
// vftable at +0x1C and copies ONE BYTE from the source's +4 to this+0x20.  A
// vptr plus a bool, with the compiler's implicit copy constructor -- an unnamed
// module-info-shaped class this file cannot identify, since no call gives it
// away.
//
// THE EXCEPTION FLAG IS EVIDENCE AND IT DISAGREES WITH THE HEADER.  Under the
// `/EHsc` that fx_particle_system_bulk.cpp uses, three of these five grow a
// three-push fs:[0] frame and run 131 and 111 bytes instead of 89 and 69: the
// second base's copy constructor becomes an unwind point, because the first base
// would have to be destroyed if it threw.  0x005ED2B0 does NOT grow one, and the
// reason is already in fx_particle_system.h -- OrthoEmissionVelocityInfo's copy
// constructor is declared `__declspec(nothrow)` there and the other three are
// not.  So either this translation unit was built with exceptions off, which is
// what the `// cl:` line above says and what makes all five land, or
// DefaultUpdateModuleInfo, RenderObjectUpdateModuleInfo and WindModuleInfo carry
// the same `nothrow` Ortho does and the header is one attribute short on each.
// The bytes cannot separate those two readings from here, and the second one
// would change a header eight other matched sources compile against, so it is
// reported rather than applied.
//
// IDENTITY IS RECOVERED FOR THE SECOND BASES AND NOT FOR ANYTHING ELSE.  The
// composite classes and the intermediates are named after the body address.
// Every vftable dword is a DIR32 site the gate takes from the target.

#include "fx_particle_system.h"

// ---- the landed first bases, as far as these bodies observe them ------------

class V3Slot0	{ public: virtual void s0(); virtual ~V3Slot0() {} int m_a, m_b, m_c, m_d; };
class V3Slot1	{ public: virtual void s0(); virtual ~V3Slot1() {} };
class V3Slot2	{ public: virtual void s0(); virtual ~V3Slot2() {} };

// slots at 0, 0x14, 0x18; width 0x1C
#define V3_FIRST_BASE_THREE_SLOT( NAME )                                   \
	class NAME : public V3Slot0, public V3Slot1, public V3Slot2            \
	{                                                                      \
	public:                                                                \
		NAME( const NAME & );                                              \
	};

V3_FIRST_BASE_THREE_SLOT( Rva005EC930 )
V3_FIRST_BASE_THREE_SLOT( Rva005ECB80 )
V3_FIRST_BASE_THREE_SLOT( Rva005ED870 )

// slots at 0 and 0x14; width 0x18
class Rva005ED310 : public V3Slot0, public V3Slot1
{
public:
	Rva005ED310( const Rva005ED310 & );
};

// ---- the intermediates whose copy constructors were inlined ----------------

class V3Mid01113190 : public Rva005EC930
{
public:
	V3Mid01113190( const V3Mid01113190 &o ) : Rva005EC930( o ) {}
};

class V3Mid01111994 : public Rva005ED310
{
public:
	V3Mid01111994( const V3Mid01111994 &o ) : Rva005ED310( o ) {}
};

// ---- 0x005ED810's inline second base: a vptr and a bool --------------------

class V3Vt0110F980
{
public:
	virtual void s0();
	virtual ~V3Vt0110F980() {}
	char m_unreconstructed_04;
};

// ---- the five rows ---------------------------------------------------------

#define V3_COMPOSITE_COPY_CTOR( NAME, FIRST, SECOND )                      \
	class NAME : public FIRST, public SECOND                               \
	{                                                                      \
	public:                                                                \
		NAME( const NAME & );                                              \
	};                                                                     \
	NAME::NAME( const NAME &o ) : FIRST( o ), SECOND( o ) {}

V3_COMPOSITE_COPY_CTOR( Rva005EC8B0, V3Mid01113190, FXParticleSystem::DefaultUpdateModuleInfo )
V3_COMPOSITE_COPY_CTOR( Rva005ECFA0, V3Mid01113190, FXParticleSystem::RenderObjectUpdateModuleInfo )
V3_COMPOSITE_COPY_CTOR( Rva005ECAF0, Rva005ECB80, FXParticleSystem::WindModuleInfo )
V3_COMPOSITE_COPY_CTOR( Rva005ED2B0, V3Mid01111994, FXParticleSystem::OrthoEmissionVelocityInfo )
V3_COMPOSITE_COPY_CTOR( Rva005ED810, Rva005ED870, V3Vt0110F980 )
