// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: SphereEmissionVolumeModuleTemplate ConcreteModuleTemplate::clone
// MSVC 7.1: integral N mangles as $(N-1) for N>=1 ($03 => N=4).

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

class SphereEmissionVolumeModule
{
};

class SphereEmissionVolumeModuleTemplate
{
public:
	virtual ~SphereEmissionVolumeModuleTemplate();
};

extern const char SPHERE_EMISSION_VOLUME_MODULE_KEY[1];
extern const char SPHERE_EMISSION_VOLUME_MODULE_NAME[1];

template <int Category, const char (&Key)[1], const char (&Name)[1], class Module, class ModuleTemplate, class ParticleModule, class ParticleModuleTemplate>
class ModuleTag
{
};

template <class Tag>
class ConcreteModuleTemplate;

typedef ModuleTag<5, SPHERE_EMISSION_VOLUME_MODULE_KEY, SPHERE_EMISSION_VOLUME_MODULE_NAME,
	SphereEmissionVolumeModule, SphereEmissionVolumeModuleTemplate,
	DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > SphereEmissionVolumeTag;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

template <>
class ConcreteModuleTemplate<SphereEmissionVolumeTag> : public SphereEmissionVolumeModuleTemplate
{
public:
	ConcreteModuleTemplate(const ConcreteModuleTemplate &);
	virtual SphereEmissionVolumeModuleTemplate *clone() const;

private:
	unsigned char m_pad[0x10];
};

SphereEmissionVolumeModuleTemplate *ConcreteModuleTemplate<SphereEmissionVolumeTag>::clone() const
{
	return new ConcreteModuleTemplate<SphereEmissionVolumeTag>(*this);
}

}
