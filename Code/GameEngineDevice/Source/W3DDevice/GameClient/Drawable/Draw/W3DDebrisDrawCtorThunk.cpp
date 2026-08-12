// cl: /DNDEBUG /MD /EHsc

extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)

class Thing;
class ModuleData;

class W3DDebrisDrawBaseShim
{
public:
    void construct(Thing *, const ModuleData *);
};

class W3DDebrisDraw
{
    volatile unsigned int primaryVtable;
    unsigned int baseData0;
    unsigned int baseData1;
    volatile unsigned int secondaryVtable;
    void * volatile renderObject;
    volatile int state;
    void * volatile animations[4];
    void * volatile tailObjects[3];
    volatile unsigned int frames;
    void * volatile shadow;
    void * volatile finalEffect;
    volatile bool finalStop;
    unsigned char padding[3];
    volatile unsigned int trailingState;

public:
    W3DDebrisDraw(Thing *, const ModuleData *);
};

// ??0W3DDebrisDraw@@QAE@PAVThing@@PBVModuleData@@@Z
W3DDebrisDraw::W3DDebrisDraw(Thing *thing, const ModuleData *moduleData)
{
    reinterpret_cast<W3DDebrisDrawBaseShim *>(this)->construct(thing, moduleData);
    secondaryVtable = 0x01121ea4;
    _ReadWriteBarrier();
    primaryVtable = 0x01121ec0;
    secondaryVtable = 0x01121eb0;
    renderObject = 0;
    state = -1;
    animations[0] = 0;
    animations[1] = 0;
    animations[2] = 0;
    animations[3] = 0;
    frames = 0;
    shadow = 0;
    finalEffect = 0;
    finalStop = false;
    trailingState = 0;
    tailObjects[0] = 0;
    tailObjects[1] = 0;
    tailObjects[2] = 0;
}
