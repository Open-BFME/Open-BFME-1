// cl: /DNDEBUG /MD /EHsc

class Thing;
class ModuleData;
class Object;
struct LargeGroupBonusModuleData
{
    unsigned char m_pad08[8];
    int m_maximumDelay;
};

enum UpdateSleepTime
{
    UPDATE_SLEEP_DUMMY
};

class LargeGroupBonusDeepBase
{
public:
    LargeGroupBonusDeepBase(Thing *, const ModuleData *);
    virtual ~LargeGroupBonusDeepBase();

protected:
    const LargeGroupBonusModuleData *m_moduleData;
    Object *m_object;
};

class LargeGroupBonusIface1 { public: virtual void slot(); };
class LargeGroupBonusIface2 { public: virtual void slot(); };

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/UpdateModule.h
class UpdateModule : public LargeGroupBonusDeepBase,
                     public LargeGroupBonusIface1,
                     public LargeGroupBonusIface2
{
public:
    UpdateModule(Thing *thing, const ModuleData *moduleData)
        : LargeGroupBonusDeepBase(thing, moduleData),
          m_nextCallFrameAndPhase(0), m_indexInLogic(-1), m_updateState(-1)
    {
    }

protected:
    void setWakeFrameViaThunk(Object *, UpdateSleepTime);
    Object *getObject() const { return m_object; }

private:
    unsigned int m_nextCallFrameAndPhase;
    int m_indexInLogic;
    int m_updateState;
};

class LargeGroupBonusInterface { public: virtual void slot(); };

struct GameLogicState
{
    unsigned char m_pad3c[0x3c];
    unsigned int m_frame;
};

extern GameLogicState *g_theGameLogic;
extern int __cdecl largeGroupRandom(int minimum, int maximum,
                                    const char *file, int line);
extern const char g_largeGroupSourceFile;

class LargeGroupBonusUpdate : public UpdateModule,
                              public LargeGroupBonusInterface
{
public:
    LargeGroupBonusUpdate(Thing *, const ModuleData *);

private:
    unsigned int m_frame;
    bool m_f28;
    bool m_f29;
    bool m_f2a;
};

// ??0LargeGroupBonusUpdate@@QAE@PAVThing@@PBVModuleData@@@Z
LargeGroupBonusUpdate::LargeGroupBonusUpdate(Thing *thing, const ModuleData *moduleData)
    : UpdateModule(thing, moduleData)
{
    Object *owner = getObject();
    m_f28 = false;
    m_f2a = false;
    m_frame = g_theGameLogic->m_frame;
    m_f29 = false;
    int delay = largeGroupRandom(1, m_moduleData->m_maximumDelay,
                                 &g_largeGroupSourceFile, 107);
    setWakeFrameViaThunk(owner, (UpdateSleepTime)delay);
}
