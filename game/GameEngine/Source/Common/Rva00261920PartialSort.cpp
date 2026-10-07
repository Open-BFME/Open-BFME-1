struct Gen8ByteElement
{
	int m_00;
	int m_04;
};

typedef bool ( *Gen8ByteElementLess )( const Gen8ByteElement &, const Gen8ByteElement & );

// The heap build is the matched STLport __make_heap instantiation at
// 0x00261140 (S4StlSortHelpers.cpp); declared here so the call resolves to it.
struct S4SortElem8;
struct S4Cmp00261140
{
	void *m_state;
};
namespace _STL { template <class _RandomAccessIterator, class _Compare, class _Tp, class _Distance> void __make_heap( _RandomAccessIterator, _RandomAccessIterator, _Compare, _Tp *, _Distance * ); }
void GenAdjust00260D80( Gen8ByteElement *first, int holeIndex, int len,
	Gen8ByteElement value, Gen8ByteElementLess comp );
void gen002616d0( void *first, void *last, void *compare );

void gen00261920( void *firstArgument, void *middleArgument,
	void *lastArgument, int zero, void *compareArgument )
{
	Gen8ByteElement *first = (Gen8ByteElement *)firstArgument;
	Gen8ByteElement *middle = (Gen8ByteElement *)middleArgument;
	Gen8ByteElement *last = (Gen8ByteElement *)lastArgument;
	Gen8ByteElementLess compare = (Gen8ByteElementLess)compareArgument;

	S4Cmp00261140 heapCompare;
	heapCompare.m_state = (void *)compare;
	_STL::__make_heap( (S4SortElem8 *)first, (S4SortElem8 *)middle, heapCompare, (S4SortElem8 *)0, (int *)0 );
	for( Gen8ByteElement *i = middle; i < last; ++i )
	{
		if( compare( *i, *first ) )
		{
			Gen8ByteElement item = *i;
			*i = *first;
			GenAdjust00260D80( first, 0, (int)( middle - first ), item, compare );
		}
	}
	gen002616d0( first, middle, compare );
}
