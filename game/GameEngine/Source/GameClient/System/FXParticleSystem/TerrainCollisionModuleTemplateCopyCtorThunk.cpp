// cl: /DNDEBUG /MD /EHsc /O2 /Ob2

namespace FXParticleSystem
{

class TerrainCollisionModuleInfo
{
public:
    TerrainCollisionModuleInfo(const TerrainCollisionModuleInfo &);
    virtual ~TerrainCollisionModuleInfo();
};

class TerrainCollisionCategoryBaseA
{
public:
    virtual ~TerrainCollisionCategoryBaseA();
};

class TerrainCollisionCategoryBaseB
{
public:
    virtual ~TerrainCollisionCategoryBaseB();
};

class TerrainCollisionCategoryBase
    : public TerrainCollisionCategoryBaseA,
      public TerrainCollisionCategoryBaseB
{
public:
    TerrainCollisionCategoryBase(const TerrainCollisionCategoryBase &) {}
    virtual ~TerrainCollisionCategoryBase();
};

class TerrainCollisionCategoryTemplate : public TerrainCollisionCategoryBase
{
public:
    TerrainCollisionCategoryTemplate(const TerrainCollisionCategoryTemplate &that)
        : TerrainCollisionCategoryBase(that)
    {
        const void *source = &that;
        const void *word_source = source ? (const unsigned char *)source + 8 : 0;
        m_word = *(const unsigned short *)word_source;
        *(volatile unsigned int *)this = 0x01073848;
        *(volatile unsigned int *)((unsigned char *)this + 4) = 0x01073844;
    }
    virtual ~TerrainCollisionCategoryTemplate();

private:
    volatile unsigned short m_word;
};

class TerrainCollisionModuleTemplate : public TerrainCollisionCategoryTemplate,
                                       public TerrainCollisionModuleInfo
{
public:
    TerrainCollisionModuleTemplate(const TerrainCollisionModuleTemplate &that);
    virtual ~TerrainCollisionModuleTemplate();
};

// ??0TerrainCollisionModuleTemplate@FXParticleSystem@@QAE@ABV01@@Z
TerrainCollisionModuleTemplate::TerrainCollisionModuleTemplate(const TerrainCollisionModuleTemplate &that)
    : TerrainCollisionCategoryTemplate(that),
      TerrainCollisionModuleInfo(that)
{
}

}
