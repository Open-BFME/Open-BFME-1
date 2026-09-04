// 41 empty destructors whose vftable stores are NOT in offset order:
//
//     mov [ecx+0x10],<vft> / mov [ecx],<vft> / mov [ecx+0xC],<vft> /
//         jmp 0x00047C53                                          (17 bodies)
//     mov [ecx+0x20],<vft> / mov [ecx+0x10],<vft> / mov [ecx],<vft> /
//         mov [ecx+0xC],<vft> / jmp 0x00047C53                    (24 bodies)
//
// WHY THE ORDER MATTERS.  The sibling families in
// MultiVptrTailJumpDestructors.cpp write their vftables in ASCENDING
// displacement order, which is what a class with several polymorphic bases
// emits.  These do not: the HIGHEST displacement is written first and the rest
// follow in ascending order behind it.  Probed, a flat class cannot produce
// that at either /O2 or /O1.  What does, on the first spelling, is an
// intermediate class with an INLINE destructor:
//
//     class Mid : public Base, public MixA { virtual ~Mid() {} };
//     class Outer : public Mid, public MixC { virtual ~Outer(); };
//
// `~Outer` re-seats its own new vftable -- the one for the sub-object Outer
// itself adds, at the top of the object -- then INLINES `~Mid`, whose stores
// come next and are Mid's vftables in ascending order, and then tail-jumps
// past Mid to the base whose destructor is out of line.  The four-store shape
// is the same thing one level deeper.
//
// WHAT THAT SETTLES ABOUT THE TARGET.  All 41 bodies jump to 0x00047C53, and the
// function there is seven bytes: `mov [ecx],<vftable> / ret`.  A class with
// ONE vftable and no base -- which is exactly what this reading requires and
// what the flat reading could not give, since a flat class's jump target would
// have had to write two.  The base is declared once here and pinned at that
// address; the intermediates and the outer classes are per-body, because each
// body writes its own distinct vftables and they have to be distinct symbols.
//
// The mixins carry one virtual function and the padding their spacing demands:
// twelve bytes for the base, four for each mixin, and twelve more inside the
// second intermediate to put the fourth sub-object at +0x20.  That is what the
// displacements witness and nothing more.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address.

class NestedInlineBase
{
public:
	virtual ~NestedInlineBase();

	unsigned int m_pad[ 2 ];
};

#define BFME_NESTED_INLINE_DTOR3( NAME )                                      \
	class NAME##MixA { public: virtual void mixA(); };                        \
	class NAME##Mid : public NestedInlineBase, public NAME##MixA              \
	{                                                                         \
	public:                                                                   \
		virtual ~NAME##Mid() {}                                               \
	};                                                                        \
	class NAME##MixC { public: virtual void mixC(); };                        \
	class NAME : public NAME##Mid, public NAME##MixC                          \
	{                                                                         \
	public:                                                                   \
		virtual ~NAME();                                                      \
	};                                                                        \
	NAME::~NAME()                                                             \
	{                                                                         \
	}

#define BFME_NESTED_INLINE_DTOR4( NAME )                                      \
	class NAME##MixA { public: virtual void mixA(); };                        \
	class NAME##Mid : public NestedInlineBase, public NAME##MixA              \
	{                                                                         \
	public:                                                                   \
		virtual ~NAME##Mid() {}                                               \
	};                                                                        \
	class NAME##MixC { public: virtual void mixC(); };                        \
	class NAME##Mid2 : public NAME##Mid, public NAME##MixC                    \
	{                                                                         \
	public:                                                                   \
		virtual ~NAME##Mid2() {}                                              \
                                                                              \
		unsigned int m_pad[ 3 ];                                              \
	};                                                                        \
	class NAME##MixD { public: virtual void mixD(); };                        \
	class NAME : public NAME##Mid2, public NAME##MixD                         \
	{                                                                         \
	public:                                                                   \
		virtual ~NAME();                                                      \
	};                                                                        \
	NAME::~NAME()                                                             \
	{                                                                         \
	}

BFME_NESTED_INLINE_DTOR3( Rva00200840NestedDtor )
BFME_NESTED_INLINE_DTOR3( Rva00200870NestedDtor )
BFME_NESTED_INLINE_DTOR3( Rva0020DB20NestedDtor )
BFME_NESTED_INLINE_DTOR3( Rva00213B70NestedDtor )
BFME_NESTED_INLINE_DTOR3( Rva00253D30NestedDtor )
BFME_NESTED_INLINE_DTOR3( Rva002545E0NestedDtor )
BFME_NESTED_INLINE_DTOR3( Rva00254960NestedDtor )
BFME_NESTED_INLINE_DTOR3( Rva00254F50NestedDtor )
BFME_NESTED_INLINE_DTOR3( Rva00255320NestedDtor )
BFME_NESTED_INLINE_DTOR3( Rva00255580NestedDtor )
BFME_NESTED_INLINE_DTOR3( Rva00255840NestedDtor )
BFME_NESTED_INLINE_DTOR3( Rva00255A40NestedDtor )
BFME_NESTED_INLINE_DTOR3( Rva00255DD0NestedDtor )
BFME_NESTED_INLINE_DTOR3( Rva002560A0NestedDtor )

BFME_NESTED_INLINE_DTOR4( Rva001F5B90NestedDtor )
BFME_NESTED_INLINE_DTOR4( Rva001F7790NestedDtor )
BFME_NESTED_INLINE_DTOR4( Rva002028E0NestedDtor )
BFME_NESTED_INLINE_DTOR4( Rva00202E80NestedDtor )
BFME_NESTED_INLINE_DTOR4( Rva00205660NestedDtor )
BFME_NESTED_INLINE_DTOR4( Rva0020D090NestedDtor )
BFME_NESTED_INLINE_DTOR4( Rva0020D4E0NestedDtor )
BFME_NESTED_INLINE_DTOR4( Rva00215A70NestedDtor )
BFME_NESTED_INLINE_DTOR4( Rva002D0480NestedDtor )
BFME_NESTED_INLINE_DTOR4( Rva002D2210NestedDtor )
