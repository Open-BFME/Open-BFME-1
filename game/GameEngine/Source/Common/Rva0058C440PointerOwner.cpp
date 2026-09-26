// Address-derived owner for the 34-byte body at 0x0058C440.  The bytes show a
// single pointer at this+0: replacing it releases the old non-null allocation,
// while assigning the current pointer is a no-op.

void __cdecl f_00881eb0( void *block );

class Rva0058C440PointerOwner
{
public:
	void assign( void *value );

private:
	void *m_value;
};

void Rva0058C440PointerOwner::assign( void *value )
{
	if( value != m_value )
	{
		if( m_value )
			f_00881eb0( m_value );
		m_value = value;
	}
}
