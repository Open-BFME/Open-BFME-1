// cl: /DNDEBUG /MD /EHsc

class Thing;
class ModuleData;
class Object;

enum UpdateSleepTime
{
    UPDATE_SLEEP_DUMMY
};

struct SpyVisionModuleData
{
    unsigned char m_pad00[0x70];
    bool m_startUpgraded;
    bool m_active;
    unsigned char m_pad72[6];
    int m_maximumDelay;
};

class PB_DeepBase
{
public:
    PB_DeepBase(Thing *, const ModuleData *);
    virtual ~PB_DeepBase();

protected:
    const SpyVisionModuleData *m_moduleData;
    Object *m_object;
};

class PB_Iface1
{
public:
    virtual void slot();
};

class PB_Iface2
{
public:
    virtual void slot();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule : public PB_DeepBase, public PB_Iface1, public PB_Iface2
{
public:
    UpdateModule(Thing *thing, const ModuleData *moduleData)
        : PB_DeepBase(thing, moduleData),
          m_nextCallFrameAndPhase(0), m_indexInLogic(-1), m_updateState(-1)
    {
    }

protected:
    void setWakeFrame(Object *, UpdateSleepTime);
    Object *getObject() const { return m_object; }

private:
    unsigned int m_nextCallFrameAndPhase;
    int m_indexInLogic;
    int m_updateState;
};

class SpyVisionUpgradeMux
{
public:
    SpyVisionUpgradeMux();
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

class SpyVisionUpdateInterface
{
public:
    virtual void slot();
};

extern int __cdecl spyVisionRandom(int minimum, int maximum,
                                   const char *file, int line);
extern const char g_spyVisionSourceFile;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpyVisionUpdate.h
class SpyVisionUpdate : public UpdateModule,
                        public SpyVisionUpgradeMux,
                        public SpyVisionUpdateInterface
{
public:
    SpyVisionUpdate(Thing *, const ModuleData *);

private:
    int getMaximumDelay() const { return m_moduleData->m_maximumDelay; }
    unsigned int m_deactivateFrame;
    bool m_active;
};

// ??0SpyVisionUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
SpyVisionUpdate::SpyVisionUpdate(Thing *thing, const ModuleData *moduleData)
    : UpdateModule(thing, moduleData),
      SpyVisionUpgradeMux(),
      m_deactivateFrame(0)
{
    m_active = m_moduleData->m_active;
    if (m_moduleData->m_startUpgraded)
    {
        giveSelfUpgrade();
        setWakeFrame(getObject(),
                     (UpdateSleepTime)spyVisionRandom(
                         1, getMaximumDelay(),
                         &g_spyVisionSourceFile, 121));
    }
    else
    {
        setWakeFrame(getObject(), (UpdateSleepTime)0x3fffffff);
    }
}
