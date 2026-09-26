// cl: /DNDEBUG /MD /GX- /O2 /Ob2
//
// Retail constructs this module with polymorphic subobjects at +0x00, +0x14,
// +0x18, and +0x1c.  The one-entry vtable at +0x18 (0x01112398) routes its
// getVelocity slot through ILT 0x00041D12 to 0x005FA920.  The declaration-only
// bases below preserve that multiple-inheritance contract without synthesizing
// implementations for any of the other virtual slots.

#include <math.h>

extern const float BfmeZeroRange;
extern float g_bfmeDefaultBU;

struct Coord3DBase
{
	float x;
	float y;
	float z;
};

// Coord3D is a global class in retail.  Its copy constructor at 0x005BC20
// copies the three floats, and its destructor at 0x005BC40 is non-trivial but
// empty.  Keeping both lifetime operations visible here gives the returned
// aggregate its real type while allowing this leaf to inline them.
class Coord3D : public Coord3DBase
{
public:
	Coord3D( const Coord3D &that )
	{
		x = that.x;
		y = that.y;
		z = that.z;
	}

	~Coord3D()
	{
	}

	__forceinline float length() const
	{
		return (float)sqrt( x * x + y * y + z * z );
	}

	__forceinline void normalize()
	{
		float len = length();
		if ( len != BfmeZeroRange )
		{
			float inverse_length = g_bfmeDefaultBU / len;
			x *= inverse_length;
			y *= inverse_length;
			z *= inverse_length;
		}
	}

	__forceinline void scale( float value )
	{
		x *= value;
		y *= value;
		z *= value;
	}
};

namespace FXParticleSystem
{

class __declspec(novtable) ParticleModulePrimary
{
public:
	virtual ~ParticleModulePrimary() = 0;

private:
	unsigned char m_state[ 0x10 ];
};

class __declspec(novtable) ParticleModuleClassInterface
{
public:
	virtual void *getModuleClass() const = 0;
};

class __declspec(novtable) EmissionVolumeModuleInterface
{
public:
	virtual Coord3D getVelocity(
		const Coord3D *position, float speed, float radial_speed ) = 0;
};

template <int Category>
class DefaultParticleModule
	: public ParticleModulePrimary,
	  public ParticleModuleClassInterface,
	  public EmissionVolumeModuleInterface
{
};

class __declspec(novtable) EmissionVolumeInfo
{
public:
	virtual ~EmissionVolumeInfo() = 0;

private:
	bool m_is_hollow;
	unsigned char m_alignment[ 3 ];
};

class SphereEmissionVolumeInfo : public EmissionVolumeInfo
{
private:
	float m_radius;
};

class SphereEmissionVolumeModule
	: public DefaultParticleModule<5>, public SphereEmissionVolumeInfo
{
public:
	virtual Coord3D getVelocity(
		const Coord3D *position, float speed, float radial_speed );
};

typedef char DefaultParticleModuleLayout[
	(sizeof( DefaultParticleModule<5> ) == 0x1c) ? 1 : -1 ];
typedef char SphereEmissionVolumeModuleLayout[
	(sizeof( SphereEmissionVolumeModule ) == 0x28) ? 1 : -1 ];

Coord3D SphereEmissionVolumeModule::getVelocity(
	const Coord3D *position, float speed, float)
{
	Coord3D velocity = *position;
	velocity.normalize();
	velocity.scale( speed );
	return velocity;
}

}
