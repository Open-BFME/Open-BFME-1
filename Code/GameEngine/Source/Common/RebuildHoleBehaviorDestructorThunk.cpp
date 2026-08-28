// cl: /DNDEBUG /MD /EHsc
// Cloned from the DynamicPortalBehaviour model: identical body once relocation
// immediates are masked so the same class shape reproduces it.
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

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/RebuildHoleBehavior.h
class RebuildHoleBehaviorInterface
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

class RebuildHoleBehaviorModule
    : public DynamicPortalObjectModule,
      public RebuildHoleBehaviorInterface
{
public:
    virtual ~RebuildHoleBehaviorModule() {}
};

class DynamicPortalUpgradeModule
    : public RebuildHoleBehaviorModule,
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

class RebuildHoleBehavior
    : public DynamicPortalUpgradeModule,
      public DynamicPortalBase4,
      public DynamicPortalBase5
{
public:
    virtual ~RebuildHoleBehavior();
};

// ??1RebuildHoleBehavior@@UAE@XZ
RebuildHoleBehavior::~RebuildHoleBehavior()
{
    reinterpret_cast<MemoryPool *>(this)->~MemoryPool();
}
