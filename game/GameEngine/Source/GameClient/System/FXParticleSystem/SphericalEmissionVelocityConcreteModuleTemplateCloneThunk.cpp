// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: SphericalEmissionVelocity ConcreteModuleTemplate::clone
// Category N mangles as $(N-1) for N>=1 in MSVC 7.1; ledger $03 => N=4.

namespace FXParticleSystem
{
template <int N>
class DefaultParticleModule
{
};

template <int N>
class DefaultParticleModuleTemplate
{
};

class SphericalEmissionVelocityModule
{
};

class SphericalEmissionVelocityModuleTemplate
{
public:
	virtual ~SphericalEmissionVelocityModuleTemplate();
};

extern const char SPHERICAL_EMISSION_VELOCITY_MODULE_KEY[1];
extern const char SPHERICAL_EMISSION_VELOCITY_MODULE_NAME[1];

template <int Category, const char (&Key)[1], const char (&Name)[1], class Module, class ModuleTemplate, class ParticleModule, class ParticleModuleTemplate>
class ModuleTag
{
};

template <class Tag>
class ConcreteModuleTemplate;

typedef ModuleTag<4, SPHERICAL_EMISSION_VELOCITY_MODULE_KEY, SPHERICAL_EMISSION_VELOCITY_MODULE_NAME,
	SphericalEmissionVelocityModule, SphericalEmissionVelocityModuleTemplate,
	DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > SphericalEmissionVelocityTag;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

template <>
class ConcreteModuleTemplate<SphericalEmissionVelocityTag> : public SphericalEmissionVelocityModuleTemplate
{
public:
	ConcreteModuleTemplate(const ConcreteModuleTemplate &);
	virtual SphericalEmissionVelocityModuleTemplate *clone() const;

private:
	unsigned char m_pad[0x14];
};

SphericalEmissionVelocityModuleTemplate *ConcreteModuleTemplate<SphericalEmissionVelocityTag>::clone() const
{
	return new ConcreteModuleTemplate<SphericalEmissionVelocityTag>(*this);
}

}
