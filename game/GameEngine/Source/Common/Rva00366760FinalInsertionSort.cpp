// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX

struct Rva00364980HeapElement
{
	char m_bytes[ 0xB4 ];
};

struct Rva00364980HeapCompare
{
	void *m_state;
};

extern void j_0002aa4f();
extern void j_00034bd5();

void rva00366760FinalInsertionSort( Rva00364980HeapElement *first,
	Rva00364980HeapElement *last, Rva00364980HeapCompare compare )
{
	if( last - first > 16 )
	{
		Rva00364980HeapElement *middle = first + 16;
		reinterpret_cast<void (*)( Rva00364980HeapElement *,
			Rva00364980HeapElement *, Rva00364980HeapCompare )>(
				&j_0002aa4f)( first, middle, compare );
		reinterpret_cast<void (*)( Rva00364980HeapElement *,
			Rva00364980HeapElement *, Rva00364980HeapElement *,
			Rva00364980HeapCompare )>( &j_00034bd5 )(
				middle, last, 0, compare );
	}
	else
	{
		reinterpret_cast<void (*)( Rva00364980HeapElement *,
			Rva00364980HeapElement *, Rva00364980HeapCompare )>(
				&j_0002aa4f)( first, last, compare );
	}
}
