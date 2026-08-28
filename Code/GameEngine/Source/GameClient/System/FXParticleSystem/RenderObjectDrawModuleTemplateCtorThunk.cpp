// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Open-BFME5: clean-C++ RenderObjectDrawModuleTemplate default constructor.

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

class RenderObjectDrawModuleInfo
{
public:
    RenderObjectDrawModuleInfo();
    virtual ~RenderObjectDrawModuleInfo();

private:
    unsigned char m_body[0x2c];
};

class RenderObjectDrawModuleTemplate : public CategoryModuleTemplate<6>,
    public RenderObjectDrawModuleInfo
{
public:
    RenderObjectDrawModuleTemplate();
};

// ??0RenderObjectDrawModuleTemplate@FXParticleSystem@@QAE@XZ
RenderObjectDrawModuleTemplate::RenderObjectDrawModuleTemplate()
    : CategoryModuleTemplate<6>(), RenderObjectDrawModuleInfo()
{
}

}
