// cl: /EHsc
// Twelve destructors of the same shape, over TWO base classes and four member
// types.
//
// WHAT THE BYTES SHOW.  A __thiscall with no stack arguments, wrapped in an
// SEH frame (`push -1` / `push <funcinfo>` / fs:[0] chain) and NOT returning
// `this` in eax -- which is what separates it from a constructor, since MSVC
// ends every constructor with `mov eax,<this>`.  Between the frame set-up and
// the teardown:
//
//     [this]      = <vftable A>          // this class's vptr
//     ecx         = this + OFFSET
//     ehState     = 0
//     call <a __thiscall taking nothing> // the member's destructor
//     [this]      = <vftable B>          // the BASE's vptr
//
// Setting the vptr, destroying a sub-object, then setting the vptr AGAIN to a
// different value is the destructor sequence: derived vptr on entry, member
// destroyed, base vptr restored by the base destructor -- which is inlined here
// and consists of nothing but that store.  The EH state exists because the
// member's destructor can throw and the base still has to be unwound.
//
// The SEH frame is not optional and not a scheduling choice: this TU carries
// `/EHsc`, and without it the same source tail-jumps in fourteen bytes.  The
// base destructor must be USER-DECLARED and inline-empty -- give the base no
// destructor at all and the second vptr store disappears along with the whole
// frame.
//
// THREE AXES, AND THE GRID IS UNEVEN ON PURPOSE.  The derived vftable is
// distinct in all twelve.  The BASE vftable takes only two values, splitting the
// twelve into a group of six and a group of six.  The member offset takes five
// values (0x08, 0x20, 0x2C, 0x3C, 0x44) and the member destructor four
// (0x005CE820, 0x000658A0, 0x00887940, 0x0089C900).  Offset and destructor do
// NOT track each other -- 0x00887940 turns up at 0x08, 0x20 and 0x44 -- so they
// are genuinely independent axes rather than one axis read twice.
//
// A base whose vptr is at 0 and whose member sits at 0x08 in one derived class
// and 0x44 in another is still ONE base: the extra room belongs to the DERIVED
// class, ahead of its member.  Eight bytes is therefore the base's size, and the
// padding is modelled where the bytes put it.
//
// IDENTITY IS NOT RECOVERED.  Every name is address-derived.  The vftable and
// EH-funcinfo operands are DIR32 sites filled from retail; what they establish
// is only the COUNT of distinct classes -- twelve derived, two base -- which is
// why they are modelled as twelve and two rather than collapsed.  Member
// destructor pins are address-derived and additive.
//
// WHAT THE BYTES CANNOT DECIDE.  How many virtuals any of these declare; what
// the derived classes hold in the space before their member; and whether the
// four member types are related to each other.

struct Q3EhMember000658A0 { ~Q3EhMember000658A0(); };
struct Q3EhMember005CE820 { ~Q3EhMember005CE820(); };
struct Q3EhMember00887940 { ~Q3EhMember00887940(); };
struct Q3EhMember0089C900 { ~Q3EhMember0089C900(); };

#define BFME_EH_BASE( NAME )                                                  \
	struct NAME                                                               \
	{                                                                         \
		virtual void slot();                                                  \
		int m_word;                                                           \
		~NAME() {}                                                            \
	};

BFME_EH_BASE( Q3EhBaseOne )
BFME_EH_BASE( Q3EhBaseTwo )

#define BFME_EH_DTOR_PADDED( NAME, BASE, MEMBER, OFFSET )                     \
	struct NAME##Object : public BASE                                         \
	{                                                                         \
		char m_lead[ OFFSET - 8 ];                                            \
		MEMBER m_sub;                                                         \
		virtual void slot();                                                  \
		~NAME##Object();                                                      \
	};                                                                        \
	NAME##Object::~NAME##Object() {}

#define BFME_EH_DTOR_TIGHT( NAME, BASE, MEMBER )                              \
	struct NAME##Object : public BASE                                         \
	{                                                                         \
		MEMBER m_sub;                                                         \
		virtual void slot();                                                  \
		~NAME##Object();                                                      \
	};                                                                        \
	NAME##Object::~NAME##Object() {}

BFME_EH_DTOR_PADDED( Rva005CE890, Q3EhBaseOne, Q3EhMember005CE820, 0x3C )
BFME_EH_DTOR_TIGHT( Rva00750440, Q3EhBaseOne, Q3EhMember00887940 )
BFME_EH_DTOR_PADDED( Rva007579F0, Q3EhBaseOne, Q3EhMember000658A0, 0x2C )
BFME_EH_DTOR_PADDED( Rva007587E0, Q3EhBaseOne, Q3EhMember00887940, 0x44 )
BFME_EH_DTOR_TIGHT( Rva00759480, Q3EhBaseOne, Q3EhMember00887940 )
BFME_EH_DTOR_PADDED( Rva0077D490, Q3EhBaseOne, Q3EhMember00887940, 0x20 )
BFME_EH_DTOR_TIGHT( Rva00899EB0, Q3EhBaseTwo, Q3EhMember0089C900 )
BFME_EH_DTOR_TIGHT( Rva0089A410, Q3EhBaseTwo, Q3EhMember0089C900 )
BFME_EH_DTOR_TIGHT( Rva0089A690, Q3EhBaseTwo, Q3EhMember0089C900 )
BFME_EH_DTOR_TIGHT( Rva0089A9D0, Q3EhBaseTwo, Q3EhMember0089C900 )
BFME_EH_DTOR_TIGHT( Rva0089AB70, Q3EhBaseTwo, Q3EhMember0089C900 )
BFME_EH_DTOR_TIGHT( Rva008CBDA0, Q3EhBaseTwo, Q3EhMember0089C900 )
