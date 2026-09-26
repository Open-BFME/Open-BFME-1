// Retail 0x006BCA80 is a 13-byte indexed-address helper reached through the
// generated thunk at ILT 0x00033FD2.  No caller proves a semantic owner, so
// the address-derived class records the field at this+0x4 and the index step.

class Rva006BCA80
{
public:
	Rva006BCA80() : m_unused( 0 ), m_data( 0 )
	{
	}

	unsigned int *element( unsigned int index );

private:
	unsigned int m_unused;
	unsigned int *m_data;
};

unsigned int *Rva006BCA80::element( unsigned int index )
{
	return m_data + index;
}
