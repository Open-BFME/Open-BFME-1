// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX

struct Rva00364980HeapElement
{
	char m_bytes[ 0xB4 ];
};

struct Rva00364980HeapCompare
{
	void *m_state;
};

void rva00366A20IntrosortLoop( Rva00364980HeapElement *first,
	Rva00364980HeapElement *last, Rva00364980HeapElement *, int depthLimit,
	Rva00364980HeapCompare compare );

void rva00366760FinalInsertionSort( Rva00364980HeapElement *first,
	Rva00364980HeapElement *last, Rva00364980HeapCompare compare );

void rva00366FA0Sort( Rva00364980HeapElement *first,
	Rva00364980HeapElement *last, Rva00364980HeapCompare compare )
{
	if( first == last )
		return;

	int count = last - first;
	int depth = 0;
	while( count != 1 )
	{
		count >>= 1;
		++depth;
	}

	rva00366A20IntrosortLoop( first, last, 0, depth * 2, compare );
	rva00366760FinalInsertionSort( first, last, compare );
}
