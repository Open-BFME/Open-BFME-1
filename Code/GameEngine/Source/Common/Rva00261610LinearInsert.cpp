// cl: /DNDEBUG /MD
//
// STLport linear insertion over the same eight-byte POD used by the
// independently matched unguarded helper at 0x00260910.  The caller at
// 0x002618D0 walks an array and passes each element here by value.

struct Gen8ByteElement00260910
{
	int m_00;
	int m_04;
};

typedef bool ( *Gen8ByteElementLess00260910 )(
	const Gen8ByteElement00260910 &, const Gen8ByteElement00260910 & );

void GenInsert00260910( Gen8ByteElement00260910 *last,
	Gen8ByteElement00260910 value, Gen8ByteElementLess00260910 comp );

struct Rva00261610RandomAccessIteratorTag
{
};

template <class RandomAccessIter, class BidirectionalIter, class Distance>
__forceinline BidirectionalIter Rva00261610CopyBackward(
	RandomAccessIter first, RandomAccessIter last, BidirectionalIter result,
	const Rva00261610RandomAccessIteratorTag &, Distance * )
{
	for ( Distance count = last - first; count > 0; --count )
		*--result = *--last;
	return result;
}

extern "C" void Rva00261610LinearInsert(
	Gen8ByteElement00260910 *first, Gen8ByteElement00260910 *last,
	Gen8ByteElement00260910 value, Gen8ByteElementLess00260910 comp )
{
	if ( comp( value, *first ) )
	{
		Rva00261610RandomAccessIteratorTag tag;
		Rva00261610CopyBackward( first, last, last + 1, tag, (int *)0 );
		*first = value;
	}
	else
	{
		GenInsert00260910( last, value, comp );
	}
}
