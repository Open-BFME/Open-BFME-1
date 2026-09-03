// cl: /DNDEBUG /DWIN32 /MD /EHs-c- /D_STLP_USE_STATIC_LIB
// stlport

// Retail at 0x000D2FB0.  Same shape as the landed BitFlags<192> one-index
// constructor at 0x001C5450, but the default bitset constructor zeroes three
// dwords (65..96 bits of storage) rather than six.  Two stack arguments and
// `ret 8`: unused first argument, then the bit index.  The owning type and
// exact NUMBITS are not recovered, so the name is address-derived.

#include <bitset>

typedef int Int;

class Rva000D2FB0BitSet
{
public:
	enum UnusedType
	{
		kInit = 0
	};

	Rva000D2FB0BitSet( UnusedType, Int idx1 );

private:
	_STL::bitset<96> m_bits;
};

Rva000D2FB0BitSet::Rva000D2FB0BitSet( UnusedType, Int idx1 )
{
	m_bits._Unchecked_set( static_cast<size_t>( idx1 ) );
}
