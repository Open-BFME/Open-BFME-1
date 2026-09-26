// cl: /DNDEBUG /MD /EHsc /O2 /Ob2

namespace FXParticleSystem
{

class LifeEventModuleInfo
{
public:
    LifeEventModuleInfo(const LifeEventModuleInfo &);
    virtual ~LifeEventModuleInfo();
};

class LifeEventCategoryBaseA
{
public:
    virtual ~LifeEventCategoryBaseA();
};

class LifeEventCategoryBaseB
{
public:
    virtual ~LifeEventCategoryBaseB();
};

class LifeEventCategoryBase
    : public LifeEventCategoryBaseA,
      public LifeEventCategoryBaseB
{
public:
    LifeEventCategoryBase(const LifeEventCategoryBase &) {}
    virtual ~LifeEventCategoryBase();
};

class LifeEventCategoryTemplate : public LifeEventCategoryBase
{
public:
    LifeEventCategoryTemplate(const LifeEventCategoryTemplate &that)
        : LifeEventCategoryBase(that)
    {
        const void *source = &that;
        const void *word_source = source ? (const unsigned char *)source + 8 : 0;
        m_word = *(const unsigned short *)word_source;
        *(volatile unsigned int *)this = 0x01073848;
        *(volatile unsigned int *)((unsigned char *)this + 4) = 0x01073844;
    }
    virtual ~LifeEventCategoryTemplate();

private:
    volatile unsigned short m_word;
};

class LifeEventModuleTemplate : public LifeEventCategoryTemplate,
                                       public LifeEventModuleInfo
{
public:
    LifeEventModuleTemplate(const LifeEventModuleTemplate &that);
    virtual ~LifeEventModuleTemplate();
};

// ??0LifeEventModuleTemplate@FXParticleSystem@@QAE@ABV01@@Z
LifeEventModuleTemplate::LifeEventModuleTemplate(const LifeEventModuleTemplate &that)
    : LifeEventCategoryTemplate(that),
      LifeEventModuleInfo(that)
{
}

}
