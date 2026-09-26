// ?getVelocity@OrthoEmissionVelocityModule@FXParticleSystem@@QAE?AUCoord3D@2@HH@Z
// cl: /DNDEBUG /MD /GX- /O2 /Ob2
// Lever: retail's frame is 12 bytes (one Coord3D) with x and y spilled into it;
// a float[3] local materializes that frame while its loads are forwarded
// (docs/shape_levers.md, 'frame larger by an unused aggregate local').

#include "../../../Common/System/game_client_random_variable.h"

namespace FXParticleSystem
{

struct Coord3D
{
	Coord3D( float x_, float y_, float z_ ) : x( x_ ), y( y_ ), z( z_ ) {}

	float x;
	float y;
	float z;
};

__forceinline float retainFloatSlot( float *value )
{
	return *value;
}

class OrthoEmissionVelocityModule
{
public:
	Coord3D getVelocity( int, int );

private:
	char m_base[ 0x1c ];
	GameClientRandomVariable m_x;
	GameClientRandomVariable m_y;
	GameClientRandomVariable m_z;
};

Coord3D OrthoEmissionVelocityModule::getVelocity( int, int )
{
	float v[3];
	v[0] = m_x.getValue();
	v[1] = m_y.getValue();
	v[2] = m_z.getValue();
	return Coord3D( v[0], v[1], v[2] );
}

}
