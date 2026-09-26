// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: LifeEventModuleTemplate default constructor. The retail body
// uses the same CategoryModuleTemplate<8> hierarchy as the independently
// matched TerrainCollisionModuleTemplate constructor.

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
		*(volatile unsigned int *)this = 0x0107375c;
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
		*(unsigned int *)((unsigned char *)this + 0) = 0x01073848;
		*(unsigned int *)((unsigned char *)this + 4) = 0x01073844;
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
	*(unsigned int *)((unsigned char *)this + 0xc) = 0x011112a4;
	*(unsigned int *)((unsigned char *)this + 0) = 0x01111290;
	*(unsigned int *)((unsigned char *)this + 4) = 0x0111128c;
}

}
