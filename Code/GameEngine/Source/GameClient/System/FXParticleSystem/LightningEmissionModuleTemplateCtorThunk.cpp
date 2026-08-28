// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Open-BFME5: clean-C++ LightningEmissionModuleTemplate default constructor.

namespace FXParticleSystem
{

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/ModuleFactory.h
class ModuleTemplate
{
public:
    ModuleTemplate() {}
    virtual ~ModuleTemplate() {}
};

template <int Category>
class CategoryModuleInfo
{
public:
    CategoryModuleInfo() {}
    virtual void unusedVirtual();

protected:
    ~CategoryModuleInfo() {}
};

template <int Category>
class CategoryModuleTemplateBase : public ModuleTemplate,
    public CategoryModuleInfo<Category>
{
public:
    CategoryModuleTemplateBase() {}
    virtual ~CategoryModuleTemplateBase() {}
};

template <int Category>
class CategoryModuleTemplate : public CategoryModuleTemplateBase<Category>
{
public:
    CategoryModuleTemplate() {}
    virtual ~CategoryModuleTemplate() {}
};

class LightningEmissionInfo
{
public:
    LightningEmissionInfo();
    virtual ~LightningEmissionInfo();

private:
    unsigned char m_body[0x7c];
};

class LightningEmissionModuleTemplate : public CategoryModuleTemplate<5>,
    public LightningEmissionInfo
{
public:
    LightningEmissionModuleTemplate();
};

// ??0LightningEmissionModuleTemplate@FXParticleSystem@@QAE@XZ
LightningEmissionModuleTemplate::LightningEmissionModuleTemplate()
    : CategoryModuleTemplate<5>(), LightningEmissionInfo()
{
}

}
