// cl: /DNDEBUG /MD /GX- /O2 /Ob2

#include <math.h>
#include "../../../Common/System/game_client_random_variable.h"

extern float GetGameClientRandomValueReal( float low, float high,
	char *file, int line );

namespace FXParticleSystem
{

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
struct Coord3D
{
	Coord3D() {}
	Coord3D( float x_, float y_, float z_ ) : x( x_ ), y( y_ ), z( z_ ) {}

	float x;
	float y;
	float z;
};

class CylindricalEmissionVelocityModule
{
public:
	Coord3D getVelocity( int, int );

private:
	char m_base[ 0x1c ];
	GameClientRandomVariable m_radial;
	GameClientRandomVariable m_normal;
};

Coord3D CylindricalEmissionVelocityModule::getVelocity( int, int )
{
	float radial = m_radial.getValue();
	char *source = "F:\\bfme\\Code\\gameengine\\Source\\GameClient\\System\\FXParticleSystem\\fxpsemittercylindervelocitymodule.cpp";
	float angle = GetGameClientRandomValueReal( 0.0f,
		6.28318530717958647692f, source, 59 );
	Coord3D components;
	components.x = (float)cos( angle ) * radial;
	components.y = (float)sin( angle ) * radial;
	return Coord3D( components.x, components.y, m_normal.getValue() );
}

}
