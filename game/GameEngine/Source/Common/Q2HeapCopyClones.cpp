// cl: /EHs-c-
// Fourteen 31-byte __thiscall const members that heap-allocate a copy of the
// receiver and return the pointer:
//
//   push esi / push <SIZE> / mov esi,ecx
//   call ??2@YAPAXI@Z / add esp,4
//   test eax,eax / je null
//   push esi / mov ecx,eax / call <COPY CTOR> / pop esi / ret
//  null:
//   xor eax,eax / pop esi / ret
//
// WHAT THE BYTES SHOW.  This is MSVC's whole `new T(expr)` sequence and not a
// hand-written allocate-then-initialise: the size is a literal push, the
// allocator is the global `operator new` body the ledger already carries at
// 0x00881F30, the `add esp,4` is the __cdecl cleanup, and the `test/je` that
// skips the constructor on a null return with `xor eax,eax` is the guard MSVC
// interposes for a class type -- source code cannot produce that arm without
// writing the check itself, and then the null arm would not re-materialise
// eax.  `mov esi,ecx` before the allocation and `push esi` as the single
// __thiscall stack argument make the constructor a COPY constructor taking the
// receiver by reference; there is no other argument.
//
// THE CONSTRUCTOR EACH ROW CALLS SITS AT ITS OWN ADDRESS PLUS 0x30, for all
// fourteen rows without exception.  That is what ties each clone to one class:
// the pairing is read off the REL32, not assumed.
//
// TWO AXES: the pushed size (sizeof(T), which is all these bodies say about
// the class) and the copy-constructor target.  23 of the 31 bytes are
// concrete; the two displacements are resolved from the ledger and the pins.
//
// WHAT THE BYTES DO NOT DECIDE.  Nothing here shows a single member of the
// class -- only its size -- so the layout is one opaque char array.  The
// return type is spelled as the class's own pointer because `new T` yields
// one, but a base-class return would encode identically.  Whether the copy
// constructor is user-written or implicit is not visible either; it is
// declared and left undefined so that the call is the only thing asserted.
// The TU is built with exception handling OFF, which retail's bytes require:
// with /EHs the same source gets a 93-byte body wrapped in an unwind frame.
//
// IDENTITY IS NOT RECOVERED.  Every name is derived from an address.

#define Q2_HEAP_COPY_CLONE( NAME, SIZE )                                  \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		NAME( const NAME &other );                                        \
		NAME *clone() const;                                              \
	private:                                                              \
		char m_unreconstructed_00[ SIZE ];                                \
	};                                                                    \
	NAME *NAME::clone() const                                             \
	{                                                                     \
		return new NAME( *this );                                         \
	}

Q2_HEAP_COPY_CLONE( Rva005E92E0, 0x4C )
Q2_HEAP_COPY_CLONE( Rva005E9750, 0x10 )
Q2_HEAP_COPY_CLONE( Rva005E9970, 0x28 )
Q2_HEAP_COPY_CLONE( Rva005E9BC0, 0x10 )
Q2_HEAP_COPY_CLONE( Rva005E9DE0, 0x18 )
Q2_HEAP_COPY_CLONE( Rva005EA020, 0x40 )
Q2_HEAP_COPY_CLONE( Rva005EA190, 0x1C )
Q2_HEAP_COPY_CLONE( Rva005EA2B0, 0x5C )
Q2_HEAP_COPY_CLONE( Rva005EA7F0, 0x14 )
Q2_HEAP_COPY_CLONE( Rva005EAA50, 0x2C )
Q2_HEAP_COPY_CLONE( Rva005EACB0, 0x14 )
Q2_HEAP_COPY_CLONE( Rva005EAF10, 0x20 )
Q2_HEAP_COPY_CLONE( Rva005EB190, 0x44 )
Q2_HEAP_COPY_CLONE( Rva005EB2C0, 0x24 )
