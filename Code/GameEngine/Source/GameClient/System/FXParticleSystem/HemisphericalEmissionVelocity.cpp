// cl: /DNDEBUG /MD /GX- /O2 /Ob2
// Hemispherical emission velocity callback at RVA 0x005F9810.
// The HemisphericalEmissionVelocityModule primary vtable at 0x0111224C
// installs this method in slot 4.  The callback samples the shared unit
// vector helper and scales the result by the embedded random variable.

#include "../../../Common/System/game_client_random_variable.h"

namespace FXParticleSystem
{

struct Coord3D
{
	Coord3D( void ) {}
	Coord3D( const Coord3D &that )
	{
		x = that.x;
		y = that.y;
		z = that.z;
	}

	float x;
	float y;
	float z;
};

extern "C" Coord3D *Rva005FAD00FillUnitVector( Coord3D *out );

class HemisphericalEmissionVelocityModule
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual Coord3D Rva005F9810Velocity( unsigned int, unsigned int );

private:
	char m_base[ 0x1c - 4 ];
	GameClientRandomVariable m_speed;
};

Coord3D HemisphericalEmissionVelocityModule::Rva005F9810Velocity( unsigned int, unsigned int )
{
	float speed = m_speed.getValue();
	Coord3D direction;
	Rva005FAD00FillUnitVector( &direction );

	Coord3D result;
	result.x = direction.x * speed;
	result.y = direction.y * speed;
	result.z = direction.z * speed;
	return result;
}

}
