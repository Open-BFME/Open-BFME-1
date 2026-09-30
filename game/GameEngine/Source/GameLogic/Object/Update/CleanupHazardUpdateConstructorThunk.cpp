// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: clean-C++ reconstruction of the retail CleanupHazardUpdate ctor.
#pragma intrinsic(_ReadWriteBarrier)
extern "C" void _ReadWriteBarrier(void);

extern "C" const void *bfmeVftExitInterface[];
extern "C" const void *bfmeVftRva002D0480NestedDtor_ThirdMixin[];
#pragma comment(linker, "/alternatename:_bfmeVftExitInterface=??_7ExitInterface@@6B@")
#pragma comment(linker, "/alternatename:_bfmeVftRva002D0480NestedDtor_ThirdMixin=??_7Rva002D0480NestedDtor@@6BRva002D0480NestedDtorThirdMixin@@@")
extern const void *g_010CB764[];
extern const void *g_010CB6A0[];
extern const void *g_010CB690[];

class Thing;
class ModuleData;
class Object;

class PB_DeepBase
{
public:
    PB_DeepBase(Thing *, const ModuleData *);
    virtual ~PB_DeepBase();

protected:
    const ModuleData *m_moduleData;
    Object *m_object;
};

class CleanupHazardUpdateBehaviorInterface
{
public:
    virtual void slot();
};

class CleanupHazardUpdateUpdateInterface
{
public:
    virtual void slot();
};

class CleanupHazardUpdateModule
    : public PB_DeepBase,
      public CleanupHazardUpdateBehaviorInterface,
      public CleanupHazardUpdateUpdateInterface
{
public:
    CleanupHazardUpdateModule(Thing *thing, const ModuleData *moduleData)
        : PB_DeepBase(thing, moduleData),
          m_nextCallFrameAndPhase(0),
          m_indexInLogic(-1),
          m_reserved(-1)
    {
    }

protected:
    volatile unsigned int m_nextCallFrameAndPhase;
    volatile int m_indexInLogic;
    volatile int m_reserved;
};

class __declspec(novtable) CleanupHazardUpdateInterface
{
public:
    virtual void slot();
    virtual ~CleanupHazardUpdateInterface();

    CleanupHazardUpdateInterface()
    {
    }
};

class __declspec(novtable) CleanupHazardUpdate : public CleanupHazardUpdateModule, public CleanupHazardUpdateInterface
{
public:
    CleanupHazardUpdate(Thing *, const ModuleData *);

private:
    unsigned int m_f24;
    unsigned int m_f28;
    unsigned int m_f2c;
    unsigned int m_f30;
    unsigned char m_f34;
    unsigned int m_f38;
    const void *m_f3c;
    unsigned int m_f40;
};

// ??0CleanupHazardUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
CleanupHazardUpdate::CleanupHazardUpdate(Thing *thing, const ModuleData *moduleData)
    : CleanupHazardUpdateModule(thing, moduleData)
{
    volatile unsigned int *words = (volatile unsigned int *)this;
    words[8] = (unsigned int)bfmeVftExitInterface;
    words[9] = 0;
    words[14] = 0;
    words[0] = (unsigned int)g_010CB764;
    words[3] = (unsigned int)g_010CB6A0;
    words[4] = (unsigned int)g_010CB690;
    words[8] = (unsigned int)bfmeVftRva002D0480NestedDtor_ThirdMixin;
    words[10] = 0;
    words[11] = 0;
    words[12] = 0;
    const ModuleData *data = *(const ModuleData * volatile *)((const char *)this + 4);
    words[16] = 0;
    *(volatile unsigned char *)((char *)this + 0x34) = 0;
    *(const void * volatile *)&m_f3c = 0;
    _ReadWriteBarrier();
    if (data != 0)
        m_f3c = *(const void **)((const char *)data + 0x28);
}
