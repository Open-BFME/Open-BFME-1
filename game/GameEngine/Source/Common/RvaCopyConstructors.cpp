// The 41 byte-identical 15-byte copy constructors of one BFME class family.
//
// WHAT THE BODY IS.  Retail:
//
//     mov eax,ecx / mov ecx,[esp+4] / mov edx,[ecx+4] / mov [eax+4],edx
//     ret 4
//
// `mov eax,ecx` with no other use of eax is MSVC returning `this`, which a
// __thiscall member function only does when it is a constructor or an
// assignment operator.  One stack argument, dereferenced at +0x04, and one
// store, to this+0x04: the argument is another object of the same type and the
// body copies exactly one dword member across.  The dword at +0x00 is neither
// read nor written here, so it is a member this body leaves alone -- the same
// situation the landed 82-member functor-bind constructor family shows at its
// own +0x04.
//
// This reproduces on the first spelling.  Six variants -- initialiser list vs
// assignment body, `void *` vs `int` member, a one-member derived class over a
// one-member base, a pointer parameter instead of a reference, and
// `operator=` returning `*this` -- all assemble to these identical fifteen
// bytes.  So the shape settles the layout and the argument but does not
// discriminate between copy constructor and assignment operator; the copy
// constructor is written here because a two-dword class with a user-written
// assignment operator and a compiler-generated copy constructor is the rarer
// of the two.
//
// WHY THE COPIES ARE NOT FOLDED.  The 41 occurrences sit at 41 distinct
// addresses, clustered exactly where the functor-bind family clusters
// (0x0054Dxxx, 0x0056Cxxx, 0x0058Fxxx, 0x00619xxx).  They are 41 separate
// template instantiations kept apart rather than identical-code folded, so
// each needs its own body and its own ledger row.
//
// IDENTITY IS NOT RECOVERED.  No named caller reaches any of them and no
// string or RTTI descriptor in the image names the class.  Every name here is
// derived from the member's own address, so the row claims the bytes without
// asserting a class name nobody has recovered.  Promoting them is a mechanical
// repoint once the template is named.

#define BFME_RVA_COPY_CTOR( NAME )  \
	class NAME                      \
	{                               \
	public:                         \
		NAME( const NAME &other );  \
                                    \
	private:                        \
		void *m_unmodelled_00;      \
		void *m_copied_04;          \
	};                              \
	NAME::NAME( const NAME &other ) : m_copied_04( other.m_copied_04 ) {}

BFME_RVA_COPY_CTOR( Rva00062850Copy )
BFME_RVA_COPY_CTOR( Rva00062D70Copy )
BFME_RVA_COPY_CTOR( Rva00072A70Copy )
BFME_RVA_COPY_CTOR( Rva00072A90Copy )
BFME_RVA_COPY_CTOR( Rva00076400Copy )
BFME_RVA_COPY_CTOR( Rva00076420Copy )
BFME_RVA_COPY_CTOR( Rva00076530Copy )
BFME_RVA_COPY_CTOR( Rva00083FD0Copy )
BFME_RVA_COPY_CTOR( Rva00084000Copy )
BFME_RVA_COPY_CTOR( Rva00387580Copy )
BFME_RVA_COPY_CTOR( Rva003875A0Copy )
BFME_RVA_COPY_CTOR( Rva00388010Copy )
BFME_RVA_COPY_CTOR( Rva00388030Copy )
BFME_RVA_COPY_CTOR( Rva00388050Copy )
BFME_RVA_COPY_CTOR( Rva003C7DA0Copy )
BFME_RVA_COPY_CTOR( Rva003C84C0Copy )
BFME_RVA_COPY_CTOR( Rva00525430Copy )
BFME_RVA_COPY_CTOR( Rva005263D0Copy )
BFME_RVA_COPY_CTOR( Rva00526BA0Copy )
BFME_RVA_COPY_CTOR( Rva00526C60Copy )
BFME_RVA_COPY_CTOR( Rva0054BBC0Copy )
BFME_RVA_COPY_CTOR( Rva0054D500Copy )
BFME_RVA_COPY_CTOR( Rva0054D520Copy )
BFME_RVA_COPY_CTOR( Rva0054D540Copy )
BFME_RVA_COPY_CTOR( Rva0054D560Copy )
BFME_RVA_COPY_CTOR( Rva0054DAD0Copy )
BFME_RVA_COPY_CTOR( Rva0054DAF0Copy )
BFME_RVA_COPY_CTOR( Rva0054DB10Copy )
BFME_RVA_COPY_CTOR( Rva0054DB30Copy )
BFME_RVA_COPY_CTOR( Rva0054DB50Copy )
BFME_RVA_COPY_CTOR( Rva0056C3D0Copy )
BFME_RVA_COPY_CTOR( Rva0056CCA0Copy )
BFME_RVA_COPY_CTOR( Rva0056D570Copy )
BFME_RVA_COPY_CTOR( Rva0056D590Copy )
BFME_RVA_COPY_CTOR( Rva0058F210Copy )
BFME_RVA_COPY_CTOR( Rva0058F230Copy )
BFME_RVA_COPY_CTOR( Rva005906F0Copy )
BFME_RVA_COPY_CTOR( Rva00590710Copy )
BFME_RVA_COPY_CTOR( Rva00604EB0Copy )
BFME_RVA_COPY_CTOR( Rva00619AF0Copy )
BFME_RVA_COPY_CTOR( Rva00619E30Copy )
