// ?setExitPosition@Rva00248F40HordeContain@@QAEXPAVHordeContainPositionSink@@@Z
// partial score=0.82 date=2026-09-02
// cl: /DNDEBUG /MD

// The Horde garrison and transport contain implementations both forward a
// compact position record built from their owning object.  The 0x30-byte gap
// is part of the retail record layout; only its two coordinates and trailing
// pointer are consumed by this helper.

struct HordeContainPosition
{
	float x;
	float y;
	float z;
	unsigned char unused[0x2C];
	float trailing_z;

	HordeContainPosition( float x_value, float y_value, float z_value )
		: x( x_value ), y( y_value ), z( z_value ), trailing_z( z_value ) {}
};

struct HordeContainObject
{
	unsigned char unused_00[0x14];
	float x;
	unsigned char unused_18[0x0C];
	float y;
	unsigned char unused_28[0x0C];
	float z;
};

class HordeContainPositionSink
{
public:
	void setHordeContainPosition( const HordeContainPosition *position );
};

class Rva00248F40HordeContain
{
public:
	void setExitPosition( HordeContainPositionSink *sink );

private:
	unsigned char unused_00[8];
	HordeContainObject *m_object;
};

void Rva00248F40HordeContain::setExitPosition( HordeContainPositionSink *sink )
{
	float x = m_object->x;
	float y = m_object->y;
	float z = m_object->z;
	HordeContainPosition position( x, y, z );
	sink->setHordeContainPosition( &position );
}
