// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: DefaultModuleTemplate (N=3) default constructor.
// The retail body constructs the CategoryModuleTemplate<3> base followed by
// its DefaultPhysicsModuleInfo subobject.

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

class DefaultPhysicsModuleInfo
{
public:
	DefaultPhysicsModuleInfo();
	virtual ~DefaultPhysicsModuleInfo();
};

template <int Category>
class DefaultModuleTemplate : public CategoryModuleTemplate<Category>, public DefaultPhysicsModuleInfo
{
public:
	DefaultModuleTemplate();
};

template <int Category>
DefaultModuleTemplate<Category>::DefaultModuleTemplate()
{
}

template DefaultModuleTemplate<3>::DefaultModuleTemplate();

}
