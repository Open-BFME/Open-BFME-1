// Row-less leaf, unclaimed-boundary sweep. Same forty-byte-checksum family
// as Bfme5ThirtyNine.cpp (g_bfmeTableDH lookup, 0x012C7128) but the input is
// not the raw object bytes: it masks this->m_field0 against the other
// instance's field first (~a & b, then & 0x1fffffff), stores the result to
// a stack local, and sums the table lookup over that local's four raw
// bytes. IDENTITY IS NOT RECOVERED; class name is derived from address.

extern unsigned char g_bfmeTableDH[];				// retail 0x012C7128

class T4Host001409F0
{
public:
	int checksum( const T4Host001409F0 *other ) const;
private:
	unsigned int m_field0;					// +0x00
};

// ?checksum@T4Host001409F0@@QBEHPBV1@@Z
int T4Host001409F0::checksum( const T4Host001409F0 *other ) const
{
	unsigned int masked = ( ~m_field0 & other->m_field0 ) & 0x1fffffff;

	int total = 0;

	const unsigned char *first = (const unsigned char *)&masked;
	const unsigned char *last = first + 4;

	while ( first < last )
	{
		total += g_bfmeTableDH[ *first ];
		++first;
	}

	return total;
}

// 0x00142140, 15 bytes: a __cdecl forwarder that calls checksum() on its first
// argument with its second, through ILT 0x00041D49 -> 0x001409F0, and returns
// the result. Its ?dup_ row used to borrow GameMemory.cpp's freeFromW3DMemPool,
// whose call reaches MemoryPool::freeBlock instead. Identity not recovered.
// Retail calls the body out of line, so it must not be inlined here.
#pragma inline_depth(0)
int Rva00142140ChecksumForward( const T4Host001409F0 *host, const T4Host001409F0 *other )
{
	return host->checksum( other );
}
#pragma inline_depth()
