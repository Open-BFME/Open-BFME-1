// cl: /DNDEBUG /MD /EHsc

extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)

class Thing;
class ModuleData;

class DeflectSpecialPowerBaseShim
{
public:
    void construct(Thing *, const ModuleData *);
};

class DeflectSpecialPower
{
    volatile unsigned int primaryVtable;
    unsigned char padding0[8];
    volatile unsigned int interfaceVtable0;
    volatile unsigned int interfaceVtable1;
    unsigned char padding1[12];
    volatile unsigned int interfaceVtable2;
    volatile unsigned int interfaceVtable3;
    unsigned char padding2[16];
    volatile unsigned int interfaceVtable4;
    volatile bool active;
    volatile bool ready;

public:
    DeflectSpecialPower(Thing *, const ModuleData *);
};

// ??0DeflectSpecialPower@@QAE@PAVThing@@PBVModuleData@@@Z
DeflectSpecialPower::DeflectSpecialPower(Thing *thing, const ModuleData *moduleData)
{
    reinterpret_cast<DeflectSpecialPowerBaseShim *>(this)->construct(thing, moduleData);
    interfaceVtable4 = 0x010a1de4;
    _ReadWriteBarrier();
    active = false;
    ready = false;
    primaryVtable = 0x010b44ec;
    interfaceVtable0 = 0x010b4428;
    interfaceVtable1 = 0x010b441c;
    interfaceVtable2 = 0x010b43f0;
    interfaceVtable3 = 0x010b4378;
    interfaceVtable4 = 0x010b4358;
}
