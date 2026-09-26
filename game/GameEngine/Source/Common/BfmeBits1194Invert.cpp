// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport

#include <bitset>

struct BfmeBits1194
{
	_STL::bitset<181> m_bits;
};

// ?bfmeInvert1194@@YAXPAUBfmeBits1194@@@Z
void bfmeInvert1194(BfmeBits1194 *bits)
{
	bits->m_bits.reset();
	bits->m_bits.flip();
}
