// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc

// Open-BFME5: CategoryModuleTemplate<7> default constructor. Category 7 owns
// the WindModuleInfo subobject; DefaultModuleTemplate<7> immediately derives
// from this object and replaces the same three vtables.

namespace FXParticleSystem
{

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
class CategoryModuleTemplateBase
	: public ModuleTemplate,
	  public CategoryModuleInfo<Category>
{
public:
	CategoryModuleTemplateBase() {}
	virtual ~CategoryModuleTemplateBase() {}
};

class WindModuleInfo
{
public:
	WindModuleInfo();
	virtual ~WindModuleInfo();
};

template <int Category>
class CategoryModuleTemplate
	: public CategoryModuleTemplateBase<Category>,
	  public WindModuleInfo
{
public:
	CategoryModuleTemplate();
	virtual ~CategoryModuleTemplate() {}
};

// MSVC mangles CategoryModuleTemplate<7> as @$06.
template <int Category>
CategoryModuleTemplate<Category>::CategoryModuleTemplate()
	: CategoryModuleTemplateBase<Category>(),
	  WindModuleInfo()
{
}

template CategoryModuleTemplate<7>::CategoryModuleTemplate();

}
