// cl: /DNDEBUG /MD /EHsc

// Open-BFME5: LifeEventModuleTemplate default constructor. The retail body
// uses the same CategoryModuleTemplate<8> hierarchy as the independently
// matched TerrainCollisionModuleTemplate constructor.

extern "C" const void *bfmeVftCategoryModuleInfo8[];
#pragma comment(linker, "/alternatename:_bfmeVftCategoryModuleInfo8=??_7?$CategoryModuleInfo@$07@FXParticleSystem@@6B@")
extern "C" char CategoryModuleTemplate8_vtbl0;
extern "C" char CategoryModuleTemplate8_vtbl4;
extern "C" const void *bfmeVftLifeEventModuleTemplate[];
#pragma comment(linker, "/alternatename:_bfmeVftLifeEventModuleTemplate=??_7LifeEventModuleTemplate@FXParticleSystem@@6B@")
extern "C" const void *bfmeVftLifeEventModuleTemplate_LifeEventCategoryBaseA[];
#pragma comment(linker, "/alternatename:_bfmeVftLifeEventModuleTemplate_LifeEventCategoryBaseA=??_7LifeEventModuleTemplate@FXParticleSystem@@6BLifeEventCategoryBaseA@1@@")
extern "C" const void *bfmeVftLifeEventModuleTemplate_LifeEventCategoryBaseB[];
#pragma comment(linker, "/alternatename:_bfmeVftLifeEventModuleTemplate_LifeEventCategoryBaseB=??_7LifeEventModuleTemplate@FXParticleSystem@@6BLifeEventCategoryBaseB@1@@")

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
		*(volatile unsigned int *)this = (unsigned int)bfmeVftCategoryModuleInfo8;
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
	*(unsigned int *)((unsigned char *)this + 0xc) = (unsigned int)bfmeVftLifeEventModuleTemplate;
	*(unsigned int *)((unsigned char *)this + 0) = (unsigned int)bfmeVftLifeEventModuleTemplate_LifeEventCategoryBaseA;
	*(unsigned int *)((unsigned char *)this + 4) = (unsigned int)bfmeVftLifeEventModuleTemplate_LifeEventCategoryBaseB;
}

}
