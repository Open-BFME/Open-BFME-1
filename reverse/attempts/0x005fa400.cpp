// ?getVelocity@SphericalEmissionVelocityModule@FXParticleSystem@@QAE?AUCoord3D@2@MMM@Z
// partial score=0.9 date=2026-09-02
// cl: /DNDEBUG /MD /GX- /O2 /Ob2

namespace FXParticleSystem
{

struct Coord3D
{
	Coord3D() {}
	Coord3D( float x_, float y_, float z_ ) : x( x_ ), y( y_ ), z( z_ ) {}

	float x;
	float y;
	float z;
};

extern "C" void bfmeRandomUnitVector( Coord3D *out );

class SphericalEmissionVelocityModule
{
public:
	Coord3D getVelocity( float, float scale, float );
};

Coord3D SphericalEmissionVelocityModule::getVelocity( float, float scale, float )
{
	Coord3D direction;
	bfmeRandomUnitVector( &direction );
	return Coord3D( direction.x * scale, direction.y * scale, direction.z * scale );
}

}
