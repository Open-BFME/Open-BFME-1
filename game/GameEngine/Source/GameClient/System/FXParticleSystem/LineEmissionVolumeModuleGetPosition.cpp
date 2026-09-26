// cl: /DNDEBUG /MD /GX- /O2 /Ob2
//
// Line emission-volume position callback at retail RVA 0x005F9AB0.
//
// Identity: the LineEmissionVolumeModule constructor at 0x005E3480 installs
// primary vtable 0x011118AC; its slot 6 reaches this body through ILT
// 0x0001B13A, the same slot the Sphere constructor's table 0x0111192C routes
// to SphereEmissionVolumeModule::getPosition (0x005FAA40).  The retail string
// VA 0x01113E80 names fxpsemitterlinevolumemodule.cpp, line 114.  The body
// reads the two endpoint records at +0x24/+0x30 copied in by the constructor,
// returns a hidden global Coord3D and pops four scalar words (ret 0x14).
//
// The statement order is the upstream ParticleSys.cpp LINE emission case:
// copy start/end, form delta, draw one random t, interpolate x/y/z.
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
	void set(float ax, float ay, float az)
	{
		x = ax;
		y = ay;
		z = az;
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

protected:
	bool m_is_hollow;
	unsigned char m_alignment[3];
};

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
	virtual Coord3D getPosition(float, float, float, float);
};

Coord3D LineEmissionVolumeModule::getPosition(float, float, float, float)
{
	Coord3D delta, start, end;

	start = m_start;
	end = m_end;

	delta.x = end.x - start.x;
	delta.y = end.y - start.y;
	delta.z = end.z - start.z;

	float t = GetGameClientRandomValueReal(0.0f, 1.0f,
		"F:\\bfme\\Code\\gameengine\\Source\\GameClient\\System\\FXParticleSystem\\fxpsemitterlinevolumemodule.cpp",
		114);

	Coord3D newPos;
	newPos.x = start.x + t * delta.x;
	newPos.y = start.y + t * delta.y;
	newPos.z = start.z + t * delta.z;
	return newPos;
}

}
