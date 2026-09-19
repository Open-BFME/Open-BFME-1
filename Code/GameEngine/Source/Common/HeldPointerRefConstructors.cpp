// The eight byte-identical 36-byte constructors at 0x005BE9C0-0x005BEDB0, laid
// out at a flat 0x90 stride through one stretch of dead COMDATs.
//
//     mov eax,[esp+4] / push esi / mov esi,ecx / mov ecx,[eax]
//     test ecx,ecx / je null / mov edx,[ecx] / call dword ptr [edx+4]
//     mov [esi],eax / mov eax,esi / pop esi / ret 4
//     null: xor eax,eax / mov [esi],eax / mov eax,esi / pop esi / ret 4
//
// WHAT THE BYTES SHOW.  `this` in ecx, one dword argument, `ret 4`, and `this`
// returned in eax: that is a __thiscall CONSTRUCTOR, not an ordinary member --
// an ordinary void member would not bother loading eax at all, and both exit
// paths here go out of their way to.  It writes exactly one dword of the object
// it is constructing, so the constructed class has one member.
//
// The argument is a pointer, and only its first dword is read; that dword is
// null-checked, and when non-null its own first dword is loaded and called
// through displacement 4 with no arguments -- a virtual call on slot 1 of a
// polymorphic pointee.  The call's return value in eax becomes the constructed
// member; when the held pointer is null, zero does instead.  So the shape is
// "build a reference to whatever this holder is currently pointing at, or to
// nothing if it holds nothing", with the dereference itself virtual.
//
// The duplicated `mov [esi],eax / mov eax,esi / pop esi / ret 4` epilogue on
// both arms is /O2 tail duplication, exactly as in ReleasingAssigners.cpp; a
// single conditional initialiser produces it.
//
// SEPARATE FUNCTIONS, NOT ALIASES.  Eight distinct addresses at a regular stride
// inside one drawer -- eight instantiations of one pattern over eight held
// types, folding to identical bytes because the dispatched slot and the member
// count coincide.  There is no inline assembly and nothing else here that would
// defeat inlining, so the per-translation-unit reading that justifies an alias
// does not apply.
//
// IDENTITY IS NOT RECOVERED.  No ledger-known vftable points at these bodies and
// no RTTI descriptor is reachable from them, so each name is derived from its
// own address.  The 46-byte assignment at 0x005BEB20 has the same held-reference
// source and release sequence as the final assignment below.

class RefTarget
{
public:
	virtual void refRelease(bool deleteFlag);
	virtual RefTarget *refFetch();
};

class RefSource
{
public:
	RefTarget *m_held;
};

#define BFME_HELD_POINTER_REF( NAME )                                         \
	class NAME                                                                \
	{                                                                         \
	public:                                                                   \
		NAME( RefSource const &source );                                      \
		NAME &operator=( RefSource const &source );                           \
                                                                              \
		RefTarget *m_ref;                                                     \
	};                                                                        \
	NAME::NAME( RefSource const &source )                                      \
	{                                                                         \
		m_ref = source.m_held ? source.m_held->refFetch() : 0;                \
	}

BFME_HELD_POINTER_REF( Rva005BE9C0Ref )
BFME_HELD_POINTER_REF( Rva005BEA50Ref )
BFME_HELD_POINTER_REF( Rva005BEAE0Ref )
BFME_HELD_POINTER_REF( Rva005BEB70Ref )
BFME_HELD_POINTER_REF( Rva005BEC00Ref )
BFME_HELD_POINTER_REF( Rva005BEC90Ref )
BFME_HELD_POINTER_REF( Rva005BED20Ref )
BFME_HELD_POINTER_REF( Rva005BEDB0Ref )

Rva005BEA50Ref &Rva005BEA50Ref::operator=( RefSource const &source )
{
	RefTarget *ref = source.m_held ? source.m_held->refFetch() : 0;
	if( m_ref )
		m_ref->refRelease( true );
	m_ref = ref;
	return *this;
}

class Rva005BEB20Ref
{
public:
	Rva005BEB20Ref &operator=( RefSource const &source );

	RefTarget *m_ref;
};

Rva005BEB20Ref &Rva005BEB20Ref::operator=( RefSource const &source )
{
	RefTarget *ref = source.m_held ? source.m_held->refFetch() : 0;
	if( m_ref )
		m_ref->refRelease( true );
	m_ref = ref;
	return *this;
}

class Rva005BEA00Ref
{
public:
	Rva005BEA00Ref &operator=( RefSource const &source );

	RefTarget *m_ref;
};

Rva005BEA00Ref &Rva005BEA00Ref::operator=( RefSource const &source )
{
	RefTarget *ref = source.m_held ? source.m_held->refFetch() : 0;
	if( m_ref )
		m_ref->refRelease( true );
	m_ref = ref;
	return *this;
}

Rva005BEDB0Ref &Rva005BEDB0Ref::operator=( RefSource const &source )
{
	RefTarget *ref = source.m_held ? source.m_held->refFetch() : 0;
	if( m_ref )
		m_ref->refRelease( true );
	m_ref = ref;
	return *this;
}

class Rva005BED60Ref
{
public:
	Rva005BED60Ref &operator=( RefSource const &source );

	RefTarget *m_ref;
};

Rva005BED60Ref &Rva005BED60Ref::operator=( RefSource const &source )
{
	RefTarget *ref = source.m_held ? source.m_held->refFetch() : 0;
	if( m_ref )
		m_ref->refRelease( true );
	m_ref = ref;
	return *this;
}

class Rva005BECD0Ref
{
public:
	Rva005BECD0Ref &operator=( RefSource const &source );

	RefTarget *m_ref;
};

Rva005BECD0Ref &Rva005BECD0Ref::operator=( RefSource const &source )
{
	RefTarget *ref = source.m_held ? source.m_held->refFetch() : 0;
	if( m_ref )
		m_ref->refRelease( true );
	m_ref = ref;
	return *this;
}
