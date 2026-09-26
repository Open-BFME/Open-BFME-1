// cl: /EHsc
//
// Three 96-byte __thiscall members that allocate one object and copy-construct
// it from the receiver:
//
//     push <SIZE> / call operator new / add esp,4
//     test eax,eax / je null
//     push this / mov ecx,eax / call <COPY CTOR>
//     return eax          (null path returns 0 without calling the ctor)
//
// This is Q4NewOwnerFactories.cpp's shape exactly, three bytes longer for one
// reason: its twelve sizes are all below 0x80 and encode as `push imm8`, while
// 0xA0, 0xB4 and 0xA8 need `push imm32`.  93 + 3 = 96, and nothing else differs.
//
// WHAT IS NEW HERE IS THE CALLEE'S IDENTITY.  All three constructors are now
// ledger rows: 0x005EC160, 0x005ECF60 and 0x005EDF60, landed in
// V3CopyCtorForwarders.cpp as the COPY constructors `??0RvaXXXXXXXX@@QAE@ABV0@@Z`
// -- each takes one pointer to its own type, forwards it to a base copy
// constructor and re-stamps its own vptrs.  So the single argument these
// factories push is not an unrelated owner: it is the receiver used as the copy
// source, the receiver and the constructed object are the SAME class, and the
// member is a clone -- `return new T( *this );`.
//
// That reading also applies to Q4NewOwnerFactories.cpp, whose Gen005EC600,
// Gen005EC870, Gen005ECCC0, Gen005ED0D0, Gen005ED4E0, Gen005ED7D0,
// Gen005ED980, Gen005EDB10, Gen005EDC80 and Gen005EDDE0 are the same ten
// bodies, all of them copy constructors by the same evidence.  A pointer
// argument and a `const T&` argument are indistinguishable in these bytes, so
// that file byte-gates either way; its `Host` classes are the part that is now
// known to be the constructed class itself.  Nothing there is wrong on the
// bytes, so it is left alone rather than rewritten from this range.
//
// THE ALLOCATION SIZE IS `sizeof` THE CLASS, exactly, because a plain `new`
// expression takes it as the operand.  V3CopyCtorForwarders.cpp accounts for
// the first 0x20 bytes of each of these three (four polymorphic subobjects at
// 0, 0x14, 0x18 and 0x1C); the rest is unreconstructed and carried here as a
// size-only member, the same device Q4NewOwnerFactories.cpp uses.
//
// The fs:[0] frame comes from `-EHsc`, this file's `// cl:` directive; the
// pushed handler address and funcinfo are DIR32 operands copied from retail and
// claim nothing.
//
// IDENTITY IS NOT RECOVERED.  Class names are the constructor's address; the
// member's own name is not recoverable from the image at all.

#define V3_CLONE_FACTORY( NAME, SIZE )                                     \
	class NAME                                                             \
	{                                                                      \
	public:                                                                \
		NAME( const NAME &other );                                         \
		NAME *clone() const;                                               \
		char m_storage[ SIZE ];                                            \
	};                                                                     \
	NAME *NAME::clone() const                                              \
	{                                                                      \
		return new NAME( *this );                                          \
	}

V3_CLONE_FACTORY( Rva005EC160, 0xa0 )
V3_CLONE_FACTORY( Rva005ECF60, 0xb4 )
V3_CLONE_FACTORY( Rva005EDF60, 0xa8 )
