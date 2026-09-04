// ?apply@Rva002AD100@@QAEXXZ
// partial score=0.63 date=2026-09-04
// ?apply@Rva002AD100@@QAEXXZ
// partial score=0.63 date=2026-09-04
// cl: /DNDEBUG /MD

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
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
	Coord3D *getPosition() { return &m_pos; }

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
	if( !resolved )
	{
		Rva002AD100 *self = this;
		self->sibling( m_object->getPosition(), m_object->getPosition() );
		return;
	}
	Rva002AD100 *self = this;
	self->sibling( &m_object->m_pos, &resolved->m_pos );
}
