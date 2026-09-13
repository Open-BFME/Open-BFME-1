// cl: /DNDEBUG /MD /EHsc
// Open-BFME5: SiegeDeploySpecialPower dtor.

class Thing;
class ModuleData;
class Object;
class MemoryPool
{
public:
	~MemoryPool();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModule
{
public:
	virtual void behaviorModuleAnchor();
	virtual ~BehaviorModule();

	unsigned int m_04;
	Object *m_object;
};

class SiegeDeploySpecialPowerIface1 { public: virtual void slot(); };
class SiegeDeploySpecialPowerIface2
{
public:
	virtual void slot();
	unsigned int m_14;
	unsigned int m_18;
	unsigned int m_1c;
};
class SiegeDeploySpecialPowerIface3 { public: virtual void slot(); };
class SiegeDeploySpecialPowerIface4 { public: virtual void slot(); };

class SiegeDeploySpecialPower
	: public BehaviorModule,
	  public SiegeDeploySpecialPowerIface1,
	  public SiegeDeploySpecialPowerIface2,
	  public SiegeDeploySpecialPowerIface3,
	  public SiegeDeploySpecialPowerIface4
{
public:
	virtual ~SiegeDeploySpecialPower();
};

extern MemoryPool *SiegeDeploySpecialPower_getPool(Object *object);

// ??1SiegeDeploySpecialPower@@UAE@XZ
SiegeDeploySpecialPower::~SiegeDeploySpecialPower()
{
	MemoryPool *pool = SiegeDeploySpecialPower_getPool(m_object);
	if (pool)
		pool->~MemoryPool();
}
