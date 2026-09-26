// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

typedef unsigned int UnsignedInt;

// Identity has not been recovered.  The complete retail body only exposes
// two adjacent dwords at offsets 0x58 and 0x5c and copies them to its two
// output arguments.
class Rva007AE3E0Pair
{
public:
	void getValues( UnsignedInt *first, UnsignedInt *second ) const;

private:
	unsigned char m_pad0[0x58];
	UnsignedInt m_first;
	UnsignedInt m_second;
};

void Rva007AE3E0Pair::getValues( UnsignedInt *first, UnsignedInt *second ) const
{
	*first = m_first;
	*second = m_second;
}
