// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift DynamicPortalBehaviour's retail constructor to C++.

#pragma intrinsic(_ReadWriteBarrier)
extern "C" void _ReadWriteBarrier(void);

class Thing;
class ModuleData;

extern "C" const void *bfmeVftBfmeBasePB0[];
extern "C" const void *bfmeVftCreateModuleInterface[];
extern "C" const void *bfmeVftDynamicPortalBehaviourObjectModule[];
extern "C" const void *bfmeVftDynamicPortalBehaviourInterface[];
extern "C" const void *bfmeVftDynamicPortalBehaviourUpgradeMux[];
extern "C" const void *bfmeVftDynamicPortalBehaviourModuleInterface[];
extern "C" const void *bfmeVftDynamicPortalBehaviourBase4[];
extern "C" const void *bfmeVftDynamicPortalBehaviourBase5[];
#pragma comment(linker, "/alternatename:_bfmeVftBfmeBasePB0=??_7?$BfmeBasePB@$0A@@@6B@")
#pragma comment(linker, "/alternatename:_bfmeVftCreateModuleInterface=??_7CreateModuleInterface@@6B@")
#pragma comment(linker, "/alternatename:_bfmeVftDynamicPortalBehaviourObjectModule=??_7DynamicPortalBehaviour@@6BDynamicPortalObjectModule@@@")
#pragma comment(linker, "/alternatename:_bfmeVftDynamicPortalBehaviourInterface=??_7DynamicPortalBehaviour@@6BDynamicPortalBehaviourInterface@@@")
#pragma comment(linker, "/alternatename:_bfmeVftDynamicPortalBehaviourUpgradeMux=??_7DynamicPortalBehaviour@@6BDynamicPortalUpgradeMux@@@")
#pragma comment(linker, "/alternatename:_bfmeVftDynamicPortalBehaviourModuleInterface=??_7DynamicPortalBehaviour@@6BDynamicPortalModuleInterface@@@")
#pragma comment(linker, "/alternatename:_bfmeVftDynamicPortalBehaviourBase4=??_7DynamicPortalBehaviour@@6BDynamicPortalBase4@@@")
#pragma comment(linker, "/alternatename:_bfmeVftDynamicPortalBehaviourBase5=??_7DynamicPortalBehaviour@@6BDynamicPortalBase5@@@")

class QueueProductionExitUpdateBase
{
public:
    void construct(Thing *, const ModuleData *);
};

class DynamicPortalBehaviour
{
public:
    DynamicPortalBehaviour(Thing *, const ModuleData *);

private:
    unsigned char m_tail[0x40];
};

// ??0DynamicPortalBehaviour@@QAE@PAVThing@@PBVModuleData@@@Z
DynamicPortalBehaviour::DynamicPortalBehaviour(Thing *thing, const ModuleData *moduleData)
{
    unsigned char *bytes = reinterpret_cast<unsigned char *>(this);
    reinterpret_cast<QueueProductionExitUpdateBase *>(this)->construct(thing, moduleData);

    volatile unsigned int *words = reinterpret_cast<volatile unsigned int *>(bytes);
    words[0x1c / 4] = reinterpret_cast<unsigned int>(bfmeVftBfmeBasePB0);
    words[0x20 / 4] = reinterpret_cast<unsigned int>(bfmeVftCreateModuleInterface);

    _ReadWriteBarrier();
    unsigned int zero = 0;
    *reinterpret_cast<volatile unsigned char *>(bytes + 0x3c) = static_cast<unsigned char>(zero);
    *reinterpret_cast<volatile unsigned char *>(bytes + 0x3d) = static_cast<unsigned char>(zero);
    words[0x00 / 4] = reinterpret_cast<unsigned int>(bfmeVftDynamicPortalBehaviourObjectModule);
    words[0x0c / 4] = reinterpret_cast<unsigned int>(bfmeVftDynamicPortalBehaviourInterface);
    words[0x10 / 4] = reinterpret_cast<unsigned int>(bfmeVftDynamicPortalBehaviourUpgradeMux);
    words[0x18 / 4] = reinterpret_cast<unsigned int>(bfmeVftDynamicPortalBehaviourModuleInterface);
    words[0x1c / 4] = reinterpret_cast<unsigned int>(bfmeVftDynamicPortalBehaviourBase4);
    words[0x20 / 4] = reinterpret_cast<unsigned int>(bfmeVftDynamicPortalBehaviourBase5);
    words[0x24 / 4] = zero;
    words[0x28 / 4] = zero;
    words[0x2c / 4] = zero;
    words[0x30 / 4] = zero;
    words[0x34 / 4] = zero;
    words[0x38 / 4] = zero;
}
