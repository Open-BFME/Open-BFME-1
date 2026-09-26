// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: DefaultModuleTemplate (N=1) default constructor.
// The retail body constructs the CategoryModuleTemplate<1> base followed by
// its DefaultAlphaModuleInfo subobject.

namespace FXParticleSystem
{

class ModuleTemplate
{
public:
	virtual ~ModuleTemplate();
};

template <int Category>
class CategoryModuleInfo
{
public:
	virtual void unusedVirtual();
};

template <int Category>
class CategoryModuleTemplateBase : public ModuleTemplate, public CategoryModuleInfo<Category>
{
};

template <int Category>
class CategoryModuleTemplate : public CategoryModuleTemplateBase<Category>
{
};

class DefaultAlphaModuleInfo
{
public:
	DefaultAlphaModuleInfo();
	virtual ~DefaultAlphaModuleInfo();
};

template <int Category>
class DefaultModuleTemplate : public CategoryModuleTemplate<Category>, public DefaultAlphaModuleInfo
{
public:
	DefaultModuleTemplate();
};

template <int Category>
DefaultModuleTemplate<Category>::DefaultModuleTemplate()
{
}

template DefaultModuleTemplate<1>::DefaultModuleTemplate();

}
