// ?getVelocity@OrthoEmissionVelocityModule@FXParticleSystem@@QAE?AUCoord3D@2@HH@Z
// partial score=0.94 date=2026-09-02
// cl: /DNDEBUG /MD /GX- /O2 /Ob2

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
	volatile float reserved;
	float x = m_x.getValue();
	float y = m_y.getValue();
	float z = m_z.getValue();
	return Coord3D( x, y, retainFloatSlot( &z ) );
}

}
