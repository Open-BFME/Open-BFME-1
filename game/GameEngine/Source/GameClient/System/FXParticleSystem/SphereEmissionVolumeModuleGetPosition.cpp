// Sphere emission-volume position callback at retail RVA 0x005FAA40.
//
// Identity is established by the primary vtable 0x0111192C slot 6, reached
// through ILT 0x0002F7A7, and by the named SphereEmissionVolumeModule
// constructor at 0x005E36C0, which installs that table on the complete object.
// The complete primary receiver stores hollow at +0x20 and radius at +0x24;
// the modeled module size is 0x28, matching the retail createModule allocation.
// The body has a hidden global Coord3D return and four scalar words, with
// callee-popped ret 0x14.  The global Coord3D copy constructor and empty
// non-trivial destructor are kept visible in this TU because the shared
// headers carry three conflicting Coord3D layouts.
//
// The default construction followed by implicit memberwise assignment is
// intentional.  It produces retail's three integer field loads/stores before
// the x87 multiplies; copy-initialization of the same native type produced a
// 109-byte near miss.

extern float GetGameClientRandomValueReal(float low, float high,
	char *file, int line);

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
	Coord3D(const Coord3D &that)
	{
		x = that.x;
		y = that.y;
		z = that.z;
	}
	~Coord3D() {}
};

// Matched cdecl helper at RVA 0x005FAD00.  It fills its Coord3D output and
// returns that address in EAX; no new pin or helper body is introduced here.
extern "C" Coord3D *Rva005FAD00FillUnitVector(Coord3D *out);

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

protected:
	bool m_is_hollow;
	unsigned char m_alignment[3];
};

class SphereEmissionVolumeInfo : public EmissionVolumeInfo
{
protected:
	float m_radius;
};

class SphereEmissionVolumeModule
	: public DefaultParticleModule<5>, public SphereEmissionVolumeInfo
{
public:
	virtual Coord3D getPosition(float, float, float, float);
};

typedef char DefaultParticleModuleLayout[
	(sizeof(DefaultParticleModule<5>) == 0x1c) ? 1 : -1];
typedef char SphereEmissionVolumeModuleLayout[
	(sizeof(SphereEmissionVolumeModule) == 0x28) ? 1 : -1];

Coord3D SphereEmissionVolumeModule::getPosition(float, float, float, float)
{
	char *source =
		"F:\\bfme\\Code\\gameengine\\Source\\GameClient\\System\\FXParticleSystem\\fxpsemitterspherevolumemodule.cpp";
	float radius = m_is_hollow ? m_radius :
		GetGameClientRandomValueReal(0.0f, m_radius, source, 86);
	Coord3D randomPoint;
	Coord3D result;
	result = *Rva005FAD00FillUnitVector(&randomPoint);
	result.x *= radius;
	result.y *= radius;
	result.z *= radius;
	return result;
}

}
