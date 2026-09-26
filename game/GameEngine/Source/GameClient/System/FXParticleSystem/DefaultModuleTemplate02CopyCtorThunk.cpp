// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: DefaultModuleTemplate (N=3) copy constructor.

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

struct GameClientRandomVariable
{
	unsigned int m_type;
	float m_low;
	float m_high;
};

class DefaultPhysicsModuleInfo
{
public:
	DefaultPhysicsModuleInfo(const DefaultPhysicsModuleInfo &that)
		: m_field0(that.m_field0), m_field1(that.m_field1), m_field2(that.m_field2),
		  m_field3(that.m_field3), m_var1(that.m_var1)
	{
	}
	virtual ~DefaultPhysicsModuleInfo();

private:
	float m_field0;
	float m_field1;
	float m_field2;
	int m_field3;
	GameClientRandomVariable m_var1;
};

template <int Category>
class DefaultModuleTemplate : public CategoryModuleTemplate<Category>, public DefaultPhysicsModuleInfo
{
public:
	DefaultModuleTemplate(const DefaultModuleTemplate &that);
};

template <int Category>
DefaultModuleTemplate<Category>::DefaultModuleTemplate(const DefaultModuleTemplate &that)
	: CategoryModuleTemplate<Category>(that), DefaultPhysicsModuleInfo(that)
{
}

template DefaultModuleTemplate<3>::DefaultModuleTemplate(const DefaultModuleTemplate &);

}
