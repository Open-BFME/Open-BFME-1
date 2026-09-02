// ?getPoint@Rva0016FFD0PathOwner@@QAEPAURva0016FFD0Coord3D@@H@Z
// partial score=0.97 date=2026-09-02
// cl: /DNDEBUG /MD
// Retail 0x0016FFD0: bounds-checked coordinate lookup through the path pointer
// at +0x30.  The owner identity is not recovered, so the name is derived from
// the verified retail address.

struct Rva0016FFD0Coord3D
{
	float x;
	float y;
	float z;
};

struct Rva0016FFD0Path
{
	char m_unknown[ 0x44 ];
	volatile Rva0016FFD0Coord3D *volatile m_begin;
	volatile Rva0016FFD0Coord3D *m_end;

	__forceinline Rva0016FFD0Coord3D *getPoint( int index )
	{
		if( index >= 0 )
		{
			volatile Rva0016FFD0Coord3D *end = m_end;
			volatile Rva0016FFD0Coord3D *begin = m_begin;
			unsigned int count = (unsigned int) (end - begin);
			if( (unsigned int) index < count )
				return const_cast<Rva0016FFD0Coord3D *>( m_begin + index );
		}

		return 0;
	}
};

class Rva0016FFD0PathOwner
{
private:
	char m_unknown[ 0x30 ];
	Rva0016FFD0Path *m_path;

public:
	Rva0016FFD0Coord3D *getPoint( int index );
};

Rva0016FFD0Coord3D *Rva0016FFD0PathOwner::getPoint( int index )
{
	return m_path->getPoint( index );
}
