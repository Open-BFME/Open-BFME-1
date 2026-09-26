// cl: /DNDEBUG /MD /GX- /O2 /Ob2
// Spherical emission velocity callback at RVA0x005FA670, complete68bytes.
// Constructor5E3A20 primaryvtable111119F4 and factory5E8E20 primary1111221C
// bothslot4->ILT1DB2E->body. Historicalmethodspelling andunusedparameter
// types remainunknown; retain twoopaque32-bitwords andhiddenCoord3Dreturn.
// Embeddedrandomvariable+1C andbothactualcalleeentries independentlyaudited.
// Sole ret0C at+41, CCafter+44; noEH,imports,literalsortables.

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

class SphericalEmissionVelocityModule
{
public:
	virtual void slot00();
    virtual void slot01();
    virtual void slot02();
    virtual void slot03();
    virtual Coord3D Rva005FA670Velocity(unsigned int, unsigned int);

private:
	char m_base[ 0x1c - 4 ];
	GameClientRandomVariable m_speed;
};

Coord3D SphericalEmissionVelocityModule::Rva005FA670Velocity(unsigned int, unsigned int)
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
