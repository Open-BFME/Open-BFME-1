// ?d_005efd60@@YAXXZ
// partial score=0.99 date=2026-09-07
class T1A1_005DD290
{
public:
    T1A1_005DD290(void *system, void *module_template);
    virtual void unusedVirtual();
    unsigned int m_storage[4];
};

class DefaultModule0SecondBase111081C
{
public:
    DefaultModule0SecondBase111081C()
    {
        _ReadWriteBarrier();
    }
    virtual void unusedVirtual();
};

class DefaultModule0SecondBase1073760
{
public:
    DefaultModule0SecondBase1073760()
    {
        _ReadWriteBarrier();
    }
    virtual __declspec(nothrow) ~DefaultModule0SecondBase1073760()
    {
    }
};

template <>
class DefaultModule<0>
    : public T1A1_005DD290,
      public DefaultModule0SecondBase111081C,
      public DefaultModule0SecondBase1073760,
      public DefaultColorModuleInfo
{
public:
    DefaultModule(TrackingPtr<ParticleSystem> &system,
        const ConcreteModuleTemplate<DefaultModuleTag<0> > *source);
};

DefaultModule<0>::DefaultModule(
    TrackingPtr<ParticleSystem> &system,
    const ConcreteModuleTemplate<DefaultModuleTag<0> > *source)
    : T1A1_005DD290(&system, const_cast<void *>((const void *)source)),
      DefaultColorModuleInfo()
{
    const DefaultColorModuleInfo *info =
        (const DefaultColorModuleInfo *)((const unsigned char *)source + 8);
    struct ColorKeyBlock {
        unsigned int value0;
        unsigned int value1;
        unsigned int value2;
        unsigned int value3;
    };

    *(ColorKeyBlock *)&m_colorKey[0] = *(const ColorKeyBlock *)&info->m_colorKey[0];
    *(ColorKeyBlock *)&m_colorKey[1] = *(const ColorKeyBlock *)&info->m_colorKey[1];
    *(ColorKeyBlock *)&m_colorKey[2] = *(const ColorKeyBlock *)&info->m_colorKey[2];
    *(ColorKeyBlock *)&m_colorKey[3] = *(const ColorKeyBlock *)&info->m_colorKey[3];
    *(ColorKeyBlock *)&m_colorKey[4] = *(const ColorKeyBlock *)&info->m_colorKey[4];
    *(ColorKeyBlock *)&m_colorKey[5] = *(const ColorKeyBlock *)&info->m_colorKey[5];
    *(ColorKeyBlock *)&m_colorKey[6] = *(const ColorKeyBlock *)&info->m_colorKey[6];
    *(ColorKeyBlock *)&m_colorKey[7] = *(const ColorKeyBlock *)&info->m_colorKey[7];
    m_colorScale.setRange(
        info->m_colorScale.minimum * *(const float *)0x0107c64c,
        info->m_colorScale.maximum * *(const float *)0x0107c64c,
        GameClientRandomVariable::UNIFORM);
}
