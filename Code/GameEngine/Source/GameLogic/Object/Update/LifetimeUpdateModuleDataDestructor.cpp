// cl: /O2 /Ob0

class ModuleData
{
public:
	virtual void moduleDataAnchor();

private:
	unsigned char m_storage[0x0C];
};

class LifetimeUpdateModuleData : public ModuleData
{
public:
	virtual ~LifetimeUpdateModuleData();

private:
	unsigned int m_minLifetime;
	unsigned int m_maxLifetime;
	bool m_waitForWakeup;
	bool m_scoreKill;
	unsigned int m_deadLifetime;
};

LifetimeUpdateModuleData::~LifetimeUpdateModuleData()
{
}
