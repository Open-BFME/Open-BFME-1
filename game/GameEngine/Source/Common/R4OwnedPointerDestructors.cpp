// Six 94-byte virtual destructors whose whole body is one delete of an owned
// member pointer -- and the mnemonic family turned out to be TWO SOURCE SHAPES,
// which is exactly what the byte gate is for.
//
// WHAT THE BYTES SHOW.  A __thiscall with an fs:[0] frame.  It opens by storing
// a vftable address into the dword at offset 0 -- MSVC's destructor vptr reset,
// so the class is polymorphic and the vptr is at offset 0 -- then drives the EH
// state to 0, loads a member pointer, and on non-null loads the pointee's
// vftable and calls SLOT 0 with the literal 1 pushed.  Slot 0 plus a flag is
// MSVC's scalar deleting destructor and flag 1 means free the storage, so this
// is `delete p` on a type with a virtual destructor, not `p->~T()`.  The member
// is zeroed, the state is driven to -1, and control leaves through a __thiscall
// call with ecx = this: the base class destructor.
//
// THE SPLIT IS ONE BRANCH DISTANCE.  `delete p` emits its own null test, and
// leaves a following `p = 0` OUTSIDE the guarded block; a source-level
// `if (p) { delete p; p = 0; }` pulls the store INSIDE it and the compiler does
// not re-test.  Three rows jump 0x0D bytes (over the call AND the store) and
// three jump 0x06 (over the call only).  Same instruction sequence, same length,
// two different sources -- the mnemonic grouping could not see it, and both
// spellings are written out below rather than one being forced onto all six.
//
// AXES.  The member's OFFSET -- 0x24, 0x28, 0x2C, 0x50, 0x60, 0x6C, all
// six distinct -- carried here as padding between the vptr and the pointer;
// and the BASE destructor's REL32, of which there are two, 0x000A1B30 and
// 0x00172430.  The guard/no-guard split cuts ACROSS both, so it is a third
// independent fact and not a restatement of either.  The vftable stored at
// offset 0 is a DIR32 operand and costs no pin; all six differ, which
// independently confirms six types rather than one seen six times.
//
// The 0x00172430 base destructor is identified independently as
// AIInternalMoveToState by its matched body, constructor, and the named state
// destructors that route through this shared cleanup.  The 0x000A1B30 base is
// named Rva000A1B30Holder: that is the DEFINING name at that address (its
// matched body lives in GameClient/GUI/Rva000A1B30VectorHolderDestructor.cpp),
// so it is spelled here rather than a local stand-in that could never link.
//
// WHAT THE BYTES CANNOT DECIDE.  The type of the owned object beyond "it has a
// virtual destructor in slot 0", and whether the padding between the vptr and
// the pointer is one member or twenty.

struct GenOwned { virtual ~GenOwned(); };

// The base destructor at 0x000A1B30 is owned by
// GameClient/GUI/Rva000A1B30VectorHolderDestructor.cpp as
// ??1Rva000A1B30Holder@@QAE@XZ, so this TU declares it by that name -- and
// without `virtual`, because a virtual base destructor would mangle UAE.
struct Rva000A1B30Holder { ~Rva000A1B30Holder(); };
struct AIInternalMoveToState { virtual ~AIInternalMoveToState(); };

// That base must still occupy four bytes at offset 0 (retail tail-calls it
// with ecx = this, i.e. it is the PRIMARY base), and the defining name cannot
// provide them: a non-virtual destructor contributes no vptr, so the derived
// classes slid past it and every member offset moved.  This stand-in reserves
// the vptr width -- and inlines into each derived destructor -- so the tail
// call itself carries the real, defining name.  Same shape as
// OwnedPtrBase000A1B30 in Q4OwnedPtrDtors.cpp, for this very destructor.
class __declspec( novtable ) R4Base000A1B30
{
public:
	virtual ~R4Base000A1B30()
	{
		reinterpret_cast<Rva000A1B30Holder *>( this )->Rva000A1B30Holder::~Rva000A1B30Holder();
	}
};

#define R4_OWNED_PTR_MEMBERS( NAME, BASE, PAD )                               \
	struct NAME : public BASE                                                 \
	{                                                                         \
		char m_pad[ PAD ];                                                    \
		GenOwned *m_owned;                                                    \
		virtual ~NAME();                                                      \
	};

// je 0x0D -- the store is inside a source-level null guard.
#define R4_OWNED_PTR_DTOR_GUARDED( NAME, BASE, PAD )                          \
	R4_OWNED_PTR_MEMBERS( NAME, BASE, PAD )                                   \
	NAME::~NAME()                                                             \
	{                                                                         \
		if ( m_owned != 0 )                                                   \
		{                                                                     \
			delete m_owned;                                                   \
			m_owned = 0;                                                      \
		}                                                                     \
	}

// je 0x06 -- only delete's own null test; the store follows unconditionally.
#define R4_OWNED_PTR_DTOR_PLAIN( NAME, BASE, PAD )                            \
	R4_OWNED_PTR_MEMBERS( NAME, BASE, PAD )                                   \
	NAME::~NAME()                                                             \
	{                                                                         \
		delete m_owned;                                                       \
		m_owned = 0;                                                          \
	}

R4_OWNED_PTR_DTOR_GUARDED( Rva00173F30, R4Base000A1B30, 0x20 )
R4_OWNED_PTR_DTOR_GUARDED( Rva001780A0, AIInternalMoveToState, 0x4C )
R4_OWNED_PTR_DTOR_GUARDED( Rva00179550, AIInternalMoveToState, 0x5C )

// Rva00183C10 now lives with its constructor and full 18-slot class in
// GameLogic/AI/Rva00183AF0StateCtor.cpp.
R4_OWNED_PTR_DTOR_PLAIN( Rva00183DC0, AIInternalMoveToState, 0x68 )
R4_OWNED_PTR_DTOR_PLAIN( DozerActionState, R4Base000A1B30, 0x24 )
R4_OWNED_PTR_DTOR_PLAIN( Rva002BF7D0, R4Base000A1B30, 0x28 )
