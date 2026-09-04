// ?apply@Rva002AD100@@QAEXXZ
// partial score=0.62 date=2026-09-02
// cl: /DNDEBUG /MD
//
// Retail 0x002AD100: thiscall wrapper that resolve()s the object at this+8
// and then calls the 0x002ACD90 sibling with two +0x38 Coord3D pointers --
// the object's own position twice when resolve returns null, otherwise the
// object's position and the resolved object's position.

struct Coord3D
{
	float x, y, z;
};

struct RvaC4390First
{
	unsigned char m_pad[ 0x38 ];
	Coord3D m_pos;
};

class RvaC4390Second
{
public:
	RvaC4390First *resolve( int allowLookup );
	Coord3D *getPosition()
	{
		return reinterpret_cast<Coord3D *>(reinterpret_cast<unsigned char *>( this ) + 0x38);
	}

	unsigned char m_pad[ 0x38 ];
	Coord3D m_pos;
};

class Rva002AD100
{
public:
	void apply();

private:
	void sibling( Coord3D *a, Coord3D *b );

	void *m_vtable;
	void *m_moduleData;
	RvaC4390Second *m_object;
};

// ?apply@Rva002AD100@@QAEXXZ
void Rva002AD100::apply()
{
	RvaC4390First *resolved = m_object->resolve( 0 );
	if( resolved )
	{
		sibling( &m_object->m_pos, &resolved->m_pos );
		return;
	}
	RvaC4390First *view = reinterpret_cast<RvaC4390First *>( m_object );
	sibling( &m_object->m_pos, &view->m_pos );
}
