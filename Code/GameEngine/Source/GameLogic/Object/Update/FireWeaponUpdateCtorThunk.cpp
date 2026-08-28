// cl: /DNDEBUG /MD /EHsc
// ModuleFactory's 0x24-byte allocation proves that BFME omits Zero Hour's
// initial-delay field while retaining the weapon setup in its constructor.

class Thing;
class ModuleData;
class WeaponTemplate;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Object.h
class Object
{
public:
    unsigned int getID() const { return m_id; }

private:
    unsigned char m_pad00[0x74];
    unsigned int m_id;
};

class FWU_ModuleData
{
private:
    unsigned char m_pad00[8];

public:
    const WeaponTemplate *m_weaponTemplate;
};

class FWU_DeepBase
{
public:
    FWU_DeepBase(Thing *, const ModuleData *);
    virtual ~FWU_DeepBase();

protected:
    const FWU_ModuleData *m_moduleData;
    Object *m_object;
};

class FWU_Iface1 { public: virtual void slot(); };
class FWU_Iface2 { public: virtual void slot(); };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule : public FWU_DeepBase, public FWU_Iface1, public FWU_Iface2
{
public:
    UpdateModule(Thing *thing, const ModuleData *moduleData)
        : FWU_DeepBase(thing, moduleData),
          m_indexInLogic(-1), m_updateState(-1),
          m_nextCallFrameAndPhase(0)
    {
    }

protected:
    const FWU_ModuleData *getModuleData() const { return m_moduleData; }
    Object *getObject() const { return m_object; }

private:
    unsigned int m_nextCallFrameAndPhase;
    int m_indexInLogic;
    int m_updateState;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Weapon.h
class Weapon
{
public:
    virtual ~Weapon();
    void setSourceID(unsigned int sourceID) { m_sourceID = sourceID; }
    void loadAmmoNow(const Object *);

private:
    void *m_template;
    unsigned int m_sourceID;
};

enum WeaponSlotType
{
    PRIMARY_WEAPON
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Weapon.h
class WeaponStore
{
public:
    Weapon *allocateNewWeapon(
        const WeaponTemplate *, WeaponSlotType) const;
};

extern WeaponStore *TheWeaponStore;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/FireWeaponUpdate.h
class FireWeaponUpdate : public UpdateModule
{
public:
    FireWeaponUpdate(Thing *, const ModuleData *);

private:
    Weapon *m_weapon;
};

// ??0FireWeaponUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
FireWeaponUpdate::FireWeaponUpdate(
    Thing *thing, const ModuleData *moduleData)
    : UpdateModule(thing, moduleData), m_weapon(0)
{
    const WeaponTemplate *weaponTemplate = getModuleData()->m_weaponTemplate;
    if (weaponTemplate != 0)
    {
        m_weapon = TheWeaponStore->allocateNewWeapon(
            weaponTemplate, PRIMARY_WEAPON);
        m_weapon->setSourceID(getObject()->getID());
        m_weapon->loadAmmoNow(getObject());
    }
}
