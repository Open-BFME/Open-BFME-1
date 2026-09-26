// 9 forty-seven-byte setters that let go of the object they hold before
// taking the new one:
//
//     push esi / mov esi,ecx / mov ecx,[esi+<D>] / test ecx,ecx / je +N /
//     mov eax,[ecx] / push 1 / call [eax] / mov ecx,[esp+8] /
//     mov [esi+<D>],ecx / pop esi / ret 4 /
//     mov edx,[esp+8] / mov [esi+<D>],edx / pop esi / ret 4
//
// WHAT THE BYTES SHOW.  The member at +<D> is read, and if it is not null a
// virtual call goes through slot 0 of its vftable with the constant 1; either
// way the function's one argument is then stored into that same member.  The
// store is duplicated into both exits, which is the compiler's tail
// duplication -- one `m_value = value` after the `if` produces exactly this.
//
// The call takes one dword and the callee cleans it (`[esp+8]` reads the same
// argument slot on both paths), so it is a __thiscall member of the held
// object's class.  Slot 0 with a constant flag is all the bytes say about it;
// it is declared here as the first virtual of a class and named for what it is
// doing to the object being dropped, not for anything witnessed.
//
// All 9 bodies use slot 0 and the constant 1, and differ only in the member's
// displacement.  IDENTITY IS NOT RECOVERED: every name is derived from an
// address.

class VRelease
{
public:
	virtual void release( int mode );
};

#define BFME_RELEASE_THEN_ASSIGN( NAME, LEAD )                                \
	class NAME                                                                \
	{                                                                         \
	public:                                                                   \
		void set( VRelease *value );                                          \
                                                                              \
		char      m_lead[ LEAD ];                                             \
		VRelease *m_value;                                                    \
	};                                                                        \
	void NAME::set( VRelease *value )                                         \
	{                                                                         \
		if ( m_value != 0 )                                                   \
			m_value->release( 1 );                                            \
		m_value = value;                                                      \
	}

BFME_RELEASE_THEN_ASSIGN( Rva000C91C0ReleaseSet, 0x1C0 )
BFME_RELEASE_THEN_ASSIGN( Rva005C4C40ReleaseSet, 0xA0 )
BFME_RELEASE_THEN_ASSIGN( Rva005C4E70ReleaseSet, 0xA4 )
BFME_RELEASE_THEN_ASSIGN( Rva005C4EB0ReleaseSet, 0xA8 )
BFME_RELEASE_THEN_ASSIGN( Rva005C4EF0ReleaseSet, 0xAC )
BFME_RELEASE_THEN_ASSIGN( Rva005C4F30ReleaseSet, 0xB0 )
BFME_RELEASE_THEN_ASSIGN( Rva005C4F70ReleaseSet, 0xB4 )
BFME_RELEASE_THEN_ASSIGN( Rva005C4FB0ReleaseSet, 0xB8 )
BFME_RELEASE_THEN_ASSIGN( Rva005C4FF0ReleaseSet, 0xBC )
