// cl: /DNDEBUG /MD /EHs- /O2 /Ob2
// Open-BFME5: convert the LightningEmission ConcreteModuleTemplate copy
// constructor from the bulk ASM dump to clean C++. The retail body initializes
// the category dual-vtable base, copies the LightningEmissionInfo subobject at
// +8 with null-preserving source adjustment, then installs the final concrete
// vtables. The inline empty base copy keeps the intermediate stores in order.

class LEMCT_VtblBaseA
{
public:
    virtual ~LEMCT_VtblBaseA();
};

class LEMCT_VtblBaseB
{
public:
    virtual ~LEMCT_VtblBaseB();
};

class LEMCT_CategoryBase : public LEMCT_VtblBaseA, public LEMCT_VtblBaseB
{
public:
    LEMCT_CategoryBase(const LEMCT_CategoryBase &) {}
    virtual ~LEMCT_CategoryBase();
};

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
};

extern const char LIGHTNING_EMISSION_MODULE_KEY[1];
extern const char LIGHTNING_EMISSION_MODULE_NAME[1];

template <int Category, const char (&Key)[1], const char (&Name)[1], class Module, class ModuleTemplate, class ParticleModule, class ParticleModuleTemplate>
class ModuleTag
{
};

template <class Tag>
class ConcreteModuleTemplate;

class LightningEmissionInfo
{
public:
    LightningEmissionInfo(const LightningEmissionInfo &);
    virtual ~LightningEmissionInfo();
};

typedef ModuleTag<5, LIGHTNING_EMISSION_MODULE_KEY, LIGHTNING_EMISSION_MODULE_NAME,
    LightningEmissionModule, LightningEmissionModuleTemplate,
    DefaultParticleModule<5>, DefaultParticleModuleTemplate<5> > LightningEmissionTag;

template <>
class ConcreteModuleTemplate<LightningEmissionTag>
    : public LEMCT_CategoryBase, public LightningEmissionInfo
{
public:
    __declspec(nothrow) ConcreteModuleTemplate(const ConcreteModuleTemplate &that);
};

// ??0?$ConcreteModuleTemplate@V?$ModuleTag@$04$E?LIGHTNING_EMISSION_MODULE_KEY@FXParticleSystem@@3QBDB$E?LIGHTNING_EMISSION_MODULE_NAME@2@3QBDBVLightningEmissionModule@2@VLightningEmissionModuleTemplate@2@V?$DefaultParticleModule@$04@2@V?$DefaultParticleModuleTemplate@$04@2@@FXParticleSystem@@@FXParticleSystem@@QAE@ABV01@@Z
ConcreteModuleTemplate<LightningEmissionTag>::ConcreteModuleTemplate(
    const ConcreteModuleTemplate<LightningEmissionTag> &that)
    : LEMCT_CategoryBase(that), LightningEmissionInfo(that)
{
}

}
