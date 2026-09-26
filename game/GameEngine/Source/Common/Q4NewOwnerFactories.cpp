// cl: /EHsc
//
// Twelve 93-byte __thiscall members that allocate one object and construct it
// with the receiver as the only constructor argument:
//
//     push <SIZE> / call operator new / add esp,4
//     test eax,eax / je null
//     push this / mov ecx,eax / call <CTOR>
//     return eax          (null path returns 0 without calling the ctor)
//
// WHAT THE BYTES SHOW.  `push <SIZE>` then `call ??2@YAPAXI@Z` with a four-byte
// caller pop is a plain `new` expression, not a placement or pool allocation:
// the size is the operand, and the null test that skips the constructor is the
// language rule for a throwless `operator new`, emitted by the compiler and not
// written in the source.  So SIZE is `sizeof` the constructed class, exactly.
//
// The receiver is copied into esi BEFORE the allocation (`mov esi,ecx` sits
// between the push and the call) and pushed as the constructor's single stack
// argument; the constructor is entered with ecx = the fresh block and pops that
// argument itself, so it is __thiscall taking one pointer.  Nothing else is
// read out of the receiver and no field of the new object is touched here, so
// the whole body is one `return new T(this);`.
//
// The fs:[0] frame is real: `-EHsc` (this file's `// cl:` directive) is what
// puts the three-push __CxxFrameHandler frame and the two EH-state stores in
// front of the allocation.  Under the project's default `-EHsc-` the same
// source emits neither, so the frame is evidence that these translation units
// were built WITH exception handling.  The pushed handler address and the
// funcinfo it loads are DIR32 operands copied from retail; they are not proof
// of anything and no identity is claimed for them.
//
// THE VARYING AXIS IS TWO FIELDS AND THEY MOVE TOGETHER: the allocation size
// and the constructor's REL32.  Twelve members, twelve distinct constructors,
// and sizes 0x24..0x60 with three repeats (0x28, 0x38, 0x3c) -- every repeat
// pairs with a different callee, so the two fields are not one axis in
// disguise.  Every constructor body sits within 0xA0 bytes of the member that
// calls it except Gen00930E00, which is 0x210 below its caller; the ILT thunk
// chain resolves all twelve unaided.
//
// IDENTITY IS NOT RECOVERED.  Every class here is named after an address: the
// HOST is named for the member's own RVA and the constructed class for its
// constructor's.  What the bytes cannot decide: the host's real type (nothing
// is loaded through it), whether the constructed type has bases or virtual
// functions (its constructor is out of line), and what the member is called.
// The `char m_storage[SIZE]` member is a size carrier, not a claim about
// layout -- only the total is evidence.

#define Q4_NEW_OWNER_FACTORY( HOST, GEN, SIZE )                            \
	class HOST;                                                            \
	class GEN                                                              \
	{                                                                      \
	public:                                                                \
		GEN( HOST *owner );                                                \
		char m_storage[ SIZE ];                                            \
	};                                                                     \
	class HOST                                                             \
	{                                                                     \
	public:                                                                \
		GEN *create();                                                     \
	};                                                                     \
	GEN *HOST::create()                                                    \
	{                                                                      \
		return new GEN( this );                                            \
	}

Q4_NEW_OWNER_FACTORY( Host0035E450, Gen0035E3B0, 0x4c )
Q4_NEW_OWNER_FACTORY( Host005EC580, Gen005EC600, 0x3c )
Q4_NEW_OWNER_FACTORY( Host005EC7F0, Gen005EC870, 0x60 )
Q4_NEW_OWNER_FACTORY( Host005ECC40, Gen005ECCC0, 0x40 )
Q4_NEW_OWNER_FACTORY( Host005ED050, Gen005ED0D0, 0x44 )
Q4_NEW_OWNER_FACTORY( Host005ED460, Gen005ED4E0, 0x28 )
Q4_NEW_OWNER_FACTORY( Host005ED750, Gen005ED7D0, 0x24 )
Q4_NEW_OWNER_FACTORY( Host005ED900, Gen005ED980, 0x3c )
Q4_NEW_OWNER_FACTORY( Host005EDA90, Gen005EDB10, 0x30 )
Q4_NEW_OWNER_FACTORY( Host005EDC00, Gen005EDC80, 0x28 )
Q4_NEW_OWNER_FACTORY( Host005EDD60, Gen005EDDE0, 0x38 )
Q4_NEW_OWNER_FACTORY( Host00931010, Gen00930E00, 0x38 )
