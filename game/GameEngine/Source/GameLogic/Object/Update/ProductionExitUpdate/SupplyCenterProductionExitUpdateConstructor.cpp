// cl: /DNDEBUG /MD /EHsc
// readable body of ??0SupplyCenterProductionExitUpdate@@: game/GameEngine/Source/GameLogic/Object/Update/ProductionExitUpdate/SupplyCenterProductionExitUpdate.cpp

// The BFME UpdateModule/ExitInterface prefix and the zeroed rally point are
// retained locally because the shared ZH declaration has a different prefix.
class Thing;
class ModuleData;
class Object;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include/Lib/BaseType.h
#include "../../../../../../Libraries/Include/Lib/Coord3D.h"

#include "../../../../../Include/GameLogic/Module/UpdateSleepTime.h"




class PB_DeepBase
{
public:
    PB_DeepBase(Thing *, const ModuleData *);
    virtual ~PB_DeepBase();

protected:
    void *m_f04;
    Object *m_object;
};

class PB_Iface1 { public: virtual void slot(); };
class PB_Iface2 { public: virtual void slot(); };

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule : public PB_DeepBase, public PB_Iface1, public PB_Iface2
{
public:
    UpdateModule(Thing *thing, const ModuleData *moduleData)
        : PB_DeepBase(thing, moduleData), m_f14(0), m_f18(-1), m_f1c(-1) {}

protected:
    void setWakeFrame(Object *, UpdateSleepTime);
    Object *getObject() const { return m_object; }

private:
    unsigned int m_f14;
    int m_f18;
    int m_f1c;
};

class SupplyCenterProductionExitUpdateIface
{
public:
    virtual void slot();
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SupplyCenterProductionExitUpdate.h
class SupplyCenterProductionExitUpdate : public UpdateModule,
    public SupplyCenterProductionExitUpdateIface
{
public:
    SupplyCenterProductionExitUpdate(Thing *, const ModuleData *);

private:
    Coord3D m_rallyPoint;
    volatile unsigned char m_rallyPointExists;
};

// ??0SupplyCenterProductionExitUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
SupplyCenterProductionExitUpdate::SupplyCenterProductionExitUpdate(
    Thing *thing, const ModuleData *moduleData)
    : UpdateModule(thing, moduleData)
{
    m_rallyPointExists = false;
    { Coord3D *const position = &m_rallyPoint; position->x = 0.0f; position->y = 0.0f; position->z = 0.0f; }
    setWakeFrame(getObject(), UPDATE_SLEEP_FOREVER);
}
