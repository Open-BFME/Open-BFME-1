// cl: /DNDEBUG /DWIN32 /MD /EHsc /O2 /Ob2
//
// Retail 0x0044F630, 90 bytes through the int3 run at +0x5A.  Nothing calls it
// or its ILT 0x0002BA99 directly, so the names keep the address.  Bits 1/2 of
// the owner's first word gate on the argument's byte +0x26; bits 4/8 and
// 0x10/0x20 then reject on bytes +0x24 and +0x25.  The gate's `false` is 8-bit
// and the reject chain's result a 32-bit 0/1, hence the three return arms.

struct Rva0044F630Arg
{
	char m_unmodelled00[ 0x24 ];
	bool m_byte24;
	bool m_byte25;
	bool m_byte26;
};

class Rva0044F630Owner
{
public:
	bool test( const Rva0044F630Arg *arg ) const;
private:
	unsigned int m_flags;
};

bool Rva0044F630Owner::test( const Rva0044F630Arg *arg ) const
{
	if( !( ( ( m_flags & 1 ) && arg->m_byte26 ) || ( ( m_flags & 2 ) && !arg->m_byte26 ) ) )
		return false;

	return !( ( arg->m_byte24 && ( m_flags & 4 ) ) || ( !arg->m_byte24 && ( m_flags & 8 ) )
		|| ( arg->m_byte25 && ( m_flags & 0x10 ) ) || ( !arg->m_byte25 && ( m_flags & 0x20 ) ) );
}
