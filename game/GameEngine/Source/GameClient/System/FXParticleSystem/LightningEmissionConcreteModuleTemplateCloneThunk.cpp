// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: LightningEmissionModuleTemplate ConcreteModuleTemplate::clone

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

class LightningEmissionModule
{
};

class LightningEmissionModuleTemplate
{
public:
	virtual ~LightningEmissionModuleTemplate();
};

extern const char LIGHTNING_EMISSION_MODULE_KEY[1];
extern const char LIGHTNING_EMISSION_MODULE_NAME[1];

template <int Category, const char (&Key)[1], const char (&Name)[1], class Module, class ModuleTemplate, class ParticleModule, class ParticleModuleTemplate>
class ModuleTag
{
};

template <class Tag>
class ConcreteModuleTemplate;

typedef ModuleTag<5, LIGHTNING_EMISSION_MODULE_KEY, LIGHTNING_EMISSION_MODULE_NAME,
	LightningEmissionModule, LightningEmissionModuleTemplate,
	DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > LightningEmissionTag;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

template <>
class ConcreteModuleTemplate<LightningEmissionTag> : public LightningEmissionModuleTemplate
{
public:
	ConcreteModuleTemplate(const ConcreteModuleTemplate &);
	virtual LightningEmissionModuleTemplate *clone() const;

private:
	unsigned char m_pad[0x90];
};

LightningEmissionModuleTemplate *ConcreteModuleTemplate<LightningEmissionTag>::clone() const
{
	return new ConcreteModuleTemplate<LightningEmissionTag>(*this);
}

}
