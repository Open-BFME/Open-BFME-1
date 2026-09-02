// cl: /DNDEBUG /MD /EHsc

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
    *(unsigned int *)((unsigned char *)this + 0xc) = 0x01111324;
    *(unsigned int *)((unsigned char *)this + 0) = 0x01111310;
    *(unsigned int *)((unsigned char *)this + 4) = 0x0111130c;
}

}
