// cl: /DNDEBUG /DWIN32 /MD /EHsc /O2 /Ob2
//
// Three short bodies whose tails were claimed as aliases of unrelated
// functions with the same bytes; retail was linked without COMDAT folding,
// so each is one function from its entry to its return.
//
// 0x001B2D80 (11 bytes) is the callee 0x001BE3D0 reaches through ILT
// 0x00046AA6, already pinned as Gen00046AA6::handle: it hands back the word
// at +0x38 and clears it.  0x001DC890 (14 bytes; ILT 0x0003A9E0 sits in an
// .rdata pointer table at 0x0109714C) is one bit shifted by the index at +0x24
// of the object at +8.  0x005F68F0 (14 bytes, cdecl; nothing references its
// ILT 0x0001F18B) tests the pointed-to word for zero.

class Gen00046AA6
{
public:
	int handle( void );
private:
	char m_unmodelled00[ 0x38 ];
	int m_value38;
};

int Gen00046AA6::handle( void )
{
	int value = m_value38;
	m_value38 = 0;
	return value;
}

struct Rva001DC890Inner
{
	char m_unmodelled00[ 0x24 ];
	int m_index24;
	int getMask( void ) const { return 1 << m_index24; }
};

class Rva001DC890Owner
{
public:
	int getMask( void ) const;
private:
	char m_unmodelled00[ 8 ];
	Rva001DC890Inner *m_inner08;
};

int Rva001DC890Owner::getMask( void ) const
{
	return m_inner08->getMask();
}

int Rva005F68F0IsZero( const int *value )
{
	return *value == 0;
}
