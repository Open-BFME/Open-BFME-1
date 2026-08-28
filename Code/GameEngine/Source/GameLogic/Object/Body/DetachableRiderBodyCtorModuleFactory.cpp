// cl: /DNDEBUG /MD /EHsc
// ModuleFactory reaches this constructor through ILT 0x0002F3AB. The
// registration string and 0xE8-byte allocation identify the retail-only
// DetachableRiderBody class.

class Thing;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/Module.h
class ModuleData
{
public:
    unsigned char m_pad[0xc8];
    bool m_startUpgraded;
};

class DRB_Primary
{
public:
    virtual ~DRB_Primary();

protected:
    const ModuleData *m_moduleData;
    void *m_object;
};

class DRB_Iface1 { public: virtual void slot(); };
class DRB_Iface2 { public: virtual void slot(); };

class DRB_BodyModule : public DRB_Primary, public DRB_Iface1, public DRB_Iface2
{
public:
    DRB_BodyModule(Thing *, const ModuleData *);

private:
    unsigned char m_pad[0xcc];
};

class DRB_UpgradeMux
{
public:
    DRB_UpgradeMux();
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0c();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1c();
    virtual void setUpgradeExecuted(bool);
    virtual void upgradeImplementation();
    virtual void slot28();
    virtual void performUpgradeFX();
    virtual void slot30();
    virtual void processUpgradeRemoval();

protected:
    void giveSelfUpgrade()
    {
        performUpgradeFX();
        processUpgradeRemoval();
        upgradeImplementation();
        setUpgradeExecuted(true);
    }

private:
    bool m_upgradeExecuted;
};

class DetachableRiderBody : public DRB_BodyModule, public DRB_UpgradeMux
{
public:
    DetachableRiderBody(Thing *, const ModuleData *);
};

// ??0DetachableRiderBody@@QAE@PAVThing@@PBVModuleData@@@Z
DetachableRiderBody::DetachableRiderBody(
    Thing *thing, const ModuleData *moduleData)
    : DRB_BodyModule(thing, moduleData), DRB_UpgradeMux()
{
    if (m_moduleData->m_startUpgraded)
        giveSelfUpgrade();
}
