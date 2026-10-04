// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: CategoryModuleTemplateBase<3> empty dual-vtbl dtor.
// The two vftable stores are the compiler's own: ~CategoryModuleTemplateBase
// inlines both base destructors (ModuleTemplate at +0, CategoryModuleInfo<3>
// at +4), so the object references ??_7ModuleTemplate@FXParticleSystem@@6B@
// and ??_7?$CategoryModuleInfo@$02@FXParticleSystem@@6B@ directly.

namespace FXParticleSystem
{

class ModuleTemplate
{
public:
	virtual ~ModuleTemplate() {}
};

template <int Category>
class CategoryModuleInfo;

template <>
class CategoryModuleInfo<3>
{
public:
	virtual ~CategoryModuleInfo() {}
};

template <int Category>
class CategoryModuleTemplateBase;

template <>
class __declspec(novtable) CategoryModuleTemplateBase<3>
	: public ModuleTemplate,
	  public CategoryModuleInfo<3>
{
public:
	virtual ~CategoryModuleTemplateBase();
};

// ??1?$CategoryModuleTemplateBase@$02@FXParticleSystem@@UAE@XZ
CategoryModuleTemplateBase<3>::~CategoryModuleTemplateBase()
{
}

}