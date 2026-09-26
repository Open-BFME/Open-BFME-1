// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: DefaultModuleTemplate (N=6) default constructor.
// The retail body constructs the CategoryModuleTemplate<6> base followed by
// its DefaultDrawModuleInfo subobject.

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

class DefaultDrawModuleInfo
{
public:
	DefaultDrawModuleInfo();
	virtual ~DefaultDrawModuleInfo();
};

template <int Category>
class DefaultModuleTemplate : public CategoryModuleTemplate<Category>, public DefaultDrawModuleInfo
{
public:
	DefaultModuleTemplate();
};

template <int Category>
DefaultModuleTemplate<Category>::DefaultModuleTemplate()
{
}

template DefaultModuleTemplate<6>::DefaultModuleTemplate();

}
