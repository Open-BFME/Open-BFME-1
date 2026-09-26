// cl: /DNDEBUG /MD /GX- /O2 /Ob2

// Open-BFME5: LightningDrawModuleTemplate ConcreteModuleTemplate::clone

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

class LightningDrawModule
{
};

class LightningDrawModuleTemplate
{
public:
	virtual ~LightningDrawModuleTemplate();
};

extern const char LIGHTNING_DRAW_MODULE_KEY[1];
extern const char LIGHTNING_DRAW_MODULE_NAME[1];

template <int Category, const char (&Key)[1], const char (&Name)[1], class Module, class ModuleTemplate, class ParticleModule, class ParticleModuleTemplate>
class ModuleTag
{
};

template <class Tag>
class ConcreteModuleTemplate;

typedef ModuleTag<6, LIGHTNING_DRAW_MODULE_KEY, LIGHTNING_DRAW_MODULE_NAME,
	LightningDrawModule, LightningDrawModuleTemplate,
	DefaultParticleModule<6>, DefaultParticleModuleTemplate<6> > LightningDrawTag;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

template <>
class ConcreteModuleTemplate<LightningDrawTag> : public LightningDrawModuleTemplate
{
public:
	ConcreteModuleTemplate(const ConcreteModuleTemplate &);
	virtual LightningDrawModuleTemplate *clone() const;

private:
	unsigned char m_pad[0x34];
};

LightningDrawModuleTemplate *ConcreteModuleTemplate<LightningDrawTag>::clone() const
{
	return new ConcreteModuleTemplate<LightningDrawTag>(*this);
}

}
