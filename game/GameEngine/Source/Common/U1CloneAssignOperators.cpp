// Three 60-byte copy-assignment operators that replace a held polymorphic
// object with a clone of the other side`s, then assign a member.  Retail:
//
//     push ebx / mov ebx,[esp+8] / push esi / mov esi,ecx
//     mov ecx,[ebx] / test ecx,ecx / push edi / je none
//     mov eax,[ecx] / call dword ptr [eax+4] / mov edi,eax / jmp have
//     none: xor edi,edi
//     have: mov ecx,[esi] / test ecx,ecx / je gone
//     mov edx,[ecx] / push 1 / call dword ptr [edx]
//     gone: add ebx,4 / push ebx / lea ecx,[esi+4] / mov [esi],edi
//     call <REL32>
//     pop edi / mov eax,esi / pop esi / pop ebx / ret 4
//
// WHAT THE BYTES SHOW.  `this` in ecx, `ret 4`, and `mov eax,esi` returning
// `this`: a __thiscall member taking one dword and returning a reference to
// the receiver.  The parameter is only ever dereferenced, never written, so it
// is a reference to const.
//
// THE FIRST HALF IS A CLONE.  The parameter`s offset-0 member is null-checked
// and, when present, SLOT 1 is called with NO arguments and its return value
// kept; the null arm supplies zero in the same register.  One value reaching
// one register on both paths is a conditional expression, not two assignments.
//
// THE SECOND HALF IS `delete`.  The RECEIVER`s offset-0 member is null-checked
// and SLOT 0 is called with a literal 1 pushed.  That flag protocol is the
// MSVC scalar deleting destructor and nothing else emits it: `delete p` where
// p`s static type declares a virtual destructor compiles to exactly this
// null test, vftable load, `push 1`, `call [edx]` -- so slot 0 is the virtual
// destructor and slot 1 is the next virtual declared after it.
//
// THE CLONE IS TAKEN BEFORE THE DELETE.  The compiler does not reorder these
// across the opaque virtual calls, so the source computes the new value first
// and only then destroys the old one -- the self-assignment-safe spelling.
// The store `mov [esi],edi` is scheduled last, after both calls, but it is the
// same assignment.
//
// THE TAIL IS A MEMBER ASSIGNMENT.  `lea ecx,[esi+4]` with no null test is a
// member subobject of the receiver, `add ebx,4` is the corresponding subobject
// of the parameter, and the call is out of line -- so the member`s
// `operator=` is only DECLARED in this translation unit.  Three rows, three
// distinct call targets, three member types.
//
// A FOURTH ROW OF THIS SHAPE, 0x005CB1D0, IS NOT CLAIMED HERE.  It is
// byte-identical except that it computes the parameter`s subobject address
// with `lea eax,[ebx+4] / push eax` instead of `add ebx,4 / push ebx` -- four
// bytes either way, same operands, but a register the allocator declines to
// clobber.  Nothing in the source spellings tried reproduces that choice, and
// guessing at it would be asserting a difference the bytes do not explain, so
// the row is left for whoever finds what keeps `ebx` live there.
//
// IDENTITY IS NOT RECOVERED.  Nothing names the held interface or any of the
// three member types; every name comes from a row or callee address.

class U1Clonable
{
public:
	virtual ~U1Clonable();
	virtual U1Clonable *clone();
};

#define U1_CLONE_ASSIGN( ROW )                                                \
	class U1Tail_##ROW                                                        \
	{                                                                         \
	public:                                                                   \
		U1Tail_##ROW &operator=( const U1Tail_##ROW &rhs );                   \
	};                                                                        \
	class U1Assign_##ROW                                                      \
	{                                                                         \
	public:                                                                   \
		U1Assign_##ROW &operator=( const U1Assign_##ROW &rhs );               \
                                                                              \
		U1Clonable *m_held;                                                   \
		U1Tail_##ROW m_tail;                                                  \
	};                                                                        \
	U1Assign_##ROW &U1Assign_##ROW::operator=( const U1Assign_##ROW &rhs )    \
	{                                                                         \
		U1Clonable *source = rhs.m_held;                                      \
		U1Clonable *copy = source ? source->clone() : 0;                      \
		delete m_held;                                                        \
		m_held = copy;                                                        \
		m_tail = rhs.m_tail;                                                  \
		return *this;                                                         \
	}

U1_CLONE_ASSIGN( 005CD380 )
U1_CLONE_ASSIGN( 005CDCD0 )
U1_CLONE_ASSIGN( 005CEC60 )
