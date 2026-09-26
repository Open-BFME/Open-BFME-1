// cl: /EHs-c-
// Eighteen 46-byte __thiscall copy constructors that do nothing but forward to
// a base copy constructor and then re-stamp their own vptrs.  Retail:
//
//     mov eax,[esp+4] ; push esi ; push eax ; mov esi,ecx
//     call <BASE COPY CTOR>                   ; the one and only call
//   [ mov [esi+0x18],<EXTRA VFTABLE> ]        ; shape A only
//     mov [esi],      <DERIVED VFTABLE 0>
//     mov [esi+0x14], <DERIVED VFTABLE 0x14>
//     mov [esi+0x18], <DERIVED VFTABLE 0x18>
//   [ mov [esi+0x1C or 0x20], <DERIVED VFTABLE> ]    ; shape B only
//     mov eax,esi ; pop esi ; ret 4
//
// WHAT THE BYTES SHOW.  `ret 4` plus `mov eax,esi` is a __thiscall taking one
// argument and returning this -- a constructor.  The single argument is passed
// straight through to the callee unmodified, so the base subobject sits at
// offset 0 and the argument is a pointer to the same kind of thing the base
// takes: a COPY constructor forwarding to the base copy constructor.  (Each
// callee, disassembled, is itself a copy constructor: 0x005EB7B0 copies a dword
// from other+0x10 to this+0x10 and copy-constructs a subobject at +4.)
//
// The trailing vptr stores are ASCENDING, which is constructor order, and there
// are three or four of them, so each of these classes has three or four
// polymorphic subobjects -- at 0, 0x14, 0x18 and, in shape B, 0x1C or 0x20.
//
// SHAPE A vs SHAPE B IS READ OFF THE LEADING STORE.  Shape A has one extra
// store, to offset 0x18, BEFORE the derived stores and with a different vftable
// address; that is a base at 0x18 whose own constructor is inlined and whose
// dead store MSVC keeps (the same asymmetry Q2MultipleBaseVtableSetters.cpp
// documents).  So in shape A the base being forwarded to covers slots 0 and
// 0x14 only and the derived class adds the third base itself.  Shape B has no
// such store, so every slot the body stamps already belongs to the forwarded-to
// base and the derived class adds no base of its own.  That distinction comes
// entirely from these 46 bytes; the callees are not needed to make it.
//
// FIFTEEN DISTINCT CALLEES FOR EIGHTEEN ROWS: 0x005EB7B0 is the base of four of
// them.  Those four store four different sets of derived vftables, so they are
// four classes over one base, not one class.  Every base is declared here with
// its copy constructor DECLARED AND NOT DEFINED -- defining it in this file
// would inline it and destroy the call.  The callee addresses are pinned in
// targets/game/reverse/symbols.csv; each is the incremental-link thunk's target, and each is
// itself still an unclaimed row of game/gen_asm/d_005e6700.asm.
//
// SHAPE A'S FIVE EXTRA VFTABLES ARE FIVE DIFFERENT ADDRESSES, so the third base
// is a different class in each of the five shape-A rows and gets its own
// declaration.  The pieces that make up a base's layout emit no bytes here at
// all (their stores are inside the callee), so they are shared: 0x14 + 4 + 4 +
// 4 for the 0x1C variant, 0x14 + 4 + 8 + 4 for the 0x20 variant.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address.  All
// vftable dwords are DIR32 relocation sites the gate takes from the target; 26
// of each body's 46 bytes are concrete.

// Layout pieces.  None of these emits a single byte of any body below -- their
// vptr stores all happen inside the out-of-line base copy constructors -- so
// they carry no evidence beyond the offsets they produce.
class V3Slot0	{ public: virtual void s0(); virtual ~V3Slot0() {} int m_a, m_b, m_c, m_d; };
class V3Slot0N	{ public: virtual void s0(); virtual ~V3Slot0N() {} int m_a; };
class V3Slot1	{ public: virtual void s0(); virtual ~V3Slot1() {} };
class V3Slot1W	{ public: virtual void s0(); virtual ~V3Slot1W() {} int m_e; };
class V3Slot2	{ public: virtual void s0(); virtual ~V3Slot2() {} };
class V3Slot2W	{ public: virtual void s0(); virtual ~V3Slot2W() {} int m_e; };
class V3Slot3	{ public: virtual void s0(); virtual ~V3Slot3() {} };

// ------------------------------------------------------------------- shape A

// base covering slots 0 and 0x14; total width 0x18
#define V3_BASE_TWO_SLOT( NAME )                                          \
	class NAME : public V3Slot0, public V3Slot1                           \
	{                                                                     \
	public:                                                               \
		NAME( const NAME & );                                             \
	};

// third base, added by the derived class, at 0x18
#define V3_DERIVED_ADDS_THIRD( NAME, BASE, THIRD )                        \
	class THIRD                                                           \
	{                                                                     \
	public:                                                               \
		virtual void s0();                                                \
		virtual ~THIRD() {}                                               \
	};                                                                    \
	class NAME : public BASE, public THIRD                                \
	{                                                                     \
	public:                                                               \
		NAME( const NAME & );                                             \
	};                                                                    \
	NAME::NAME( const NAME &o ) : BASE( o ) {}

V3_BASE_TWO_SLOT( Rva005EB7B0 )
V3_BASE_TWO_SLOT( Rva005ED8B0 )

V3_DERIVED_ADDS_THIRD( Rva005EB730, Rva005EB7B0, V3Third01110920 )
V3_DERIVED_ADDS_THIRD( Rva005EB8B0, Rva005EB7B0, V3Third01110C78 )
V3_DERIVED_ADDS_THIRD( Rva005EB9B0, Rva005EB7B0, V3Third01110CB8 )
V3_DERIVED_ADDS_THIRD( Rva005EBAB0, Rva005EB7B0, V3Third01110CF8 )
V3_DERIVED_ADDS_THIRD( Rva005ED870, Rva005ED8B0, V3Third011106F4 )

// ------------------------------------------------------------------- shape B

// base covering slots 0, 0x14, 0x18, 0x1C
#define V3_BASE_FOUR_SLOT( NAME )                                         \
	class NAME : public V3Slot0, public V3Slot1,                          \
	             public V3Slot2, public V3Slot3                           \
	{                                                                     \
	public:                                                               \
		NAME( const NAME & );                                             \
	};

// base covering slots 0, 0x14, 0x18, 0x20
#define V3_BASE_FOUR_SLOT_WIDE( NAME )                                    \
	class NAME : public V3Slot0, public V3Slot1,                          \
	             public V3Slot2W, public V3Slot3                          \
	{                                                                     \
	public:                                                               \
		NAME( const NAME & );                                             \
	};

#define V3_DERIVED_PLAIN( NAME, BASE )                                    \
	class NAME : public BASE                                              \
	{                                                                     \
	public:                                                               \
		NAME( const NAME & );                                             \
	};                                                                    \
	NAME::NAME( const NAME &o ) : BASE( o ) {}

V3_BASE_FOUR_SLOT( Rva005EC1A0 )
V3_BASE_FOUR_SLOT( Rva005EC640 )
V3_BASE_FOUR_SLOT( Rva005EC8B0 )
V3_BASE_FOUR_SLOT( Rva005ECAF0 )
V3_BASE_FOUR_SLOT( Rva005ECFA0 )
V3_BASE_FOUR_SLOT( Rva005ED810 )
V3_BASE_FOUR_SLOT( Rva005ED9C0 )
V3_BASE_FOUR_SLOT( Rva005EDB50 )
V3_BASE_FOUR_SLOT( Rva005EDCC0 )
V3_BASE_FOUR_SLOT( Rva005EDE20 )
V3_BASE_FOUR_SLOT_WIDE( Rva005ECD00 )
V3_BASE_FOUR_SLOT_WIDE( Rva005ED110 )

V3_DERIVED_PLAIN( Rva005EC160, Rva005EC1A0 )
V3_DERIVED_PLAIN( Rva005EC600, Rva005EC640 )
V3_DERIVED_PLAIN( Rva005EC870, Rva005EC8B0 )
V3_DERIVED_PLAIN( Rva005ECAB0, Rva005ECAF0 )
V3_DERIVED_PLAIN( Rva005ECF60, Rva005ECFA0 )
V3_DERIVED_PLAIN( Rva005ED7D0, Rva005ED810 )
V3_DERIVED_PLAIN( Rva005ED980, Rva005ED9C0 )
V3_DERIVED_PLAIN( Rva005EDB10, Rva005EDB50 )
V3_DERIVED_PLAIN( Rva005EDC80, Rva005EDCC0 )
V3_DERIVED_PLAIN( Rva005EDDE0, Rva005EDE20 )
V3_DERIVED_PLAIN( Rva005ECCC0, Rva005ECD00 )
V3_DERIVED_PLAIN( Rva005ED0D0, Rva005ED110 )

struct GenNode_006fa270
{
	GenNode_006fa270( const GenNode_006fa270 & );

	void *m_owner;
	GenNode_006fa270 *m_previous;
	GenNode_006fa270 *m_next;
};

struct Rva005EDFA0FirstBase
{
	Rva005EDFA0FirstBase( const Rva005EDFA0FirstBase & );

	void *m_vftable;
	GenNode_006fa270 m_node;
	int m_value;
};

class Rva005EDFA0SecondBase
{
public:
	Rva005EDFA0SecondBase( const Rva005EDFA0SecondBase & )
		: m_vftable( (void *)0x0110F9AC )
	{
	}

	void *m_vftable;
};

class Rva005EDFA0ThirdBase
{
public:
	Rva005EDFA0ThirdBase( const Rva005EDFA0ThirdBase & )
		: m_vftable( (void *)0x011106F4 )
	{
	}

	void *m_vftable;
};

class Rva005EDFA0Middle
	: public Rva005EDFA0FirstBase,
	  public Rva005EDFA0SecondBase,
	  public Rva005EDFA0ThirdBase
{
public:
	Rva005EDFA0Middle( const Rva005EDFA0Middle & );
};

namespace FXParticleSystem
{

class LightningEmissionInfo
{
public:
	LightningEmissionInfo( const LightningEmissionInfo & );

	void *m_vftable;
};

}

class Rva005EDFA0
	: public Rva005EDFA0Middle,
	  public FXParticleSystem::LightningEmissionInfo
{
public:
	Rva005EDFA0( const Rva005EDFA0 & );
};

// ??0Rva005EDFA0Middle@@QAE@ABV0@@Z absent-from-retail (inlined into the matched copy constructor)
Rva005EDFA0Middle::Rva005EDFA0Middle(
	const Rva005EDFA0Middle &other)
	: Rva005EDFA0FirstBase( other ),
	  Rva005EDFA0SecondBase( other ),
	  Rva005EDFA0ThirdBase( other )
{
	Rva005EDFA0FirstBase::m_vftable = (void *)0x0111182C;
	Rva005EDFA0SecondBase::m_vftable = (void *)0x01111828;
	Rva005EDFA0ThirdBase::m_vftable = (void *)0x01111824;
}

// ??0Rva005EDFA0FirstBase@@QAE@ABV0@@Z absent-from-retail (inlined into the matched copy constructor)
Rva005EDFA0FirstBase::Rva005EDFA0FirstBase(
	const Rva005EDFA0FirstBase &other)
	: m_vftable( (void *)0x0111126C ),
	  m_node( other.m_node ),
	  m_value( other.m_value )
{
}

Rva005EDFA0::Rva005EDFA0( const Rva005EDFA0 &other )
	: Rva005EDFA0Middle( other ), FXParticleSystem::LightningEmissionInfo( other )
{
	Rva005EDFA0FirstBase::m_vftable = (void *)0x011132F0;
	Rva005EDFA0SecondBase::m_vftable = (void *)0x011132EC;
	Rva005EDFA0ThirdBase::m_vftable = (void *)0x011132E8;
	FXParticleSystem::LightningEmissionInfo::m_vftable = (void *)0x011132D4;
}

class Rva005EDF60 : public Rva005EDFA0
{
public:
	Rva005EDF60( const Rva005EDF60 & );
};

Rva005EDF60::Rva005EDF60( const Rva005EDF60 &other )
	: Rva005EDFA0( other )
{
	Rva005EDFA0FirstBase::m_vftable = (void *)0x01112420;
	Rva005EDFA0SecondBase::m_vftable = (void *)0x0111241C;
	Rva005EDFA0ThirdBase::m_vftable = (void *)0x01112418;
	FXParticleSystem::LightningEmissionInfo::m_vftable = (void *)0x01112404;
}

// ------------------------------------- shape B over narrower base layouts
//
// Same source shape, same 46-byte skeleton minus the stores it does not make:
// the forwarded-to base has two or three polymorphic subobjects instead of
// four, so the body is 32 or 39 bytes.  The slot offsets say how wide each
// piece is -- {0, 8} needs a first base of eight bytes, {0, 8, 0xC} adds a
// four-byte second, {0, 8, 0x10} an eight-byte one, {0, 0x14, 0x18} is the
// wide first base again.  Every one of these callees is a neighbouring row of
// the same gen_asm file, and each has been disassembled far enough to confirm
// it stamps exactly the slots its caller re-stamps.

#define V3_BASE_TWO_SLOT_N( NAME )                                        \
	class NAME : public V3Slot0N, public V3Slot1                          \
	{                                                                     \
	public:                                                               \
		NAME( const NAME & );                                             \
	};

#define V3_BASE_THREE_SLOT_N( NAME )                                      \
	class NAME : public V3Slot0N, public V3Slot1, public V3Slot2          \
	{                                                                     \
	public:                                                               \
		NAME( const NAME & );                                             \
	};

#define V3_BASE_THREE_SLOT_NW( NAME )                                     \
	class NAME : public V3Slot0N, public V3Slot1W, public V3Slot2         \
	{                                                                     \
	public:                                                               \
		NAME( const NAME & );                                             \
	};

#define V3_BASE_THREE_SLOT_W( NAME )                                      \
	class NAME : public V3Slot0, public V3Slot1, public V3Slot2           \
	{                                                                     \
	public:                                                               \
		NAME( const NAME & );                                             \
	};

V3_BASE_TWO_SLOT_N( Rva005EA430 )
V3_BASE_TWO_SLOT_N( Rva005EA6F0 )
V3_BASE_TWO_SLOT_N( Rva005EA9B0 )
V3_BASE_TWO_SLOT_N( Rva005EABB0 )
V3_BASE_TWO_SLOT_N( Rva005EAE70 )

V3_BASE_THREE_SLOT_N( Rva005EA310 )
V3_BASE_THREE_SLOT_N( Rva005EA590 )
V3_BASE_THREE_SLOT_N( Rva005EA850 )
V3_BASE_THREE_SLOT_N( Rva005EAAB0 )
V3_BASE_THREE_SLOT_N( Rva005EAD10 )
V3_BASE_THREE_SLOT_N( Rva005EB1F0 )

V3_BASE_THREE_SLOT_NW( Rva005EAF70 )
V3_BASE_THREE_SLOT_NW( Rva005EB320 )

V3_BASE_THREE_SLOT_W( Rva005ED3E0 )

V3_DERIVED_PLAIN( Rva005EA400, Rva005EA430 )
V3_DERIVED_PLAIN( Rva005EA6C0, Rva005EA6F0 )
V3_DERIVED_PLAIN( Rva005EA920, Rva005EA9B0 )
V3_DERIVED_PLAIN( Rva005EAB80, Rva005EABB0 )
V3_DERIVED_PLAIN( Rva005EADE0, Rva005EAE70 )

V3_DERIVED_PLAIN( Rva005EA2E0, Rva005EA310 )
V3_DERIVED_PLAIN( Rva005EA560, Rva005EA590 )
V3_DERIVED_PLAIN( Rva005EA820, Rva005EA850 )
V3_DERIVED_PLAIN( Rva005EAA80, Rva005EAAB0 )
V3_DERIVED_PLAIN( Rva005EACE0, Rva005EAD10 )
V3_DERIVED_PLAIN( Rva005EB1C0, Rva005EB1F0 )

V3_DERIVED_PLAIN( Rva005EAF40, Rva005EAF70 )
V3_DERIVED_PLAIN( Rva005EB2F0, Rva005EB320 )

V3_DERIVED_PLAIN( Rva005ED4E0, Rva005ED3E0 )
