// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: DefaultModuleTemplate (N=2) default constructor.
// The retail body constructs the CategoryModuleTemplate<2> base followed by
// its DefaultUpdateModuleInfo subobject.

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

class DefaultUpdateModuleInfo
{
public:
	DefaultUpdateModuleInfo();
	virtual ~DefaultUpdateModuleInfo();
};

template <int Category>
class DefaultModuleTemplate : public CategoryModuleTemplate<Category>, public DefaultUpdateModuleInfo
{
public:
	DefaultModuleTemplate();
};

template <int Category>
DefaultModuleTemplate<Category>::DefaultModuleTemplate()
{
}

template DefaultModuleTemplate<2>::DefaultModuleTemplate();

}
