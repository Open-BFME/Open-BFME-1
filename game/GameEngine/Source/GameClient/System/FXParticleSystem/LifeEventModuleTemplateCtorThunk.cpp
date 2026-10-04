// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: LifeEventModuleTemplate default constructor. The retail body
// uses the same CategoryModuleTemplate<8> hierarchy as the independently
// matched TerrainCollisionModuleTemplate constructor.

// The retail vftables are real data symbols with their own decorated names.
// They are referenced here by those exact names (__identifier is the only way
// to spell a decorated identifier), so no linker alias stand-in is needed.
extern "C" char __identifier("??_7?$CategoryModuleInfo@$07@FXParticleSystem@@6B@")[];
extern "C" char CategoryModuleTemplate8_vtbl0;
extern "C" char CategoryModuleTemplate8_vtbl4;
extern "C" char __identifier("??_7LifeEventModuleTemplate@FXParticleSystem@@6B@")[];
extern "C" char __identifier("??_7LifeEventModuleTemplate@FXParticleSystem@@6BLifeEventCategoryBaseA@1@@")[];
extern "C" char __identifier("??_7LifeEventModuleTemplate@FXParticleSystem@@6BLifeEventCategoryBaseB@1@@")[];

namespace FXParticleSystem
{

class __declspec(novtable) ModuleTemplate
{
public:
	virtual ~ModuleTemplate();
};

template <int N>
class CategoryModuleInfo;

template <>
class __declspec(novtable) CategoryModuleInfo<8>
{
public:
	CategoryModuleInfo()
	{
		*(volatile unsigned int *)this = (unsigned int)__identifier("??_7?$CategoryModuleInfo@$07@FXParticleSystem@@6B@");
		m_a = true;
		m_b = true;
	}

	virtual void unused();

private:
	volatile bool m_a;
	volatile bool m_b;
};

template <int N>
class __declspec(novtable) CategoryModuleTemplateBase
{
public:
	CategoryModuleTemplateBase() {}
	virtual ~CategoryModuleTemplateBase();
};

template <>
class __declspec(novtable) CategoryModuleTemplateBase<8>
	: public ModuleTemplate,
	  public CategoryModuleInfo<8>
{
public:
	CategoryModuleTemplateBase()
		: ModuleTemplate(), CategoryModuleInfo<8>() {}
	virtual ~CategoryModuleTemplateBase();
};

template <int N>
class __declspec(novtable) CategoryModuleTemplate
{
public:
	CategoryModuleTemplate();
	virtual ~CategoryModuleTemplate();
};

template <>
class __declspec(novtable) CategoryModuleTemplate<8>
	: public CategoryModuleTemplateBase<8>
{
public:
	CategoryModuleTemplate()
		: CategoryModuleTemplateBase<8>()
	{
		*(unsigned int *)((unsigned char *)this + 0) = (unsigned int)&CategoryModuleTemplate8_vtbl0;
		*(unsigned int *)((unsigned char *)this + 4) = (unsigned int)&CategoryModuleTemplate8_vtbl4;
	}
	virtual ~CategoryModuleTemplate();
};

class __declspec(novtable) LifeEventModuleInfo
{
public:
	virtual ~LifeEventModuleInfo();
	LifeEventModuleInfo();
};

class LifeEventModuleTemplate
	: public CategoryModuleTemplate<8>,
	  public LifeEventModuleInfo
{
public:
	LifeEventModuleTemplate();
};

// ??0LifeEventModuleTemplate@FXParticleSystem@@QAE@XZ
LifeEventModuleTemplate::LifeEventModuleTemplate()
	: CategoryModuleTemplate<8>(),
	  LifeEventModuleInfo()
{
	*(unsigned int *)((unsigned char *)this + 0xc) = (unsigned int)__identifier("??_7LifeEventModuleTemplate@FXParticleSystem@@6B@");
	*(unsigned int *)((unsigned char *)this + 0) = (unsigned int)__identifier("??_7LifeEventModuleTemplate@FXParticleSystem@@6BLifeEventCategoryBaseA@1@@");
	*(unsigned int *)((unsigned char *)this + 4) = (unsigned int)__identifier("??_7LifeEventModuleTemplate@FXParticleSystem@@6BLifeEventCategoryBaseB@1@@");
}

}
