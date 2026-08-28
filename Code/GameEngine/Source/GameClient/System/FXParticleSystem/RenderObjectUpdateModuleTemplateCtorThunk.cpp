// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: clean-C++ RenderObjectUpdateModuleTemplate default constructor.

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

class RenderObjectUpdateModuleInfo
{
public:
    RenderObjectUpdateModuleInfo();
    virtual ~RenderObjectUpdateModuleInfo();
};

class RenderObjectUpdateModuleTemplate : public CategoryModuleTemplate<1>,
    public RenderObjectUpdateModuleInfo
{
public:
    RenderObjectUpdateModuleTemplate();
};

// ??0RenderObjectUpdateModuleTemplate@FXParticleSystem@@QAE@XZ
RenderObjectUpdateModuleTemplate::RenderObjectUpdateModuleTemplate()
    : CategoryModuleTemplate<1>(), RenderObjectUpdateModuleInfo()
{
}

}
