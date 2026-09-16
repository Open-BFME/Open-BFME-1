// cl: /DNDEBUG /MD /GX- /O2 /Ob2
//
// Identity/ABI evidence: the LightningEmissionModule constructor at RVA
// 0x005FBBE0 installs vtable 0x011132E8 at the emission interface secondary
// subobject (enclosing object +0x18); its allocation constructor at 0x005E6F30
// installs 0x01112418 there.  Slot 0 of the former reaches this body through
// ILT 0x0003B462.  The endpoint records therefore begin at enclosing-object
// +0x24/+0x30, seen by this body as this+0x0c..+0x20.  The hidden Coord3D
// return, ignored position pointer, and two float arguments give ret 0x10.
//
// Coord3D is the global non-trivial class: retail exposes its copy constructor
// at 0x005BC20 and empty destructor at 0x005BC40.  This TU keeps that ABI and
// uses the native static crossProduct operation; the legacy member helper has
// a different volatile operand shape.  Coord3D has conflicting layouts in
// other TUs, so this is intentionally a TU-local declaration rather than a
// broad header edit.

#include <math.h>

extern const float BfmeZeroRange;
extern float g_bfmeDefaultBU;

struct Coord3DBase
{
	float x;
	float y;
	float z;
};

class Coord3D : public Coord3DBase
{
public:
	Coord3D() {}
	Coord3D(float xValue, float yValue, float zValue)
	{
		x = xValue;
		y = yValue;
		z = zValue;
	}
	Coord3D(const Coord3D &that)
	{
		x = that.x;
		y = that.y;
		z = that.z;
	}
	~Coord3D() {}

	__forceinline float length() const
	{
		return (float)sqrt(x * x + y * y + z * z);
	}

	__forceinline void normalize()
	{
		float len = length();
		if (len != BfmeZeroRange)
		{
			float scale = g_bfmeDefaultBU / len;
			x *= scale;
			y *= scale;
			z *= scale;
		}
	}

	static __forceinline void crossProduct(const Coord3D *left,
		const Coord3D *right, Coord3D *result)
	{
		result->x = left->y * right->z - left->z * right->y;
		result->y = left->z * right->x - left->x * right->z;
		result->z = left->x * right->y - left->y * right->x;
	}
};

namespace FXParticleSystem
{

class __declspec(novtable) ParticleModulePrimary
{
public:
	virtual ~ParticleModulePrimary() = 0;

private:
	unsigned char m_state[0x10];
};

class __declspec(novtable) ParticleModuleClassInterface
{
public:
	virtual void *getModuleClass() const = 0;
};

class __declspec(novtable) EmissionVolumeModuleInterface
{
public:
	virtual Coord3D getVelocity(const Coord3D *, float, float) = 0;
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
	unsigned char m_alignment[3];
};

class LightningEmissionInfo : public EmissionVolumeInfo
{
protected:
	Coord3D m_start;
	Coord3D m_end;
};

class LightningEmissionModule
	: public DefaultParticleModule<5>, public LightningEmissionInfo
{
public:
	virtual Coord3D getVelocity(const Coord3D *, float speed, float radialSpeed);
};

typedef char DefaultParticleModuleLayout[
	(sizeof(DefaultParticleModule<5>) == 0x1c) ? 1 : -1];
// This assertion covers only the LightningEmissionInfo prefix.  The retail
// Lightning record has a constructor-copied tail beyond it; no full-class
// sizeof claim is made here.
typedef char LightningEmissionInfoPrefixLayout[
	(sizeof(LightningEmissionInfo) == 0x20) ? 1 : -1];

Coord3D LightningEmissionModule::getVelocity(const Coord3D *, float speed,
	float radialSpeed)
{
	Coord3D along;
	along.x = m_end.x - m_start.x;
	along.y = m_end.y - m_start.y;
	along.z = m_end.z - m_start.z;
	along.normalize();

	Coord3D perp;
	Coord3D up;
	up.x = 0.0;
	up.y = 0.0;
	up.z = 1.0;
	perp.crossProduct(&up, &along, &perp);
	up.crossProduct(&along, &perp, &up);

	Coord3D result;
	result.x = perp.x * speed + up.x * radialSpeed;
	result.y = perp.y * speed + up.y * radialSpeed;
	result.z = perp.z * speed + up.z * radialSpeed;
	return result;
}

// Independent Line identity evidence: retail LineEmissionVolumeModule's
// constructor at 0x005E3480 installs vtable 0x011118A4 at its +0x18 emission
// subobject and 0x01111890 at +0x1c, then copies the two Coord3D endpoint
// records into enclosing-object +0x24..+0x38.  Slot 0 of 0x011118A4 is ILT
// 0x0003266E, whose five-byte jump targets 0x005F98F0.  The named
// LineEmissionVolumeModule createModule path independently allocates its
// 0x3c-byte record before invoking that constructor.  This proves the owner
// and secondary-this adjustment independently of the byte-identical body.
class LineEmissionVolumeInfo : public EmissionVolumeInfo
{
protected:
	Coord3D m_start;
	Coord3D m_end;
};

class LineEmissionVolumeModule
	: public DefaultParticleModule<5>, public LineEmissionVolumeInfo
{
public:
	virtual Coord3D getVelocity(const Coord3D *, float speed, float radialSpeed);
};

typedef char LineEmissionVolumeInfoPrefixLayout[
	(sizeof(LineEmissionVolumeInfo) == 0x20) ? 1 : -1];

Coord3D LineEmissionVolumeModule::getVelocity(const Coord3D *, float speed,
	float radialSpeed)
{
	Coord3D along;
	along.x = m_end.x - m_start.x;
	along.y = m_end.y - m_start.y;
	along.z = m_end.z - m_start.z;
	along.normalize();

	Coord3D perp;
	Coord3D up;
	up.x = 0.0;
	up.y = 0.0;
	up.z = 1.0;
	perp.crossProduct(&up, &along, &perp);
	up.crossProduct(&along, &perp, &up);

	Coord3D result;
	result.x = perp.x * speed + up.x * radialSpeed;
	result.y = perp.y * speed + up.y * radialSpeed;
	result.z = perp.z * speed + up.z * radialSpeed;
	return result;
}

}
