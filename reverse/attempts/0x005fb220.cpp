// ?getVelocity@LightningEmissionModule@FXParticleSystem@@UAE?AUCoord3D@2@PBU32@MM@Z
// partial score=0.72 date=2026-09-12
// ?getVelocity@LightningEmissionModule@FXParticleSystem@@UAE?AUCoord3D@2@PBU32@MM@Z
// The retail method reads LightningEmissionInfo at offsets 0x0c through 0x20.

// cl: /DNDEBUG /MD /GX- /O2 /Ob2

#include <math.h>

extern const float BfmeZeroRange;
extern float g_bfmeDefaultBU;

namespace FXParticleSystem
{

struct Coord3D
{
	Coord3D( void )
	{
	}

	Coord3D( float xValue, float yValue, float zValue )
		: x( xValue ), y( yValue ), z( zValue )
	{
	}

	float x;
	float y;
	float z;
};

class LightningEmissionModule
{
public:
	virtual Coord3D getVelocity( const Coord3D *position, float speed,
		float radialSpeed );

	unsigned char m_pad[ 0x08 ];
	Coord3D m_start;
	Coord3D m_end;
};

Coord3D LightningEmissionModule::getVelocity( const Coord3D *, float speed,
	float radialSpeed )
{
	float x = m_end.x - m_start.x;
	float y = m_end.y - m_start.y;
	float z = m_end.z - m_start.z;

	float length = (float)sqrt( x * x + y * y + z * z );
	if ( length != BfmeZeroRange )
	{
		float scale = g_bfmeDefaultBU / length;
		x *= scale;
		y *= scale;
		z *= scale;
	}

	Coord3D side;
	side.x = BfmeZeroRange * z - y;
	side.y = x - BfmeZeroRange * z;
	side.z = BfmeZeroRange * y - BfmeZeroRange * x;
	Coord3D perpendicular;
	perpendicular.x = y * side.z - z * side.y;
	perpendicular.y = z * side.x - x * side.z;
	perpendicular.z = x * side.y - y * side.x;

	return Coord3D( side.x * speed + perpendicular.x * radialSpeed,
		side.y * speed + perpendicular.y * radialSpeed,
		side.z * speed + perpendicular.z * radialSpeed );
}

}
