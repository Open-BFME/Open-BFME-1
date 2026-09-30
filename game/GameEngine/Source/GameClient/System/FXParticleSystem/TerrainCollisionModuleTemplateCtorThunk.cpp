// cl: /DNDEBUG /MD /EHsc

extern "C" const void *bfmeVftCategoryModuleInfo8[];
#pragma comment(linker, "/alternatename:_bfmeVftCategoryModuleInfo8=??_7?$CategoryModuleInfo@$07@FXParticleSystem@@6B@")
extern "C" char CategoryModuleTemplate8_vtbl0;
extern "C" char CategoryModuleTemplate8_vtbl4;
extern "C" const void *bfmeVftTerrainCollisionModuleTemplate[];
#pragma comment(linker, "/alternatename:_bfmeVftTerrainCollisionModuleTemplate=??_7TerrainCollisionModuleTemplate@FXParticleSystem@@6B@")
extern "C" const void *bfmeVftTerrainCollisionModuleTemplate_TerrainCollisionCategoryBaseA[];
#pragma comment(linker, "/alternatename:_bfmeVftTerrainCollisionModuleTemplate_TerrainCollisionCategoryBaseA=??_7TerrainCollisionModuleTemplate@FXParticleSystem@@6BTerrainCollisionCategoryBaseA@1@@")
extern "C" const void *bfmeVftTerrainCollisionModuleTemplate_TerrainCollisionCategoryBaseB[];
#pragma comment(linker, "/alternatename:_bfmeVftTerrainCollisionModuleTemplate_TerrainCollisionCategoryBaseB=??_7TerrainCollisionModuleTemplate@FXParticleSystem@@6BTerrainCollisionCategoryBaseB@1@@")

namespace FXParticleSystem
{

// Retail layout: CategoryModuleTemplate<8> has a ModuleTemplate primary base,
// a CategoryModuleInfo<8> secondary base at +4, and two flag bytes at +8/+9.
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

class __declspec(novtable) TerrainCollisionModuleInfo
{
public:
    virtual ~TerrainCollisionModuleInfo();
    TerrainCollisionModuleInfo();
};

class TerrainCollisionModuleTemplate
    : public CategoryModuleTemplate<8>,
      public TerrainCollisionModuleInfo
{
public:
    TerrainCollisionModuleTemplate();
};

// ??0TerrainCollisionModuleTemplate@FXParticleSystem@@QAE@XZ
TerrainCollisionModuleTemplate::TerrainCollisionModuleTemplate()
    : CategoryModuleTemplate<8>(),
      TerrainCollisionModuleInfo()
{
    *(unsigned int *)((unsigned char *)this + 0xc) = (unsigned int)bfmeVftTerrainCollisionModuleTemplate;
    *(unsigned int *)((unsigned char *)this + 0) = (unsigned int)bfmeVftTerrainCollisionModuleTemplate_TerrainCollisionCategoryBaseA;
    *(unsigned int *)((unsigned char *)this + 4) = (unsigned int)bfmeVftTerrainCollisionModuleTemplate_TerrainCollisionCategoryBaseB;
}

}
