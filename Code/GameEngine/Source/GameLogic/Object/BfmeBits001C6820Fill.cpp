// cl: /O2 /Ob1 /DNDEBUG /MD
// BFME retail 0x001C6820: clear six words, then set the selected bit.
// stlport

#include <bitset>

struct BfmeBits001C6820
{
	_STL::bitset<192> m_bits;

	BfmeBits001C6820(unsigned int index)
		: m_bits()
	{
		m_bits._Unchecked_set(index);
	}
};

class BfmeBitsOwner001C6820
{
public:
	BfmeBits001C6820 get() const;

private:
	char m_pad[0x20];
	unsigned int m_index;
};

BfmeBits001C6820 BfmeBitsOwner001C6820::get() const
{
	unsigned int index = m_index;
	return BfmeBits001C6820(index);
}
