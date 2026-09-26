// STLport's unguarded linear insertion over an eight-byte trivially-copyable
// element.  The by-value element is the two-dword stack argument visible at
// retail 0x00260910; the comparator is the fourth incoming dword.

struct Gen8ByteElement00260910
{
	int m_00;
	int m_04;
};

typedef bool ( *Gen8ByteElementLess00260910 )(
	const Gen8ByteElement00260910 &, const Gen8ByteElement00260910 & );

void GenInsert00260910( Gen8ByteElement00260910 *last,
	Gen8ByteElement00260910 value, Gen8ByteElementLess00260910 comp )
{
	Gen8ByteElement00260910 *next = last;
	--next;
	while ( comp( value, *next ) )
	{
		*last = *next;
		last = next;
		--next;
	}
	*last = value;
}
