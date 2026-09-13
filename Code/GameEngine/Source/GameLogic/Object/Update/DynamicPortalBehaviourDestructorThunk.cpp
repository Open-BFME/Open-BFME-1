// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: lift MASM dump to standalone C++ thunk.

class MemoryPool
{
public:
    ~MemoryPool();
};

class Gen_dtor_00113f20
{
public:
    virtual void anchor();
    virtual ~Gen_dtor_00113f20();
    const void *m_moduleData;
};

class DynamicPortalObjectModule : public Gen_dtor_00113f20
{
public:
    void *m_object;
};

class DynamicPortalBehaviourInterface
{
public:
    virtual void anchor();
};

class DynamicPortalUpgradeMux
{
public:
    virtual void anchor();
    bool m_upgradeExecuted;
};

class DynamicPortalModuleInterface
{
public:
    virtual void anchor();
};

class DynamicPortalBehaviourModule
    : public DynamicPortalObjectModule,
      public DynamicPortalBehaviourInterface
{
public:
    virtual ~DynamicPortalBehaviourModule() {}
};

class DynamicPortalUpgradeModule
    : public DynamicPortalBehaviourModule,
      public DynamicPortalUpgradeMux,
      public DynamicPortalModuleInterface
{
public:
    virtual ~DynamicPortalUpgradeModule() {}
};

class DynamicPortalBase4
{
public:
    virtual void anchor();
};

class DynamicPortalBase5
{
public:
    virtual void anchor();
};

class DynamicPortalBehaviour
    : public DynamicPortalUpgradeModule,
      public DynamicPortalBase4,
      public DynamicPortalBase5
{
public:
    virtual ~DynamicPortalBehaviour();
};

// ??1DynamicPortalBehaviour@@UAE@XZ
DynamicPortalBehaviour::~DynamicPortalBehaviour()
{
    reinterpret_cast<MemoryPool *>(this)->~MemoryPool();
}
