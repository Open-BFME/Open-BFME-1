// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX

struct Rva00364980HeapElement
{
	Rva00364980HeapElement( const Rva00364980HeapElement &other );
	~Rva00364980HeapElement();
	Rva00364980HeapElement &operator=(
		const Rva00364980HeapElement &other );

	char m_bytes[ 0xB4 ];
};

void rva00363BE0IterSwap( Rva00364980HeapElement *left,
	Rva00364980HeapElement *right )
{
	Rva00364980HeapElement temporary( *left );
	*left = *right;
	*right = temporary;
}
