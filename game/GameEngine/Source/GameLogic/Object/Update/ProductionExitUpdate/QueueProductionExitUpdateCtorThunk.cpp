// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift QueueProductionExitUpdate's retail constructor to C++.

#pragma intrinsic(_ReadWriteBarrier)
extern "C" void _ReadWriteBarrier(void);

class Thing;
class ModuleData;

extern "C" const void *bfmeVftBfmeBasePB0[];
extern "C" const void *bfmeVftCreateModuleInterface[];
extern "C" const void *bfmeVftQueueProductionExitUpdateObjectModule[];
extern "C" const void *bfmeVftQueueProductionExitUpdateInterface[];
extern "C" const void *bfmeVftQueueProductionExitUpdateUpgradeMux[];
extern "C" const void *bfmeVftQueueProductionExitUpdateModuleInterface[];
extern "C" const void *bfmeVftQueueProductionExitUpdateBase4[];
extern "C" const void *bfmeVftQueueProductionExitUpdateBase5[];
#pragma comment(linker, "/alternatename:_bfmeVftBfmeBasePB0=??_7?$BfmeBasePB@$0A@@@6B@")
#pragma comment(linker, "/alternatename:_bfmeVftCreateModuleInterface=??_7CreateModuleInterface@@6B@")
#pragma comment(linker, "/alternatename:_bfmeVftQueueProductionExitUpdateObjectModule=??_7QueueProductionExitUpdate@@6BDynamicPortalObjectModule@@@")
#pragma comment(linker, "/alternatename:_bfmeVftQueueProductionExitUpdateInterface=??_7QueueProductionExitUpdate@@6BQueueProductionExitUpdateInterface@@@")
#pragma comment(linker, "/alternatename:_bfmeVftQueueProductionExitUpdateUpgradeMux=??_7QueueProductionExitUpdate@@6BDynamicPortalUpgradeMux@@@")
#pragma comment(linker, "/alternatename:_bfmeVftQueueProductionExitUpdateModuleInterface=??_7QueueProductionExitUpdate@@6BDynamicPortalModuleInterface@@@")
#pragma comment(linker, "/alternatename:_bfmeVftQueueProductionExitUpdateBase4=??_7QueueProductionExitUpdate@@6BDynamicPortalBase4@@@")
#pragma comment(linker, "/alternatename:_bfmeVftQueueProductionExitUpdateBase5=??_7QueueProductionExitUpdate@@6BDynamicPortalBase5@@@")

class QueueProductionExitUpdateBase
{
public:
    void construct(Thing *, const ModuleData *);
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/QueueProductionExitUpdate.h
class QueueProductionExitUpdate
{
public:
    QueueProductionExitUpdate(Thing *, const ModuleData *);

private:
    unsigned char m_tail[0x40];
};

// ??0QueueProductionExitUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
QueueProductionExitUpdate::QueueProductionExitUpdate(Thing *thing, const ModuleData *moduleData)
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
    words[0x00 / 4] = reinterpret_cast<unsigned int>(bfmeVftQueueProductionExitUpdateObjectModule);
    words[0x0c / 4] = reinterpret_cast<unsigned int>(bfmeVftQueueProductionExitUpdateInterface);
    words[0x10 / 4] = reinterpret_cast<unsigned int>(bfmeVftQueueProductionExitUpdateUpgradeMux);
    words[0x18 / 4] = reinterpret_cast<unsigned int>(bfmeVftQueueProductionExitUpdateModuleInterface);
    words[0x1c / 4] = reinterpret_cast<unsigned int>(bfmeVftQueueProductionExitUpdateBase4);
    words[0x20 / 4] = reinterpret_cast<unsigned int>(bfmeVftQueueProductionExitUpdateBase5);
    words[0x24 / 4] = zero;
    words[0x28 / 4] = zero;
    words[0x2c / 4] = zero;
    words[0x30 / 4] = zero;
    words[0x34 / 4] = zero;
    words[0x38 / 4] = zero;
}
