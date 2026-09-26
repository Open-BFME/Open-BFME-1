// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: DefaultModuleTemplate (N=0) default constructor.
// The retail body constructs the CategoryModuleTemplate<0> base followed by
// its DefaultColorModuleInfo subobject.

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

class DefaultColorModuleInfo
{
public:
	DefaultColorModuleInfo();
	virtual ~DefaultColorModuleInfo();
};

template <int Category>
class DefaultModuleTemplate : public CategoryModuleTemplate<Category>, public DefaultColorModuleInfo
{
public:
	DefaultModuleTemplate();
};

template <int Category>
DefaultModuleTemplate<Category>::DefaultModuleTemplate()
{
}

template DefaultModuleTemplate<0>::DefaultModuleTemplate();

}
