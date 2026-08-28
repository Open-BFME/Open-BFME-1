// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift TemporarilyDefectUpdate ctor __emit thunk to clean C++.
// ICF-identical to the PoisonedBehavior ctor: deep base ctor (out-of-line),
// UpdateModule's inline ctor stores the two interface subobjects' vtables at
// +0x0C/+0x10 and inits its three scalars; the most-derived vtable batch, four
// member zeroings, then setWakeFrame(getObject(), 0x3fffffff).

class Thing;
class ModuleData;
class Object;
enum UpdateSleepTime { UPDATE_SLEEP_DUMMY };

class PB_DeepBase
{
public:
    PB_DeepBase(Thing *, const ModuleData *);
    virtual ~PB_DeepBase();

protected:
    void *m_p4;
    Object *m_object;
};

class PB_Iface1 { public: virtual void slot(); };
class PB_Iface2 { public: virtual void slot(); };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule : public PB_DeepBase, public PB_Iface1, public PB_Iface2
{
public:
    UpdateModule(Thing *thing, const ModuleData *moduleData)
        : PB_DeepBase(thing, moduleData), m_f14(0), m_f18(-1), m_f1C(-1) {}

protected:
    void setWakeFrame(Object *, UpdateSleepTime);
    Object *getObject() const { return m_object; }

private:
    unsigned int m_f14;
    int m_f18;
    int m_f1C;
};

class TemporarilyDefectUpdate : public UpdateModule
{
public:
    TemporarilyDefectUpdate(Thing *, const ModuleData *);

private:
    unsigned int m_f20;
    unsigned int m_f24;
    unsigned int m_f28;
    unsigned char m_f2C;
};

// ??0TemporarilyDefectUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
TemporarilyDefectUpdate::TemporarilyDefectUpdate(Thing *thing, const ModuleData *moduleData)
    : UpdateModule(thing, moduleData), m_f20(0), m_f24(0), m_f28(0), m_f2C(0)
{
    setWakeFrame(getObject(), (UpdateSleepTime)0x3fffffff);
}
