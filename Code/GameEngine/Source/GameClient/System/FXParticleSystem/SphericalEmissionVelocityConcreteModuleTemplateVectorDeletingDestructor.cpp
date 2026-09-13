// cl: /O2
// Retail RVA 0x005DB930. Scalar destructor ILT 0x0003B8DB routes to the
// matched SphericalEmissionVelocity ConcreteModuleTemplate destructor at 0x005DB850.
void operator delete[](void *block);

namespace FXParticleSystem
{
extern const char SPHERICAL_EMISSION_VELOCITY_MODULE_KEY[1];
extern const char SPHERICAL_EMISSION_VELOCITY_MODULE_NAME[1];

class SphericalEmissionVelocityModule;
class SphericalEmissionVelocityModuleTemplate;
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
    SPHERICAL_EMISSION_VELOCITY_MODULE_KEY,
    SPHERICAL_EMISSION_VELOCITY_MODULE_NAME,
    SphericalEmissionVelocityModule, SphericalEmissionVelocityModuleTemplate,
    DefaultParticleModule<4>, DefaultParticleModuleTemplate<4> > > SphericalTemplate;

SphericalTemplate *MakeSphericalTemplateArray()
{
    return new SphericalTemplate[2];
}

void DeleteSphericalTemplateArray(SphericalTemplate *array)
{
    delete[] array;
}
}
