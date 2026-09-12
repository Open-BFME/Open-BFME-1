// The 22 byte-identical 27-byte slot forwarders -- one shape parameterised by
// the vftable slot it calls, four slots wide.
//
// Retail, with SLOT taking the four values 0x0C, 0x10, 0x14 and 0x18:
//
//     push ecx / mov eax,[ecx] / push esi / mov esi,[esp+0xC] / push esi
//     mov dword ptr [esp+8],0 / call dword ptr [eax+SLOT] / mov eax,esi
//     pop esi / pop ecx / ret 4
//
// Six copies call slot 3, six call slot 4, six call slot 5 and four call slot 6;
// the 27 bytes are otherwise identical down to the last byte, and the four
// families interleave at fixed stride ten times over (0x00838460-0x00838540,
// 0x0083A340-0x0083A420), which is what a header of non-inlinable helpers looks
// like when the compiler emits it once per including TU.
//
// WHAT THE BYTES SHOW.  `ret 4` with `this` in ecx is __thiscall with one dword
// stack argument.  ecx is never modified, so the virtual call is on `this`; the
// dword at `this+0` is the vftable.  esi holds the single incoming argument --
// `[esp+0xC]` after two pushes and the return address -- it is pushed as the
// call's only argument (the callee's `ret 4` is what returns esp to the saved
// esi, which is how we know the callee takes exactly one), and `mov eax,esi`
// then returns that same pointer.  A function that returns the pointer it was
// handed is the classic MSVC hidden-return-buffer shape, but the bytes cannot
// distinguish that from an explicit `return p;`, so the spelling below asserts
// only the latter.
//
// THE ZEROED LOCAL.  `push ecx` is MSVC 7.1's one-byte `sub esp,4`: it opens
// four bytes of frame, and `mov dword ptr [esp+8],0` is a store into that slot,
// not into the outgoing argument block -- the saved esi sits between the two, so
// they cannot be one contiguous argument area, and the callee pops only four
// bytes.  Nothing ever reads the slot.  A plain `int f = 0;` does not survive:
// probed, MSVC deletes the store and the whole four bytes with it, emitting 17
// bytes instead of 27.  What reproduces the 27 exactly, on the first spelling,
// is a local the compiler is forbidden to eliminate, which in C++ is a
// `volatile` one.  That is all the bytes support: four bytes of frame that must
// be zeroed and are never read.  Whatever the original declaration was -- a
// debug counter, a profiling hook, a guard word -- its observable effect here is
// exactly this store, and modelling it as anything richer would be inventing
// source that the bytes do not witness.
//
// WHY THE MEMBERS ARE SEPARATE FUNCTIONS AND NOT ALIASES.  22 distinct
// addresses, and the four slot values prove they are not one function: a single
// COMDAT copied per TU could not call four different vftable slots.  They are
// distinct instantiations of one small forwarding template or macro, and the
// spelling below keeps them distinct.
//
// WHY THE NAMES ARE ADDRESS-DERIVED.  No name is witnessed for the class, for
// the argument type, or for the interface whose slots 3 through 6 are called;
// the region is a dead-COMDAT drawer with neighbours from unrelated sources.
// Each body is named for its own address so the row claims the bytes without
// asserting an identity nobody has recovered.

class OneArgVtableSlot3
{
public:
	virtual void slotPad0();
	virtual void slotPad1();
	virtual void slotPad2();
	virtual void slotDispatch( void *argument );
};

class OneArgVtableSlot4
{
public:
	virtual void slotPad0();
	virtual void slotPad1();
	virtual void slotPad2();
	virtual void slotPad3();
	virtual void slotDispatch( void *argument );
};

class OneArgVtableSlot5
{
public:
	virtual void slotPad0();
	virtual void slotPad1();
	virtual void slotPad2();
	virtual void slotPad3();
	virtual void slotPad4();
	virtual void slotDispatch( void *argument );
};

class OneArgVtableSlot6
{
public:
	virtual void slotPad0();
	virtual void slotPad1();
	virtual void slotPad2();
	virtual void slotPad3();
	virtual void slotPad4();
	virtual void slotPad5();
	virtual void slotDispatch( void *argument );
};

#define BFME_SLOT_FORWARD( NAME, BASE )                                       \
	class NAME : public BASE                                                  \
	{                                                                         \
	public:                                                                   \
		void *forward( void *argument );                                      \
	};                                                                        \
	void *NAME::forward( void *argument )                                     \
	{                                                                         \
		volatile int retained = 0;                                            \
                                                                              \
		slotDispatch( argument );                                             \
		return argument;                                                      \
	}

BFME_SLOT_FORWARD( Rva0053A5A0SlotForward, OneArgVtableSlot3 )
BFME_SLOT_FORWARD( Rva00838460SlotForward, OneArgVtableSlot3 )
BFME_SLOT_FORWARD( Rva008384E0SlotForward, OneArgVtableSlot3 )
BFME_SLOT_FORWARD( Rva0083A340SlotForward, OneArgVtableSlot3 )
BFME_SLOT_FORWARD( Rva0083A3C0SlotForward, OneArgVtableSlot3 )
BFME_SLOT_FORWARD( Rva0083F690SlotForward, OneArgVtableSlot3 )

BFME_SLOT_FORWARD( Rva00838480SlotForward, OneArgVtableSlot4 )
BFME_SLOT_FORWARD( Rva00838500SlotForward, OneArgVtableSlot4 )
BFME_SLOT_FORWARD( Rva00838FA0SlotForward, OneArgVtableSlot4 )
BFME_SLOT_FORWARD( Rva0083A360SlotForward, OneArgVtableSlot4 )
BFME_SLOT_FORWARD( Rva0083A3E0SlotForward, OneArgVtableSlot4 )
BFME_SLOT_FORWARD( Rva0083AE60SlotForward, OneArgVtableSlot4 )

BFME_SLOT_FORWARD( Rva008384A0SlotForward, OneArgVtableSlot5 )
BFME_SLOT_FORWARD( Rva00838520SlotForward, OneArgVtableSlot5 )
BFME_SLOT_FORWARD( Rva00838FC0SlotForward, OneArgVtableSlot5 )
BFME_SLOT_FORWARD( Rva0083A380SlotForward, OneArgVtableSlot5 )
BFME_SLOT_FORWARD( Rva0083A400SlotForward, OneArgVtableSlot5 )
BFME_SLOT_FORWARD( Rva0083AE80SlotForward, OneArgVtableSlot5 )

BFME_SLOT_FORWARD( Rva008384C0SlotForward, OneArgVtableSlot6 )
BFME_SLOT_FORWARD( Rva00838540SlotForward, OneArgVtableSlot6 )
BFME_SLOT_FORWARD( Rva0083A3A0SlotForward, OneArgVtableSlot6 )
BFME_SLOT_FORWARD( Rva0083A420SlotForward, OneArgVtableSlot6 )

