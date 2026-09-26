// cl: /O2
// Retail RVA 0x005DC130. Scalar destructor ILT 0x0003C69B routes to the
// matched LineEmissionVolume specialization destructor at 0x005DC030.
void operator delete[](void *block);

namespace FXParticleSystem
{
extern const char LINE_EMISSION_VOLUME_MODULE_KEY[1];
extern const char LINE_EMISSION_VOLUME_MODULE_NAME[1];

class LineEmissionVolumeModule;
class LineEmissionVolumeModuleTemplate;
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
    unsigned char m_data[0x24];
};

typedef ConcreteModuleTemplate<ModuleTag<5,
    LINE_EMISSION_VOLUME_MODULE_KEY, LINE_EMISSION_VOLUME_MODULE_NAME,
    LineEmissionVolumeModule, LineEmissionVolumeModuleTemplate,
    DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > > LineTemplate;

LineTemplate *MakeLineTemplateArray()
{
    return new LineTemplate[2];
}

void DeleteLineTemplateArray(LineTemplate *array)
{
    delete[] array;
}
}
