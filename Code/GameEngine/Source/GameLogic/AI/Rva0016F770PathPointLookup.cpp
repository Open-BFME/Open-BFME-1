// cl: /DNDEBUG /MD
// Retail 0x0016F770: bounds-checked lookup in a contiguous array of
// twelve-byte coordinates.  No surviving caller or string identifies the
// owning class, so the name is deliberately address-derived.

struct Rva0016F770Coord3D
{
	float x;
	float y;
	float z;
};

class Rva0016F770Path
{
private:
	char m_unknown[ 0x44 ];
	Rva0016F770Coord3D *volatile m_begin;
	Rva0016F770Coord3D *m_end;

public:
	Rva0016F770Coord3D *getPoint( int index );
};

Rva0016F770Coord3D *Rva0016F770Path::getPoint( int index )
{
	if( index >= 0 )
	{
		if( (unsigned int) index < (unsigned int) (m_end - m_begin) )
			return m_begin + index;
	}

	return 0;
}
