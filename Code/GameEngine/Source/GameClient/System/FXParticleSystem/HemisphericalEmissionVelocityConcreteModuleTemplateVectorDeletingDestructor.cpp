// cl: /O2
// Retail RVA 0x005DBAB0. Scalar destructor ILT 0x000408EA routes to the
// matched HemisphericalEmissionVelocity specialization destructor at 0x005DB9D0.
void operator delete[](void *block);

namespace FXParticleSystem
{
extern const char HEMISPHERICAL_EMISSION_VELOCITY_MODULE_KEY[1];
extern const char HEMISPHERICAL_EMISSION_VELOCITY_MODULE_NAME[1];

class HemisphericalEmissionVelocityModule;
class HemisphericalEmissionVelocityModuleTemplate;
template<int Category> class DefaultParticleModule;
template<int Category> class DefaultParticleModuleTemplate;
template<int Category, const char (&Key)[1], const char (&Name)[1], class Module,
    class ModuleTemplate, class DefaultModule, class DefaultModuleTemplate>
class ModuleTag;

template<class Tag> class ConcreteModuleTemplate
{
public:
    virtual ~ConcreteModuleTemplate();
private:
    unsigned char m_data[0x14];
};

typedef ConcreteModuleTemplate<ModuleTag<4,
    HEMISPHERICAL_EMISSION_VELOCITY_MODULE_KEY,
    HEMISPHERICAL_EMISSION_VELOCITY_MODULE_NAME,
    HemisphericalEmissionVelocityModule,
    HemisphericalEmissionVelocityModuleTemplate,
    DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > > HemisphericalTemplate;

HemisphericalTemplate *MakeHemisphericalTemplateArray()
{
    return new HemisphericalTemplate[2];
}

void DeleteHemisphericalTemplateArray(HemisphericalTemplate *array)
{
    delete[] array;
}
}
