// Two row-less leaf bodies from the unclaimed-boundary sweep, same shape,
// different element count: a thiscall bool member that walks its own int
// array against another instance's, returning false on the first mismatch.
// MSVC keeps this as a real loop (not unrolled) using a single incrementing
// pointer (eax) plus a constant delta (ecx = other - this), which is exactly
// what `for (i) if (m_val[i] != other.m_val[i]) return false;` compiles to
// at /O2 for a small fixed count. IDENTITY IS NOT RECOVERED; class names are
// derived from address.

typedef int Int;

// ---------------------------------------------------------------------------
// 0x002E4D20 -- 3-element form
// ---------------------------------------------------------------------------
class T4Host002E4D20
{
public:
	bool equals( const T4Host002E4D20 &other ) const;
private:
	Int m_val[ 3 ];
};

bool T4Host002E4D20::equals( const T4Host002E4D20 &other ) const
{
	for ( unsigned int i = 0; i < 3; i++ )
	{
		if ( m_val[ i ] != other.m_val[ i ] )
			return false;
	}
	return true;
}

// ---------------------------------------------------------------------------
// 0x002E4D60 -- 10-element form
// ---------------------------------------------------------------------------
class T4Host002E4D60
{
public:
	bool equals( const T4Host002E4D60 &other ) const;
private:
	Int m_val[ 10 ];
};

bool T4Host002E4D60::equals( const T4Host002E4D60 &other ) const
{
	for ( unsigned int i = 0; i < 10; i++ )
	{
		if ( m_val[ i ] != other.m_val[ i ] )
			return false;
	}
	return true;
}
